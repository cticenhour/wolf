#ifndef IONFLUXBC_H
#define IONFLUXBC_H

#include "IntegratedBC.h"

class IonFluxBC;

template <>
InputParameters validParams<IonFluxBC>();

/**
 *
 */
class IonFluxBC : public IntegratedBC
{
public:
  IonFluxBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const VariableGradient & _grad_potential;

  Real _mobility;
};

#endif // IONFLUXBC_H
