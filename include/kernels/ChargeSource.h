#ifndef CHARGESOURCE_H
#define CHARGESOURCE_H

#include "Kernel.h"

class ChargeSource;

template <>
InputParameters validParams<ChargeSource>();

/**
 *
 */
class ChargeSource : public Kernel
{
public:
  ChargeSource(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const VariableValue & _coupled_val;

  Real _sign;

  Real _q;

  Real _eps0;
};

#endif // CHARGESOURCE_H
