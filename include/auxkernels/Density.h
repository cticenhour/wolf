#ifndef DENSITY_H
#define DENSITY_H

#include "AuxKernel.h"

class Density;

template <>
InputParameters validParams<Density>();

/**
 *
 */
class Density : public AuxKernel
{
public:
  Density(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

private:
  const VariableValue & _density_log;
};

#endif // DENSITY_H
