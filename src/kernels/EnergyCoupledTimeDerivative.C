#include "EnergyCoupledTimeDerivative.h"

registerMooseObject("WolfApp", EnergyCoupledTimeDerivative);

template <>
InputParameters
validParams<EnergyCoupledTimeDerivative>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("electrons", "The electron density.");
  return params;
}

EnergyCoupledTimeDerivative::EnergyCoupledTimeDerivative(const InputParameters & parameters)
  : Kernel(parameters),

    _electrons_dot(coupledDot("electrons"))
{
}

Real
EnergyCoupledTimeDerivative::computeQpResidual()
{
  return _test[_i][_qp] * _u[_qp] * _electrons_dot[_qp];
}

Real
EnergyCoupledTimeDerivative::computeQpJacobian()
{
  return 0;
}
