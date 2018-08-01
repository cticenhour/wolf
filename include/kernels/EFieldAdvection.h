#ifndef EFIELDADVECTION_H
#define EFIELDADVECTION_H

#include "Kernel.h"

class EFieldAdvection;

template <>
InputParameters validParams<EFieldAdvection>();

/**
 *
 */
class EFieldAdvection : public Kernel
{
public:
  EFieldAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableGradient & _grad_potential;

  Real _mobility;

  Real _sign;
};

#endif // EFIELDADVECTION_H
