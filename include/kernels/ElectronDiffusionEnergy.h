#ifndef ELECTRONDIFFUSIONENERGY_H
#define ELECTRONDIFFUSIONENERGY_H

#include "Kernel.h"

class ElectronDiffusionEnergy;

template <>
InputParameters validParams<ElectronDiffusionEnergy>();

/**
 *
 */
class ElectronDiffusionEnergy : public Kernel
{
public:
  ElectronDiffusionEnergy(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _diffusivity;

  const VariableValue & _electron_density;

  const VariableGradient & _grad_electron_density;
};

#endif // ELECTRONDIFFUSIONENERGY_H
