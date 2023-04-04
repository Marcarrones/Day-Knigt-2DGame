#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE

#include "Sprite.h"
#include "Text.h"


class Instructions
{

public:
	~Instructions();
	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void initSpriteBackground();


	ShaderProgram texProgram;
	glm::ivec2 tileMapDispl;
	glm::mat4 projection;
	ShaderProgram shader;
	Texture spritesheetBackground;
	Sprite *background;
	float currentTime;
};
#endif