#include "CoupledCoeffDiffusion.h"

registerMooseObject("WolfApp", CoupledCoeffDiffusion);

template <>
InputParameters
validParams<CoupledCoeffDiffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("coupled_var", "Coupled species density.");
  params.addRequiredParam<Real>("diffusivity", "Coupled species diffusivity.");
  return params;
}

CoupledCoeffDiffusion::CoupledCoeffDiffusion(const InputParameters & parameters)
  : Kernel(parameters),

    _coupled_grad(coupledGradient("coupled_var")),
    _diffusivity(getParam<Real>("diffusivity"))
{
}

Real
CoupledCoeffDiffusion::computeQpResidual()
{
  return _diffusivity * _grad_test[_i][_qp] * _coupled_grad[_qp];
}

Real
CoupledCoeffDiffusion::computeQpJacobian()
{
  return 0;
}
