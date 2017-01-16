#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct coord{
	int x;
	int y;
};

void readMap(string filename);
void printMap();
vector<coord> getCoords();
void initialSolve(vector<coord> coords);
vector<coord> pathTo(coord start, coord end);

vector<vector<char>> maze;
vector<vector<char>> originalMaze;

int main()
{
	string filename;
	std::cout << "Enter in the filename of the maze you want solved\n";
	std::cin >> filename;
	readMap(filename);
	originalMaze = maze;
	printMap();
	vector<coord> coords;
	coords = getCoords();
	initialSolve(coords);
}

vector<coord> getCoords()
{
	vector<coord> coords;
	coord holder;
	for (int i = 0; i < maze.size(); i++)
	{
		for (int z = 0; z < maze[i].size(); z++)
			if (maze[i][z] >= '0' && maze[i][z] <= '9')
			{
				holder.x = i;
				holder.y = z;
				if (maze[i][z] == '0')
					coords.insert(coords.begin(), holder);
				else
					coords.push_back(holder);
				cout << "x:" << i << " y:" << z << " character: " << maze[i][z] << endl;
			}
	}
	return coords;
}

void initialSolve(vector<coord> coords)
{
	vector<int> distances;
	vector<coord> bestOrder;
	bestOrder.push_back(coords[0]);
	int minDistance = INT_MAX, smallest;
	vector<coord> holder;
	for (int i = 0; i < coords.size(); i++)
	{
		for (int z = i+1; z < coords.size(); z++)
		{
			holder = pathTo(coords[i], coords[z]);
			if (holder.size() < minDistance)
			{
				minDistance = holder.size();
				smallest = z;
			}
		}
		bestOrder.push_back(coords[smallest]);
		coords.insert(coords.begin()+i + 1, coords[smallest]);
		coords.erase(coords.begin()+smallest+1);
	}
	for (int i = 0; i < bestOrder.size(); i++)
		std::cout << bestOrder[i].x << bestOrder[i].y << endl;
}


void readMap(string filename)
{
	fstream reader;
	reader.open(filename);
	string holder;
	int counter = 0;
	while (std::getline(reader, holder))
	{
		vector<char> line;
		for (int i = 0; i < holder.size(); i++)
			line.push_back(holder[i]);
		maze.push_back(line);
	}
}

void printMap()
{
	for (int i = 0; i < maze.size(); i++)
	{
		for (int z = 0; z < maze[i].size(); z++)
			std::cout << maze[i][z];
		std::cout << endl;
	}
}

vector<coord> pathTo(coord start, coord end)
{
	std::cout << ".";
	vector<coord> pathNorth, pathSouth, pathEast, pathWest;
	if (start.x == end.x && start.y == end.y){
		pathNorth.push_back(start);
		return pathNorth;
	}
	if ((start.x + 1 < maze.size()) && (maze[start.x + 1][start.y] != '#')){
		maze[start.x][start.y] = '#';
		pathEast = pathTo({ start.x + 1, start.y }, end);
		if (pathEast.size() != 0)
			pathEast.insert(pathEast.begin(), start);
		
	}
	else if ((start.y + 1 < maze[0].size()) && (maze[start.x][start.y + 1] != '#')){
		maze[start.x][start.y] = '#';
		pathNorth = pathTo({ start.x, start.y + 1 }, end);
		if (pathNorth.size() != 0)
			pathNorth.insert(pathNorth.begin(), start);
		
	}
	else if ((start.x - 1 >= 0) && (maze[start.x - 1][start.y] != '#')){
		maze[start.x][start.y] = '#';
		pathWest = pathTo({ start.x - 1, start.y }, end);
		if (pathWest.size() != 0)
			pathWest.insert(pathWest.begin(), start);
	}
	else if ((start.y - 1 >= 0) && (maze[start.x][start.y - 1] != '#')){
		maze[start.x][start.y] = '#';
		pathSouth = pathTo({ start.x, start.y - 1 }, end);
		if(pathSouth.size() != 0)
			pathSouth.insert(pathSouth.begin(), start);
	}
	else
		return pathNorth;

	if (maze[start.x][start.y] == '#');
		maze[start.x][start.y] = '.';
	if (pathEast.size() > pathWest.size()){
		if (pathNorth.size() > pathSouth.size())
			return((pathSouth.size() > pathWest.size()) ? pathWest : pathSouth);
		else
			return((pathNorth.size() > pathWest.size()) ? pathWest : pathNorth);
	}
	else{
		if (pathNorth.size() > pathSouth.size())
			return((pathSouth.size() > pathEast.size()) ? pathEast : pathSouth);
		else
			return((pathNorth.size() > pathEast.size()) ? pathEast : pathNorth);
	}
}