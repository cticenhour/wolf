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
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  const VariableValue & _second_species_density;

  const MaterialProperty<Real> & _k;

  unsigned int _coupled_id;
};

#endif // GNDSTATEIONIZATIONELECTRONS_H
