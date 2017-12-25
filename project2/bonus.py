import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys, os, glob

if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} <input file> <solution prefix>'.format(sys.argv[0]))
    sys.exit(0)

input_file = sys.argv[1]
sol_file = sys.argv[2]

with open(input_file,'r') as f:
	xlen, ylen, h = (float(x) for x in f.readline().split());
	tc, th = (float(x) for x in f.readline().split());


print("Input file processed: " + input_file)

files = glob.glob(sol_file+"*")
filenames = [os.path.split(x)[1] for x in files]

y, x = np.mgrid[0.:ylen+h:h, 0.:xlen+h:h]

fig = plt.figure()

ims = []
for file in filenames:
	sol = np.loadtxt(file)
	ims.append((plt.pcolor(x, y, sol, cmap='jet', vmin=tc, vmax=th),))

im_ani = animation.ArtistAnimation(fig, ims, interval=200, repeat_delay=1000,
                                   blit=True)

plt.show()