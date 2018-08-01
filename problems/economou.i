[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
  xmin = 0
  xmax = 2.54  # cm
[]

[Variables]
  [./ne]
  [../]
  [./potential]
  [../]
[]

[Kernels]
  [./potential_diffusion]
    type = Diffusion
    variable = potential
  [../]
  [./ne_charge_source]
    type = ChargeSource
    variable = potential
    coupled_species = ne
    sign = -1.0
  [../]
  [./ni_charge_source]
    type = ChargeSource
    variable = potential
    coupled_species = 3.6e8 # placeholder for ni
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
  [./ne_advection]
    type = EFieldAdvectionElectrons
    variable = ne
    potential = potential
    mobility = mu_ne
  [../]
  [./ne_gnd_state_ioniz]
    type = IonizationRxn
    variable = ne
    rate_coefficient = 6.5e-10 # temporary until I have a file reader for the properties
    second_species = 3.22e16 # background gas density (cm^-3)
  [../]
[]

[BCs]
  [./ne_left]
    type = DirichletBC
    variable = ne
    boundary = left
    value = 1e7
  [../]
[]

[ICs]
  [./ne_ic]
    type = FunctionIC
    variable = ne
    function = n_ic_func
  [../]
  [./potential_ic]
    type = FunctionIC
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
[]

[Outputs]
  exodus = true
  execute_on = 'INITIAL TIMESTEP_END'
[]
