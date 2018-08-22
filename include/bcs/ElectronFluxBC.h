#ifndef ELECTRONFLUXBC_H
#define ELECTRONFLUXBC_H

#include "IntegratedBC.h"

class ElectronFluxBC;

template <>
InputParameters validParams<ElectronFluxBC>();

/**
 *
 */
class ElectronFluxBC : public IntegratedBC
{
public:
  ElectronFluxBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  const VariableGradient & _grad_potential;

  const VariableValue & _ion_density;

  Real _see_coeff;

  Function & _ion_mobility;

  Real _recombination_coeff;

  unsigned int _potential_id;

  unsigned int _ion_id;
};

#endif // ELECTRONFLUXBC_H
