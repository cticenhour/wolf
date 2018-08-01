#ifndef IONIZATIONRXN_H
#define IONIZATIONRXN_H

#include "Reaction.h"

class IonizationRxn;

template <>
InputParameters validParams<IonizationRxn>();

/**
 *
 */
class IonizationRxn : public Reaction
{
public:
  IonizationRxn(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableValue & _second_species_val;

  Function & _k;
};

#endif // IONIZATIONRXN_H
