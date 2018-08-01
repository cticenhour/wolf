#ifndef GNDSTATEIONIZATIONELECTRONS_H
#define GNDSTATEIONIZATIONELECTRONS_H

#include "Reaction.h"

class GndStateIonizationElectrons;

template <>
InputParameters validParams<GndStateIonizationElectrons>();

/**
 *
 */
class GndStateIonizationElectrons : public Reaction
{
public:
  GndStateIonizationElectrons(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableValue & _second_species_density;

  Function & _k;
};

#endif // GNDSTATEIONIZATIONELECTRONS_H
