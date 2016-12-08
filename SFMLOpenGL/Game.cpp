#include "Game.h"

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube"), primitives(1)
{
	index = glGenLists(primitives);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml

	corner1 = MyVector3(1.0f, 1.0f, -5.0f);
	corner2 = MyVector3(-1.0f, 1.0f, -5.0f);
	corner3 = MyVector3(-1.0f, -1.0f, -5.0f);
	corner4 = MyVector3(1.0f, -1.0f, -5.0f);
	corner5 = MyVector3(1.0f, 1.0f, -15.0f);
	corner6 = MyVector3(-1.0f, 1.0f, -15.0f);
	corner7 = MyVector3(-1.0f, -1.0f, -15.0f);
	corner8 = MyVector3(1.0f, -1.0f, -15.0f);
	scale = scale.scale(99.9f, 99.9f);
	rot = rot.rotationZ(rotationAngle);
	translate = translate.translateX(0.0001f, 0.00011f);
	mold = rot * translate * scale;
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	corner1 = mold * corner1;
	corner2 = mold * corner2;
	corner3 = mold * corner3;
	corner4 = mold * corner4;
	corner5 = mold * corner5;
	corner6 = mold * corner6;
	corner7 = mold * corner7;
	corner8 = mold * corner8;

	glNewList(index, GL_COMPILE);
	/*glBegin(GL_POINTS);
	{
		glPointSize(50);
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
	}*/
	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());

		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());

		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
			current++;
			if (current > primitives)
			{
				current = 1;
			}
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}
	
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << current << endl;
	glLoadIdentity();
	//glRotatef(rotationAngle, 0, 1, 0); // Rotates the camera on Y Axis

	glCallList(current);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

