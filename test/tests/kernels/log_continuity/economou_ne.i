[Mesh]
  type = GeneratedMesh
  xmin = 0
  xmax = 2.54
  nx = 100
  dim = 1
[]

[Materials]
  [./argon_ionization] # assume mean_en = 4
    type = GenericConstantMaterial
    prop_names = ki
    prop_values = 6.02909e-17
  [../]
[]

[Variables]
  [./ne]  # defaults to first order Lagrange
    scaling = 1e-13
  [../]
[]

[AuxVariables]
  [./ne_lin]
    order = FIRST
    family = LAGRANGE
  [../]
  [./potential_MMS]
    order = FIRST
    family = LAGRANGE
  [../]
  [./ne_MMS]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxKernels]
  [./ne_lin]
    type = Density
    variable = ne_lin
    density_log = ne
  [../]
  [./potential_aux]
    type = FunctionAux
    variable = potential_MMS
    function = potential_func
  [../]
  [./ne_MMS_aux]
    type = FunctionAux
    variable = ne_MMS
    function = ne_profile_func
  [../]
[]

[Kernels]
  [./electron_diffusion]
    type = CoeffDiffusion
    diffusivity = 1.1988e6
    variable = ne
  [../]
  [./electron_field_advection]
    type = EFieldAdvection
    variable = ne
    potential = potential_MMS
    mobility = 3e5
    sign = -1.0
  [../]
  [./ne_gnd_state_ioniz]
    type = GndStateIonizationElectrons
    variable = ne
    second_species = 3.22e16 # background gas density (cm^-3)
    mean_energy = 4
  [../]
  [./rhs]
    type = BodyForce
    function = rhs_func
    variable = ne
  [../]
[]

[BCs]
  [./left_ne]
    type = FunctionDirichletBC
    variable = ne
    function = n_bc_func
    boundary = left
  [../]
  [./right_ne]
    type = FunctionDirichletBC
    variable = ne
    function = n_bc_func
    boundary = right
  [../]
[]

[Functions]
  [./n_bc_func]
    type = ParsedFunction
    value = 'log(1000)'
  [../]
  [./potential_func]
    type = ParsedFunction
    value = '(1 / 5) * (-x * x + 2.54 * x)'
  [../]
  [./rhs_func]
    type = ParsedFunction
    value = '38827339.6 * x * x - 98621442.584 * x + 47951999998058.6'
  [../]
  [./ne_profile_func]
    type = ParsedFunction
    value = '2e7 * (-x * x + 2.54 * x) + 1000'
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
[]

[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  [./out]
    type = Exodus
    execute_on = 'initial timestep_end failed'
  [../]
  print_linear_residuals = true
  perf_graph = true
[]
