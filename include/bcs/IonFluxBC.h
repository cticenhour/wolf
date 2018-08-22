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
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  const VariableGradient & _grad_potential;

  Real _mobility;

  unsigned int _potential_id;
};

#endif // IONFLUXBC_H
