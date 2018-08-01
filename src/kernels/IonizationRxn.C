#include "IonizationRxn.h"
#include "Function.h"

registerMooseObject("WolfApp", IonizationRxn);

template <>
InputParameters
validParams<IonizationRxn>()
{
  InputParameters params = validParams<Reaction>();
  params.addRequiredCoupledVar("second_species", "Second species involved in reaction.");
  params.addRequiredParam<FunctionName>("rate_coefficient", "Reaction rate coefficient.");
  return params;
}

IonizationRxn::IonizationRxn(const InputParameters & parameters)
  : Reaction(parameters),

    _second_species_val(coupledValue("second_species")),
    _k(getFunction("rate_coefficient"))
{
}

Real
IonizationRxn::computeQpResidual()
{
  return _k.value(_t, _q_point[_qp]) * _second_species_val[_qp] * Reaction::computeQpResidual();
}

Real
IonizationRxn::computeQpJacobian()
{
  return _k.value(_t, _q_point[_qp]) * _second_species_val[_qp] * Reaction::computeQpJacobian();
}
