#ifndef _MENU_SUPERIOR_INCLUDE
#define _MENU_SUPERIOR_INCLUDE

#include "Sprite.h"
#include "Text.h"


class MenuSuperior
{

public:
	~MenuSuperior();
	void init(glm::ivec2 pos, ShaderProgram& shaderProgram);
	void restart();

	void update(int deltaTime);
	void render();
	void calculateVitExp(int vitExp, int option);
	void setScreen(int scene, int screen);
	void setPoints(int points);
	void updateTime(int currentTime);
	void changeLive(int live);
	void changeLevel(int level);

private:
	glm::ivec2 tileMapDispl;
	ShaderProgram shader;
	Texture spritesheetVit;
	Sprite* spriteVit;
	Text* text;
	int high;
};


#endif // _MENU_SUPERIOR_INCLUDE