#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int playerID;
const int size = 10;

void findCorners(vector<int>& possibleMoves);
void readBoard(int board[][size], vector<int>& possibleMoves);
void firstMove(vector<int>& possibleMoves);
void displayMoves(vector<int>& possibleMoves);
void displayBoard(int board[][size]);
int getPoints(int board[][size], int a, int b);

int main()
{
  srand(time(NULL));
  
  int vectorSize, score, scoreSize, largest, index, counter;
  vector<int> moves, points;
  int board[size][size] = {0};
  
  readBoard(board, moves);  
  
  vectorSize = moves.size();
 
 //Gets a score for each individual move
  for(int i = 0; i < vectorSize; i+=2)
  {
    score = getPoints(board, moves[i], moves[i+1]);
    points.push_back(score);
  }
  
  //Finds the largest score
  
  
  scoreSize = points.size();
  
  for(int i = 0; i < scoreSize - 1; i++)
  {
    if(points[i] > points[i + 1])
    {
      index = i;
      largest = points[i];
    }
    else
    {
      index = i + 1;
      largest = points[i + 1];
    }
  }
  
  counter = 0;
  
  for(int i = 0; i < vectorSize; i+=2)
  {
    if(counter == index)
    {
      cout<<moves[i]<<" "<<moves[i + 1]<<endl;
      break;
    }
    counter++;
  }
  
  firstMove(moves);
  
  return 0;
}
 


void findCorners(vector<int>& possibleMoves)
{
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    if((possibleMoves[i] == 0) && (possibleMoves[i+1] == 0))
    {
      cout<<possibleMoves[i]<<" "<<possibleMoves[i + 1]<<endl;
      return;
    }
    
    if((possibleMoves[i] == 0) && (possibleMoves[i+1] == 9))
    {
      cout<<possibleMoves[i]<<" "<<possibleMoves[i + 1]<<endl;
      return;
    }
    
    if((possibleMoves[i] == 9) && (possibleMoves[i+1] == 0))
    {
      cout<<possibleMoves[i]<<" "<<possibleMoves[i + 1]<<endl;
      return;
    }
    
    if((possibleMoves[i] == 9) && (possibleMoves[i+1] == 9))
    {
      cout<<possibleMoves[i]<<" "<<possibleMoves[i + 1]<<endl;
      return;
    }
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
        //possibleMoves.push_back(-1);
      }
    }
  }
  cin>>playerID;
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
  
void displayMoves(vector<int>& possibleMoves)
{
  for(int i = 0; i < possibleMoves.size(); i++)
  {
    cout<<possibleMoves[i]<<" ";
  }
}  


int getPoints(int board[][size], int a, int b)
{
  int points = 0;
  
  //Strongly encourages making moves at corners
  if(((a == 0) || (a == 9)) && ((b == 0) || (b == 9)))
  {
    cout<<a<<" "<<b<<endl;
    points += 100;
    return points;
  }
  
  //Punishes making moves that are directly diagnol to a corner
  if(((a == 1) || (a == 8)) && ((b == 1) || (b == 8)))
  {
    //If corner is filled by me then a move in this area is strongly encouraged
    if((a - 1) == 0)
    {
      if((b - 1) == 0)
      {
        //I am close to 0,0
        if(board[a-1][b-1] == playerID)
        {
          points += 20;
        }
        else
        {
          points -= 20;
        }
      }
      if((b + 1) == 9)
      {
        //I am close to 0,9
        if(board[a-1][b+1] == playerID)
        {
          points += 20;
        }
        else
        {
          points -= 20;
        }
      }
    }      
    else if((a + 1) == 9)
    {
      if((b - 1) == 0)
      {
        //I am close to 9,0
        if(board[a+1][b-1] == playerID)
        {
          points += 20;
        }
        else
        {
          points -= 20;
        }
      }
      if((b + 1) == 9)
      {
        //I am close to 9,9
        if(board[a+1][b+1] == playerID)
        {
          points += 20;
        }
        else
        {
          points -= 20;
        }
      }
    }
    else
    {
      points -= 50;
    }
  }
  
  //Discourages putting stones near edges especially when surrounded
  if((a == 0) || (a == 9))
  {
    if(((b - 1) >= 0) ||((b + 1) <= 9))
    {
      if((board[a][b - 1] != playerID) && (board[a][b + 1] != playerID))
      {
        points -= 20;
      }
      else
      {
        points -= 10;
      }
    }  
  }
  else if((b == 0) || (b == 9))
  {
    if(((a - 1) >= 0) ||((a + 1) <= 9))
    {
      if((board[a - 1][b] != playerID) && (board[a + 1][b] != playerID))
      {
        points -= 20;
      }
      else
      {
        points -= 10;
      }
    }      
    
  }

  return points;
}


//WIP  
void firstMove(vector<int>& possibleMoves)
{
  cout<<possibleMoves[0]<<" "<<possibleMoves[1]<<endl; 
}