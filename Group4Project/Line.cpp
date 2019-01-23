/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <GL\glut.h>
#include <iostream>
#include "Transform.h"
#include "Entity.h"
#include <algorithm>
#include "Line.h"

using namespace std;

vec2 Line::getPoint()
{
	return point;
}

vec2 Line::getDirection()
{
	return direction;
}

void Line::update(float dt) {};
void Line::draw(int width, int height) {
};