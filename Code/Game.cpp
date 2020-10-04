#include <iostream>
#include "Game.h"

Game::Game(std::string player1, std::string player2)
{
    this->player1 = player1;
    this->player2 = player2;
	player1Mosaic = nullptr;
    player2Mosaic = nullptr;
    factories = nullptr;
    tileBag = nullptr;
    copyTileBag = nullptr;
}

Game::Game()
{
	player1Mosaic = nullptr;
    player2Mosaic = nullptr;
    factories = nullptr;
    tileBag = nullptr;
    copyTileBag = nullptr;  
}

Game::~Game()
{
    if(player1Mosaic != nullptr)
    {
	    delete player1Mosaic;
    }
    if(player2Mosaic != nullptr)
    {
        delete player2Mosaic;
    }
    if(factories != nullptr)
    {
        delete factories;
    }
    if(tileBag != nullptr)
    {
        delete tileBag;
    }
    tileBag = nullptr;
    player1Mosaic = nullptr;
    player2Mosaic = nullptr;
    factories = nullptr;
}

bool Game::isNumber(std::string string) 
{ 
	bool isNumber = true;
	for (std::string::size_type i = 0; i < string.size(); i++) 
    {
        if (isdigit(string[i]) == false) 
        {
            isNumber = false;
        }
    }
    if(string.size() == 0)
    {
        isNumber = false;
    }
	return isNumber; 
} 

//This method used to start a new Game with new TileBag, Mosaics and Factories
void Game::startNewGame()
{   
    player1Mosaic = new Mosaic(player1);
    player2Mosaic = new Mosaic(player2);
    factories = new Factories();
    tileBag = new TileBag();
    copyTileBag = new TileBag(*tileBag);
    bool gameContinue;
    for(int i = 0; i < NUMBER_OF_ROUNDS; i++)
    {
        gameContinue = true;
        if(factories != nullptr && tileBag != nullptr)
        {
            factories->dealTile(tileBag);
        }
        while(gameContinue)
        {
            if(!gameDeleted())
            {
                std::cout << "=== Start Round ===" << std::endl;
            }
            if(!gameDeleted() && !factories->factoriesAreEmpty())
            {
                playerTurn(player1);
            }
            if(!gameDeleted() && !factories->factoriesAreEmpty())
            {
                playerTurn(player2);
            }
            if(!gameDeleted())
            {
                std::cout << "=== END OF ROUND ===" << std::endl << std::endl;
            }
            if(!gameDeleted())
            {
                if(factories->factoriesAreEmpty())
                {
                    gameContinue = false;
                }
            }
            else
            {
                gameContinue = false;
            }
        }
        if(!gameDeleted())
        {
            player1Mosaic->updateTable(tileBag);
            player2Mosaic->updateTable(tileBag);
        }
    }
    if(!gameDeleted())
    {
        std::cout << "=== GAME OVER ===" << std::endl << std::endl;
        std::cout << "Final Result: " << std::endl;
        player1Mosaic->printMosaic();
        player2Mosaic->printMosaic();
        std::cout << "Final Score: " << std::endl;
        std::cout << "Player " << player1 << ": " << player1Mosaic->getScore() << std::endl;
        std::cout << "Player " << player2 << ": " << player2Mosaic->getScore() << std::endl;
        if(player1Mosaic->getScore() > player2Mosaic->getScore())
        {
            std::cout << "Player " << player1 << " wins!" << std::endl;
        }
        else if(player1Mosaic->getScore() < player2Mosaic->getScore())
        {
            std::cout << "Player " << player2 << " wins!" << std::endl;
        }
        else
        {
            std::cout << "Draw!" << std::endl;
        }
    }
}

//This method used to run game login and input logic for 1 player
void Game::playerTurn(std::string player)
{
    std::cout << "TURN FOR PLAYER: " << player << std::endl;
    factories->printFactories();
    std::cout<< "Score for Player " << player << ": " ;
    if(player == player1)
    {
        std::cout << player1Mosaic->getScore() << std::endl;
        player1Mosaic->printMosaic();
    }
    else if (player == player2)
    {
        std::cout << player2Mosaic->getScore() << std::endl;
        player2Mosaic->printMosaic();
    }
    Tile ** factory = nullptr;
    bool validFactoryRow = false;
    int factoryRow, storageRow;
    char tileCode;
    std::string command, saveFile;
    while(!validFactoryRow && !std::cin.eof())
    {
        factoryRow = -1, storageRow = -1;
        while((factoryRow < 0 || factoryRow > 5 || storageRow < 1 || storageRow > 6 || (tileCode != 'R' && tileCode != 'Y' && tileCode != 'F' && tileCode != 'B' && tileCode != 'L' && tileCode != 'U')) && !std::cin.eof())
        {                     
            while(std::cout << "> " && std::getline(std::cin, command) && !inputCommand(command, factoryRow, tileCode, storageRow, saveFile) && !std::cin.eof())
            {
                std::cout << "Invalid Input" << std::endl;
            }
            if(std::cin.eof())
            {
                std::cout << "Goodbye" << std::endl;
                delete factories;
                factories = nullptr;
                delete player1Mosaic;
                player1Mosaic = nullptr;
                delete player2Mosaic;
                player2Mosaic = nullptr;
                delete tileBag;
                tileBag = nullptr;
            }
            else if((factoryRow < 0 || factoryRow > 5 || storageRow < 1 || storageRow > 6 || (tileCode != 'R' && tileCode != 'Y' && tileCode != 'F' && tileCode != 'B' && tileCode != 'L' && tileCode != 'U')))
            {
                if(saveFile.empty())
                {
                    std::cout << "Invalid Input" << std::endl;
                }
                else
                {
                    saveFile.erase();
                }
            }
        }
        if(!gameDeleted())
        {   
            if(factoryRow == 0)
            {
                for(int i = 0; i < factories->getCentral()->size(); i++)
                {
                    if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                    {
                        validFactoryRow = true;
                    }
                }
            }
            else
            {
                factory = factories->getFactory(factoryRow-1);
                if(factory != nullptr)
                {
                    for(int i = 0; i < FACTORY_SIZE; i++)
                    {
                        if (factory[i]->getTileName() == tileCode)
                        {
                            validFactoryRow = true;
                        }
                    }                    
                }
                else
                {
                    validFactoryRow = false;
                }
            }
            
            if(storageRow != 6)
            {
                if(player == player1)
                {
                    if(player1Mosaic->tileDiff(tileCode, storageRow-1))
                    {
                        validFactoryRow = false;
                    } 
                }
                else if(player == player2)
                {
                  if(player2Mosaic->tileDiff(tileCode, storageRow-1))
                    {
                    validFactoryRow = false;
                    }  
                }
            }

            if(validFactoryRow == false)
            {
                std::cout << "Invalid Input" << std::endl;
            } 
            else
            {
                if(factoryRow == 0)
                {
                    if(tileCode == 'F')
                    {
                        if(storageRow != 6)
                        {
                            validFactoryRow = false;
                            std::cout << "Invalid Input" << std::endl;
                        }
                        else
                        {
                            if(factories->getCentral()->getTileAtIndex(0)->getTileName() == tileCode)
                            {
                                addToBrokenTiles(factories->getCentral()->getTileAtIndex(0), player);
                                factories->getCentral()->removeFromFront();
                            }
                            else
                            {
                                validFactoryRow = false;
                                std::cout << "Invalid Input" << std::endl;                            
                            }
                        }
                    }
                    else
                    {
                        //Use to check the first player takes tiles from central
                        if(factories->getCentral()->getTileAtIndex(0)->getTileType() == F)
                        {           
                            addToBrokenTiles(factories->getCentral()->getTileAtIndex(0), player);
                            factories->getCentral()->removeFromFront();
                        }
                        std::vector<int> deleteNumber;
                        for(int i = 0; i < factories->getCentral()->size(); i++)
                        {
                            if(storageRow != 6)
                            {
                                if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                                {                
                                    validFactoryRow = addToTable(factories->getCentral()->getTileAtIndex(i), player, storageRow-1);
                                    deleteNumber.push_back(i);
                                }
                            }
                            else
                            {
                                if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                                {
                                    addToBrokenTiles(factories->getCentral()->getTileAtIndex(i), player);
                                    deleteNumber.push_back(i);  
                                }  
                            } 
                        }
                        if(validFactoryRow)
                        {
                            for(int i = deleteNumber.size()-1; i >= 0; i--)
                            {
                                factories->getCentral()->removeAtIndex(deleteNumber[i]);
                            }
                        }
                        else
                        {
                            std::cout << "Invalid Input" << std::endl;    
                        }
                    }
                }
                else
                {
                    for(int i = 0; i < FACTORY_SIZE; i++)
                    {
                        if(factory[i]->getTileName() == tileCode)
                        {
                            if(storageRow != 6)
                            {
                                validFactoryRow = addToTable(factory[i], player, storageRow-1);
                            }   
                            else
                            {
                                addToBrokenTiles(factory[i], player);
                            }
                        }
                        else
                        {
                            factories->addToCentral(factory[i]);
                        }              
                    }
                    if(validFactoryRow)
                    {
                        factories->clearFactory(factoryRow-1);
                    }
                }                     
                if(validFactoryRow)
                {
                    consoleCommands.push_back(command);
                    if(factory != nullptr)
                    {
                        delete [] factory;
                        factory = nullptr;
                    }
                    std::cout << "Turn successful" << std::endl << std::endl;
                }   
                else
                {                  
                    std::cout << "Invalid Input" << std::endl;    
                }
                                        
            }
        }
    }
}

//This method is the same with playerTurn above , but read input from inputFile
void Game::playerTurn(std::ifstream& inputFile, std::string player)
{
    Tile ** factory = nullptr;
    bool validFactoryRow = false;
    int factoryRow, storageRow;
    char tileCode;
    std::string command, saveFile;         
    std::getline(inputFile, command); 
    inputCommand(command, factoryRow, tileCode, storageRow, saveFile);  
    if(command.empty() || factoryRow < 0 || factoryRow > 5 || storageRow < 1 || storageRow > 6)
    {
        std::cin.clear();
        std::cin.ignore();
        playerTurn(player);
        inputFile.close();
    }
    else
    {
        if(!gameDeleted())
        {   
            if(factoryRow == 0)
            {
                for(int i = 0; i < factories->getCentral()->size(); i++)
                {
                    if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                    {
                        validFactoryRow = true;
                    }
                }
            }
            else
            {
                factory = factories->getFactory(factoryRow-1);
                if(factory != nullptr)
                {
                    for(int i = 0; i < FACTORY_SIZE; i++)
                    {
                        if (factory[i]->getTileName() == tileCode)
                        {
                            validFactoryRow = true;
                        }
                    }                    
                }
                else
                {
                    validFactoryRow = false;
                }
            }
            if(player1Mosaic != nullptr && player2Mosaic != nullptr && storageRow != 6)
            {
                if(player == player1)
                {
                    if(player1Mosaic->tileDiff(tileCode, storageRow-1))
                    {
                        validFactoryRow = false;
                    } 
                }
                else if(player == player2)
                {
                  if(player2Mosaic->tileDiff(tileCode, storageRow-1))
                    {
                    validFactoryRow = false;
                    }  
                }
            }
            if(validFactoryRow)
            {
                if(factoryRow == 0)
                {
                    if(tileCode == 'F')
                    {
                        if(storageRow != 6)
                        {
                            validFactoryRow = false;
                        }
                        else
                        {
                            if(factories->getCentral()->getTileAtIndex(0)->getTileName() == tileCode)
                            {
                                addToBrokenTiles(factories->getCentral()->getTileAtIndex(0), player);
                                factories->getCentral()->removeFromFront();
                            }
                        }
                    }
                    else
                    {
                        //Use to check the first player takes tiles from central
                        if(factories->getCentral()->getTileAtIndex(0)->getTileType() == F)
                        {           
                            addToBrokenTiles(factories->getCentral()->getTileAtIndex(0), player);
                            factories->getCentral()->removeFromFront();
                        }
                        std::vector<int> deleteNumber;
                        for(int i = 0; i < factories->getCentral()->size(); i++)
                        {
                            if(storageRow != 6)
                            {
                                if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                                {                
                                    validFactoryRow = addToTable(factories->getCentral()->getTileAtIndex(i), player, storageRow-1);
                                    deleteNumber.push_back(i);
                                }
                            }
                            else
                            {
                                if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                                {
                                    addToBrokenTiles(factories->getCentral()->getTileAtIndex(i), player);
                                    deleteNumber.push_back(i);  
                                }  
                            } 
                        }
                        if(validFactoryRow)
                        {
                            for(int i = deleteNumber.size()-1; i >= 0; i--)
                            {
                                factories->getCentral()->removeAtIndex(deleteNumber[i]);
                            }
                        }
                    }
                }
                else
                {
                    for(int i = 0; i < FACTORY_SIZE; i++)
                    {
                        if(factory[i]->getTileName() == tileCode)
                        {
                            if(storageRow != 6)
                            {
                                validFactoryRow = addToTable(factory[i], player, storageRow-1);
                            }   
                            else
                            {
                                addToBrokenTiles(factory[i], player);
                            }
                        }
                        else
                        {
                            factories->addToCentral(factory[i]);
                        }                       
                    }
                    if(validFactoryRow)
                    {
                        factories->clearFactory(factoryRow-1);
                    }
                }                     
                if(validFactoryRow)
                {
                    consoleCommands.push_back(command);
                    if(factory != nullptr)
                    {
                        delete [] factory;
                        factory = nullptr;
                    }
                }                           
            }
        }
    }
}

//This method is used to know if the tile is added successfully to the table or not, depend on input, existed tile in Table
bool Game::addToTable(Tile * tile, std::string player, int playerRow)
{
    bool validFactoryRow = true;
    if(player == player1)
    {
        bool typeExisted = player1Mosaic->tileTypeExitedInTable(tile, playerRow);
        if(typeExisted)
        {
            validFactoryRow = false;
        }
        else
        {
            bool tileAdded = player1Mosaic->addTile(tile, playerRow);
            if(tileAdded == false)
            {
                bool brokenTileAdded = player1Mosaic->addBrokenTile(tile);
                if(brokenTileAdded == false)
                {
                    tileBag->addTileBackToBag(tile);
                }
            }
        }
    }
    else if(player == player2)
    {
        bool typeExisted = player2Mosaic->tileTypeExitedInTable(tile, playerRow);
        if(typeExisted)
        {
            validFactoryRow = false;
        }
        else
        {
            bool tileAdded = player2Mosaic->addTile(tile, playerRow);
            if(tileAdded == false)
            {
                bool brokenTileAdded = player2Mosaic->addBrokenTile(tile);
                if(brokenTileAdded == false)
                {
                    tileBag->addTileBackToBag(tile);
                }
            }
        }       
    }
    return validFactoryRow;
}

//This method is used to know if the tile is added successfully to the broken tiles section or not
void Game::addToBrokenTiles(Tile * tile, std::string player)
{   
    if(player == player1)
    {
        bool brokenTileAdded = player1Mosaic->addBrokenTile(tile);
        if(brokenTileAdded == false)
        {
            tileBag->addTileBackToBag(tile);
        }
    }
    else if(player == player2)
    {
        bool brokenTileAdded = player2Mosaic->addBrokenTile(tile);
        if(brokenTileAdded == false)
        {
            tileBag->addTileBackToBag(tile);
        }
    }
}


//This method return true or false depending on the input
bool Game::inputCommand(std::string command, int& factoryRow, char& tileCode, int& storageRow, std::string& saveFile)
{
    bool validInput = true;
	int charCount = 0;
	int charCount2 = 0;
    int charCount3 = 0;
	int spaceInMiddle = 0;
	int spaceinMiddle2 = 0;
    int spaceinMiddle3 = 0;
	std::string str1,str2,str3,str4;
	for(std::string::size_type i = 0; i < command.size(); i++)
	{
		if(command[i] != ' ' && spaceInMiddle == 0)
		{
			str1 += command[i];
			charCount++;
		}
		if(charCount > 0 && command[i] == ' ')
		{
			spaceInMiddle++;
		}
		if(spaceInMiddle > 0 && command[i] != ' ' && spaceinMiddle2 == 0)
		{
			str2 += command[i];
			charCount2 ++;
		}
		if(charCount2 > 0 && command[i] == ' ')
		{
			spaceinMiddle2++;
		}
		if(spaceinMiddle2 > 0 && charCount2 > 0 && command[i] != ' ' && spaceinMiddle3 == 0) 
		{
			str3 += command[i];
            charCount3++;
		}
		if(charCount3 > 0 && command[i] == ' ' && spaceinMiddle3 == 0)
		{
			spaceinMiddle3++;
		}
		if(spaceinMiddle3 > 0 && charCount3 > 0 && command[i] != ' ') 
		{
			str4 += command[i];
		}
	}
    if(str1 == "turn")
    {
        if(isNumber(str2) && isNumber(str4) && str3.size() == 1 && isupper(str3[0]))
        {
            factoryRow = std::stoi(str2);
            storageRow = std::stoi(str4);
            tileCode = str3[0];
        }
        else 
        {
            validInput = false;
        }
    }
    else if (str1 == "save")
    {
        if(str3.empty() && !str2.empty())
        {
            saveGame(str2);
            saveFile = str2;
            std::cout << std::endl;
            std::cout << "Game successfully saved to '"<< str2 << "'" << std::endl << std::endl;
        }
        else
        {
            validInput = false;
        } 
    }
    else
    {
        validInput = false;
    }
    
    return validInput;
}

//This method is used to check if the game is deleted, useful to check if the user press ^D in the middle of the game
bool Game::gameDeleted()
{
    bool isGameDeleted = false;
    if(tileBag == nullptr && factories == nullptr && player1Mosaic == nullptr && player2Mosaic == nullptr)
    {
        isGameDeleted = true;
    }
    return isGameDeleted;
}

//This method is used to save the game(players' name, tileBag order, turns,... into a save file. This can overwrite existing file with the same name)
void Game::saveGame(std::string saveFile)
{
    saveFile = "saveFolder/" + saveFile + ".txt";
    std::ofstream outputFile(saveFile);
    for(int i = 0; i < copyTileBag->size(); i++)
    {
        copyTileBag->printTileAtIndex(outputFile, i);
    }
    outputFile << std::endl;
    outputFile << player1 << std::endl;
    outputFile << player2 << std::endl;
    for(std::size_t i = 0, max = consoleCommands.size(); i != max; ++i)
    {
        outputFile << consoleCommands[i] << std::endl;
    }
    outputFile.close();
}

//This method used to load the game with all the information from the inputFile
void Game::loadGame(std::ifstream& inputFile)
{
    std::string tileList;
    std::getline(inputFile, tileList);
    std::getline(inputFile, player1);
    std::getline(inputFile, player2);
    tileBag = new TileBag(tileList);
    copyTileBag = new TileBag(*tileBag);
    player1Mosaic = new Mosaic(player1);
    player2Mosaic = new Mosaic(player2);
    factories = new Factories;
    bool gameContinue;
    bool continueGameplay = false;
    for(int i = 0; i < NUMBER_OF_ROUNDS; i++)
    {
        gameContinue = true;
        if(factories != nullptr && tileBag != nullptr)
        {
            factories->dealTile(tileBag);
        }
        while(gameContinue)
        {
            if(!gameDeleted() && continueGameplay)
            {
                std::cout << "=== Start Round ===" << std::endl;
            }
            if(!gameDeleted() && !factories->factoriesAreEmpty())
            {
                if(inputFile.is_open())
                {
                    playerTurn(inputFile, player1);
                }
                else
                {
                    continueGameplay = true;
                    playerTurn(player1);
                } 
            }
            if(!gameDeleted() && !factories->factoriesAreEmpty())
            {
                if(inputFile.is_open())
                {
                    playerTurn(inputFile, player2);
                }
                else
                {
                    continueGameplay = true;
                    playerTurn(player2);
                }        
            }
            if(!gameDeleted() && continueGameplay)
            {
                std::cout << "=== END OF ROUND ===" << std::endl << std::endl;
            }
            if(!gameDeleted())
            {
                if(factories->factoriesAreEmpty())
                {
                    gameContinue = false;
                }
            }
            else
            {
                gameContinue = false;
            }
        }
        if(!gameDeleted())
        {
            player1Mosaic->updateTable(tileBag);
            player2Mosaic->updateTable(tileBag);
        }
    }
    if(!gameDeleted())
    {
        std::cout << "=== GAME OVER ===" << std::endl << std::endl;
        std::cout << "Final Result: " << std::endl;
        player1Mosaic->printMosaic();
        player2Mosaic->printMosaic();
        std::cout << "Final Score: " << std::endl;
        std::cout << "Player " << player1 << ": " << player1Mosaic->getScore() << std::endl;
        std::cout << "Player " << player2 << ": " << player2Mosaic->getScore() << std::endl;
        if(player1Mosaic->getScore() > player2Mosaic->getScore())
        {
            std::cout << "Player " << player1 << " wins!" << std::endl;
        }
        else if(player1Mosaic->getScore() < player2Mosaic->getScore())
        {
            std::cout << "Player " << player2 << " wins!" << std::endl;
        }
        else
        {
            std::cout << "Draw!" << std::endl;
        }
    }
    inputFile.close();
}

//This is used for testing mode
void Game::testingMode(std::ifstream& inputFile)
{
    std::string tileList;
    std::getline(inputFile, tileList);
    std::getline(inputFile, player1);
    std::getline(inputFile, player2);
    tileBag = new TileBag(tileList);
    copyTileBag = new TileBag(*tileBag);
    player1Mosaic = new Mosaic(player1);
    player2Mosaic = new Mosaic(player2);
    factories = new Factories;
    bool gameStop = false;
    factories->dealTile(tileBag);
    while(!gameStop)
    {    
        while(!gameStop && !factories->factoriesAreEmpty())
        {
            if(!gameStop && !factories->factoriesAreEmpty())
            { 
                gameStop = playerTurnTestingMode(inputFile, player1); 
            }
            if(!gameStop && !factories->factoriesAreEmpty())
            { 
                gameStop = playerTurnTestingMode(inputFile, player2);       
            }
        }  
        if(factories->factoriesAreEmpty())
        {
            player1Mosaic->updateTable(tileBag);
            player2Mosaic->updateTable(tileBag); 
            factories->dealTile(tileBag);
        } 
    }
    std::cout << std::endl;
    factories->printFactories();
    std::cout<< "Score for Player " << player1 << ": " ;
    std::cout << player1Mosaic->getScore() << std::endl;
    player1Mosaic->printMosaic();
    std::cout<< "Score for Player " << player2 << ": " ;
    std::cout << player2Mosaic->getScore() << std::endl;
    player2Mosaic->printMosaic();                
}

//this is used as normal playerTurn but for testing mode, users cant input anything in this state. testing mode only display and then terminate.
bool Game::playerTurnTestingMode(std::ifstream& inputFile, std::string player) 
{
    bool stopGame = false;
    Tile ** factory = nullptr;
    bool validFactoryRow = false;
    int factoryRow, storageRow;
    char tileCode;
    std::string command, saveFile;         
    std::getline(inputFile, command); 
    inputCommand(command, factoryRow, tileCode, storageRow, saveFile);  
    if(command.empty() || factoryRow < 0 || factoryRow > 5 || storageRow < 1 || storageRow > 6 || (tileCode != 'R' && tileCode != 'Y' && tileCode != 'F' && tileCode != 'B' && tileCode != 'L' && tileCode != 'U'))
    {
        inputFile.close();
        stopGame = true;
        if(command.empty())
        {
            validFactoryRow = true;
        }
    }
    else
    {
        if(!gameDeleted())
        {   
            if(factoryRow == 0)
            {
                for(int i = 0; i < factories->getCentral()->size(); i++)
                {
                    if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                    {
                        validFactoryRow = true;
                    }
                }
            }
            else
            {
                factory = factories->getFactory(factoryRow-1);
                if(factory != nullptr)
                {
                    for(int i = 0; i < FACTORY_SIZE; i++)
                    {
                        if (factory[i]->getTileName() == tileCode)
                        {
                            validFactoryRow = true;
                        }
                    }                    
                }
                else
                {
                    validFactoryRow = false;
                }
            }
            if(player1Mosaic != nullptr && player2Mosaic != nullptr && storageRow != 6)
            {
                if(player == player1)
                {
                    if(player1Mosaic->tileDiff(tileCode, storageRow-1))
                    {
                        validFactoryRow = false;
                    } 
                }
                else if(player == player2)
                {
                  if(player2Mosaic->tileDiff(tileCode, storageRow-1))
                    {
                    validFactoryRow = false;
                    }  
                }
            }
            if(validFactoryRow)
            {
                if(factoryRow == 0)
                {
                    if(tileCode == 'F')
                    {
                        if(storageRow != 6)
                        {
                            validFactoryRow = false;
                        }
                        else
                        {
                            if(factories->getCentral()->getTileAtIndex(0)->getTileName() == tileCode)
                            {
                                addToBrokenTiles(factories->getCentral()->getTileAtIndex(0), player);
                                factories->getCentral()->removeFromFront();
                            }
                        }
                    }
                    else
                    {
                        //Use to check the first player takes tiles from central
                        if(factories->getCentral()->getTileAtIndex(0)->getTileType() == F)
                        {           
                            addToBrokenTiles(factories->getCentral()->getTileAtIndex(0), player);
                            factories->getCentral()->removeFromFront();
                        }
                        std::vector<int> deleteNumber;
                        for(int i = 0; i < factories->getCentral()->size(); i++)
                        {
                            if(storageRow != 6)
                            {
                                if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                                {                
                                    validFactoryRow = addToTable(factories->getCentral()->getTileAtIndex(i), player, storageRow-1);
                                    deleteNumber.push_back(i);
                                }
                            }
                            else
                            {
                                if(factories->getCentral()->getTileAtIndex(i)->getTileName() == tileCode)
                                {
                                    addToBrokenTiles(factories->getCentral()->getTileAtIndex(i), player);
                                    deleteNumber.push_back(i);  
                                }  
                            } 
                        }
                        if(validFactoryRow)
                        {
                            for(int i = deleteNumber.size()-1; i >= 0; i--)
                            {
                                factories->getCentral()->removeAtIndex(deleteNumber[i]);
                            }
                        }
                    }
                }
                else
                {
                    for(int i = 0; i < FACTORY_SIZE; i++)
                    {
                        if(factory[i]->getTileName() == tileCode)
                        {
                            if(storageRow != 6)
                            {
                                validFactoryRow = addToTable(factory[i], player, storageRow-1);
                            }   
                            else
                            {
                                addToBrokenTiles(factory[i], player);
                            }
                        }
                        else
                        {
                            factories->addToCentral(factory[i]);
                        }                       
                    }
                    if(validFactoryRow)
                    {
                        factories->clearFactory(factoryRow-1);
                    }
                }                     
                if(validFactoryRow)
                {
                    consoleCommands.push_back(command);
                    if(factory != nullptr)
                    {
                        delete [] factory;
                        factory = nullptr;
                    }
                }                           
            }
        }
    }
    if(!validFactoryRow)
    {
        std::cout << std::endl;
        std::cout << "=== Error found in save file! Invalid input! ===" << std::endl;
    }   
    return stopGame;
}
