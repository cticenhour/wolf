#ifndef ENERGYFLUXBC_H
#define ENERGYFLUXBC_H

#include "IntegratedBC.h"

class EnergyFluxBC;

template <>
InputParameters validParams<EnergyFluxBC>();

/**
 *
 */
class EnergyFluxBC : public IntegratedBC
{
public:
  EnergyFluxBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  Real _ion_mobility;

  const VariableGradient & _grad_electron_density;

  const VariableValue & _electron_density;

  const VariableValue & _ion_density;

  const VariableGradient & _grad_potential;

  Real _T_e_wall;

  Real _electron_mass;

  Real _secondary_electron_coefficient;

  Real _T_secondary_electron;
};

#endif // ENERGYFLUXBC_H
