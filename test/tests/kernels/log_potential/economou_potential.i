[Mesh]
  type = FileMesh
  file = 'economou_paper.msh'
  construct_side_list_from_node_list = true
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
    scaling = 1e-14
  [../]
  [./ni]
    scaling = 1e-11
  [../]
  [./potential]
  [../]
[]

[AuxVariables]
  [./ne_lin]
    order = FIRST
    family = LAGRANGE
  [../]
  [./ni_lin]
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
  [./ni_lin]
    type = Density
    variable = ni_lin
    density_log = ni
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
  [./potential_rhs]
    type = BodyForce
    function = potential_rhs_func
    variable = potential
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
    mean_energy = 4
  [../]
  [./ne_rhs]
    type = BodyForce
    function = ne_rhs_func
    variable = ne
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
    mean_energy = 4
  [../]
  [./ni_rhs]
    type = BodyForce
    function = ni_rhs_func
    variable = ni
  [../]
[]

[BCs]
  [./left_ne]
    type = FunctionDirichletBC
    variable = ne
    function = ne_bc_func
    boundary = left
  [../]
  [./right_ne]
    type = FunctionDirichletBC
    variable = ne
    function = ne_bc_func
    boundary = right
  [../]
  [./left_ni]
    type = FunctionDirichletBC
    variable = ni
    function = ni_bc_func
    boundary = left
  [../]
  [./right_ni]
    type = FunctionDirichletBC
    variable = ni
    function = ni_bc_func
    boundary = right
  [../]
  [./left_potential]
    type = DirichletBC
    variable = potential
    value = 0
    boundary = left
  [../]
  [./right_potential]
    type = DirichletBC
    variable = potential
    value = 0
    boundary = right
  [../]
[]

[Functions]
  [./ni_bc_func]
    type = ParsedFunction
    value = 'log(1e3)'
  [../]
  [./ne_bc_func]
    type = ParsedFunction
    value = 'log(1e3)'
  [../]
  [./potential_func]
    type = ParsedFunction
    value = '0.2 * (-x*x + 2.54*x)'
  [../]
  [./potential_rhs_func]
    type = ParsedFunction
    value = '0.4'
  [../]
  [./ne_rhs_func]
    type = ParsedFunction
    value = '2400038827339.6*x^2 - 6096098621442.58*x + (-12000000000000.0*x + 15240000000000.0)*(-0.4*x + 0.508) + 47951879998058.6'
  [../]
  [./ni_rhs_func]
    type = ParsedFunction
    value = '-11513172660.4*x^2 + 29243458557.416*x + (-57760000000.0*x + 73355200000.0)*(0.4*x - 0.508) + 2572175658.63302'
  [../]
  [./n_profile_func]
    type = ParsedFunction
    value = '2e7 * (-x * x + 2.54 * x) + 1000'
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
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
