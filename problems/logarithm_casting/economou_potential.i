[Mesh]
  type = FileMesh
  file = '../economou_paper.msh'
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
  [./potential_MMS]
    order = FIRST
    family = LAGRANGE
  [../]
  [./ne_MMS]
    order = FIRST
    family = LAGRANGE
  [../]
  [./ni_MMS]
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
  [./ni_MMS_aux]
    type = FunctionAux
    variable = ni_MMS
    function = ni_profile_func
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
    value = 'log(1e7)'
  [../]
  [./ne_bc_func]
    type = ParsedFunction
    value = '-10'
  [../]
  [./potential_func]
    type = ParsedFunction
    value = '-(exp(1.58478*x) - 1) - 56*exp(-1.58478*x) + 56'
  [../]
  [./potential_rhs_func]
    type = ParsedFunction
    value = '-2.5115276484 * exp(1.58478*x) + 1.8095131930788e-8*exp(6.34571*x) - 1.8095131930788e-8 + 0.18095131930788*exp(-6.34571*x) - 138.134020662*exp(-1.58478*x)'
  [../]
  [./ne_rhs_func]
    type = ParsedFunction
    value = '-0.300912483724967*x*x*(-393700787.401575*x + 1000000000.0)*(-0.393700787401575*x + 1) - 57602570410051.2*x*x + 292621.05768306*x*(-393700787.401575*x + 1000000000.0) + 292621057683060.0*x*(-0.393700787401575*x + 1) + (-393700787.401575*x + 1000000000.0)*(146310.52884153*x - 371628.743257486) + (-2.5115276484*exp(1.58478*x) - 138.134020662*exp(-1.58478*x))*(46500.093000186*x*x*(-393700787.401575*x + 1000000000.0)*(-0.393700787401575*x + 1) - 300000.0*exp(6.34571*x) + 3000000300000.0 - 3000000000000.0*exp(-6.34571*x)) + (-1.58478*exp(1.58478*x) + 87.1629*exp(-1.58478*x))*(-18307.1232284197*x*x*(-393700787.401575*x + 1000000000.0) - 18307123228419.7*x*x*(-0.393700787401575*x + 1) + 93000.186000372*x*(-393700787.401575*x + 1000000000.0)*(-0.393700787401575*x + 1) - 1903713.0*exp(6.34571*x) + 19037130000000.0*exp(-6.34571*x)) + 48273322.7838021*exp(6.34571*x) - 19413671.741367 + 482733227838021.0*exp(-6.34571*x)'
  [../]
  [./ni_rhs_func]
    type = ParsedFunction
    value = '-0.300912483724967*x*x*(-393700787.401575*x + 1000000000.0)*(-0.393700787401575*x + 1) - 3089146856.57507*x*x + 15.6928660314014*x*(-393700787.401575*x + 1000000000.0) + 15692866031.4014*x*(-0.393700787401575*x + 1) + (-393700787.401575*x + 1000000000.0)*(7.84643301570068*x - 19.9299398598797) + (-223.820447640895*x*x*(-393700787.401575*x + 1000000000.0)*(-0.393700787401575*x + 1) - 14440000000.0)*(-2.5115276484*exp(1.58478*x) - 138.134020662*exp(-1.58478*x)) + (-1.58478*exp(1.58478*x) + 87.1629*exp(-1.58478*x))*(88.1182864727934*x*x*(-393700787.401575*x + 1000000000.0) + 88118286472.7934*x*x*(-0.393700787401575*x + 1) - 447.640895281791*x*(-393700787.401575*x + 1000000000.0)*(-0.393700787401575*x + 1)) + 1.94136698*exp(6.34571*x) - 19413671.741367 + 19413669.8*exp(-6.34571*x)'
  [../]
  [./ne_profile_func]
    type = ParsedFunction
    value = '1e7 + 1e9 * (1 - x/2.54) * (1 - x/2.54) * (x / 2.54) * (x / 2.54) - (exp(6.34571*x) - 1) - 1e7*exp(-6.34571*x)'
  [../]
  [./ni_profile_func]
    type = ParsedFunction
    value = '1e7 + 1e9 * (1 - x/2.54) * (1 - x/2.54) * (x / 2.54) * (x / 2.54)'
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
  print_linear_residuals = false
  perf_graph = true
[]
