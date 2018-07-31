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

[Kernels]
  [./laplacian]
    type = Diffusion
    variable = potential
  [../]
  [./rhs]
    type = BodyForce
    variable = potential
    function = 1
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
