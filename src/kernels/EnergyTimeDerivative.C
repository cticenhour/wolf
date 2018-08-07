#include "EnergyTimeDerivative.h"

registerMooseObject("WolfApp", EnergyTimeDerivative);

template <>
InputParameters
validParams<EnergyTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addRequiredCoupledVar("electrons", "The electron density.");
  return params;
}

EnergyTimeDerivative::EnergyTimeDerivative(const InputParameters & parameters)
  : TimeDerivative(parameters),

    _electron_density(coupledValue("electrons"))
{
}

Real
EnergyTimeDerivative::computeQpResidual()
{
  return _electron_density[_qp] * TimeDerivative::computeQpResidual();
}

Real
EnergyTimeDerivative::computeQpJacobian()
{
  return _electron_density[_qp] * TimeDerivative::computeQpJacobian();
}
