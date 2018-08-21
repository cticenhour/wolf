#ifndef ENERGYTIMEDERIVATIVE_H
#define ENERGYTIMEDERIVATIVE_H

#include "TimeDerivative.h"

class EnergyTimeDerivative;

template <>
InputParameters validParams<EnergyTimeDerivative>();

/**
 *
 */
class EnergyTimeDerivative : public TimeDerivative
{
public:
  EnergyTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  const VariableValue & _electron_density;

  unsigned int _electron_id;
};

#endif // ENERGYTIMEDERIVATIVE_H
