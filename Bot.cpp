#include <iostream>
#include <vector>

using namespace std;

int playerID;
const int size = 10;


int highestScore(vector<int>& points);
void displayBoard(int board[][size]);
void firstMove(vector<int>& possibleMoves);
void displayPoints(vector<int>& points);
void displayMoves(vector<int>& possibleMoves);
void finalOutput(vector<int>& possibleMoves, int index);
void readBoard(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateCorners(vector<int>& possibleMoves, vector<int>& points);
void evaluateHorizontal(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateNearCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points);

int main()
{ 
  int vectorSize, scoreSize, index;
  vector<int> moves, points;
  int board[size][size] = {0};
  
  readBoard(board, moves, points);  
  
  vectorSize = moves.size();
  scoreSize = vectorSize / 2;
  
  evaluateCorners(moves, points); 
  evaluateNearCorners(board, moves, points); 
  evaluateHorizontal(board, moves, points); 
  
  index = highestScore(points);
  
  finalOutput(moves, index);

  return 0;
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
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    cout<<"("<<possibleMoves[i]<<", "<<possibleMoves[i + 1]<<"), ";
  }
  cout<<endl;
}  

void readBoard(int board[][size], vector<int>& possibleMoves, vector<int>& points)
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
        points.push_back(0);
      }
    }
  }
  cin>>playerID;
}

void evaluateCorners(vector<int>& possibleMoves, vector<int>& points)
{
  int j = 0;
  
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    if(((possibleMoves[i] == 0) || (possibleMoves[i] == 9))&& ((possibleMoves[i + 1] == 0) || (possibleMoves[i + 1] == 9)))
    {
      points[j] = 100;
    }
    else
    {
      points[j] = 0;
    }
    
    j++;
  }
}

void evaluateNearCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int j =0;

  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    if(((possibleMoves[i] == 1) || (possibleMoves[i] == 8))&& ((possibleMoves[i + 1] == 1) || (possibleMoves[i + 1] == 8)))
    {
      if((possibleMoves[i] - 1) == 0)
      {
        if((possibleMoves[i + 1] - 1) == 0)
        {
          //I am near 0,0
          if((board[0][0] == 0) || (board[0][0] != playerID))
          {
            points[j] += 0;
          }
          else
          {
            points[j] += 5;
          }
        }
        else if((possibleMoves[i + 1] + 1) == 9)
        {
          //I am near 0,9
          if((board[0][9] == 0) || (board[0][9] != playerID))
          {
            points[j] += 0;
          }
          else
          {
            points[j] += 5;
          }
        }
      }
      else if((possibleMoves[i] + 1) == 9)
      {
        if((possibleMoves[i + 1] - 1) == 0)
        {
          //I am near 9,0
          if((board[9][0] == 0) || (board[9][0] != playerID))
          {
            points[j] += 0;
          }
          else
          {
            points[j] += 5;
          }
        }
        else if((possibleMoves[i + 1] + 1) == 9)
        {
          //I am near 9,9
          if((board[9][9] == 0) || (board[9][9] != playerID))
          {
            points[j] += 0;
          }
          else
          {
            points[j] += 5;
          }
        }
      }
    }
    else
    {
      points[j] += 5;
    }
    
    j++;
  }
} 
       
       
void firstMove(vector<int>& possibleMoves)
{
  cout<<possibleMoves[0]<<" "<<possibleMoves[1]<<endl; 
}  


void displayPoints(vector<int>& points)
{
  for(int j = 0; j < points.size(); j++)
  {
    cout<<points[j]<<" ";
  }   
  cout<<endl;
}  


void evaluateHorizontal(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int counter = 0, zero = 0, player1 = 0, player2 = 0, possible = 0, tempPoints = 0;
  int arr[size];
  bool skipOnce, skipTwice;
  
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    tempPoints = 0;
    
    for(int j = 0; j < size; j++)
    {
      if(board[j][possibleMoves[i + 1]] == 0)
      {
        zero++;
      }
      else if(board[j][possibleMoves[i + 1]] == 1)
      {
        player1++;
      }
      else if(board[j][possibleMoves[i + 1]] == 2)
      {
        player2++;
      }
      else if(board[j][possibleMoves[i + 1]] == 3)
      {
        possible++;
      }
      
      arr[j] = board[j][possibleMoves[i + 1]];
    }
    
    skipOnce = false;
    
    for(int j = possibleMoves[i]; j < size; j++)
    {
      if(skipOnce == true)
      {
        if((arr[j] == 0) || (arr[j] == 3) || (arr[j] != playerID))
        {
          tempPoints += 0;
        }
        else
        {
          skipTwice = false;
          
          for(int k = j; k < size; k++)
          {
            if(skipTwice == true)
            {
              if(arr[k] == playerID)
              {
                tempPoints += 2;
              }
              else if(arr[k] == 0)
              {
                tempPoints += 0;
              }
              else
              {
                tempPoints -= 2;
                break;
              } 
            }
            
            skipTwice = true;
          }
        }
      }
      
      skipOnce = true;   
    }
    
    points[counter] += tempPoints;
    counter++;
  }
}     


void finalOutput(vector<int>& possibleMoves, int index)
{
  int counter = 0;
  
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    if(counter == index)
    {
      cout<<possibleMoves[i]<<" "<<possibleMoves[i + 1]<<endl;
      break;
    }
    counter++;
  }
}  

int highestScore(vector<int>& points)
{
  int largest, index = 0;
  
  largest = points[0];
  
  for(int i = 1; i < points.size() - 1; i++)
  {
    if(largest < points[i])
    {
      largest = points[i];
      index = i;
    }
  }
  
  return index;  
}

