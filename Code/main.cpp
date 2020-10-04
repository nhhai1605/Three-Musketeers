#include <iostream>
#include <fstream>
#include <filesystem>
#include "Game.h"

void printMenu();
void printCredit();

int main(int argc, char**argv) 
{
	if(argc == 1)
	{
		std::cout << "Welcome to Azul!" << std::endl;
		std::cout << "-------------------" << std::endl;
		std::string input;

		//endProgram is used to check if the program is end or not, really helpful to prevent the program from keep running after ^D
		bool endProgram = false;
		while(!std::cin.eof() && !endProgram)
		{
			printMenu();
			std::cin >> input;
			if(input == "1")
			{
				std::string player1, player2;
				std::cout << std::endl;
				std::cout << "Enter a name for player 1" << std::endl << "> ";
				std::cin >> player1;
				if(std::cin.eof() && !endProgram)
				{
					std::cout << "Goodbye" << std::endl;
					endProgram = true;
				}
				if(!endProgram)
				{
					std::cout << "Enter a name for player 2" << std::endl << "> ";
					std::cin >> player2;
					if(std::cin.eof())
					{
						std::cout << "Goodbye" << std::endl;
						endProgram = true;
					}
				}
				while(player2 == player1 && !endProgram)
				{
					std::cout << "Name taken. Please enter another name." << std::endl << "> ";
					std::cin >> player2;
					if(std::cin.eof())
					{
						std::cout << "Goodbye" << std::endl;
						endProgram = true;
					}
				}
				if(!endProgram)
				{
					std::cout << std::endl;
					std::cout << "Let's Play!" << std::endl;
					std::cout << std::endl;
					std::cin.ignore (1024, '\n'); 
					Game * game = new Game(player1, player2);
					game->startNewGame();
					delete game;
				}
			}
			else if (input == "2") 
			{
				std::string fileName;
				std::cout << "Enter the filename from which load a game" << std::endl;
				bool validFile = false;
				std::ifstream inputFile;
				while(!validFile && !std::cin.eof() && !endProgram)
				{
					std::cout << "> ";
					std::cin >> fileName;

					//fileName can be change, for now it read from the "test" folder 
					fileName = "test/" + fileName + ".txt";
					inputFile.open(fileName);

					//this used to check if the file is open
					if(inputFile.is_open())
					{
						validFile = true;

						//this used to check if the file is empty
						int c = inputFile.peek();
						if(c == EOF)
						{
							std::cout << std::endl;
							std::cout << "=== Empty file ===" << std::endl << std::endl;
							validFile = false;
						}
					}
					else
					{
						std::cout << "Invalid file" << std::endl;
					}
					if(std::cin.eof())
					{
						std::cout << "Goodbye" << std::endl;
						endProgram = true;
					}
					if(!endProgram && validFile == true)
					{
						std::cout << std::endl;
						std::cout << "Azul game successfully loaded" << std::endl;
						Game * game = new Game();
						game->loadGame(inputFile);
						endProgram = true;
						delete game;
					}
					inputFile.close();
				}	
			}
			else if (input == "3") 
			{
				printCredit();
			}
			else if(input == "4" || std::cin.eof())
			{
				std::cout << "Goodbye" << std::endl;
				endProgram = true;
			}
			else
			{
				std::cout << "Invalid Input" << std::endl;	
			}
		}
	}
	else if (argc == 3)
	{
		std::string command(argv[1]);
		if(command == "-t")
		{
			std::string fileName(argv[2]); 

			//fileName can be change, for now it read from the "test" folder 
			fileName = "test/" + fileName + ".txt";
			std::ifstream inputFile(fileName);
			bool validFile = false;

			//this used to check if the file is open
			if(inputFile.is_open())
			{
				validFile = true;
				
				//this used to check if the file is empty
  				int c = inputFile.peek();
				if(c == EOF)
				{
					std::cout << std::endl;
					std::cout << "=== Empty file ===" << std::endl << std::endl;
					validFile = false;
				}
			}
			else
			{
				std::cout << "Invalid file" << std::endl;
			}
			if(validFile)
			{
				Game* game = new Game();
				game->testingMode(inputFile);
			}
		}
		else
		{
			std::cout << "Invalid command" << std::endl;
		}
	}
	else
	{
		std::cout << "Invalid command" << std::endl;
	}
	return EXIT_SUCCESS;
};

void printMenu()
{
	std::cout << std::endl;
	std::cout << "Menu" << std::endl;
	std::cout << "----" << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Load Game" << std::endl;
	std::cout << "3. Credits (Show student information)" << std::endl;
	std::cout << "4. Quit" << std::endl;
	std::cout << std::endl;
	std::cout << "> ";
};

void printCredit()
{
	std::cout << std::endl;
	std::cout << "----------------------------------" << std::endl;
	std::cout << "Student 1" << std::endl;
	std::cout << "Name: Hin Yap Lee" << std::endl;
	std::cout << "Student ID: s3801049" << std::endl;
	std::cout << "Email: s3801049@student.rmit.edu.au" << std::endl;
	std::cout << std::endl;
	std::cout << "Student 2" << std::endl;
	std::cout << "Name: Yong Ping Soo" << std::endl;
	std::cout << "Student ID: s3736281" << std::endl;
	std::cout << "Email: s3736281@student.rmit.edu.au" << std::endl;
	std::cout << std::endl;
	std::cout << "Student 3" << std::endl;
	std::cout << "Name: Nguyen Hoang Hai" << std::endl;
	std::cout << "Student ID: s3822918" << std::endl;
	std::cout << "Email: s3822918@rmit.edu.vn" << std::endl;
	std::cout << "----------------------------------" << std::endl;		
};
