[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
  xmin = 0
  xmax = 2.54  # cm
[]

[Variables]
  [./ne]
    family = LAGRANGE
    order = FIRST
  [../]
[]

[Kernels]
  [./electron_time_derivative]
    type = TimeDerivative
    variable = ne
  [../]
  [./electron_diffusion]
    type = CoeffDiffusion
    diffusivity = 1.1988e6
    variable = ne
  [../]
  [./electron_rhs]
    type = BodyForce
    variable = ne
    function = 0
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
  [./ne_initial_condition]
    type = FunctionIC
    variable = ne
    function = ne_ic
  [../]
[]

[Functions]
  [./ne_ic]
    type = ParsedFunction
    value = '1e7 + 1e9 * (1 - x/2.54) * (1 - x/2.54) * (x / 2.54) * (x / 2.54)'
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
