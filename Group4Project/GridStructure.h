/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <map>
#include<vector>
#include <glm\glm.hpp>
#include "Entity.h"

using namespace std;
using namespace glm;

typedef pair<int, int> Indices;

class Grid {
public:
	Grid(int width, int height, int cell);
	virtual ~Grid();
	void registerObject(Entity* obj);
	vector<Entity*> getNeighbours(Entity* obj);
	void clearGrid();
private: 
	int cellSize, width, height;
	int columns, rows;
	map<Indices, vector<Entity*>> objBuckets;
	Indices computeCellIndices(vec2 position);
};