#include "pch.h"
#include "DungeonInitializer.h"

using namespace CourseWork;

DungeonInitializer::DungeonInitializer()
{

};

Dungeon* DungeonInitializer::Initialize()
{
	Map* loadedMap;
	list<Map*> maps;
	list<Monster*> monsterList;
	int** pattern1 = new int*[MapWidth];
	/*int** pattern2 = new int*[MapWidth];
	int** pattern3 = new int*[MapWidth];
	int** pattern4 = new int*[MapWidth];
	int** pattern5 = new int*[MapWidth];*/

	pattern1[0] = new int[MapWidth] {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall};
	pattern1[1] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[2] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[3] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[4] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[5] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[6] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[7] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[8] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[9] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[10] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[11] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[12] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[13] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[14] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[15] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[16] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[17] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[18] = new int[MapWidth] {wall, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, floor, wall};
	pattern1[19] = new int[MapWidth] {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall};

	loadedMap = new Map(MapHeight, MapWidth, pattern1, monsterList);
	maps.push_back(loadedMap);
	maps.push_back(loadedMap);
	maps.push_back(loadedMap);
	maps.push_back(loadedMap);
	maps.push_back(loadedMap);

	return new Dungeon(maps);
};