#include "ElectronDiffusionEnergy.h"

registerMooseObject("WolfApp", ElectronDiffusionEnergy);

template <>
InputParameters
validParams<ElectronDiffusionEnergy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("diffusivity", "Diffusivity of the species.");
  params.addRequiredCoupledVar("electrons", "Electron species density coupled variable.");
  return params;
}

ElectronDiffusionEnergy::ElectronDiffusionEnergy(const InputParameters & parameters)
  : Kernel(parameters),

    _diffusivity(getParam<Real>("diffusivity")),
    _electron_density(coupledValue("electrons")),
    _grad_electron_density(coupledGradient("electrons"))
{
}

Real
ElectronDiffusionEnergy::computeQpResidual()
{
  return _grad_test[_i][_qp] * (2 / 3) * (_u[_qp] / _electron_density[_qp]) * _diffusivity *
         _grad_electron_density[_qp];
}

Real
ElectronDiffusionEnergy::computeQpJacobian()
{
  return _grad_test[_i][_qp] * (2 / 3) * (_phi[_j][_qp] / _electron_density[_qp]) * _diffusivity *
         _grad_electron_density[_qp];
}
