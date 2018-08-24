[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
  xmin = 0
  xmax = 2.54  # cm
[]

[Materials]
  [./argon_ionization]
    type = ParsedMaterial
    args = mean_en
    f_name = ki
    function = '2.34e-14 * ((2 / 3) * mean_en)^0.59 * exp(-17.44 * 3 / (2 * mean_en))'
  [../]
  [./argon_excitation]
    type = ParsedMaterial
    args = mean_en
    f_name = kex
    function = '5e-15 * ((2 / 3) * mean_en)^0.74 * exp(-11.56 * 3 / (2 * mean_en))'
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
    diffusivity = 1.1988e6
    variable = ne
  [../]
  [./electron_field_advection]
    type = EFieldAdvection
    variable = ne
    potential = potential
    mobility = 3e5
    sign = -1.0
  [../]
  [./ne_gnd_state_ioniz]
    type = GndStateIonizationElectrons
    variable = ne
    second_species = 3.22e16 # background gas density (cm^-3)
  [../]
  [./ion_time_derivative]
    type = TimeDerivative
    variable = ni
  [../]
  [./ion_diffusion]
    type = CoeffDiffusion
    diffusivity = 64.29
    variable = ni
  [../]
  [./ion_field_advection]
    type = EFieldAdvection
    variable = ni
    potential = potential
    mobility = 1.444e3
    sign = 1.0
  [../]
  [./ni_gnd_state_ioniz]
    type = GndStateIonizationIons
    variable = ni
    electrons = ne
    second_species = 3.22e16 # background gas density (cm^-3)
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
    diffusivity = 1.988e6
    electrons = ne
  [../]
  [./energy_advection]
    type = EFieldAdvectionEnergy
    variable = mean_en
    electrons = ne
    mobility = 3e5
    potential = potential
  [../]
  [./energy_electron_diffusion]
    type = ElectronDiffusionEnergy
    variable = mean_en
    diffusivity = 1.988e6
    electrons = ne
  [../]
  [./energy_joule_heating]
    type = JouleHeating
    variable = mean_en
    electrons = ne
    potential = potential
    diffusivity = 1.988e6
    mobility = 3e5
  [../]
  [./energy_gnd_state_excitation]
    type = EnergyExcitation
    variable = mean_en
    electrons = ne
    background_gas_density = 3.22e16
  [../]
  [./energy_gnd_state_ionization]
    type = EnergyIonization
    variable = mean_en
    electrons = ne
    background_gas_density = 3.22e16
  [../]
[]

[BCs]
  [./ne_flux_bc_left]
    type = ElectronFluxBC
    variable = ne
    boundary = left
    potential = potential
    sec_elec_emission = 0.01
    recombination_coeff = 1.19e7
    ion_species = ni
    ion_mobility = 1.444e3
  [../]
  [./ne_flux_bc_right]
    type = ElectronFluxBC
    variable = ne
    boundary = right
    potential = potential
    sec_elec_emission = 0.01
    recombination_coeff = 1.19e7
    ion_species = ni
    ion_mobility = 1.444e3
  [../]
  [./ni_flux_bc]
    type = IonFluxBC
    variable = ni
    boundary = 'left right'
    potential = potential
    mobility = 1.444e3
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
  # [./mean_en_left]
  #   type = DirichletBC
  #   variable = mean_en
  #   boundary = left
  #   value = 0.75
  # [../]
  # [./mean_en_right]
  #   type = DirichletBC
  #   variable = mean_en
  #   boundary = right
  #   value = 0.75
  # [../]
  [./energy_flux_left]
    type = EnergyFluxBC
    variable = mean_en
    electrons = ne
    ions = ni
    potential = potential
    sec_elec_emission = 0.01
    ion_mobility = 1.444e3
    #electron_temp_at_wall = 0.5
    boundary = left
  [../]
  [./energy_flux_right]
    type = EnergyFluxBC
    variable = mean_en
    electrons = ne
    ions = ni
    potential = potential
    sec_elec_emission = 0.01
    ion_mobility = 1.444e3
    #electron_temp_at_wall = 0.5
    boundary = right
  [../]
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
    value = '(3/2) * 1.0'
  [../]
[]

# [Dampers]
#   [./ne_damp]
#     type = ConstantDamper
#     variable = ne
#     damping = 0.9
#   [../]
# []

[Preconditioning]
  # [./FDP]
  #   type = FDP
  #   full = true
  # [../]
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  num_steps = 1e6     # 10 is one rf cycle if dt is 7.374631e-9 and f = 13.56 MHz
                      # Economou mentions 1e5 rf cycles needed for convergence without acceleration
  #dt = 7.374631e-9
  end_time = 0.00737463126   # 10 rf cycles for f = 13.56 MHz
  #petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
  #nl_rel_tol = 1e-12
[]

[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  exodus = true
  execute_on = 'INITIAL TIMESTEP_END'
  print_linear_residuals = false
  perf_graph = false
[]
