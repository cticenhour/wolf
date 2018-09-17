#include "CoeffDiffusion.h"

registerMooseObject("WolfApp", CoeffDiffusion);

template <>
InputParameters
validParams<CoeffDiffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("diffusivity", "Diffusivity of the species.");
  return params;
}

CoeffDiffusion::CoeffDiffusion(const InputParameters & parameters)
  : Kernel(parameters),

    _diffusivity(getParam<Real>("diffusivity"))
{
}

Real
CoeffDiffusion::computeQpResidual()
{
  return -_grad_test[_i][_qp] * -_diffusivity * std::exp(_u[_qp]) * _grad_u[_qp];
}

Real
CoeffDiffusion::computeQpJacobian()
{
  return -_grad_test[_i][_qp] * -_diffusivity *
         (std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] +
          std::exp(_u[_qp]) * _grad_phi[_j][_qp]);
}
