#include "GndStateIonizationIons.h"

registerMooseObject("WolfApp", GndStateIonizationIons);

template <>
InputParameters
validParams<GndStateIonizationIons>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("second_species", "Second species involved in reaction.");
  params.addRequiredCoupledVar("electrons", "Electron species variable name.");
  params.addRequiredCoupledVar("mean_energy", "Electron mean energy variable name.");
  return params;
}

GndStateIonizationIons::GndStateIonizationIons(const InputParameters & parameters)
  : Kernel(parameters),

    _second_species_density(coupledValue("second_species")),
    _k(getMaterialProperty<Real>("ki")),
    _electron_density(coupledValue("electrons")),
    _electron_id(coupled("electrons")),
    _coupled_id(coupled("second_species")),
    _mean_en_id(coupled("mean_energy")),
    _mean_en(coupledValue("mean_energy"))
{
}

Real
GndStateIonizationIons::computeQpResidual()
{
  return -_test[_i][_qp] * _k[_qp] * _second_species_density[_qp] * _electron_density[_qp];
}

Real
GndStateIonizationIons::computeQpJacobian()
{
  return 0;
}

Real
GndStateIonizationIons::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _electron_id)
    return -_test[_i][_qp] * _k[_qp] * _second_species_density[_qp] * _phi[_j][_qp];

  else if (jvar == _coupled_id)
    return -_test[_i][_qp] * _k[_qp] * _phi[_j][_qp] * _electron_density[_qp];

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * _k[_qp] *
           (0.59 / ((2 / 3) * _mean_en[_qp]) + 17.44 / std::pow((2 / 3) * _mean_en[_qp], 2)) *
           _phi[_j][_qp] * _second_species_density[_qp] * _electron_density[_qp];

  else
    return 0;
}
