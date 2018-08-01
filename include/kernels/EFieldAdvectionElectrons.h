#ifndef EFIELDADVECTIONELECTRONS_H
#define EFIELDADVECTIONELECTRONS_H

#include "Kernel.h"

class EFieldAdvectionElectrons;

template <>
InputParameters validParams<EFieldAdvectionElectrons>();

/**
 *
 */
class EFieldAdvectionElectrons : public Kernel
{
public:
  EFieldAdvectionElectrons(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableGradient & _grad_potential;

  Real _mobility;
};

#endif // EFIELDADVECTIONELECTRONS_H
