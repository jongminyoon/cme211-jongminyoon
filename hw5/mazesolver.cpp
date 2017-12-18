#include <iostream>
#include <fstream>
#include <string>

#define MAX 256 // maximum size of a maze

int main (int argc, char *argv[]){
	if (argc < 3) {
		std::cout << "Usage:" << std::endl;
		std::cout << "  " << argv[0] << " <maze file> <solution file>" << std::endl;
		return 0;
	}

	std::string maze_name = argv[1];
	std::string sol_name = argv[2];

	int maze[MAX][MAX] = {0};

	int nrows = 0, ncols = 0;


	// read the maze file and set 1's on the walls
	std::ifstream maze_file(maze_name);
	if (maze_file.is_open()) {
		maze_file >> nrows >> ncols;
		if (nrows > MAX or ncols > MAX) {
			std::cout << "maze size too large!" << std::endl;
			return 0;
		}
		int row, col;
		while (maze_file >> row >> col){
			maze[row][col] = 1;
		}
		maze_file.close();
	}

	// set the outside of the maze to be 1
	for (int i = 0 ; i < MAX ; i++ ) {
		for (int j = 0 ; j < MAX ; j++) {
			if (i >= nrows or j>= ncols) maze[i][j] = 1;
		}
	}
	// write the solution
	std::ofstream sol_file(sol_name);
	if (sol_file.is_open()) {
		
		// find the entrance
		int r = 0, c = 0, d = 1;
		while (true) {
			if (maze[r][c] == 0) break;
			c++;
		}
		sol_file << r << " " << c << std::endl;

		// direction using the right-hand wall following algorithm
		int dir[4][4][2] = {{{-1,0},{0,-1},{1,0},{0,1}}, // when moving left
							{{0,-1},{1,0},{0,1},{-1,0}}, // moving down
							{{1,0},{0,1},{-1,0},{0,-1}}, // moving right
							{{0,1},{-1,0},{0,-1},{1,0}}}; // moving up

		// find the next step
		while (r < nrows-1) {
			for (int i = 0 ; i < 4 ; i++) {
				int tempr = r + dir[d][i][0];
				int tempc = c + dir[d][i][1];
				// std::cout << tempr << " " << tempc << std::endl;
				if (tempr >=0 and tempc >=0 and maze[tempr][tempc] == 0) {
					r = tempr; c = tempc; d = (d+3+i)%4;
					sol_file << r << " " << c << std::endl;
					break;
				}
			}
		}

		sol_file.close();
	}

	return 0;
}