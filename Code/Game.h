#ifndef GAME
#define GAME
#include "Mosaic.h"
#include <fstream>
#include <string>

class Game
{
	public:
	Game(std::string player1, std::string player2);
	Game();
	~Game();
	void startNewGame();
	void loadGame(std::ifstream& inputFile);
	void testingMode(std::ifstream& inputFile);

	private:
	std::string player1, player2;
	Mosaic * player1Mosaic;
	Mosaic * player2Mosaic;
	Factories * factories;
	TileBag * tileBag;
	TileBag * copyTileBag;
	std::vector<std::string> consoleCommands;
	void playerTurn(std::string player);
	void playerTurn(std::ifstream& inputFile, std::string player);
	bool playerTurnTestingMode(std::ifstream& inputFile, std::string player);
	bool addToTable(Tile * tile, std::string player, int storageRow);
	void addToBrokenTiles(Tile * tile, std::string player);
	bool isNumber(std::string string);
	bool inputCommand(std::string command, int& factoryRow, char& tileCode, int& storageRow, std::string& saveFile);
	bool gameDeleted();
	void saveGame(std::string saveFile);
};

#endif //GAME