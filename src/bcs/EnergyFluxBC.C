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
  params.addRequiredParam<Real>("sec_elec_emission", "Secondary electron emission coefficient.");
  // params.addRequiredParam<Real>("electron_temp_at_wall",
  //                              "Specified electron temperature at the wall in volts.");
  return params;
}

EnergyFluxBC::EnergyFluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _ion_mobility(getParam<Real>("ion_mobility")),
    _grad_electron_density(coupledGradient("electrons")),
    _electron_density(coupledValue("electrons")),
    _ion_density(coupledValue("ions")),
    _grad_potential(coupledGradient("potential")),
    //_T_e_wall(getParam<Real>("electron_temp_at_wall")),
    _electron_mass(9.109384e-31),
    _secondary_electron_coefficient(getParam<Real>("sec_elec_emission")),
    _T_secondary_electron(0.5),
    _electron_id(coupled("electrons")),
    _ion_id(coupled("ions")),
    _potential_id(coupled("potential"))
{
}

Real
EnergyFluxBC::computeQpResidual()
{
  return _test[_i][_qp] * _normals[_qp] *
         ((5 / 2) * (2 / 3) * std::exp(_u[_qp]) * 0.25 *
              std::pow((8 * (2 / 3) * std::exp(_u[_qp])) / (libMesh::pi * _electron_mass), 0.5) *
              std::exp(_electron_density[_qp]) * _normals[_qp] -
          _secondary_electron_coefficient * (5 / 2) * _T_secondary_electron *
              (-_ion_mobility * std::exp(_ion_density[_qp]) * _grad_potential[_qp]));
}

Real
EnergyFluxBC::computeQpJacobian()
{
  return _test[_i][_qp] * _normals[_qp] * (5 / 2) * (2 / 3) * std::exp(_u[_qp]) * 0.25 *
         std::pow((8 * (2 / 3) * std::exp(_u[_qp])) / (libMesh::pi * _electron_mass), 0.5) *
         std::exp(_electron_density[_qp]) * _normals[_qp] * 1.5 * _phi[_j][_qp];
}

Real
EnergyFluxBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _electron_id)
    return _test[_i][_qp] * _normals[_qp] *
           ((5 / 2) * (2 / 3) * std::exp(_u[_qp]) * 0.25 *
            std::pow((8 * (2 / 3) * std::exp(_u[_qp])) / (libMesh::pi * _electron_mass), 0.5) *
            std::exp(_electron_density[_qp]) * _phi[_j][_qp] * _normals[_qp]);

  else if (jvar == _ion_id)
    return _test[_i][_qp] * _normals[_qp] *
           (-_secondary_electron_coefficient * (5 / 2) * _T_secondary_electron *
            (-_ion_mobility * std::exp(_ion_density[_qp]) * _phi[_j][_qp] * _grad_potential[_qp]));

  else if (jvar == _potential_id)
    return _test[_i][_qp] * _normals[_qp] *
           (-_secondary_electron_coefficient * (5 / 2) * _T_secondary_electron *
            (-_ion_mobility * std::exp(_ion_density[_qp]) * _grad_phi[_j][_qp]));

  else
    return 0;
}
