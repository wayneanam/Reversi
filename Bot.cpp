#include <iostream>
#include <vector>
#include <string>

using namespace std;

static int playerID = 1;
const int min = 0;
const int size = 10;

int countPoints(int board[][size], int a, int b);
void findValid(int board[][size]);
void readBoard(int board[][size], vector<int>& possibleMoves);
void displayBoard(int board[][size]);

int main()
{
  int tempB;
  
  vector<int> moves;
  int board[size][size] = {0};
 
  readBoard(board, moves);
  

  int x = moves.size();
  int counter = 1;
  
  for(int i = 0; i < x; i++)
  {
    if(moves[i] == 77)
    {
      moves[i] = countPoints(board, moves[i-2], moves[i - 1]);
    }
  }
 
  //Finds the move that gives the most points
  for(int i = 0; i < x - 2; i++)
  {
    i+=2;
    if(moves[i] > moves[i + 2])
     tempB = i;
  }
 
  cout<<moves[tempB-2]<<endl;
  cout<<moves[tempB-1]<<endl;
   
  for(int i = 0; i < x; i++)
  {
    cout<<moves[i]<<"-";
  }
  
  return 0;
}

//You aren't accounting for which player you are. I'm Player 1 always
int countPoints(int board[][size], int a, int b)
{
  int points = 0;
  
  //The edge of the board carries the most risk (I think) 
  if((a > 1) && (a < 8))
    points +=5;
  
  if((b > 1) && (b < 8))
    points += 5;
  
  //Horizontal point tracking
  if((a > 0) && (a < 9))
  {
    if(board[a-1][b] == 1)
      points += 1;
   
    if(board[a+1][b] == 1)
      points += 1 ;
  }

  if((b > 0) && (b < 9))
  {
    if(board[a][b - 1] == 1)
      points += 1;
   
    if(board[a+1][b + 1] == 1)
      points += 1  ; 
  }
  
  return points;
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

void displayBoard(int board[][size])
{
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      cout<<board[i][j]<<" ";
    }
    cout<<endl;
  } 
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
      }
    }
  }
  cin>>playerID;
}