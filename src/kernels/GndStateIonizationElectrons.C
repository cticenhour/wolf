#include "GndStateIonizationElectrons.h"
#include "Function.h"

registerMooseObject("WolfApp", GndStateIonizationElectrons);

template <>
InputParameters
validParams<GndStateIonizationElectrons>()
{
  InputParameters params = validParams<Reaction>();
  params.addRequiredCoupledVar("second_species", "Second species involved in reaction.");
  params.addRequiredParam<FunctionName>("rate_coefficient", "Reaction rate coefficient.");
  return params;
}

GndStateIonizationElectrons::GndStateIonizationElectrons(const InputParameters & parameters)
  : Reaction(parameters),

    _second_species_density(coupledValue("second_species")),
    _k(getFunction("rate_coefficient"))
{
}

Real
GndStateIonizationElectrons::computeQpResidual()
{
  return -_k.value(_t, _q_point[_qp]) * _second_species_density[_qp] *
         Reaction::computeQpResidual();
}

Real
GndStateIonizationElectrons::computeQpJacobian()
{
  return -_k.value(_t, _q_point[_qp]) * _second_species_density[_qp] *
         Reaction::computeQpJacobian();
}
