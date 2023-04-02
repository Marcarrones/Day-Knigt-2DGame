#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MenuSuperior.h"
#include "Game.h"


MenuSuperior::~MenuSuperior() {

}

void MenuSuperior::init(glm::ivec2 pos, ShaderProgram& shaderProgram)
{
	shader = shaderProgram;
	int high = 0;
	spriteVit = new Sprite();
	spritesheetVit.loadFromFile("images/vida.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteVit = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 1), &spritesheetVit, &shaderProgram);
	spriteVit->setPosition(glm::vec2(float(pos.x -16 ), float(pos.y -38 )));
	text = new Text[6];
	text[0].init(glm::vec2(float(pos.x + 16), float(pos.y - 32)), shaderProgram, 2,  "X");
	text[1].init(glm::vec2(float(pos.x + 36), float(pos.y - 32)), shaderProgram, 2, "03");
	text[2].init(glm::vec2(float(pos.x + 90), float(pos.y - 32)), shaderProgram, 2, "000000");
	text[3].init(glm::vec2(float(pos.x + 230), float(pos.y - 32)), shaderProgram, 2, "000000");
	text[4].init(glm::vec2(float(pos.x + 400), float(pos.y - 32)), shaderProgram, 2, "STAGE");
	text[5].init(glm::vec2(float(pos.x + 520), float(pos.y - 32)), shaderProgram, 2, "01");
	


}

void MenuSuperior::restart() {


}

void MenuSuperior::update(int deltaTime)
{
	spriteVit->update(deltaTime);
	for (int i = 0; i < 6; ++i) text[i].update(deltaTime);
}

void MenuSuperior::render()
{
	spriteVit->render();
	for (int i = 0; i < 6; ++i) text[i].render();
}

void MenuSuperior::calculateVitExp(int vitExp, int option) {
	int VitExp8 = vitExp / 100 + 1;
	if (VitExp8 < 0) VitExp8 = 0;
	int aux = vitExp % 100;
}

void MenuSuperior::setScreen(int scene, int screen) {
	string num = "0" + to_string(scene) + "-0" + to_string(screen);
	text[3].setText(num);
}

void MenuSuperior::setPoints(int points) {
	string num = to_string(points);
	while (num.size() != 6) num = "0" + num;
	text[2].setText(num);

}

void MenuSuperior::updateTime(int currentTime)
{
	string num = to_string(currentTime);
	while (num.size() != 6) num = "0" + num;
	text[3].setText(num);
}

void MenuSuperior::changeLive(int live)
{
	string num = to_string(live);
	while (num.size() != 2) num = "0" + num;
	text[1].setText(num);
}

void MenuSuperior::changeLevel(int level)
{
	string num = to_string(level);
	while (num.size() != 2) num = "0" + num;
	text[5].setText(num);
}



