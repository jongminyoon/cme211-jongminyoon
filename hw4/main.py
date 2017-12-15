import sys

import truss

if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} [joints file] [beams file] [optional plot output file]'.format(sys.argv[0]))
    sys.exit(0)

t = truss.Truss(sys.argv[1:])
print(t)
