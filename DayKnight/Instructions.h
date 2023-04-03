#include "Sprite.h"
#include "Text.h"


class Instructions
{

public:
	~Instructions();
	void init(glm::ivec2 pos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void initSpriteBackground();


private:
	ShaderProgram texProgram;
	glm::ivec2 tileMapDispl;
	glm::mat4 projection;
	ShaderProgram shader;
	Texture spritesheetIns;
	Sprite* background;
	float currentTime;
};
