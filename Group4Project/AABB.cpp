/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "AABB.h"
#include <iostream>

using namespace std;

void AABB::VelocityVerletSolver(float dt)
{
	move(dt * velocity + 0.5f * dt * dt * acceleration);
	vec2 velInBetween = velocity + 0.5f * dt * acceleration;
	velocity = velInBetween + 0.5f * acceleration;
}

void AABB::move(vec2 traslation)
{
	transform.Translate(traslation);
}

void AABB::update(float dt)
{
	VelocityVerletSolver(dt);
}

void AABB::draw(int width, int height)
{
	vec2 position = transform.getPosition();

	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
		(position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_QUADS);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(2 * radius.x * aspectRatio / width, 2 * radius.y / height);
	glVertex2f(-2 * radius.x * aspectRatio / width, 2 * radius.y / height);
	glVertex2f(-2 * radius.x * aspectRatio / width, -2 * radius.y / height);
	glVertex2f(2 * radius.x * aspectRatio / width, -2 * radius.y / height);
	glEnd();
}


void AABB::setColor(float r, float g, float b)
{
	color = vec3(r, g, b);
}

vec2 AABB::getPosition()
{
	return transform.getPosition();
}

vec2 AABB::getRadius()
{
	return radius;
}

vec2 AABB::setVelocity(vec2 vel)
{
	velocity = vel;
	return velocity;
}

vec2 AABB::getVelocity()
{
	return velocity;
}
