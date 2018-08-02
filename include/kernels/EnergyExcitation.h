#ifndef ENERGYEXCITATION_H
#define ENERGYEXCITATION_H

#include "Kernel.h"

class EnergyExcitation;

template <>
InputParameters validParams<EnergyExcitation>();

/**
 *
 */
class EnergyExcitation : public Kernel
{
public:
  EnergyExcitation(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Function & _k_ex;

  const VariableValue & _electron_density;

  Real _N_gas;

  Real _energy_exchange;
};

#endif // ENERGYEXCITATION_H
