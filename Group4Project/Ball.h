/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/

#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <GL\glut.h>
#include <iostream>
#include "Transform.h"
#include "Entity.h"
#include <algorithm>

using namespace std;
using namespace glm;

class Ball : public Entity
{
private:
	float radius;
	vec2 acceleration;
	vec3 color;
	vec2 velo;
	void VelocityVerletSolver(float dt);
	Transform transform;
	void move(vec2 traslation);

public:
	Ball(float r, vec2& pos, vec2& vel, vec2& acc) : color(vec3(1.0f, 1.0f, 1.0f)),
		radius(r), velo(vel), acceleration(acc)
	{
		move(pos);
	}

	virtual ~Ball() {}

	vec2 getPosition();

	float getRadius();

	vec2 getVelocity();

	void setColor(float r, float g, float b);

	void setVelocity(vec2 vel);

	// --------- Methods that implement the Entity parent class --------- 
	void update(float dt);		
	void draw(int width, int height);
};
