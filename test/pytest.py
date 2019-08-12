import matplotlib.pyplot as plt
import numpy as np


def hm(N):
    n = np.linspace(0, N, N)
    return 0.53836-0.46164*np.cos(2*np.pi*n/(N-1))


plt.plot(hm(512))
plt.show()
