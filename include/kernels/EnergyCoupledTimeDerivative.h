#ifndef ENERGYCOUPLEDTIMEDERIVATIVE_H
#define ENERGYCOUPLEDTIMEDERIVATIVE_H

#include "Kernel.h"

class EnergyCoupledTimeDerivative;

template <>
InputParameters validParams<EnergyCoupledTimeDerivative>();

/**
 *
 */
class EnergyCoupledTimeDerivative : public Kernel
{
public:
  EnergyCoupledTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const VariableValue & _electrons_dot;
};

#endif // ENERGYCOUPLEDTIMEDERIVATIVE_H
