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
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  const VariableValue & _second_species_density;

  const MaterialProperty<Real> & _k;

  const VariableValue & _electron_density;

  unsigned int _electron_id;

  unsigned int _coupled_id;

  unsigned int _mean_en_id;

  const VariableValue & _mean_en;
};

#endif // GNDSTATEIONIZATIONIONS_H
