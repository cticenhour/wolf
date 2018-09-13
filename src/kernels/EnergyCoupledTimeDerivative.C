#include "EnergyCoupledTimeDerivative.h"

registerMooseObject("WolfApp", EnergyCoupledTimeDerivative);

template <>
InputParameters
validParams<EnergyCoupledTimeDerivative>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addRequiredCoupledVar("electrons", "The electron density.");
  return params;
}

EnergyCoupledTimeDerivative::EnergyCoupledTimeDerivative(const InputParameters & parameters)
  : TimeKernel(parameters),

    _electron_density(coupledValue("electrons")),
    _electrons_dot(coupledDot("electrons")),
    _delectrons_dot(coupledDotDu("electrons")),
    _electron_id(coupled("electrons"))
{
}

Real
EnergyCoupledTimeDerivative::computeQpResidual()
{
  return _test[_i][_qp] * std::exp(_u[_qp]) * std::exp(_electron_density[_qp]) *
         _electrons_dot[_qp];
}

Real
EnergyCoupledTimeDerivative::computeQpJacobian()
{
  return _test[_i][_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * std::exp(_electron_density[_qp]) *
         _electrons_dot[_qp];
}

// See CoupledTimeDerivative in MOOSE for the origin of this bit of code.
Real
EnergyCoupledTimeDerivative::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _electron_id)
    return _test[_i][_qp] * std::exp(_u[_qp]) *
           (std::exp(_electron_density[_qp]) * _phi[_j][_qp] * _electrons_dot[_qp] +
            std::exp(_electron_density[_qp]) * _delectrons_dot[_qp] * _phi[_j][_qp]);

  else
    return 0;
}
