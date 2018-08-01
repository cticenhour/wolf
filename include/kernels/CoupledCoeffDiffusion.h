#ifndef COUPLEDCOEFFDIFFUSION_H
#define COUPLEDCOEFFDIFFUSION_H

#include "Kernel.h"

class CoupledCoeffDiffusion;

template <>
InputParameters validParams<CoupledCoeffDiffusion>();

/**
 *
 */
class CoupledCoeffDiffusion : public Kernel
{
public:
  CoupledCoeffDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableGradient & _coupled_grad;

  Real _diffusivity;
};

#endif // COUPLEDCOEFFDIFFUSION_H
