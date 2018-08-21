#include "GndStateIonizationElectrons.h"

registerMooseObject("WolfApp", GndStateIonizationElectrons);

template <>
InputParameters
validParams<GndStateIonizationElectrons>()
{
  InputParameters params = validParams<Reaction>();
  params.addRequiredCoupledVar("second_species", "Second species involved in reaction.");
  return params;
}

GndStateIonizationElectrons::GndStateIonizationElectrons(const InputParameters & parameters)
  : Reaction(parameters),

    _second_species_density(coupledValue("second_species")),
    _k(getMaterialProperty<Real>("ki")),
    _coupled_id(coupled("second_species"))
{
}

Real
GndStateIonizationElectrons::computeQpResidual()
{
  return -_k[_qp] * _second_species_density[_qp] * Reaction::computeQpResidual();
}

Real
GndStateIonizationElectrons::computeQpJacobian()
{
  return -_k[_qp] * _second_species_density[_qp] * Reaction::computeQpJacobian();
}

Real
GndStateIonizationElectrons::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _coupled_id)
    return -_k[_qp] * _phi[_j][_qp] * Reaction::computeQpResidual();

  else
    return 0;
}
