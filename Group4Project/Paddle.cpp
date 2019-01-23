/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Paddle.h"
#include <iostream>
#include <Windows.h>
#include <gl/glut.h>

using namespace std;

void Paddle::VelocityVerletSolver(float dt)
{
	move(dt * velocity + 0.5f * dt * dt * acceleration);
	vec2 velInBetween = velocity + 0.5f * dt * acceleration;
	velocity = velInBetween + 0.5f * acceleration;
}

void Paddle::move(vec2 traslation)
{
	transform.Translate(traslation);
}

void Paddle::update(float dt)
{
	VelocityVerletSolver(dt);
}

void Paddle::draw(int width, int height)
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


void Paddle::setColor(float r, float g, float b)
{
	color = vec3(r, g, b);
}

vec2 Paddle::getPosition()
{
	return transform.getPosition();
}

vec2 Paddle::getRadius()
{
	return radius;
}

vec2 Paddle::setVelocity(vec2 vel)
{
	velocity = vel;
	return velocity;
}

vec2 Paddle::setAcc(vec2 acc)
{
	acceleration = acc;
	return acceleration;
}

vec2 Paddle::getAcc()
{
	return acceleration;
}

vec2 Paddle::getVelocity()
{
	return velocity;
}

