#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;

int PAINTABLE_TILE = 1;
int PAINTED_TILE = 2;



TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);

	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	paintedTiles = 0;
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if (map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	/*
	sstram >> tilePainting[0].first >> tilePainting[0].second;
	sstram >> tilePainting[1].first >> tilePainting[1].second;
	*/
	map = new int[mapSize.x * mapSize.y];
	paintableTiles = 0;
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			glm::ivec2 entityPos = glm::ivec2(i * tileSize, (j - 1) * tileSize);
			fin.get(tile);
			if (tile - int('0') < 10 && tile - int('0') >= 0) {
				int tileNumber = tile - int('0');
				map[j*mapSize.x + i] = tileNumber;
				// COUNT TILES
				if (tileNumber == tilePainting[0].first || tileNumber == tilePainting[1].first)
					if (j != 0 && map[(j - 1)*mapSize.x + i] == 0) paintableTiles++;
			}
			else {
				map[j*mapSize.x + i] = 0;
				setPositions(tile, entityPos);
			}
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}

	fin.close();

	return true;
}

void TileMap::setPositions(char tile, const glm::ivec2 &entityPos) {
	switch (tile)
	{
	default: return;
	case 'p':	// PLAYER
		playerPos = entityPos;
		break;
	case 'k':	// KEY
		keyPos = entityPos;
		break;
	case 'd':	// EXIT DOOR
		exitPos = entityPos;
		break;
	case 'c': // CLOCK
		clockPos = entityPos;
		break;
	case 'g':
		gemPos = entityPos;
		break;
	case 'h':
		healthPos = entityPos;
		break;
		//ITEMS
	case 'i':
		itemPos.push(entityPos);
		break;



		//ENEMIES
	case 'e':
		enemy1Pos.push(entityPos);
		break;
	case 'r':
		enemy2Pos.push(entityPos);
		break;
	case 't':
		enemy3Pos.push(entityPos);
		break;
	}
	return;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	oldShader = program;
	oldMinCoords = minCoords;

	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

void TileMap::paintBottomTile(const glm::ivec2 &pos, const glm::ivec2 &size /*, int paintableTileInt, int paintedTileInt */) {
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y) / tileSize;
	bool painted = false;
	for (int x = x0; x <= x1; x++)
	{
		int valuePre = map[y*mapSize.x + x];
		bool isPaintable = (valuePre == tilePainting[0].first || valuePre == tilePainting[1].first);

		if (map[y*mapSize.x + x] == tilePainting[0].first) {
			painted = true;
			paintedTiles++;
			map[y*mapSize.x + x] = tilePainting[0].second;
		}
		else if (map[y*mapSize.x + x] == tilePainting[1].first) {
			painted = true;
			paintedTiles++;
			map[y*mapSize.x + x] = tilePainting[1].second;
		}
		//int valuePost = map[(y + 1)*mapSize.x + x];
	}
	if (painted) reloadArrays();
}

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y*mapSize.x + x] != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y*mapSize.x + x] != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y*mapSize.x + x] != 0)
		{
			if (*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}

	return false;
}

Edge TileMap::checkEdge(const glm::ivec2 &pos, const glm::ivec2 &size) {
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y) / tileSize;
	Edge edge = None;

	bool ground = (map[y*mapSize.x + x0] != 0);
	for (int x = x0 + 1; x <= x1; x++)
	{
		if (map[y*mapSize.x + x] == 0) {
			if (ground) edge = Right;
			ground = false;
		}
		else {
			if (!ground) edge = Left;
			ground = true;
		}
	}
	return edge;
}

bool TileMap::checkSpike(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y) / tileSize;
	bool onlySpike = true;

	for (int x = x0; x <= x1; x++)
	{
		if (onlySpike == false) break;
		if (map[y*mapSize.x + x] == spikeTiles.first || map[y*mapSize.x + x] == spikeTiles.second)
			onlySpike = true;
		else onlySpike = false;
	}

	return onlySpike;
}

void TileMap::reloadArrays() {
	prepareArrays(oldMinCoords, oldShader);
}