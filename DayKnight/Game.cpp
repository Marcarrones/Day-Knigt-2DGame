#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>

enum CurrentScreen {
	MAIN_MENU, GAME, CREDITS, INSTRUCTIONS
};


void Game::init()
{
	currentScreen = GAME;
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
	mainMenu.init();
}

bool Game::update(int deltaTime)
{
	switch (currentScreen) 
	{
	case MAIN_MENU:
		mainMenu.update(deltaTime);
		break;
	case GAME:
		scene.update(deltaTime);
		break;
	}
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (currentScreen) 
	{
	case MAIN_MENU:
		mainMenu.render();
		break;
	case GAME:
		scene.render();
		break;
	}
	
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;

	if (key == 109)
		currentScreen = MAIN_MENU;
	if (key == 103)
		currentScreen = GAME;

	std::cout << key << endl;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





