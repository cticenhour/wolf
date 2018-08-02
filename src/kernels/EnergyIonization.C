#include "EnergyIonization.h"
#include "Function.h"

registerMooseObject("WolfApp", EnergyIonization);

template <>
InputParameters
validParams<EnergyIonization>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<FunctionName>("ionization_rate", "Ionization rate coefficient.");
  params.addRequiredCoupledVar("electrons", "Electron density coupled variable.");
  params.addRequiredParam<Real>("background_gas_density", "The background gas density.");
  return params;
}

EnergyIonization::EnergyIonization(const InputParameters & parameters)
  : Kernel(parameters),

    _k_i(getFunction("ionization_rate")),
    _electron_density(coupledValue("electrons")),
    _N_gas(getParam<Real>("background_gas_density")),
    _energy_exchange(15.7)
{
}

Real
EnergyIonization::computeQpResidual()
{
  return _test[_i][_qp] * _energy_exchange * _k_i.value(_t, _q_point[_qp]) * _N_gas *
         _electron_density[_qp];
}

Real
EnergyIonization::computeQpJacobian()
{
  return 0;
}
