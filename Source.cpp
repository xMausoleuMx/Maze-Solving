#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void readMap(string filename);
void printMap();
vector<vector<int>> getCoords();
void initialSolve(vector<vector<int>> coords);
int pathTo(vector<int> start, vector<int> end, int type);

vector<vector<char>> maze;

int main()
{
	string filename;
	std::cout << "Enter in the filename of the maze you want solved\n";
	std::cin >> filename;
	readMap(filename);
	printMap();
	vector<vector<int>> coords;
	coords = getCoords();
	initialSolve(coords);
}

vector<vector<int>> getCoords()
{
	vector<vector<int>> coords;
	for (int i = 0; i < maze.size(); i++)
	{
		for (int z = 0; z < maze[i].size(); z++)
			if (maze[i][z] >= '0' && maze[i][z] <= '9')
			{
				if (maze[i][z] == '0')
					coords.insert(coords.begin(), { maze[i][z], i, z });
				else
					coords.push_back({ maze[i][z], i, z});
				cout << "x:" << i << " y:" << z << " character: " << maze[i][z] << endl;
			}
	}
	return coords;
}

void initialSolve(vector<vector<int>> coords)
{
	vector<int> distances;
	vector<vector<int>> bestOrder;
	bestOrder.push_back(coords[0]);
	int minDistance = INT_MAX, holder = 0, smallest;
	for (int i = 0; i < coords.size(); i++)
	{
		for (int z = i+1; z < coords.size(); z++)
		{
			holder = pathTo(coords[i], coords[z], 0);
			if (holder < minDistance)
			{
				minDistance = holder;
				smallest = z;
			}
		}
		bestOrder.push_back(coords[smallest]);
		coords.insert(coords.begin()+i + 1, coords[smallest]);
		coords.erase(coords.begin()+smallest+1);
	}
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

int pathTo(vector<int> start, vector<int> end, int type)
{
	int distances [] = {0,0,0,0};
	if (start[1] == end[1] && start[2] == end[2])
		return 0;
	if ((start[1] + 1 < maze.size()) && (maze[start[1] + 1][start[2]] != '#'))
		distances[0] = pathTo({ start[0], start[1] + 1, start[2] }, end, type);
	else if ((start[2] + 1 <maze[0].size()) && (maze[start[1]][start[2]+1] != '#'))
		distances[1] = pathTo({ start[0], start[1], start[2] + 1 }, end, type);
	else if ((start[1] - 1 >= 0 ) && (maze[start[1] - 1][start[2]] != '#'))
		distances[2] = pathTo({ start[0], start[1] - 1, start[2] }, end, type);
	else if ((start[2] - 1 >= 0 ) && (maze[start[1]][start[2]-1] != '#'))
		distances[3] = pathTo({ start[0], start[1], start[2] - 1 }, end, type);
	else
		return -1;

	if()
}