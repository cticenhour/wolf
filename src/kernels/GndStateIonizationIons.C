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

// Second species density is assumed to be a linear variable (since it's generally been a constant
// background gas density)
Real
GndStateIonizationIons::computeQpResidual()
{
  return -_test[_i][_qp] * _k[_qp] * _second_species_density[_qp] *
         std::exp(_electron_density[_qp]);
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
    return -_test[_i][_qp] * _k[_qp] * _second_species_density[_qp] *
           std::exp(_electron_density[_qp]) * _phi[_j][_qp];

  else if (jvar == _coupled_id)
    return -_test[_i][_qp] * _k[_qp] * _phi[_j][_qp] * std::exp(_electron_density[_qp]);

  else if (jvar == _mean_en_id)
    return -_test[_i][_qp] * _second_species_density[_qp] * std::exp(_electron_density[_qp]) *
           (2.34e-14 * 0.59 * std::pow((2 / 3), 0.59) * std::pow(std::exp(_mean_en[_qp]), 0.59) *
                std::exp(-17.44 * 3 / (2 * std::exp(_mean_en[_qp]))) * _phi[_j][_qp] +
            2.34e-14 * std::pow((2 / 3), 0.59) * (17.44 * 3 / 2) *
                std::pow(std::exp(_mean_en[_qp]), -0.41) *
                std::exp(-17.44 * 3 / (2 * std::exp(_mean_en[_qp]))) * _phi[_j][_qp]);

  else
    return 0;
}
