#include "OBB.h"
#include <iostream>

using namespace std;

void OBB::VelocityVerletSolver(float dt)
{
	move(dt * velocity + 0.5f * dt * dt * acceleration);
	vec2 velInBetween = velocity + 0.5f * dt * acceleration;
	velocity = velInBetween + 0.5f * acceleration;
}

void OBB::move(vec2 traslation)
{
	transform.Translate(traslation);
}

void OBB::update(float dt)
{
	VelocityVerletSolver(dt);
}

void OBB::setColor(float r, float g, float b)
{
	color = vec3(r, g, b);
}

vec2 OBB::getPosition()
{
	return transform.getPosition();
}

vec2 OBB::getDirection()
{
	return versor;
}

vec2 OBB::getHalfExtends()
{
	//half height //half width
	return this->radius;
}

//get the orthogonal direction
vec2 OBB::getOrtDirection()
{
	//return dirction with coords (-y, x)
	vec2 ortDirection;

	ortDirection.x = -getDirection().y;
	ortDirection.y = getDirection().x;

	return ortDirection;
}

void OBB::draw(int width, int height)
{
	vec2 position = transform.getPosition();

	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	vec2 mainDir = (getDirection() * radius.x * aspectRatio) / (float)width;
	vec2 orthDir = (getOrtDirection() * radius.y) / (float)height;
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
		(position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_QUADS);
	glColor3f(color.r, color.g, color.b);
	vec2 vertex = 2.0f * (mainDir + orthDir);
	glVertex2f(vertex.x, vertex.y);
	vertex = 2.0f * (-mainDir + orthDir);
	glVertex2f(vertex.x, vertex.y);
	vertex = 2.0f * (-mainDir - orthDir);
	glVertex2f(vertex.x, vertex.y);
	vertex = 2.0f * (mainDir - orthDir);
	glVertex2f(vertex.x, vertex.y);
	glEnd();
}
