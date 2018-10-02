#include "ElectronFluxBC.h"
#include "Function.h"

registerMooseObject("WolfApp", ElectronFluxBC);

template <>
InputParameters
validParams<ElectronFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("potential", "The electric potential.");
  params.addRequiredCoupledVar("ion_species", "Coupled ion species density.");
  params.addRequiredParam<Real>("sec_elec_emission", "Secondary electron emission coefficient.");
  params.addRequiredParam<FunctionName>("ion_mobility", "Positive ion mobility.");
  params.addRequiredParam<Real>("recombination_coeff", "Electron recombination coefficient.");
  return params;
}

ElectronFluxBC::ElectronFluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _grad_potential(coupledGradient("potential")),
    _ion_density(coupledValue("ion_species")),
    _see_coeff(getParam<Real>("sec_elec_emission")),
    _ion_mobility(getFunction("ion_mobility")),
    _recombination_coeff(getParam<Real>("recombination_coeff")),
    _potential_id(coupled("potential")),
    _ion_id(coupled("ion_species"))
{
}

Real
ElectronFluxBC::computeQpResidual()
{
  return _test[_i][_qp] *
         (_normals[_qp] * _recombination_coeff * std::exp(_u[_qp]) * _normals[_qp] +
          _see_coeff * _ion_mobility.value(_t, _q_point[_qp]) * std::exp(_ion_density[_qp]) *
              _grad_potential[_qp] * _normals[_qp]);
}

Real
ElectronFluxBC::computeQpJacobian()
{
  return _test[_i][_qp] *
         (_normals[_qp] * _recombination_coeff * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp]);
}

Real
ElectronFluxBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    return _test[_i][_qp] * (_see_coeff * _ion_mobility.value(_t, _q_point[_qp]) *
                             std::exp(_ion_density[_qp]) * _grad_phi[_j][_qp] * _normals[_qp]);

  else if (jvar == _ion_id)
    return _test[_i][_qp] * (_see_coeff * _ion_mobility.value(_t, _q_point[_qp]) *
                             std::exp(_phi[_j][_qp]) * _grad_potential[_qp] * _normals[_qp]);

  else
    return 0;
}
