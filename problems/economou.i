[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
  xmin = 0
  xmax = 2.54  # cm
[]

[Variables]
  [./ne]  # defaults to first order Lagrange
  [../]
  [./ni]
  [../]
  [./potential]
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
[]

[Executioner]
  type = Transient
  solve_type = PJFNK
  num_steps = 100
  dt = 1.474925e-8
[]

[Outputs]
  exodus = true
  execute_on = 'INITIAL TIMESTEP_END'
[]
