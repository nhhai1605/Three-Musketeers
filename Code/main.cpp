#include <iostream>

int main(int argc, char *argv[]) {
	std::cout << "Welcome to Azul!" << std::endl;
	std::cout << "-------------------" << std::endl;
	int input = 1;
	while(!std::cin.eof())
	{
		if(input <= 3 && input >= 1)
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
			std::cin >> input;
		}
		else 
		{
			std::cin >> input;
		}
		if(input == 1)
		{
			//
		}
		else if (input == 2) 
		{
			//
		}
		else if (input == 3) 
		{
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
		}
		else if(input == 4 || std::cin.eof())
		{
			std::cout << "Goodbye" << std::endl;
			return EXIT_SUCCESS;
		}
		else
		{
			std::cout << "Invalid Input" << std::endl;
			std::cout << "> ";	
			std::cin.clear();
			std::cin.ignore(1000,'\n');
		}
	}
}