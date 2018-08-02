#include "EnergyExcitation.h"
#include "Function.h"

registerMooseObject("WolfApp", EnergyExcitation);

template <>
InputParameters
validParams<EnergyExcitation>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<FunctionName>("excitation_rate", "Excitation rate coefficient.");
  params.addRequiredCoupledVar("electrons", "Electron density coupled variable.");
  params.addRequiredParam<Real>("background_gas_density", "The background gas density.");
  return params;
}

EnergyExcitation::EnergyExcitation(const InputParameters & parameters)
  : Kernel(parameters),

    _k_ex(getFunction("excitation_rate")),
    _electron_density(coupledValue("electrons")),
    _N_gas(getParam<Real>("background_gas_density")),
    _energy_exchange(11.56)
{
}

Real
EnergyExcitation::computeQpResidual()
{
  return _test[_i][_qp] * _energy_exchange * _k_ex.value(_t, _q_point[_qp]) * _N_gas *
         _electron_density[_qp];
}

Real
EnergyExcitation::computeQpJacobian()
{
  return 0;
}
