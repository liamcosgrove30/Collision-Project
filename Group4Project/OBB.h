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

class OBB : public Entity
{
private:
	vec2 versor;
	vec2 radius;
	vec2 velocity;
	vec2 acceleration;
	vec3 color;
	void VelocityVerletSolver(float dt);
	Transform transform;
	void move(vec2 traslation);

public:
	OBB(vec2 c, vec2& versor, vec2& halfExtends, vec2& vel, vec2& acc) : color(vec3(1.0f, 1.0f, 1.0f)),
		radius(halfExtends), velocity(vel), acceleration(acc), versor(versor)
	{
		move(c);
	}

	virtual ~OBB() {}

	vec2 getPosition();

	vec2 getDirection();

	vec2 getOrtDirection();

	vec2 getHalfExtends();

	void setColor(float r, float g, float b);

	// --------- Methods that implement the Entity parent class --------- 
	void update(float dt);
	void draw(int width, int height);
};
