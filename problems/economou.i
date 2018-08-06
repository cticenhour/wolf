[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 500
  xmin = 0
  xmax = 2.54  # cm
[]

[Variables]
  [./ne]  # defaults to first order Lagrange
    scaling = 1e-14
  [../]
  [./ni]
    scaling = 1e-12
  [../]
  [./potential]
    scaling = 1
  [../]
  [./mean_en]
    scaling = 1e-14
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
    rate_coefficient = 6.5e-10 # temporary until I have a file reader for the properties
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
    variable = ne
    potential = potential
    mobility = 1.444e3
    sign = 1.0
  [../]
  [./ni_gnd_state_ioniz]
    type = GndStateIonizationIons
    variable = ni
    electrons = ne
    rate_coefficient = 6.5e-10 # temporary
    second_species = 3.22e16 # background gas density (cm^-3)
  [../]
  [./energy_time_derivative]
    type = TimeDerivative
    variable = mean_en
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
    excitation_rate = 1e-12 # placeholder
  [../]
  [./energy_gnd_state_ionization]
    type = EnergyIonization
    variable = mean_en
    electrons = ne
    background_gas_density = 3.22e16
    ionization_rate = 1e-12 # placeholder
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
  [./energy_flux_left]
    type = EnergyFluxBC
    variable = mean_en
    electrons = ne
    ions = ni
    potential = potential
    ion_mobility = 1.444e3
    electron_temp_at_wall = 0.5
    boundary = left
  [../]
  [./energy_flux_right]
    type = EnergyFluxBC
    variable = mean_en
    electrons = ne
    ions = ni
    potential = potential
    ion_mobility = 1.444e3
    electron_temp_at_wall = 0.5
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

[Executioner]
  type = Transient
  solve_type = PJFNK
  num_steps = 100
  dt = 1.474925e-14
[]

[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  exodus = true
  execute_on = 'INITIAL TIMESTEP_END'
[]
