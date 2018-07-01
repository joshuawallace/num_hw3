import numpy as np

N2 = .75
O2 = .23
N  = .01
O  = .01
NO = 0.0

k1b = 3e-12
k1f = 2e3
k2f = 2e1

F1=[-k1f*O, 0., k1b*NO, -k1f*N2, k1b*N]
print F1

F2=[0., -k2f*N, -k2f*O2, 0., 0.]
print F2

F3=[k1f*O, k2f*N, -k1b*NO - k2f*O2, k1f*N2, -k1b*N]
print F3

F4=[-k1f*O, k2f*N, k1b*NO + k2f*O2, -k1f*N2, k1b*N]
print F4

F5=[k1f*O, k2f*N, -k1b*NO + k2f*O2, k1f*N2, -k1b*N]
print F5

values,vectors = np.linalg.eig( [F1,F2,F3,F4,F5])
print values
print vectors
