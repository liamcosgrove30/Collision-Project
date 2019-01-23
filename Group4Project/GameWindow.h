/*

Name:Liam Cosgrove

Student ID: B00287629

I declare that the following code was produced by Liam Cosgrove, Dale Thomson, Jakub Gembacz as a group assignment for the RTCD module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <GL\glut.h>


class GameWindow
{
private:
	// Projection clipping area
	double clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
	int width, height;
public:

	GameWindow(char* title, int width, int height, int posX, int posY) :width(width), height(height)
	{
		glutInitDisplayMode(GLUT_DOUBLE);	// Enable double buffered mode
		glutInitWindowSize(width, height);	// Initial window width and height
		glutInitWindowPosition(posX, posY); // Initial window top-left corner (x, y)
		glutCreateWindow(title);			// Create window with given title
	}

	virtual ~GameWindow() {}

	void Reshape(GLsizei width, GLsizei height);
	int getWidth();
	int getHeight();
};