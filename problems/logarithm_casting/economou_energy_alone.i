# [Mesh]
#   type = GeneratedMesh
#   xmin = 0
#   xmax = 2.54
#   nx = 1000
#   dim = 1
# []

[Mesh]
  type = FileMesh
  file = '../economou_paper.msh'
  construct_side_list_from_node_list = true
[]

[Materials]
  [./argon_ionization]
    type = GenericConstantMaterial
    prop_names = ki
    prop_values = 6.02909e-17
  [../]
  [./argon_excitation]
    type = GenericConstantMaterial
    prop_names = kex
    prop_values = 1.35369e-16
  [../]
[]

[Variables]
  [./mean_en]
    scaling = 1e-13
  [../]
[]

[AuxVariables]
  [./ne]
    order = FIRST
    family = LAGRANGE
  [../]
  [./potential]
    order = FIRST
    family = LAGRANGE
  [../]
  [./mean_en_lin]
    order = FIRST
    family = LAGRANGE
  [../]
  [./mean_en_MMS]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxKernels]
  [./ne_MMS]
    type = FunctionAux
    variable = ne
    function = ne_profile_func
  [../]
  [./potential_MMS]
    type = FunctionAux
    variable = potential
    function = potential_func
  [../]
  [./mean_en_lin]
    type = Density
    variable = mean_en_lin
    density_log = mean_en
  [../]
  [./mean_en_MMS]
    type = FunctionAux
    variable = mean_en_MMS
    function = energy_profile_func
  [../]
[]

[Kernels]
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
  # [./energy_joule_heating]
  #   type = JouleHeating
  #   variable = mean_en
  #   electrons = ne
  #   potential = potential
  #   diffusivity = 1.988e6
  #   mobility = 3e5
  # [../]
  # [./energy_gnd_state_excitation]
  #   type = EnergyExcitation
  #   variable = mean_en
  #   electrons = ne
  #   background_gas_density = 3.22e16
  # [../]
  # [./energy_gnd_state_ionization]
  #   type = EnergyIonization
  #   variable = mean_en
  #   electrons = ne
  #   background_gas_density = 3.22e16
  # [../]
  [./energy_rhs]
    type = BodyForce
    function = energy_rhs_func
    variable = mean_en
  [../]
[]

[BCs]
  [./left_energy]
    type = FunctionDirichletBC
    variable = mean_en
    function = energy_bc_left
    boundary = left
  [../]
  [./right_energy]
    type = FunctionDirichletBC
    variable = mean_en
    function = energy_bc_right
    boundary = right
  [../]
[]

[Functions]
  [./energy_bc_left]
    type = ParsedFunction
    value = 'log(4)'
  [../]
  [./energy_bc_right]
    type = ParsedFunction
    value = 'log(12)'
  [../]
  [./potential_func]
    type = ParsedFunction
    value = '0.2 * (-x^2 + 2.54 * x)'
  [../]
  [./ne_profile_func]
    type = ParsedFunction
    value = 'log(2e7 * (-x^2 + 2.54 * x) + 1000)'
  [../]
  [./energy_profile_func]
    type = ParsedFunction
    value = 'exp((log(9) / 2.54) * x) + 3'
  [../]
  [./energy_rhs_func]
    type = ParsedFunction
    value = '(31464566929133.9*x - 39960000000000.0)*exp(0.393700787401575*x*log(9))*log(9) + (1.66666666666667*exp(0.393700787401575*x*log(9)) + 5.0)*(2400000000000.0*x^2 - 6096000000000.0*x + (-12000000000000.0*x + 15240000000000.0)*(-0.4*x + 0.508) + 47951880000000.0) + 0.656167979002625*(47952000000000.0*x + (-0.4*x + 0.508)*(-6000000000000.0*x^2 + 15240000000000.0*x + 300000000.0) - 60899040000000.0)*exp(0.393700787401575*x*log(9))*log(9) + 0.393700787401575*(15732283464566.9*x^2 - 39960000000000.0*x - 786614173.228346)*exp(0.393700787401575*x*log(9))*log(9)^2'
  [../]
[]

# [Preconditioning]
#   [./smp]
#     type = SMP
#     full = true
#   [../]
# []

[Executioner]
  type = Steady
  solve_type = PJFNK
  #petsc_options = '-snes_check_jacobian'
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
