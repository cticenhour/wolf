[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 50
  xmin = 0
  xmax = 2.54  # cm
[]

[Variables]
  [./potential]
    family = LAGRANGE
    order = FIRST
  [../]
[]



[Functions]
  [./rho_over_epsilon]
    type = ParsedFunction
    value = '-(1.602177e-19/8.854187e-12)*(3.6e10*exp(-(x-1.27)*(x-1.27)/(2*0.5*0.5)) - 3.6e10*(exp(-(x-1.27)*(x-1.27)/(2*0.5*0.5)) - (x-1.27)*(x-1.27)*exp(-1.27*1.27/(2*0.5*0.5))))'
  [../]
[]

[Kernels]
  [./laplacian]
    type = Diffusion
    variable = potential
  [../]
  [./rhs]
    type = BodyForce
    variable = potential
    function = rho_over_epsilon
  [../]
[]

[BCs]
  [./all]
    type = DirichletBC
    value = 0
    variable = potential
    boundary = 'left right'
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
[]

[Outputs]
  exodus = true
[]
