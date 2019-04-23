#include "ElectronTemperature.h"

registerMooseObject("WolfApp", ElectronTemperature);

template <>
InputParameters
validParams<ElectronTemperature>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Calculate the electron temperature in eV given the mean energy.");
  params.addRequiredCoupledVar("energy", "Coupled electron mean energy.");
  return params;
}

ElectronTemperature::ElectronTemperature(const InputParameters & parameters)
  : AuxKernel(parameters),

    _energy(coupledValue("energy"))
{
}

Real
ElectronTemperature::computeValue()
{
  return 2.0 / 3.0 * _energy[_qp];
}
