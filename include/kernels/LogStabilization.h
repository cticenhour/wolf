#ifndef LOGSTABILIZATION_H
#define LOGSTABILIZATION_H

#include "Kernel.h"

class LogStabilization;

template <>
InputParameters validParams<LogStabilization>();

/**
 *
 */
class LogStabilization : public Kernel
{
public:
  LogStabilization(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real _offset;
};

#endif // LOGSTABILIZATION_H
