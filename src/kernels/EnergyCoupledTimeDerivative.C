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

    _electrons_dot(coupledDot("electrons")),
    _delectrons_dot(coupledDotDu("electrons")),
    _electron_id(coupled("electrons"))
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

// See CoupledTimeDerivative in MOOSE for the origin of this bit of code.
Real
EnergyCoupledTimeDerivative::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _electron_id)
    return _test[_i][_qp] * _u[_qp] * _phi[_j][_qp] * _delectrons_dot[_qp];

  else
    return 0;
}
