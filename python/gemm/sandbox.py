import numpy as np

W = np.ndarray(shape=(8, 32), dtype=int)
W.fill(1)

A = np.ndarray(shape=(32, 4), dtype=int)
A.fill(1)
print(W, A)

print(np.dot(W,A))

