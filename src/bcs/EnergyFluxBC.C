#include "EnergyFluxBC.h"

registerMooseObject("WolfApp", EnergyFluxBC);

template <>
InputParameters
validParams<EnergyFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("diffusivity", "The electron diffusivity.");
  params.addRequiredParam<Real>("mobility", "The electron mobility");
  params.addRequiredCoupledVar("electrons", "The electron density coupled variable.");
  params.addRequiredCoupledVar("potential", "The electric potential.");
  params.addRequiredParam<Real>("electron_temp_at_wall",
                                "Specified electron temperature at the wall in volts.");
  return params;
}

EnergyFluxBC::EnergyFluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _diffusivity(getParam<Real>("diffusivity")),
    _mobility(getParam<Real>("mobility")),
    _grad_electron_density(coupledGradient("electrons")),
    _electron_density(coupledValue("electrons")),
    _grad_potential(coupledGradient("potential")),
    _T_e_wall(getParam<Real>("electron_temp_at_wall"))
{
}

Real
EnergyFluxBC::computeQpResidual()
{
  return _test[_i][_qp] * _normals[_qp] *
         (_diffusivity * _grad_u[_qp] + _T_e_wall * _diffusivity * _grad_electron_density[_qp] -
          (5 / 2) * _mobility * _electron_density[_qp] * _T_e_wall * _grad_potential[_qp]);
}

Real
EnergyFluxBC::computeQpJacobian()
{
  return _test[_i][_qp] * _normals[_qp] * _diffusivity * _grad_phi[_j][_qp];
}
