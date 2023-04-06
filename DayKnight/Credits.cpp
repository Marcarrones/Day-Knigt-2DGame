#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Credits.h"
#include "Game.h"

Credits::Credits()
{

}

Credits::~Credits()
{

}

void Credits::init() {
	initShaders();
	currentTime = 0.0f;
	initSpriteBackground();
	printTexts();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Credits::printTexts() {
	texts = new Text[11];

	texts[0].init(glm::vec2(float(96), float(100)), texProgram, 2, "DEVELOPED BY");
	texts[1].init(glm::vec2(float(96), float(140)), texProgram, 2, "MARCH DUCH");

	//texts[2].init(glm::vec2(float(96), float(180)), texProgram, 2, "MAPS DESIGNED BY");
	texts[3].init(glm::vec2(float(96), float(180)), texProgram, 2, "HAOPENG LIN");

	//texts[4].init(glm::vec2(float(96), float(210)), texProgram, 2, "CHARACTERS MODIFICATIONS BY");
	//texts[5].init(glm::vec2(float(96), float(230)), texProgram, 2, " AND MARCH DUCH ");

	//texts[6].init(glm::vec2(float(96), float(270)), texProgram, 2,"ORIGINAL TILESHEETS");
	//texts[7].init(glm::vec2(float(96), float(290)), texProgram, 2,"THE SPRITERS RESOURCE");

	//texts[8].init(glm::vec2(float(96), float(330)), texProgram, 2, "MUSIC BY");
	texts[9].init(glm::vec2(float(150), float(410)), texProgram, 2, "PRESS ESC");

	texts[10].init(glm::vec2(float(96), float(450)), texProgram, 2, " TO GO TO MENU");
}


void Credits::update(int deltaTime) {
	currentTime += deltaTime;
	background->update(deltaTime);
	for (int i = 0; i < 11; ++i)
		texts[i].update(deltaTime);
}

void Credits::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	for (int i = 0; i < 11; ++i)
		texts[i].render();
}

void Credits::initSpriteBackground() {
	spritesheetBackground.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = new Sprite();
	background = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.0, 1.0), &spritesheetBackground, &texProgram);
	background->setNumberAnimations(1);

	background->setAnimationSpeed(0, 8);
	background->addKeyframe(0, glm::vec2(0.f, 0.f));

	background->changeAnimation(0);
	background->setPosition(glm::vec2(0, 0));
}

void Credits::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}