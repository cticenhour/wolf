#ifndef COEFFDIFFUSION_H
#define COEFFDIFFUSION_H

#include "Kernel.h"

class CoeffDiffusion;

template <>
InputParameters validParams<CoeffDiffusion>();

/**
 *
 */
class CoeffDiffusion : public Kernel
{
public:
  CoeffDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _diffusivity;
};

#endif // COEFFDIFFUSION_H
