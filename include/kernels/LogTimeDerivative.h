#ifndef LOGTIMEDERIVATIVE_H
#define LOGTIMEDERIVATIVE_H

#include "TimeKernel.h"

class LogTimeDerivative;

template <>
InputParameters validParams<LogTimeDerivative>();

/**
 *
 */
class LogTimeDerivative : public TimeKernel
{
public:
  LogTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
};

#endif // LOGTIMEDERIVATIVE_H
