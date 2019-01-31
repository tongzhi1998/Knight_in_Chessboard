#include "Board.h"
#include <iostream>
#include <ctime>
#include <queue>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const int unExplored = -1;
const int noKnight = -2;

Board::Board (int row, int column, int totalNum)
{
	attempts = 0;// num of attempts
	currNum = 0; // num of knight discovered
	queue <pair<int,int>> myQueue;// queue of 2D array
	bool** visit;// indicate whether a grid in the board is visited
	int* position;// position of knights
	this->row = row;
	this->column = column;
	this->totalNum = totalNum;
	lowPriority = new bool* [row];
	for (int i=0;i<row;i++)
	{
		lowPriority[i] = new bool [column];
	}
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<column;j++)
		{
			lowPriority[i][j] = false;
		}
	}
	guessBoard = new int* [row];
	for (int i=0;i<row;i++)
	{
		guessBoard[i]=new int [column];
	}
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<column;j++)
		{
			guessBoard[i][j]=unExplored;
		}
	}
	position = new int [totalNum];
	visit = new bool* [row];
	for (int i=0;i<row;i++)
	{
		visit[i] = new bool [column];
	}
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<column;j++)
		{
			visit[i][j]=false;
		}
	}
	startBoard = new int* [row];
	for (int i=0;i<row;i++)
	{
		startBoard[i]=new int [column];
	}
	int sampleSpace = row*column;
	for (int i=0;i<totalNum;i++)
	{
		position[i]=rand()%sampleSpace;
		bool valid = false;
		while (!valid)
		{
			valid = true;
			for (int j=0;j<i;j++)
			{
				if (position[i]==position[j])
				{
					position[i]=rand()%sampleSpace;
					valid = false;
				}
			}
		}
	}
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<column;j++)
		{
			startBoard[i][j]=-1;
		}
	}
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<column;j++)
		{
			for (int k=0;k<totalNum;k++)
			{
				if (i*row+j==position[k])
				{
					startBoard[i][j]=0;
					visit[i][j]=true;
					pair <int, int> temp (i,j);
					myQueue.push(temp);
					break;
				}
			}
		}
	}
	int iter = 0;
	generate(startBoard,myQueue,visit,iter);
}

Board::~Board()
{
	for (int i=0;i<row;i++)
	{
		delete []startBoard[i];
		delete []guessBoard[i];
	}
	delete []startBoard;
	delete []guessBoard;
}

void Board::generate(int** board,std::queue<std::pair<int,int>> myQueue, bool** visit,int iter)
{
	while(!myQueue.empty())
	{
		while (board[myQueue.front().first][myQueue.front().second]==iter)
		{
			if (myQueue.empty())
				break;
			pair <int,int> temp = myQueue.front();
			myQueue.pop();
			if (temp.first-2>=0&&temp.second-1>=0 && visit[temp.first-2][temp.second-1]==false)
			{
				pair <int,int> curr (temp.first-2,temp.second-1);
				myQueue.push(curr);
				visit[temp.first-2][temp.second-1]=true;
				board[temp.first-2][temp.second-1]=iter+1;
			}
			if (temp.first-1>=0&&temp.second-2>=0 && visit[temp.first-1][temp.second-2]==false)
			{
				pair <int,int> curr (temp.first-1,temp.second-2);
				myQueue.push(curr);
				visit[temp.first-1][temp.second-2]=true;
				board[temp.first-1][temp.second-2]=iter+1;
			}
			if (temp.first+1<row&&temp.second-2>=0 && visit[temp.first+1][temp.second-2]==false)
			{
				pair <int,int> curr (temp.first+1,temp.second-2);
				myQueue.push(curr);
				visit[temp.first+1][temp.second-2]=true;
				board[temp.first+1][temp.second-2]=iter+1;
			}
			if (temp.first+2<row&&temp.second-1>=0 && visit[temp.first+2][temp.second-1]==false)
			{
				pair <int,int> curr (temp.first+2,temp.second-1);
				myQueue.push(curr);
				visit[temp.first+2][temp.second-1]=true;
				board[temp.first+2][temp.second-1]=iter+1;
			}
			if (temp.first+2<row&&temp.second+1<column && visit[temp.first+2][temp.second+1]==false)
			{
				pair <int,int> curr (temp.first+2,temp.second+1);
				myQueue.push(curr);
				visit[temp.first+2][temp.second+1]=true;
				board[temp.first+2][temp.second+1]=iter+1;
			}
			if (temp.first+1<row&&temp.second+2<column && visit[temp.first+1][temp.second+2]==false)
			{
				pair <int,int> curr (temp.first+1,temp.second+2);
				myQueue.push(curr);
				visit[temp.first+1][temp.second+2]=true;
				board[temp.first+1][temp.second+2]=iter+1;
			}
			if (temp.first-1>=0&&temp.second+2<column && visit[temp.first-1][temp.second+2]==false)
			{
				pair <int,int> curr (temp.first-1,temp.second+2);
				myQueue.push(curr);
				visit[temp.first-1][temp.second+2]=true;
				board[temp.first-1][temp.second+2]=iter+1;
			}
			if (temp.first-2>=0&&temp.second+1<column && visit[temp.first-2][temp.second+1]==false)
			{
				pair <int,int> curr (temp.first-2,temp.second+1);
				myQueue.push(curr);
				visit[temp.first-2][temp.second+1]=true;
				board[temp.first-2][temp.second+1]=iter+1;
			}
			if (myQueue.empty())
				break;
		}
		iter++;
	}
}

int Board::getAttempts()
{
	return attempts;
}

void Board::Search()
{
	if (attempts==0)
	{
		std::pair<int,int> curr;
		curr.first = (row-1)/2;
		curr.second = (column-1)/2;
		guessBoard[curr.first][curr.second]=startBoard[curr.first][curr.second];
		attempts++;
		if (startBoard[curr.first][curr.second]==0){
			int i = curr.first;
			int j = curr.second;
			if (i-2>=0&&j-1>=0&&guessBoard[i-2][j-1]==-1)
				lowPriority[i][j]=true;
			if (i-1>=0&&j-2>=0&&guessBoard[i-1][j-2]==-1)
				lowPriority[i][j]=true;
			if (i+1<row&&j-2>=0&&guessBoard[i+1][j-2]==-1)
				lowPriority[i][j]=true;
			if (i+2<row&&j-1>=0&&guessBoard[i+2][j-1]==-1)
				lowPriority[i][j]=true;
			if (i+2<row&&j+1<column&&guessBoard[i+2][j+1]==-1)
				lowPriority[i][j]=true;
			if (i+1<row&&j+2<column&&guessBoard[i+1][j+2]==-1)
				lowPriority[i][j]=true;
			if (i-1>=0&&j+2<column&&guessBoard[i-1][j+2]==-1)
				lowPriority[i][j]=true;
			if (i-2>=0&&j+1<column&&guessBoard[i-2][j+1]==-1)
				lowPriority[i][j]=true;
			currNum++;
		}
	}
	else
	{
		std::pair<int,int> curr = Evaluation();
		guessBoard[curr.first][curr.second] = startBoard[curr.first][curr.second];
		Update(curr);
		attempts++;
	}
}

void Board::reWrite()
{
	for (int x=0;x<row;x++)
	{
		for (int y=0;y<column;y++)
		{
			if (guessBoard[x][y]==0)
			{
				int ** generatedBoard;
				generatedBoard = new int*[row];
				for (int i=0;i<row;i++)
				{
					generatedBoard[i] = new int [column];
				}
				for (int i=0;i<row;i++)
				{
					for (int j=0;j<column;j++)
					{
						generatedBoard[i][j]=-5;
					}
				}
				bool ** visited;
				visited = new bool* [row];
				for (int i=0;i<row;i++)
				{
					visited[i] = new bool [column];
				}
				for (int i=0;i<row;i++)
				{
					for (int j=0;j<column;j++)
					{
						visited[i][j]=false;
					}
				}
				int iter = 0;
				std::queue<pair<int,int>> myQueue;
				myQueue.push(make_pair(x,y));
				generatedBoard[x][y]=0;
				generate(generatedBoard,myQueue,visited,iter);
				for (int i=0;i<row;i++)
				{
					for (int j=0;j<column;j++)
					{
						if (guessBoard[i][j]!=0&&guessBoard[i][j]==generatedBoard[i][j])
						{
							updateHelper(make_pair(i,j),guessBoard[i][j]);
							guessBoard[i][j]=-2;
						}
					}
				}
			}	
		}
	}
}

void Board::Update(std::pair<int,int> curr)
{
	int x = curr.first;
	int y = curr.second;
	if (guessBoard[x][y]==1||guessBoard[x][y]==2)
		return;
	if (guessBoard[x][y]==0)
	{
		int i=x;
		int j=y;
		if (i-2>=0&&j-1>=0&&guessBoard[i-2][j-1]==-1)
			lowPriority[i][j]=true;
		if (i-1>=0&&j-2>=0&&guessBoard[i-1][j-2]==-1)
			lowPriority[i][j]=true;
		if (i+1<row&&j-2>=0&&guessBoard[i+1][j-2]==-1)
			lowPriority[i][j]=true;
		if (i+2<row&&j-1>=0&&guessBoard[i+2][j-1]==-1)
			lowPriority[i][j]=true;
		if (i+2<row&&j+1<column&&guessBoard[i+2][j+1]==-1)
			lowPriority[i][j]=true;
		if (i+1<row&&j+2<column&&guessBoard[i+1][j+2]==-1)
			lowPriority[i][j]=true;
		if (i-1>=0&&j+2<column&&guessBoard[i-1][j+2]==-1)
			lowPriority[i][j]=true;
		if (i-2>=0&&j+1<column&&guessBoard[i-2][j+1]==-1)
			lowPriority[i][j]=true;
		currNum++;
		int ** generatedBoard;
		generatedBoard = new int*[row];
		for (int i=0;i<row;i++)
		{
			generatedBoard[i] = new int [column];
		}
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<column;j++)
			{
				generatedBoard[i][j]=-5;
			}
		}
		bool ** visited;
		visited = new bool* [row];
		for (int i=0;i<row;i++)
		{
			visited[i] = new bool [column];
		}
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<column;j++)
			{
				visited[i][j]=false;
			}
		}
		int iter = 0;
		std::queue<pair<int,int>> myQueue;
		myQueue.push(make_pair(x,y));
		generatedBoard[x][y]=0;
		generate(generatedBoard,myQueue,visited,iter);
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<column;j++)
			{
				if (guessBoard[i][j]!=0&&guessBoard[i][j]==generatedBoard[i][j])
				{
					updateHelper(make_pair(i,j),guessBoard[i][j]);
					guessBoard[i][j]=-2;
				}
			}
		}
	}
	else
	{
		int value = guessBoard[x][y];
		updateHelper (curr,value);
	}
}

void Board::updateHelper(std::pair<int,int>curr, int value)
{
	if (value==1)
		return;
	int i=curr.first;
	int j = curr.second;
	if (i-2>=0&&j-1>=0&&guessBoard[i-2][j-1]==-1)
	{
		guessBoard[i-2][j-1]=-2;
		updateHelper(make_pair(i-2,j-1),value-1);
	}
	if (i-1>=0&&j-2>=0&&guessBoard[i-1][j-2]==-1)
	{
		guessBoard[i-1][j-2]=-2;
		updateHelper(make_pair(i-1,j-2),value-1);
	}
	if (i+1<row&&j-2>=0&&guessBoard[i+1][j-2]==-1)
	{
		guessBoard[i+1][j-2]=-2;
		updateHelper(make_pair(i+1,j-2),value-1);
	}
	if (i+2<row&&j-1>=0&&guessBoard[i+2][j-1]==-1)
	{
		guessBoard[i+2][j-1]=-2;
		updateHelper(make_pair(i+2,j-1),value-1);
	}
	if (i+2<row&&j+1<column&&guessBoard[i+2][j+1]==-1)
	{
		guessBoard[i+2][j+1]=-2;
		updateHelper(make_pair(i+2,j+1),value-1);
	}
	if (i+1<row&&j+2<column&&guessBoard[i+1][j+2]==-1)
	{
		guessBoard[i+1][j+2]=-2;
		updateHelper(make_pair(i+1,j+2),value-1);
	}
	if (i-1>=0&&j+2<column&&guessBoard[i-1][j+2]==-1)
	{
		guessBoard[i-1][j+2]=-2;
		updateHelper(make_pair(i-1,j+2),value-1);
	}
	if (i-2>=0&&j+1<column&&guessBoard[i-2][j+1]==-1)
	{
		guessBoard[i-2][j+1]=-2;
		updateHelper(make_pair(i-2,j+1),value-1);
	}
}


std::pair<int,int> Board::Evaluation()
{
	std::vector <std::pair<int,int>> potential;
	/* when there is only one knight left in the board */
	if (currNum==totalNum-1)
	{
		int positiveNum = 0;
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<column;j++)
			{
				if (guessBoard[i][j]>0)
				{
					positiveNum++;
				}
			}
		}
		if (positiveNum!=0)
		{
			for (int x=0;x<row;x++)
			{
				for (int y=0;y<column;y++)
				{
					/* This part is used to generate the imaginary board */
					if (guessBoard[x][y]==-1)
					{
						int ** generatedBoard;
						generatedBoard = new int*[row];
						for (int i=0;i<row;i++)
						{
							generatedBoard[i] = new int [column];
						}
						for (int i=0;i<row;i++)
						{
							for (int j=0;j<column;j++)
							{
								generatedBoard[i][j]=-5;
							}
						}
						bool ** visited;
						visited = new bool* [row];
						for (int i=0;i<row;i++)
						{
							visited[i] = new bool [column];
						}
						for (int i=0;i<row;i++)
						{
							for (int j=0;j<column;j++)
							{
								visited[i][j]=false;
							}
						}
						int iter = 0;
						std::queue<pair<int,int>> myQueue;
						myQueue.push(make_pair(x,y));
						generatedBoard[x][y]=0;
						generate(generatedBoard,myQueue,visited,iter);
						/* end of generation */
						int count=0;
						for (int i=0;i<row;i++)
						{
							for (int j=0;j<column;j++)
							{
								if (generatedBoard[i][j]==guessBoard[i][j])
									count++;
							}
						}
						if (count!=positiveNum){
							guessBoard[x][y]=-2;
						}
					}
				}
			}
		}
	}

	/* If there is a 1 in the guessBoard */
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<column;j++)
		{
			if (guessBoard[i][j]==1)
			{
				std:: pair<int,int> curr;
				curr.first = i*row+j;
				int temp=0;
				if (i-2>=0&&j-1>=0&&guessBoard[i-2][j-1]==-1)
					temp--;
				if (i-1>=0&&j-2>=0&&guessBoard[i-1][j-2]==-1)
					temp--;
				if (i+1<row&&j-2>=0&&guessBoard[i+1][j-2]==-1)
					temp--;
				if (i+2<row&&j-1>=0&&guessBoard[i+2][j-1]==-1)
					temp--;
				if (i+2<row&&j+1<column&&guessBoard[i+2][j+1]==-1)
					temp--;
				if (i+1<row&&j+2<column&&guessBoard[i+1][j+2]==-1)
					temp--;
				if (i-1>=0&&j+2<column&&guessBoard[i-1][j+2]==-1)
					temp--;
				if (i-2>=0&&j+1<column&&guessBoard[i-2][j+1]==-1)
					temp--;
				curr.second = temp;
				if (temp!=0)
					potential.push_back(curr);
			}
		}
	}
	if (potential.size()>0)
	{
		int max = potential[0].second;
		for (std::vector<pair<int,int>>::iterator pairIter = potential.begin();pairIter!=potential.end();pairIter++)
		{
			if (pairIter->second>max){
				max = pairIter->second;
			}
		}
		for (std::vector<pair<int,int>>::iterator pairIter = potential.begin();pairIter!=potential.end();pairIter++)
		{
			if (pairIter->second==max)
			{
				int i = pairIter->first/row;
				int j = pairIter->first%row;
				if (i-2>=0&&j-1>=0&&guessBoard[i-2][j-1]==-1)
					return std::make_pair(i-2,j-1);
				else if (i-1>=0&&j-2>=0&&guessBoard[i-1][j-2]==-1)
				{
					std::pair<int,int> result(i-1,j-2);
					return result;
				}
				else if (i+1<row&&j-2>=0&&guessBoard[i+1][j-2]==-1)
				{
					std::pair<int,int> result(i+1,j-2);
					return result;
				}
				else if (i+2<row&&j-1>=0&&guessBoard[i+2][j-1]==-1)
				{
					std::pair<int,int> result(i+2,j-1);
					return result;
				}
				else if (i+2<row&&j+1<column&&guessBoard[i+2][j+1]==-1)
				{
					std::pair<int,int> result(i+2,j+1);
					return result;
				}
				else if (i+1<row&&j+2<column&&guessBoard[i+1][j+2]==-1)
				{
					std::pair<int,int> result(i+1,j+2);
					return result;
				}
				else if (i-1>=0&&j+2<column&&guessBoard[i-1][j+2]==-1)
				{
					std::pair<int,int> result(i-1,j+2);
					return result;
				}
				else if (i-2>=0&&j+1<column&&guessBoard[i-2][j+1]==-1)
				{
					std::pair<int,int> result(i-2,j+1);
					attempts--;
					return result;
				}
			}
		}
	}

	/* If there is a 2 in the guessBoard */
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<column;j++)
		{
			if (guessBoard[i][j]==2)
			{
				std:: pair<int,int> curr;
				curr.first = i*row+j;
				int temp=0;
				if (i-2>=0&&j-1>=0&&guessBoard[i-2][j-1]==-1)
					temp--;
				if (i-1>=0&&j-2>=0&&guessBoard[i-1][j-2]==-1)
					temp--;
				if (i+1<row&&j-2>=0&&guessBoard[i+1][j-2]==-1)
					temp--;
				if (i+2<row&&j-1>=0&&guessBoard[i+2][j-1]==-1)
					temp--;
				if (i+2<row&&j+1<column&&guessBoard[i+2][j+1]==-1)
					temp--;
				if (i+1<row&&j+2<column&&guessBoard[i+1][j+2]==-1)
					temp--;
				if (i-1>=0&&j+2<column&&guessBoard[i-1][j+2]==-1)
					temp--;
				if (i-2>=0&&j+1<column&&guessBoard[i-2][j+1]==-1)
					temp--;
				curr.second = temp;
				if (temp!=0)
					potential.push_back(curr);
			}
		}
	}
	if (potential.size()>0)
	{
		int max = potential[0].second;
		for (std::vector<pair<int,int>>::iterator pairIter = potential.begin();pairIter!=potential.end();pairIter++)
		{
			if (pairIter->second>max){
				max = pairIter->second;
			}
		}
		for (std::vector<pair<int,int>>::iterator pairIter = potential.begin();pairIter!=potential.end();pairIter++)
		{
			if (pairIter->second==max)
			{
				int i = pairIter->first/row;
				int j = pairIter->first%row;
				if (i-2>=0&&j-1>=0&&guessBoard[i-2][j-1]==-1)
				{
					std::pair<int,int> result(i-2,j-1);
					return result;
				}
				else if (i-1>=0&&j-2>=0&&guessBoard[i-1][j-2]==-1)
				{
					std::pair<int,int> result(i-1,j-2);
					return result;
				}
				else if (i+1<row&&j-2>=0&&guessBoard[i+1][j-2]==-1)
				{
					std::pair<int,int> result(i+1,j-2);
					return result;
				}
				else if (i+2<row&&j-1>=0&&guessBoard[i+2][j-1]==-1)
				{
					std::pair<int,int> result(i+2,j-1);
					return result;
				}
				else if (i+2<row&&j+1<column&&guessBoard[i+2][j+1]==-1)
				{
					std::pair<int,int> result(i+2,j+1);
					return result;
				}
				else if (i+1<row&&j+2<column&&guessBoard[i+1][j+2]==-1)
				{
					std::pair<int,int> result(i+1,j+2);
					return result;
				}
				else if (i-1>=0&&j+2<column&&guessBoard[i-1][j+2]==-1)
				{
					std::pair<int,int> result(i-1,j+2);
					return result;
				}
				else if (i-2>=0&&j+1<column&&guessBoard[i-2][j+1]==-1)
				{
					std::pair<int,int> result(i-2,j+1);
					attempts--;
					return result;
				}
			}
		}
	}

	/* If there is no significant clue*/
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<row;j++)
		{
			if (guessBoard[i][j]==-1)
			{
				std:: pair<int,int> curr;
				curr.first = i*row+j;
				int temp=0;
				if (i-2>=0&&j-1>=0&&guessBoard[i-2][j-1]==-1)
					temp++;
				if (i-1>=0&&j-2>=0&&guessBoard[i-1][j-2]==-1)
					temp++;
				if (i+1<row&&j-2>=0&&guessBoard[i+1][j-2]==-1)
					temp++;
				if (i+2<row&&j-1>=0&&guessBoard[i+2][j-1]==-1)
					temp++;
				if (i+2<row&&j+1<column&&guessBoard[i+2][j+1]==-1)
					temp++;
				if (i+1<row&&j+2<column&&guessBoard[i+1][j+2]==-1)
					temp++;
				if (i-1>=0&&j+2<column&&guessBoard[i-1][j+2]==-1)
					temp++;
				if (i-2>=0&&j+1<column&&guessBoard[i-2][j+1]==-1)
					temp++;
				if (lowPriority[i][j])
					continue;
				curr.second = temp;
				if (temp==8)
				{
					std::pair<int,int> result (i,j);
					return result;
				}
				potential.push_back(curr);
			}
		}
	}
	int max = potential[0].second;
	for (std::vector<pair<int,int>>::iterator pairIter = potential.begin();pairIter!=potential.end();pairIter++)
	{
		if (pairIter->second>max){
			max = pairIter->second;
		}
	}
	for (std::vector<pair<int,int>>::iterator pairIter = potential.begin();pairIter!=potential.end();pairIter++)
	{
		if (pairIter->second==max)
		{
			int i = pairIter->first/row;
			int j= pairIter->first%row;
			std::pair <int,int> result (i,j);
			return result;
		}
	}
	return potential[0];
}

void Board::Guess()
{
	while (currNum!=totalNum)
	{
		//std::cout << "In " << getAttempts()+1 << "th try" << std::endl;
		Search();
		reWrite();
		//printGuess();
		//cout << endl;
		//std::cin.ignore (256,'\n');
	}
}

void Board::printGuess()
{
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<column;j++)
		{
			std::cout << setw(3)<< guessBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}
}