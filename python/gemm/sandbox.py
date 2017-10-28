import numpy as np

W = np.ndarray(shape=(1, 32), dtype=int)
W.fill(-1)

A = np.ndarray(shape=(32, 1), dtype=int)
A.fill(-1)
print(W, A)

print(np.dot(W,A))

