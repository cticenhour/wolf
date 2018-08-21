#include "EnergyExcitation.h"
#include "Function.h"

registerMooseObject("WolfApp", EnergyExcitation);

template <>
InputParameters
validParams<EnergyExcitation>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("electrons", "Electron density coupled variable.");
  params.addRequiredParam<Real>("background_gas_density", "The background gas density.");
  return params;
}

EnergyExcitation::EnergyExcitation(const InputParameters & parameters)
  : Kernel(parameters),

    _k(getMaterialProperty<Real>("kex")),
    _electron_density(coupledValue("electrons")),
    _N_gas(getParam<Real>("background_gas_density")),
    _energy_exchange(11.56),
    _electron_id(coupled("electrons"))
{
}

Real
EnergyExcitation::computeQpResidual()
{
  return _test[_i][_qp] * _energy_exchange * _k[_qp] * _N_gas * _electron_density[_qp];
}

Real
EnergyExcitation::computeQpJacobian()
{
  return 0;
}

Real
EnergyExcitation::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _electron_id)
    return _test[_i][_qp] * _energy_exchange * _k[_qp] * _N_gas * _phi[_j][_qp];

  else
    return 0;
}
