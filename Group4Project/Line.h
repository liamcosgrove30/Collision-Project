/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <GL\glut.h>
#include <iostream>
#include "Transform.h"
#include "Entity.h"
#include <algorithm>

using namespace std;

class Line : public Entity
{
private:
	vec2 point;
	vec2 direction;
public:
	Line(vec2 p, vec2 d) : point(p), direction(d)
	{

	}

	virtual ~Line()
	{

	}

	vec2 getPoint();

	vec2 getDirection();
	void update(float dt);
	void draw(int width, int height);
};