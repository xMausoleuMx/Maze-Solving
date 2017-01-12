#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void readMap(string filename);
void printMap();
vector<vector<int>> getCoords();

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

}

vector<vector<int>> getCoords()
{
	for (int i = 0; i < maze.size(); i++)
	{
		for (int z = 0; z < maze[i].size(); z++)
			if (maze[i][z] >= '0' || maze[i][z] <= '9')
			{

			}
		std::cout << endl;
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