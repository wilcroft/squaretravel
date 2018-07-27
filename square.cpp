#include <iostream>
#include <vector>
#include <iomanip>

enum dir_opt{
	N,
	S,
	E,
	W,
	NE,
	NW,
	SE,
	SW
};

int count (std::vector<std::vector<int> > map){
	int c=0;
	for (int i=0; i<5; i++)
		for (int j=0; j<5; j++)
			c += map[i][j]>0 ? 1:0;
	if (c==25){
		for (int i=0; i<5;i++){
			for(int j=0; j<5; j++)
				std::cout << std::setw(3) << map[i][j];
			std::cout << std::endl;
		}
		std::cout << std::setw(0) << "---------------" << std::endl;
	}
	return c;
}

int traverse (std::vector<std::vector<int> > map, enum dir_opt dir, int x, int y){
	int newx, newy;
	switch (dir){
		case N :
			newx = x;
			newy = y-3;
			break;
		case S :
			newx = x;
			newy = y+3;
			break;
		case E :
			newx = x+3;
			newy = y;
			break;
		case W :
			newx = x-3;
			newy = y;
			break;
		case NE :
			newx = x+2;
			newy = y-2;
			break;
		case NW :
			newx = x-2;
			newy = y-2;
			break;
		case SE :
			newx = x+2;
			newy = y+2;
			break;
		case SW:
			newx = x-2;
			newy = y+2;
			break;
	}
	if (newx >=5 || newy >=5 || newx <0 || newy < 0 || map[newx][newy]!=0)
		return count(map);
	else{
		map[newx][newy] = map[x][y]+1;
		if (count(map)==25) return 25;
		return std::max (std::max (std::max(traverse(map,N,newx, newy),traverse(map,S,newx, newy)),std::max(traverse(map,E,newx, newy),traverse(map,W,newx, newy))),
				std::max(std::max(traverse(map,NE,newx, newy),traverse(map,NW,newx, newy)),std::max(traverse(map,SE,newx, newy),traverse(map,SW,newx, newy))));
	}
}	

int main (void){
//	bool map [5][5];
	std::vector<std::vector<int> > map;
	map.resize(5);
	int best [3][3];
	char c;

	for(int i=0; i<5; i++){
		map[i].resize(5);
		for(int j=0; j<5; j++)
			map[i][j]=false;
	}

	for (int i=0; i<3; i++)
		for (int j=0; j<=i; j++){
			map[i][j] = 1;
			best[i][j] = std::max (std::max (std::max(traverse(map,N,i, j),traverse(map,S,i, j)),std::max(traverse(map,E,i, j),traverse(map,W,i, j))),
					                std::max(std::max(traverse(map,NE,i, j),traverse(map,NW,i, j)),std::max(traverse(map,SE,i, j),traverse(map,SW,i, j))));
			map[i][j] = 0;
			std::cout << std::endl;
		}

	for (int i=0; i<3; i++){
		for (int j=0; j<=i; j++)
			std::cout << best[i][j] << " ";
		std::cout << std::endl;
	}

	return 0;
}
