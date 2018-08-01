#include "GndStateIonizationIons.h"
#include "Function.h"

registerMooseObject("WolfApp", GndStateIonizationIons);

template <>
InputParameters
validParams<GndStateIonizationIons>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("second_species", "Second species involved in reaction.");
  params.addRequiredParam<FunctionName>("rate_coefficient", "Reaction rate coefficient.");
  params.addRequiredCoupledVar("electrons", "Electron species variable name.");
  return params;
}

GndStateIonizationIons::GndStateIonizationIons(const InputParameters & parameters)
  : Kernel(parameters),

    _second_species_density(coupledValue("second_species")),
    _k(getFunction("rate_coefficient")),
    _electron_density(coupledValue("electrons"))
{
}

Real
GndStateIonizationIons::computeQpResidual()
{
  return -_test[_i][_qp] * _k.value(_t, _q_point[_qp]) * _second_species_density[_qp] *
         _electron_density[_qp];
}

Real
GndStateIonizationIons::computeQpJacobian()
{
  return 0;
}
