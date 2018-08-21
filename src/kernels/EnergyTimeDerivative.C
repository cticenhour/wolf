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

    _electron_density(coupledValue("electrons")),
    _electron_id(coupled("electrons"))
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

Real
EnergyTimeDerivative::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _electron_id)
    return _phi[_j][_qp] * TimeDerivative::computeQpResidual();

  else
    return 0;
}
