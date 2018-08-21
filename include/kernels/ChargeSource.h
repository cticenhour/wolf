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
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  const VariableValue & _coupled_val;

  Real _sign;

  Real _q;

  Real _eps0;

  unsigned int _coupled_id;
};

#endif // CHARGESOURCE_H
