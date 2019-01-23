/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <glm\glm.hpp>
#include<glm\gtc\matrix_access.hpp>

using namespace glm;

class Transform
{
private:
	mat3 transformMatrix;

public:
	Transform();
	virtual ~Transform() {}

	void Translate(vec2& translation);
	void Scale(vec2& scaling);
	void Rotate(float angle);

	vec2 getPosition();
	vec2 getScale();
	vec2 getOrientation();
	vec2 getUpDir();
	vec2 getLeftDir();

	mat3 localToWorldMatrix();
	mat3 worldToLocalMatrix();
};