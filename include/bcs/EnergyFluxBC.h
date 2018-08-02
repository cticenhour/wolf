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
  Real _diffusivity;

  Real _mobility;

  const VariableGradient & _grad_electron_density;

  const VariableValue & _electron_density;

  const VariableGradient & _grad_potential;

  Real _T_e_wall;
};

#endif // ENERGYFLUXBC_H
