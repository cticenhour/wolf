#ifndef JOULEHEATING_H
#define JOULEHEATING_H

#include "Kernel.h"

class JouleHeating;

template <>
InputParameters validParams<JouleHeating>();

/**
 *
 */
class JouleHeating : public Kernel
{
public:
  JouleHeating(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableValue & _electron_density;

  const VariableGradient & _grad_electron_density;

  Real _diffusivity;

  Real _mobility;

  const VariableGradient & _grad_potential;

  Real _e;
};

#endif // JOULEHEATING_H
