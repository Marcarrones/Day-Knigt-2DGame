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
	credit.init();
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
	case CREDITS:
		credit.update(deltaTime);
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
	case CREDITS:
		credit.render();
		break;
	}
	
}

void Game::keyPressed(int key)
{
	if (key == 27) {// Escape code
		switch (currentScreen)
		{
		case MAIN_MENU:
			bPlay = false;
			break;
		case GAME:
			currentScreen = MAIN_MENU;
			break;
		case CREDITS:
			currentScreen = MAIN_MENU;
			break;
		case INSTRUCTIONS:
			currentScreen = MAIN_MENU;
			break;
		}
	}

	if (key == 109)
		currentScreen = MAIN_MENU;
	if (key == 103)
		currentScreen = GAME;
	if (key == 99)
		currentScreen = CREDITS;
	if (key == 114 && currentScreen == GAME) {
		scene.restar();
	}
	
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

void Game::mouseRelease(int button,int x, int y)
{
	if (currentScreen == MAIN_MENU) {
		if (x >= 288 && x < 352 && y >= 160 && y < 176) {

			currentScreen = GAME;
	
		}
		if (x >= 224 && x < 416 && y >= 224 && y < 240) {
	
			currentScreen = INSTRUCTIONS;
		}
		if (x >= 264 && x < 376 && y >= 288 && y < 304) {

			currentScreen = CREDITS;
		}
		if (x >= 288 && x < 352 && y >= 352 && y < 368) {
			bPlay = false;
		}
	}
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





