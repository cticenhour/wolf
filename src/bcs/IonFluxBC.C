#include "IonFluxBC.h"

registerMooseObject("WolfApp", IonFluxBC);

template <>
InputParameters
validParams<IonFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("potential", "The electric potential.");
  params.addRequiredParam<Real>("mobility", "Species mobility.");
  return params;
}

IonFluxBC::IonFluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _grad_potential(coupledGradient("potential")),
    _mobility(getParam<Real>("mobility"))
{
}

Real
IonFluxBC::computeQpResidual()
{
  return -_test[_i][_qp] * _mobility * _u[_qp] * _grad_potential[_qp] * _normals[_qp];
}

Real
IonFluxBC::computeQpJacobian()
{
  return -_test[_i][_qp] * _mobility * _phi[_j][_qp] * _grad_potential[_qp] * _normals[_qp];
}
