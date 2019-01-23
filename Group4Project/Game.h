/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/

// (c) Marco Gilardi, 2017
#include <vector>
#include <GL\glut.h>
#include "GameWindow.h"
#include "Entity.h"
#include "Ball.h"
#include "AABB.h"
#include "OBB.h"
#include "Paddle.h"
#include "GridStructure.h"
using namespace std;
#pragma once

class Game
{
private:
	vector<Entity*> gameEntities;
	GameWindow* window;
	void CheckCollisions();

	Grid* grid;
	Paddle* paddle1;
	Paddle* paddle2;


public:
	void Load();
	void Render();
	void Inputs();
	void Update(float dt);
	void ReshapeWindow(int weigth, int height);

	//added by me
	bool CircleCircleCollision(Ball* ballPointer1, Ball* ballPointer2);
	void ClosestPointAABB(vec2& r, AABB& b, vec2& c);
	void ClosestPointPaddle(vec2& r, Paddle& b, vec2& c);
	bool AABBCollision(AABB& A, AABB& B);
	bool PaddleAABBCollision(Paddle& paddle, AABB& aabb);
	int aabbCircle(AABB& a, Ball& b, vec2& c);
	int PaddleBallCollision(Paddle& paddle, Ball& ball, vec2& c);

	bool isKeyDown(int key);
	

	Game() {};
	virtual ~Game()
	{
		for (vector<Entity*>::iterator it = gameEntities.begin(); it < gameEntities.end(); it++)
		{
			delete(*it);
		}

	}
};