/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "GridStructure.h"

using namespace std;

Grid::Grid(int width, int height, int cellSize) :cellSize(cellSize), width(width), height(height)
{
	columns = width / cellSize;
	rows = height ;
}

Grid::~Grid()
{
	for (auto it = objBuckets.begin(); it != objBuckets.end(); it++)
	{
		it->second.clear();
	}
	objBuckets.clear();
}

Indices Grid::computeCellIndices(vec2 position)
{
	int i = position.x / columns;
	int j = position.y / rows;
	return Indices(i, j);
}

void Grid::registerObject(Entity* obj)
{
	Indices cellInd = computeCellIndices(obj->getPosition());
	objBuckets[cellInd].push_back(obj);
}

void Grid::clearGrid()
{
	objBuckets.clear();
}

vector<Entity*> Grid::getNeighbours(Entity* obj)
{
	vector<Entity*> neighbours;
	Indices cellInd = computeCellIndices(obj->getPosition());
	neighbours.insert(neighbours.end(), objBuckets[cellInd].begin(), objBuckets[cellInd].end());

	Indices E(cellInd.first + 1, cellInd.second + 1);
	if (objBuckets.count(E) > 0)
		neighbours.insert(neighbours.end(), objBuckets[E].begin(), objBuckets[E].end());

	Indices SE(cellInd.first + 1, cellInd.second + 1);
	if (objBuckets.count(SE) > 0)
		neighbours.insert(neighbours.end(), objBuckets[SE].begin(), objBuckets[SE].end());

	Indices S(cellInd.first + 1, cellInd.second + 1);
	if (objBuckets.count(S) > 0)
		neighbours.insert(neighbours.end(), objBuckets[S].begin(), objBuckets[S].end());

	return neighbours;
}