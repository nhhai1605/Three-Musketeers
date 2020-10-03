#include "TileBag.h"
#include "Factories.h"
#include "Mosaic.h"
#include <iostream>
#include <fstream>
void readFile(std::ifstream& file)
{
    std::string player1;
    std::string player2;
    std::string tileList;
    std::getline(file, player1);
    std::getline(file, player2);
    std::getline(file, tileList);
    std::cout << player1 <<" " << player2 << " " << tileList << std::endl;
}
int main(int argc, char *argv[]) 
{
    std::ifstream inputFile("save.txt");
    readFile(inputFile);
    
}