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

// Second species density is assumed to be a linear variable (since it's generally been a constant
// background gas density)
Real
GndStateIonizationElectrons::computeQpResidual()
{
  return -_test[_i][_qp] * _k[_qp] * _second_species_density[_qp] * std::exp(_u[_qp]);
}

Real
GndStateIonizationElectrons::computeQpJacobian()
{
  return -_test[_i][_qp] * _k[_qp] * _second_species_density[_qp] * std::exp(_u[_qp]) *
         _phi[_j][_qp];
}

Real
GndStateIonizationElectrons::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _second_species_id)
    return -_test[_i][_qp] * _k[_qp] * _phi[_j][_qp] * std::exp(_u[_qp]);

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * _second_species_density[_qp] * std::exp(_u[_qp]) *
           (2.34e-14 * 0.59 * std::pow((2 / 3), 0.59) * std::pow(std::exp(_mean_en[_qp]), 0.59) *
                std::exp(-17.44 * 3 / (2 * std::exp(_mean_en[_qp]))) * _phi[_j][_qp] +
            2.34e-14 * std::pow((2 / 3), 0.59) * (17.44 * 3 / 2) *
                std::pow(std::exp(_mean_en[_qp]), -0.41) *
                std::exp(-17.44 * 3 / (2 * std::exp(_mean_en[_qp]))) * _phi[_j][_qp]);

  else
    return 0;
}
