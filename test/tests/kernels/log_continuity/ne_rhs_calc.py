#!/usr/bin/env python
from sympy import *

x, y, z = symbols('x y z')
init_printing(use_unicode=True)

De = 1.1988e6
mue = 3e5
N = 3.22e16
ki = 6.02909e-17
V = 0.2 * (-x * x + 2.54 * x)
ne = 2e7 * (-x * x + 2.54 * x) + 1000

diff_ne = diff(ne, x)
diff_V = diff(V, x)
diff2_V = diff(diff_V, x)

lhs_preDiff = -De * diff_ne + mue * ne * diff_V
rxn = ki * N * ne

MMS_rhs = diff(lhs_preDiff, x) - rxn
