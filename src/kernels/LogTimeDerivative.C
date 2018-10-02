#include "LogTimeDerivative.h"

registerMooseObject("WolfApp", LogTimeDerivative);

template <>
InputParameters
validParams<LogTimeDerivative>()
{
  InputParameters params = validParams<TimeKernel>();
  return params;
}

LogTimeDerivative::LogTimeDerivative(const InputParameters & parameters) : TimeKernel(parameters) {}

Real
LogTimeDerivative::computeQpResidual()
{
  return _test[_i][_qp] * std::exp(_u[_qp]) * _u_dot[_qp];
}

Real
LogTimeDerivative::computeQpJacobian()
{
  return _test[_i][_qp] * (std::exp(_u[_qp]) * _phi[_j][_qp] * _u_dot[_qp] +
                           std::exp(_u[_qp]) * _du_dot_du[_qp] * _phi[_j][_qp]);
}
