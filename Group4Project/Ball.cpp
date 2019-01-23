/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Ball.h"
#include <iostream>

using namespace std;

void Ball::VelocityVerletSolver(float dt)
{
	move(dt * velo + 0.5f * dt * dt * acceleration);
	vec2 velInBetween = velo + 0.5f * dt * acceleration;
	velo = velInBetween + 0.5f * acceleration;
}

void Ball::move(vec2 traslation)
{
	transform.Translate(traslation);
}

void Ball::update(float dt)
{
	VelocityVerletSolver(dt);
}

void Ball::draw(int width, int height) // coordinates need to be in space (-aspectRatio, aspectRatio)x(-1, 1)
{
	vec2 position = transform.getPosition();
	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
		(position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

																  // Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color.r, color.g, color.b);								// Cyan
	glVertex2f(0.0f, 0.0f);										// Center of circle
	int numSegments = 100;
	float angle;
	for (int i = 0; i <= numSegments; i++) {					// Last vertex same as first vertex
		angle = i * 2.0f * pi<float>() / numSegments;			// 360 deg for all segments
		glVertex2f(cos(angle) * (2.0f * radius / width)* aspectRatio,
			sin(angle) * (2.0f * radius / height));
	}
	glEnd();
}

void Ball::setColor(float r, float g, float b)
{
	color = vec3(r, g, b);
}

void Ball::setVelocity(vec2 velocity)
{
	velo = velocity;
}

vec2 Ball::getPosition()
{
	return transform.getPosition();
}

float Ball::getRadius()
{
	return radius;
}

vec2 Ball::getVelocity()
{
	return velo;
}
