#include "LogStabilization.h"

registerMooseObject("WolfApp", LogStabilization);

template <>
InputParameters
validParams<LogStabilization>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Kernel to help stabilize logarithmically-casted variables.");
  params.addRequiredParam<Real>(
      "offset", "The offset parameter that goes into the exponential stabilization function.");
  return params;
}

LogStabilization::LogStabilization(const InputParameters & parameters)
  : Kernel(parameters),

    _offset(getParam<Real>("offset"))
{
}

Real
LogStabilization::computeQpResidual()
{
  return -_test[_i][_qp] * std::exp(-(_offset + _u[_qp]));
}

Real
LogStabilization::computeQpJacobian()
{
  return -_test[_i][_qp] * std::exp(-(_offset + _u[_qp])) * -_phi[_j][_qp];
}
