# -*- coding: utf-8 -*-
"""
Created on Fri Oct 16 22:13:43 2020

@author: w'm'h
"""
from sympy import *
init_session()
expand((x + y)**5)
factor(x**6 - 1)
pi.n(100)
plot(besselj(0, x), besselij(1, x), (x, 0, 10))
diff(x * sin(y), x, y)
integrate(cos(x)**2, x)
integrate(exp(-x**2), (x, -oo, oo))
Sum(k**3, (k, 0, m)).doit().factor()
dsolve(f(x).diff() + f(x) - x, f(x)).simplify()
limit(sin(x) / x, x, 0)
