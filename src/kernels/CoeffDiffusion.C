#include "CoeffDiffusion.h"

registerMooseObject("WolfApp", CoeffDiffusion);

template <>
InputParameters
validParams<CoeffDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredParam<Real>("diffusivity", "Diffusivity of the species.");
  return params;
}

CoeffDiffusion::CoeffDiffusion(const InputParameters & parameters)
  : Diffusion(parameters),

    _diffusivity(getParam<Real>("diffusivity"))
{
}

Real
CoeffDiffusion::computeQpResidual()
{
  return _diffusivity * Diffusion::computeQpResidual();
}

Real
CoeffDiffusion::computeQpJacobian()
{
  return _diffusivity * Diffusion::computeQpJacobian();
}
