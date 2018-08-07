#ifndef GNDSTATEIONIZATIONIONS_H
#define GNDSTATEIONIZATIONIONS_H

#include "Kernel.h"

class GndStateIonizationIons;

template <>
InputParameters validParams<GndStateIonizationIons>();

/**
 *
 */
class GndStateIonizationIons : public Kernel
{
public:
  GndStateIonizationIons(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableValue & _second_species_density;

  const MaterialProperty<Real> & _k;

  const VariableValue & _electron_density;
};

#endif // GNDSTATEIONIZATIONIONS_H
