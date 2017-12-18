import sys
import numpy as np
from scipy.sparse import csr_matrix

if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} <maze file> <solution file>'.format(sys.argv[0]))
    sys.exit(0)

maze_file = sys.argv[1]
sol_file = sys.argv[2]

temp = np.loadtxt(maze_file, dtype=np.int16)
maze_size = temp[0,:]
maze = csr_matrix((np.ones(temp[1:,:].shape[0], dtype=np.int8), (temp[1:,0], temp[1:,1])), shape=maze_size, dtype=np.int8)
sol = np.loadtxt(sol_file, dtype=np.int16)

if sol[0,0] != 0 or maze[tuple(sol[0,:])] == 1:
	print("Solution is invalid! : a wrong starting point")
	sys.exit(0)

for i,x in enumerate(sol[:-1,:]):
	if sum(abs(sol[i,:]-sol[i+1,:])) != 1:
		print("Solution is invalid! : you move more than one position or does not move at a time")
		sys.exit(0)
	if maze[tuple(sol[i,:])] == 1:
		print("Solution is invalid! : you move to a wall")
		print(sol[i,:])
		sys.exit(0)

if sol[-1,0] != maze_size[0]-1 :	
	print("Solution is invalid! : a wrong final point")
	sys.exit(0)	

print("Solution is valid!")



# import sys, scipy.sparse
# import numpy as np

# if len(sys.argv) < 3:
#     print('Usage:')
#     print('  python3 {} <maze file> <solution file>'.format(sys.argv[0]))
#     sys.exit(0)

# maze_file = sys.argv[1]
# sol_file = sys.argv[2]

# temp = np.loadtxt(maze_file, dtype=np.int8)
# maze_size = temp[0,:]
# maze = temp[1:,:]
# sol = np.loadtxt(sol_file, dtype=np.int8)

# if sol[0,0] != 0 or any(np.array_equal(x,sol[0,:]) for x in maze):
# 	print("Solution is invalid! : a wrong starting point")
# 	sys.exit(0)

# for i,x in enumerate(sol[:-1,:]):
# 	if sum(abs(sol[i,:]-sol[i+1,:])) != 1:
# 		print("Solution is invalid! : you move more than one position or does not move at a time")
# 		sys.exit(0)
# 	if any(np.array_equal(x,sol[i+1,:]) for x in maze):
# 		print("Solution is invalid! : you move to a wall")
# 		sys.exit(0)

# if sol[-1,0] != maze_size[0]-1 :	
# 	print("Solution is invalid! : a wrong final point")
# 	sys.exit(0)	

# print("Solution is valid!")
