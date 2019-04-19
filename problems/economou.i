# Argon specific parameters (from paper)
backgroundGasDensity = 3.22e16   # in 1 / cm^3
diffem = 1.1988e6
diffArp = 64.29
mobem = 3e5
mobArp = 1444.099

[GlobalParams]
  background_gas_density = ${backgroundGasDensity}
  sec_elec_emission = 0.01
  recombination_coeff = 1.19e7
[]

[Mesh]
  type = FileMesh
  file = 'economou_paper.msh'
  construct_side_list_from_node_list = true
[]

[Materials]
  [./argon_ionization]
    type = ParsedMaterial
    args = mean_en
    f_name = ki
    function = '1e6 * 2.34e-14 * ((2 / 3) * mean_en)^0.59 * exp(-17.44 * 3 / (2 * mean_en))'
  [../]
  [./argon_excitation]
    type = ParsedMaterial
    args = mean_en
    f_name = kex
    function = '1e6 * 2.48e-14 * ((2 / 3) * mean_en)^0.33 * exp(-12.78 * 3 / (2 * mean_en))'
  [../]
[]

[Variables]
  [./ne]  # defaults to first order Lagrange
    scaling = 1e-16
  [../]
  [./ni]
    scaling = 1e-16
  [../]
  [./potential]
  [../]
  [./mean_en]
    scaling = 1e-20
  [../]
[]

[AuxVariables]
  [./ki_output]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./ki_transfer]
    type = MaterialRealAux
    property = ki
    variable = ki_output
  [../]
[]

[Kernels]
  [./potential_diffusion]
    type = Diffusion
    variable = potential
  [../]
  [./potential_ne_charge_source]
    type = ChargeSource
    variable = potential
    coupled_species = ne
    sign = -1.0
  [../]
  [./potential_ni_charge_source]
    type = ChargeSource
    variable = potential
    coupled_species = ni
    sign = 1.0
  [../]
  [./electron_time_derivative]
    type = TimeDerivative
    variable = ne
  [../]
  [./electron_diffusion]
    type = CoeffDiffusion
    diffusivity = ${diffem}
    variable = ne
  [../]
  [./electron_field_advection]
    type = EFieldAdvection
    variable = ne
    potential = potential
    mobility = ${mobem}
    sign = -1.0
  [../]
  [./ne_gnd_state_ioniz]
    type = GndStateIonizationElectrons
    variable = ne
    second_species = ${backgroundGasDensity}
    mean_energy = mean_en
  [../]
  [./ion_time_derivative]
    type = TimeDerivative
    variable = ni
  [../]
  [./ion_diffusion]
    type = CoeffDiffusion
    diffusivity = ${diffArp}
    variable = ni
  [../]
  [./ion_field_advection]
    type = EFieldAdvection
    variable = ni
    potential = potential
    mobility = ${mobArp}
    sign = 1.0
  [../]
  [./ni_gnd_state_ioniz]
    type = GndStateIonizationIons
    variable = ni
    electrons = ne
    second_species = ${backgroundGasDensity}
    mean_energy = mean_en
  [../]
  [./energy_time_derivative]
    type = EnergyTimeDerivative
    variable = mean_en
    electrons = ne
  [../]
  [./energy_times_electron_time_derivative]
    type = EnergyCoupledTimeDerivative
    variable = mean_en
    electrons = ne
  [../]
  [./energy_diffusion]
    type = CoupledEnergyDiffusion
    variable = mean_en
    diffusivity = ${diffem}
    electrons = ne
  [../]
  [./energy_advection]
    type = EFieldAdvectionEnergy
    variable = mean_en
    electrons = ne
    mobility = ${mobem}
    potential = potential
  [../]
  [./energy_electron_diffusion]
    type = ElectronDiffusionEnergy
    variable = mean_en
    diffusivity = ${diffem}
    electrons = ne
  [../]
  [./energy_joule_heating]
    type = JouleHeating
    variable = mean_en
    electrons = ne
    potential = potential
    diffusivity = ${diffem}
    mobility = ${mobem}
  [../]
  [./energy_gnd_state_excitation]
    type = EnergyExcitation
    variable = mean_en
    electrons = ne
  [../]
  [./energy_gnd_state_ionization]
    type = EnergyIonization
    variable = mean_en
    electrons = ne
  [../]
[]

[BCs]
  [./ne_flux_bc_left]
    type = ElectronFluxBC
    variable = ne
    boundary = left
    potential = potential
    ion_species = ni
    ion_mobility = ${mobArp}
  [../]
  [./ne_flux_bc_right]
    type = ElectronFluxBC
    variable = ne
    boundary = right
    potential = potential
    ion_species = ni
    ion_mobility = ${mobArp}
  [../]
  [./ni_flux_bc]
    type = IonFluxBC
    variable = ni
    boundary = 'left right'
    potential = potential
    mobility = ${mobArp}
  [../]
  [./potential_left]
    type = FunctionDirichletBC
    variable = potential
    function = electrode_potential_func
    boundary = left
  [../]
  [./potential_right]
    type = DirichletBC
    variable = potential
    value = 0
    boundary = right
  [../]
  [./mean_en_left]
    type = DirichletBC
    variable = mean_en
    boundary = left
    value = 0.75
  [../]
  [./mean_en_right]
    type = DirichletBC
    variable = mean_en
    boundary = right
    value = 0.75
  [../]
  # [./energy_flux_left]
  #   type = EnergyFluxBC
  #   variable = mean_en
  #   electrons = ne
  #   ions = ni
  #   potential = potential
  #   ion_mobility = ${mobArp}
  #   #electron_temp_at_wall = 0.5
  #   boundary = left
  # [../]
  # [./energy_flux_right]
  #   type = EnergyFluxBC
  #   variable = mean_en
  #   electrons = ne
  #   ions = ni
  #   potential = potential
  #   ion_mobility = ${mobArp}
  #   #electron_temp_at_wall = 0.5
  #   boundary = right
  # [../]
[]

[ICs]
  [./ne_ic]
    type = FunctionIC
    variable = ne
    function = n_ic_func
  [../]
  [./ni_ic]
    type = FunctionIC
    variable = ni
    function = n_ic_func
  [../]
  [./potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  [../]
  [./mean_en_ic]
    type = FunctionIC
    variable = mean_en
    function = mean_en_ic_func
  [../]
[]

[Functions]
  [./n_ic_func]
    type = ParsedFunction
    value = '1e7 + 1e9 * (1 - x/2.54) * (1 - x/2.54) * (x / 2.54) * (x / 2.54)'
  [../]
  [./potential_ic_func]
    type = ConstantFunction
    value = 0
  [../]
  [./electrode_potential_func]
    type = ParsedFunction
    vars = vrf
    vals = 100
    value = 'vrf*sin(2*pi*13.56e6*t)'
  [../]
  [./mean_en_ic_func]
    type = ParsedFunction
    vars = 'Te_init'
    vals = '1.0'
    value = '(3/2) * Te_init'
  [../]
[]

[Preconditioning]
  active = 'FDP'
  [./SMP]
    type = SMP
    full = true
  [../]
  [./FDP]
    type = FDP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  #num_steps = 1e6     # 10 is one rf cycle if dt is 7.374631e-9 and f = 13.56 MHz
                      # Economou mentions 1e5 rf cycles needed for convergence without acceleration
  dt = 1e-11
  #dtmax = 1.685e-9
  #end_time = 0.00737463126   # 10 rf cycles for f = 13.56 MHz
  end_time = 0.001
  #petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  #petsc_options = '-snes_test_jacobian'
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
  #nl_abs_tol = 1e-08
  # [./TimeStepper]
  #   type = IterationAdaptiveDT
  #   dt = 1e-11
  #   cutback_factor = 0.9
  #   growth_factor = 1.01
  # [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  exodus = true
  execute_on = 'INITIAL TIMESTEP_END FAILED'
  print_linear_residuals = true
  perf_graph = true
[]
