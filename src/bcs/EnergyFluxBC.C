#include "EnergyFluxBC.h"

registerMooseObject("WolfApp", EnergyFluxBC);

template <>
InputParameters
validParams<EnergyFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("ion_mobility", "The ion mobility");
  params.addRequiredCoupledVar("electrons", "The electron density coupled variable.");
  params.addRequiredCoupledVar("ions", "The ion density coupled variable.");
  params.addRequiredCoupledVar("potential", "The electric potential.");
  params.addRequiredParam<Real>("electron_temp_at_wall",
                                "Specified electron temperature at the wall in volts.");
  return params;
}

EnergyFluxBC::EnergyFluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _ion_mobility(getParam<Real>("ion_mobility")),
    _grad_electron_density(coupledGradient("electrons")),
    _electron_density(coupledValue("electrons")),
    _ion_density(coupledValue("ions")),
    _grad_potential(coupledGradient("potential")),
    _T_e_wall(getParam<Real>("electron_temp_at_wall")),
    _electron_mass(9.109384e-31),
    _secondary_electron_coefficient(0.01),
    _T_secondary_electron(0.5)
{
}

Real
EnergyFluxBC::computeQpResidual()
{
  return _test[_i][_qp] * _normals[_qp] *
         ((5 / 2) * _T_e_wall * 0.25 *
              std::pow((8 * _T_e_wall / (libMesh::pi * _electron_mass)), 0.25) *
              _electron_density[_qp] * _normals[_qp] -
          _secondary_electron_coefficient * (5 / 2) * _T_secondary_electron *
              (-_ion_mobility * _ion_density[_qp] * _grad_potential[_qp]));
}

Real
EnergyFluxBC::computeQpJacobian()
{
  return 0;
}
