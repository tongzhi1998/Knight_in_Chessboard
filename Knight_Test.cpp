#include "Board.h"
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
	double average = 0;
	for (int i=0;i<10000;i++)
	{
		Board* gameBoard = new Board(8,8,1);
		gameBoard->Guess();
		//cout << gameBoard->getAttempts() << endl;
		average+=gameBoard->getAttempts();
		delete gameBoard;
	}
	cout << endl;
	average = average/10000.0;
	cout << average << endl;
	return 0;
}