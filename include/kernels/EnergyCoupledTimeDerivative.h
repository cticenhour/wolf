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
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  const VariableValue & _electrons_dot;

  const VariableValue & _delectrons_dot;

  unsigned int _electron_id;
};

#endif // ENERGYCOUPLEDTIMEDERIVATIVE_H
