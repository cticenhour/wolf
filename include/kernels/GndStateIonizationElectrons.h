#ifndef GNDSTATEIONIZATIONELECTRONS_H
#define GNDSTATEIONIZATIONELECTRONS_H

#include "Kernel.h"

class GndStateIonizationElectrons;

template <>
InputParameters validParams<GndStateIonizationElectrons>();

/**
 *
 */
class GndStateIonizationElectrons : public Kernel
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

  unsigned int _second_species_id;

  unsigned int _mean_en_id;

  const VariableValue & _mean_en;
};

#endif // GNDSTATEIONIZATIONELECTRONS_H
