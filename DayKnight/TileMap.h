#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include <stack>


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.

enum Edge {
	Left, Right, None
};

class TileMap
{

private:
	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }


	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;

	Edge checkEdge(const glm::ivec2 & pos, const glm::ivec2 & size);
	bool checkSpike(const glm::ivec2 &pos, const glm::ivec2 &size) const;

	void paintBottomTile(const glm::ivec2 &pos, const glm::ivec2 &size);

	int remainingTiles() { return paintableTiles - paintedTiles; }
	int getPaintedTiles() { return paintedTiles; }

	glm::ivec2 playerPos, keyPos, exitPos, clockPos;
	std::stack<glm::ivec2> enemy1Pos, enemy2Pos, enemy3Pos, itemPos, stopwatchPos, gemPos;

private:
	bool loadLevel(const string &levelFile);
	void setPositions(char tile, const glm::ivec2 & entityPos);

	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);
	void reloadArrays();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles, paintableTiles, paintedTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;

	// Indica que tiles [0].first y [1].first se deberian pintar 
	// y a que nuevas tiles [0].second y [1].second respectivamente
	// Evitar que se el primero y el segundo sean los mismos (ej de que no hacer: (1,2) (2,4) -> Pinta dos veces
	pair<int, int> tilePainting[2] = { pair<int,int>(2,1), pair<int,int >(5,4) };
	pair<int, int> spikeTiles = pair<int, int>(3, 6);

	glm::vec2 oldMinCoords;
	ShaderProgram oldShader;

};


#endif // _TILE_MAP_INCLUDE

