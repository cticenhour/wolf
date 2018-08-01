#include "EFieldAdvectionElectrons.h"

registerMooseObject("WolfApp", EFieldAdvectionElectrons);

template <>
InputParameters
validParams<EFieldAdvectionElectrons>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The electric potential.");
  params.addRequiredParam<Real>("mobility", "Electron mobility.");
  return params;
}

EFieldAdvectionElectrons::EFieldAdvectionElectrons(const InputParameters & parameters)
  : Kernel(parameters),

    _grad_potential(coupledGradient("potential")),

    _mobility(getParam<Real>("mobility"))
{
}

Real
EFieldAdvectionElectrons::computeQpResidual()
{
  return -_mobility * _u[_qp] * _grad_potential[_qp] * _grad_test[_i][_qp];
}

Real
EFieldAdvectionElectrons::computeQpJacobian()
{
  return -_mobility * _phi[_j][_qp] * _grad_potential[_qp] * _grad_test[_i][_qp];
}
