#include "GndStateIonizationElectrons.h"

registerMooseObject("WolfApp", GndStateIonizationElectrons);

template <>
InputParameters
validParams<GndStateIonizationElectrons>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("second_species", "Second species involved in reaction.");
  params.addRequiredCoupledVar("mean_energy", "Electron mean energy variable name.");
  return params;
}

GndStateIonizationElectrons::GndStateIonizationElectrons(const InputParameters & parameters)
  : Kernel(parameters),

    _second_species_density(coupledValue("second_species")),
    _k(getMaterialProperty<Real>("ki")),
    _second_species_id(coupled("second_species")),
    _mean_en_id(coupled("mean_energy")),
    _mean_en(coupledValue("mean_energy"))
{
}

Real
GndStateIonizationElectrons::computeQpResidual()
{
  return -_test[_i][_qp] * _k[_qp] * _second_species_density[_qp] * _u[_qp];
}

Real
GndStateIonizationElectrons::computeQpJacobian()
{
  return -_test[_i][_qp] * _k[_qp] * _second_species_density[_qp] * _phi[_j][_qp];
}

Real
GndStateIonizationElectrons::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _second_species_id)
    return -_test[_i][_qp] * _k[_qp] * _phi[_j][_qp] * _u[_qp];

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * _k[_qp] *
           (0.59 / ((2 / 3) * _mean_en[_qp]) + 17.44 / std::pow((2 / 3) * _mean_en[_qp], 2)) *
           _phi[_j][_qp] * _second_species_density[_qp] * _u[_qp];

  else
    return 0;
}
