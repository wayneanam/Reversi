#include <iostream>
#include <vector>

using namespace std;

static int playerID;
const int size = 10;


void findValid(int board[][size]);
void readBoard(int board[][size], vector<int>& possibleMoves);

int main()
{
  int tempB;
  
  vector<int> moves;
  int board[size][size] = {0};
 
  readBoard(board, moves);
  findValid(board);
  
  for(int i = 0; i < moves.size() - 1; i++)
  {
    cout<<moves[i]<<" "<<moves[i + 1]<<endl;
  }
  
  return 0;
}

void readBoard(int board[][size], vector<int>& possibleMoves)
{
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      cin>>board[i][j];
      
      if(board[i][j] == 3)
      {
        possibleMoves.push_back(i);
        possibleMoves.push_back(j);
        possibleMoves.push_back(77);
        possibleMoves.push_back(99);
      }
    }
  }
  cin>>playerID;
}

void findValid(int board[][size])
{
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      if(board[i][j] == 3)
      {
        cout<<i<<endl;
        cout<<j<<endl;
        return;
      }
    }
  }  
}

