#ifndef COUPLEDENERGYDIFFUSION_H
#define COUPLEDENERGYDIFFUSION_H

#include "Kernel.h"

class CoupledEnergyDiffusion;

template <>
InputParameters validParams<CoupledEnergyDiffusion>();

/**
 *
 */
class CoupledEnergyDiffusion : public Kernel
{
public:
  CoupledEnergyDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _diffusivity;

  const VariableValue & _electron_density;
};

#endif // COUPLEDENERGYDIFFUSION_H
