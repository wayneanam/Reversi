#include <iostream>
#include <vector>

using namespace std;

int playerID, opponentID;
const int size = 10;

int findFirstVal(int arr[size], int a);
int findFirstVal(int arr[size], int a, int b, int c);
int findLastVal(int arr[size], int a);
int findLastVal(int arr[size], int a, int b, int c);
int highestScore(vector<int>& points);
void displayBoard(int board[][size]);
void displayPoints(vector<int>& points);
void displayMoves(vector<int>& possibleMoves);
void finalOutput(vector<int>& possibleMoves, int index);
void evaluateCorners(vector<int>& possibleMoves, vector<int>& points);
void readBoard(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateHorizontal(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateDiagCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points);


int main()
{
  int vectorSize, scoreSize, score;
  vector<int> moves, points;
  int board[size][size] = {0};

  readBoard(board, moves, points);

  vectorSize = moves.size();
  scoreSize = points.size();
  //scoreSize = vectorSize / 2;
  
  evaluateCorners(moves, points);
  evaluateDiagCorners(board, moves, points);
  evaluateHorizontal(board, moves, points);
  
  
  
  score = highestScore(points);
  
  finalOutput(moves, score);
  //displayMoves(moves);
  //displayPoints(points);
  
  return 0;
}

int findFirstVal(int arr[size], int a)
{
  for(int i = 0; i < size; i++)
  {
    if(arr[i] == a)
    {
      return i;
    }
  }
  
  return -1;
}

int findFirstVal(int arr[size], int a, int b, int c)
{
  for(int i = 0; i < size; i++)
  {
    if((arr[i] != a) && (arr[i] != b) && (arr[i] != c))
    {
      return i;
    }
  }
  
  return -1;  
}


int findLastVal(int arr[size], int a)
{
  for(int i = size - 1; i >= 0; i--)
  {
    if(arr[i] == a)
    {
      return i;
    }
  }
  
  return -1;
}

int findLastVal(int arr[size], int a, int b, int c)
{
  for(int i = size - 1; i >= 0; i--)
  {
    if((arr[i] != a) && (arr[i] != b) && (arr[i] != c))
    {
      return i;
    }
  }
  
  return -1;  
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

void displayPoints(vector<int>& points)
{
  for(int j = 0; j < points.size(); j++)
  {
    cout<<points[j]<<" ";
  }   
  cout<<endl;
}  

void displayMoves(vector<int>& possibleMoves)
{
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    cout<<"("<<possibleMoves[i]<<", "<<possibleMoves[i + 1]<<"), ";
  }
  cout<<endl;
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

void evaluateCorners(vector<int>& possibleMoves, vector<int>& points)
{
  int j = 0;
  
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    if(((possibleMoves[i] == 0) || (possibleMoves[i] == 9))&& ((possibleMoves[i + 1] == 0) || (possibleMoves[i + 1] == 9)))
    {
      cout<<possibleMoves[i]<<" "<<possibleMoves[i + 1]<<endl;
      points[j] = 1000;
    }
    else
    {
      points[j] = 0;
    }
    
    j++;
  }
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
  
  if(playerID == 1)
  {
    opponentID = 2;
  }
  else
  {
    opponentID = 1;
  }
}  
void evaluateHorizontal(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int arr[size];
  int coordA, coordB, index, temp;
  int playerScore = 0, opponentScore = 0;
  int zeroes = 0, ones = 0, twos = 0, threes = 0, counter = 0;
  int zeroA, zeroB, threeA, threeB, playerIDA, playerIDB, nonPlayerIDA, nonPlayerIDB; 
  vector<int> vec;
  bool continuous, skipOnce;
  
  
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    //Grab values and place them in an array and a vector
    for(int j = 0; j < size; j++)
    {
      arr[j] = board[j][possibleMoves[i + 1]];
      vec.push_back(board[j][possibleMoves[i + 1]]);
    }

    coordA = possibleMoves[i];
    coordB = possibleMoves[i + 1];
    
    //Find the first instance where each value occurs
    zeroA = findFirstVal(arr, 0);
    threeA = findFirstVal(arr, 3);
    playerIDA = findFirstVal(arr, playerID);
    nonPlayerIDA = findFirstVal(arr, playerID, 0, 3);

    //Find the last instance where each value occurs
    zeroB = findLastVal(arr, 0);
    threeB = findLastVal(arr, 3);
    playerIDB = findLastVal(arr, playerID);
    nonPlayerIDB = findLastVal(arr, playerID, 0, 3);

    
    vec[coordA] = playerID;
    
    for(int j = coordA; j < size; j++)
    {
      if((vec[j] == nonPlayerIDA) || (vec[j] == playerID))
      {
        vec[j] = playerID;
      }
      else 
      {
        break;
      }
    }
    
    for(int j = coordA; j > 0; j--)
    {
      if((vec[j] == nonPlayerIDA) || (vec[j] == playerID))
      {
        vec[j] = playerID;
      }
      else 
      {
        break;
      }
    } 
    
    
    for(int j = 0; j < size; j++)
    {
      if(vec[j] == playerID)
      {
        playerScore++;
      }
      else if(vec[j] == opponentID)
      {
        opponentScore++;
      }
    }
    
    if(opponentScore == 0)
    {
      points[counter] += (5 * playerScore);
    }
    
    if(opponentScore >= 1)
    {
      points[counter] += -(3 * opponentScore);
    }
    


 //Find the index where playerID occurs
  for(int i = 0; i < size; i++)
  {
    if(vec[i] == playerID)
    {
      index = i;
      break;
    }
  }
  
  skipOnce == false;
  
  for(int i = index; i < size; i++)
  {
    if(vec[i] == playerID)
    {
      continuous = true;
    }
    else
    {
      temp = i; 
      continuous = false;
    }
    
    if(continuous == false)
    {
      for(int i = temp; i < size; i++)
      {
        if(skipOnce == true)
        {
          if(vec[i] == 0)
          {
            points[counter] += 20;
          }
          else if(vec[i] == opponentID)
          {
            points[counter] += -50;
          }
          else if(vec[i] == 3)
          {
            points[counter] += 5;
          }
          else
          {
            points[counter] += 0;
          }
        }
          
        skipOnce = true;
      }
    }
  }
 
    vec.clear();
    counter++;
  }
}

void evaluateDiagCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int counter = 0;

  for(int i = 0; i < possibleMoves.size(); i+= 2)
  {
    if(((possibleMoves[i] == 1) || (possibleMoves[i] == 8))&& ((possibleMoves[i + 1] == 1) || (possibleMoves[i + 1] == 8)))
    {
      if((possibleMoves[i] == 1) && (possibleMoves[i + 1] == 1))
      {
        //There is a possible move at 1 1
        if(board[0][0] == playerID)
        {
          points[counter] += 60;
        }
        else if((board[0][0] == 0) || (board[0][0] == opponentID))
        {
          points[counter] += -60;
        }
      }
      else if((possibleMoves[i] == 1) && (possibleMoves[i + 1] == 8))
      {
        //There is a possible move at 1 8
        if(board[0][9] == playerID)
        {
          points[counter] += 60;
        }
        else if((board[0][9] == 0) || (board[0][9] == opponentID))
        {
          points[counter] += -60;
        }
      }
      else if((possibleMoves[i] == 8) && (possibleMoves[i + 1] == 1))
      {
        //There is a possible move at 8 1
        if(board[9][0] == playerID)
        {
          points[counter] += 60;
        }
        else if((board[9][0] == 0) || (board[9][0] == opponentID))
        {
          points[counter] += -60;
        }
      }
      else if((possibleMoves[i] == 8) && (possibleMoves[i + 1] == 8))
      {
        //There is a possible move at 8 8
        if(board[9][9] == playerID)
        {
          points[counter] += 60;
        }
        else if((board[9][9] == 0) || (board[9][9] == opponentID))
        {
          points[counter] += -60;
        }
      }
      else
      {
        points[counter] -= -50;
      }
    }
    else
    {
      points[counter] += 5;
    }
    
    counter++;
  }
}
