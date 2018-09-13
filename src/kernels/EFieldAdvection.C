#include "EFieldAdvection.h"

registerMooseObject("WolfApp", EFieldAdvection);

template <>
InputParameters
validParams<EFieldAdvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The electric potential.");
  params.addRequiredParam<Real>("mobility", "Electron mobility.");
  params.addRequiredParam<Real>("sign", "Species charge sign (1.0 or -1.0).");
  return params;
}

EFieldAdvection::EFieldAdvection(const InputParameters & parameters)
  : Kernel(parameters),

    _grad_potential(coupledGradient("potential")),
    _mobility(getParam<Real>("mobility")),
    _sign(getParam<Real>("sign")),
    _potential_id(coupled("potential"))
{
}

Real
EFieldAdvection::computeQpResidual()
{
  return _grad_test[_i][_qp] * _sign * _mobility * std::exp(_u[_qp]) * _grad_potential[_qp];
}

Real
EFieldAdvection::computeQpJacobian()
{
  return _grad_test[_i][_qp] * _sign * _mobility * std::exp(_u[_qp]) * _phi[_j][_qp] *
         _grad_potential[_qp];
}

Real
EFieldAdvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    return _grad_test[_i][_qp] * _sign * _mobility * std::exp(_u[_qp]) * _grad_phi[_j][_qp];

  else
    return 0;
}
