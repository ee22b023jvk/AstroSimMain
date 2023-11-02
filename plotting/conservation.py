import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys

data = np.genfromtxt("AstroSimMain/momentum.txt", delimiter = ",", skip_header = 1,dtype = float)

x = np.array(data[:,0])
y = np.array(data[:,1])
z = np.array(data[:,2])

t = list(range(len(x)))


plt.plot(t, x)
plt.show()

plt.plot(t, y)
plt.show()

plt.plot(t, z)
plt.show()

del x, y, z, data

data = np.genfromtxt("AstroSimMain/energy.txt", delimiter = ",", skip_header = 1,dtype = float)

x = np.array(data)

plt.plot(t, x)
plt.show()

