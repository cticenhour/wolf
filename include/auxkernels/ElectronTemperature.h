#ifndef ELECTRONTEMPERATURE_H
#define ELECTRONTEMPERATURE_H

#include "AuxKernel.h"

class ElectronTemperature;

template <>
InputParameters validParams<ElectronTemperature>();

/**
 *
 */
class ElectronTemperature : public AuxKernel
{
public:
  ElectronTemperature(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _energy;
};

#endif // ELECTRONTEMPERATURE_H
