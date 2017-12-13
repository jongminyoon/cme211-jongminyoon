import sys

import airfoil

if len(sys.argv) < 2:
    print('Usage:')
    print('  python3 {} <airfoil data directory>'.format(sys.argv[0]))
    sys.exit(0)

inputdir = sys.argv[1]

try:
    a = airfoil.Airfoil(inputdir)
except RuntimeError as e:
    print('ERROR: {}'.format(e))
    sys.exit(2)

print(a)
