/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
// (c) Marco Gilardi, 2017
#include "Game.h"
#include <random>
#include <time.h>
#include <Windows.h>

using namespace std;
using namespace glm;

void Game::Load()
{
	window = new GameWindow("Group 4 Project", 640, 800, 50, 50);
	
	grid = new Grid(window->getWidth(), window->getHeight(), 3);

	srand(time(NULL));
	//this is number of obstacles on the screen, reduce to make program run smoother
	int numObs = 100;

	Ball* testBall = new  Ball(10.0f, vec2(320, 240), vec2(0, 0), vec2(0, 0));
	testBall->setColor(0.0f, 1.0f, 1.0f);
	testBall->setVelocity(vec2(0,-80));
	gameEntities.push_back(testBall);

	for(int i =0;i<numObs;i++)
	{ 
		vec2 position = vec2(rand() % (window->getWidth() - 40) + 20, rand() % (window->getHeight() - 80) + 40);
		AABB* Wall = new AABB(vec2(5, 5), vec2(position), vec2(30, 0), vec2(0, 0));
		Wall->setColor(1.0f, 1.0f, 1.0f);
		gameEntities.push_back(Wall);
		grid->registerObject(Wall);
	}

	AABB* leftWall = new AABB(vec2(10, 1000), vec2(-70, 30), vec2(0, 0), vec2(0, 0));
	leftWall->setColor(1.0f, 1.0f, 1.0f);
	gameEntities.push_back(leftWall);
	grid->registerObject(leftWall);

	AABB* rightWall = new AABB(vec2(10, 1000), vec2(730, 30), vec2(0, 0), vec2(0, 0));
	rightWall->setColor(1.0f, 1.0f, 1.0f);
	gameEntities.push_back(rightWall);
	grid->registerObject(rightWall);

	paddle1 = new Paddle(vec2(80, 10), vec2(320, 5), vec2(0, 0), vec2(0, 0));
	paddle1->setColor(1.0f, 1.0f, 1.0f);
	gameEntities.push_back(paddle1);
	grid->registerObject(paddle1);

	paddle2 = new Paddle(vec2(80, 10), vec2(320, 790), vec2(0, 0), vec2(0, 0));
	paddle2->setColor(1.0f, 1.0f, 1.0f);
	gameEntities.push_back(paddle2);
	grid->registerObject(paddle2);
}

void Game::Update(float dt)
{
	if(isKeyDown(VK_LEFT))
	{
		paddle1->setAcc(vec2(-5, 0));
	}
	 else if (isKeyDown(VK_RIGHT))
	{
		 paddle1->setAcc(vec2(5, 0));
	}
	 else if(isKeyDown(VK_SPACE))
	 {
		 paddle1->setAcc(vec2(0, 0));
		 paddle1->setVelocity(vec2(0, 0));
	 }
	 else
	 {
		 paddle1->setAcc(vec2(0, 0));
	 }
	

	if (isKeyDown(0x44))
	{
		paddle2->setAcc(vec2(5, 0));
	}
	else if (isKeyDown(0x41))
	{
		paddle2->setAcc(vec2(-5, 0));
	}
	else
	{
		paddle2->setAcc(vec2(0, 0));
	}

	grid->clearGrid();

	for (vector<Entity*>::iterator it = gameEntities.begin(); it < gameEntities.end(); it++)
	{
		(*it)->update(dt);
		grid->registerObject(*it);
	}
	CheckCollisions();
}

//Brute force collision check
void Game::CheckCollisions()
{
	for (vector<Entity*>::iterator it = gameEntities.begin(); it < gameEntities.end() - 1; it++)
	{
		Ball* ball = dynamic_cast<Ball*> (*it);
		if (ball != nullptr)
		{
			vector<Entity*>objs = grid->getNeighbours(ball);

			for (auto it1 = objs.begin(); it1 != objs.end(); ++it1)
			{
				if (*it != *it1)
				{			
					AABB* aabb = dynamic_cast<AABB*>(*it1);
					if (aabb != nullptr)
					{
						if (aabbCircle(*aabb, *ball, vec2()))
						{
							ball->setColor(1.0, 0.0, 0.0);
							ball->setVelocity(-ball->getVelocity());
						}
					}
					
					Paddle* paddle = dynamic_cast<Paddle*>(*it1);
					if (paddle != nullptr)
					{
						if (PaddleBallCollision(*paddle, *ball, vec2()))
						{
							ball->setColor(0.0, 1.0, 0.0);
							ball->setVelocity(-ball->getVelocity());
						}
					}
				}
			}
		}
		


		AABB* wall = dynamic_cast<AABB*> (*it);
		if (wall != nullptr)
			{
				vector<Entity*>objs = grid->getNeighbours(wall);

				for (auto it1 = objs.begin(); it1 != objs.end(); it1++)
				{
					if (*it != *it1)
					{
						AABB* aabb = dynamic_cast<AABB*>(*it1);
						if (aabb != nullptr)
						{
							if (AABBCollision(*aabb, *wall))
							{
								wall->setColor(1.0, 0.0, 0.0);
								wall->setVelocity(-wall->getVelocity());
							}
						}
					}
				}
			}


		if (paddle1 != nullptr)
			{
				vector<Entity*>objs = grid->getNeighbours(paddle1);

				for (auto it1 = objs.begin(); it1 != objs.end(); it1++)
				{
					if (*it != *it1)
					{
						AABB* aabb1 = dynamic_cast<AABB*>(*it1);
						if (aabb1 != nullptr)
						{
							if (PaddleAABBCollision(*paddle1, *aabb1))
							{
								cout << true;
								paddle1->setColor(0.0f, 1.0f, 0.0f);
								cout << "Before" << paddle1->getVelocity().x << endl;
								paddle1->setVelocity(-paddle1->getVelocity());
								cout << "After" << paddle1->getVelocity().x << endl;
								paddle1->setAcc(vec2(0, 0));
							}
							/*for (auto it2 = objs.begin(); it2!= objs.end(); it2++)
							{
								if (*it != *it2)
								{
									AABB* aabb2 = dynamic_cast<AABB*>(*it2);
									if (aabb2 != nullptr)
									{
										if (PaddleAABBCollision(*paddle1, *aabb2))
										{
											cout << true;
											paddle1->setColor(0.0f, 1.0f, 0.0f);
											cout << "Before" << paddle1->getVelocity().x << endl;
											paddle1->setVelocity(-paddle1->getVelocity());
											cout << "After" << paddle1->getVelocity().x << endl;
											paddle1->setAcc(vec2(0, 0));
										}
									}
								}
							}*/
						}
					}
				}
			}

		if (paddle2 != nullptr)
			{
				vector<Entity*>objs = grid->getNeighbours(paddle2);
				for (auto it1 = objs.begin(); it1 != objs.end(); it1++)
				{
					if (*it != *it1)
					{
						AABB* aabb2 = dynamic_cast<AABB*>(*it1);
						if (aabb2 != nullptr)
						{
							if (PaddleAABBCollision(*paddle2, *aabb2))
							{
								cout << true;
								paddle2->setColor(0.0f, 1.0f, 0.0f);
								cout << "Before" << paddle2->getVelocity().x << endl;
								paddle2->setVelocity(-paddle2->getVelocity());
								cout << "After" << paddle2->getVelocity().x << endl;
								paddle2->setAcc(vec2(0, 0));
							}
							/*for (vector<Entity*>::iterator it2 = it1 + 1; it2 < gameEntities.end(); it2++)
							{
								AABB* aabb2 = dynamic_cast<AABB*>(*it2);
								if (aabb2 != nullptr)
								{
									if (PaddleAABBCollision(*paddle2, *aabb2))
									{
										cout << true;
										paddle2->setColor(0.0f, 1.0f, 0.0f);
										cout << "Before" << paddle2->getVelocity().x << endl;
										paddle2->setVelocity(-paddle2->getVelocity());
										cout << "After" << paddle2->getVelocity().x << endl;
										paddle2->setAcc(vec2(0, 0));
									}
								}
							}*/
						}
					}
				}
			}
	}
}

void Game::ReshapeWindow(int width, int height)
{
	window->Reshape(width, height);
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix
	for (vector<Entity*>::iterator it = gameEntities.begin(); it < gameEntities.end(); it++)
	{
		(*it)->draw(window->getWidth(), window->getHeight());
	}

	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}

void Game::Inputs()
{
}


bool Game::isKeyDown(int key)
{
	bool result = GetAsyncKeyState(key) & (1 << 16);
	return (GetAsyncKeyState(key) & (1 << 16));
}

bool Game::CircleCircleCollision(Ball* ballPointer1, Ball* ballPointer2)
{
	if (glm::distance(ballPointer1->getPosition(), ballPointer2->getPosition()) < ballPointer1->getRadius() + ballPointer2->getRadius())
	{
		return true;
	}
	return false;
}

void Game::ClosestPointAABB(vec2& r, AABB& b, vec2& c)
{
	vec2 minimum(b.getPosition() - b.getRadius());
	vec2 maximum(b.getPosition() + b.getRadius());

	for (int i = 0; i < 2; i++)
	{
		float v = r[i];
		if (v < minimum[i])
			v = minimum[i];
		if (v > maximum[i])
			v = maximum[i];
		c[i] = v;
	}
}

void Game::ClosestPointPaddle(vec2& r, Paddle& b, vec2& c)
{
	vec2 minimum(b.getPosition() - b.getRadius());
	vec2 maximum(b.getPosition() + b.getRadius());

	for (int i = 0; i < 2; i++)
	{
		float v = r[i];
		if (v < minimum[i])
			v = minimum[i];
		if (v > maximum[i])
			v = maximum[i];
		c[i] = v;
	}
}

int Game::aabbCircle(AABB& aabb, Ball& ball, vec2& c)
{
	ClosestPointAABB(ball.getPosition(), aabb, c);
	vec2 v = c - ball.getPosition();
	return length(v) <= ball.getRadius();
}

int Game::PaddleBallCollision(Paddle& paddle, Ball& ball, vec2& c)
{
	ClosestPointPaddle(ball.getPosition(), paddle, c);
	vec2 v = c - ball.getPosition();
	return length(v) <= ball.getRadius();
}

bool Game::AABBCollision(AABB& A, AABB& B)
{
	if (abs(A.getPosition().x - B.getPosition().x) > (A.getRadius().x + B.getRadius().x)) return false;
	if (abs(A.getPosition().y - B.getPosition().y) > (A.getRadius().y + B.getRadius().y)) return false;
	return true;
}

bool Game::PaddleAABBCollision(Paddle& paddle, AABB& aabb)
{
	if(abs(paddle.getPosition().x - aabb.getPosition().x)  > (paddle.getRadius().x + aabb.getRadius().x)) return false;
	if (abs(paddle.getPosition().y - aabb.getPosition().y) > (paddle.getRadius().y + aabb.getRadius().y)) return false;
	return true;
}

