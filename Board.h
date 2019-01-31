#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <queue>

class Board
{
public:
	Board (int row, int column, int total);
	~Board();
	//void regularSearch (int row, int column, int totalNum, int currNum, int** startBoard, int** guessBoard, bool ** visited);
	//void lastSearch (int row, int column, int totalNum, int** startBoard, int** guessBoard, bool** visited);
	bool isFinish();
	void Search();
	std::pair<int,int> Evaluation();
	void Update(std::pair<int,int> curr);
	void updateHelper(std::pair<int,int> curr, int value);
	int getAttempts();
	void Guess();
	void printGuess();
	void reWrite();
	void generate(int** board,std::queue<std::pair<int,int>> myQueue, bool** visit,int iter);
private:
	int row;
	int column;
	int** startBoard;
	int** guessBoard;
	int totalNum;
	int currNum;
	int attempts;
	bool** lowPriority;
};

#endif