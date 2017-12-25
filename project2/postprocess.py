import sys
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} <input file> <solution file>'.format(sys.argv[0]))
    sys.exit(0)

input_file = sys.argv[1]
sol_file = sys.argv[2]

with open(input_file,'r') as f:
	xlen, ylen, h = (float(x) for x in f.readline().split());

print("Input file processed: " + input_file)

sol = np.loadtxt(sol_file)
meantemp = np.mean(sol[:,1:])
print("Mean Temperature: {:8.5f}".format(meantemp))

interpolation = np.zeros(sol.shape[1])
ygrid = range(sol.shape[0])
for i in range(sol.shape[1]):
	f = interp1d(sol[:,i],ygrid, kind='cubic')
	interpolation[i] = f(meantemp)

# generate 2 2d grids for the x & y bounds
y, x = np.mgrid[0.:ylen+h:h, 0.:xlen+h:h]
sol_min, sol_max = np.abs(sol).min(), np.abs(sol).max()

plt.pcolor(x, y, sol, cmap='jet', vmin=sol_min, vmax=sol_max)
plt.title('pcolor')
plt.axis([x.min(), x.max(), y.min(), y.max()])
plt.colorbar()
plt.plot(np.arange(0.,xlen+h,h), interpolation*h, 'k')
plt.show()
