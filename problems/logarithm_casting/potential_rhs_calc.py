#!/usr/bin/env python
from sympy import *

x, y, z = symbols('x y z')
#init_printing(use_unicode=True)

De = 1.1988e6
Di = 64.29
mue = 3e5
mui = 1.444e3
N = 3.22e16
ki = 6.02909e-17
V = -((exp(1.58478*x)-1) + 55*exp(-1.58478*x)) + 55
ne = 1e7 + 1e9 * (1 - x / 2.54) * (1 - x / 2.54) * (x / 2.54) * (x / 2.54) - (exp(6.34571 * x) - 1) - 1e7 * exp(-6.34571*x)
ni = 1e7 + 1e9 * (1 - x / 2.54) * (1 - x / 2.54) * (x / 2.54) * (x / 2.54)
e = 1.602177e-19
eps = 8.854188e-12

diff_ne = diff(ne, x)
diff_ni = diff(ni, x)
diff_V = diff(V, x)
diff2_V = diff(diff_V, x)

lhs_ne_preDiff = -De * diff_ne + mue * ne * diff_V
rxn_ne = ki * N * ne
ne_MMS_rhs = diff(lhs_ne_preDiff, x) - rxn_ne

lhs_ni_preDiff = -Di * diff_ni - mui * ni * diff_V
rxn_ni = rxn_ne
ni_MMS_rhs = diff(lhs_ni_preDiff, x) - rxn_ni

V_MMS_rhs = -diff2_V - (e / eps) * (ni - ne)
