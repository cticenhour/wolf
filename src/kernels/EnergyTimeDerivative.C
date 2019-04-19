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
  return _test[_i][_qp] * _electron_density[_qp] * std::exp(_u[_qp]) * _u_dot[_qp];
}

Real
EnergyTimeDerivative::computeQpJacobian()
{
  return _test[_i][_qp] * _electron_density[_qp] *
         (std::exp(_u[_qp]) * _phi[_j][_qp] * _u_dot[_qp] +
          std::exp(_u[_qp]) * _phi[_j][_qp] * _du_dot_du[_qp]);
}

Real
EnergyTimeDerivative::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _electron_id)
    return _test[_i][_qp] * _electron_density[_qp] * _phi[_j][_qp] * std::exp(_u[_qp]) *
           _u_dot[_qp];

  else
    return 0;
}
