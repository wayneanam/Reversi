#include <iostream>
#include <vector>

using namespace std;

int playerID, opponentID;
const int size = 10;

int findFirstVal(vector<int> arr, int a);
int findLastVal(vector<int> arr, int a);
int highestScore(vector<int>& points);
void displayBoard(int board[][size]);
void displayPoints(vector<int>& points);
void displayVector(vector<int>& vec);
void displayMoves(vector<int>& possibleMoves);
void finalOutput(vector<int>& possibleMoves, int index);
void evaluateCorners(vector<int>& possibleMoves, vector<int>& points);
void readBoard(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateVertical(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateHorizontal(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateDiagCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateNearCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateFurtherCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points);


int main()
{
  int score;
  vector<int> moves, points;
  int board[size][size] = {0};

  readBoard(board, moves, points);
  
  evaluateCorners(moves, points);
  evaluateDiagCorners(board, moves, points);
  evaluateNearCorners(board, moves, points);
  evaluateFurtherCorners(board, moves, points);
  evaluateVertical(board, moves, points);
  
  
  
  score = highestScore(points);
  
  finalOutput(moves, score);

  
  return 0;
}

int findFirstVal(vector<int> arr, int a)
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


int findLastVal(vector<int> arr, int a)
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

int highestScore(vector<int>& points)
{
  int index = 0, largest = 0;
  int temp = points.size();
 
  for(int i = 0; i < temp; i++)
  {
    if(points[i] > largest)
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
  int temp = points.size();
  
  for(int j = 0; j < temp; j++)
  {
    cout<<points[j]<<" ";
  }   
  cout<<endl;
}  

void displayVector(vector<int>& vec)
{
  int temp = vec.size();
  
  for(int j = 0; j < temp; j++)
  {
    cout<<vec[j]<<" ";
  }   
  cout<<endl; 
  
}

void displayMoves(vector<int>& possibleMoves)
{
  int temp = possibleMoves.size();
  
  for(int i = 0; i < temp; i+=2)
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

void evaluateVertical(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int coordA, coordB, index, opp, holes, playerScore, opponentScore, first, last, counter = 0;;
  vector<int> vec;
  bool skipOnce;
  
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    index = 0;
    first = -1;
    last = 10;
    opp = 0;
    holes = 0;
    playerScore = 0;
    playerScore = 0;
    opponentScore = 0;
 
    //Grab values and place them in an array and a vector
    for(int j = 0; j < size; j++)
    {
      vec.push_back(board[j][possibleMoves[i + 1]]);
    }
    
    coordA = possibleMoves[i];
    coordB = possibleMoves[i + 1];
       
    vec[coordA] = playerID;

    //Replace all 3's in the vector with 0's
    for(int k = 0; k < size; k++)
    {
      if(vec[k] == 3)
      {
        vec[k] = 0;
      }
    }
    
    skipOnce = false;
    
    for(int j = coordA; j > -1; j--)
    {
      if(skipOnce == true)
      {
        if(vec[j] == playerID)
        {
          first = j;
          break;
        }
      }
      
      skipOnce = true;
    }
   
    skipOnce = false;
        
    for(int j = coordA; j < size; j++)
    {
      if(skipOnce == true)
      {
        if(vec[j] == playerID)
        {
          last = j;
          break;
        }
      }
      
      skipOnce = true;
    }      
    
    if(first != -1)
    {
      for(int k = first; k < coordA; k++)
      {
        if(vec[k] == opponentID)
        {
          vec[k] = playerID;
        }
        else 
        {
          break;
        }
      }

      for(int k = first; k < coordA; k++)
      {
        if(vec[k] == 0)
        {
          holes++;
        }
        else if(vec[k] == opponentID)
        {
          opp++;
        }
      }
    }
    
    if(last != 10)
    {
      for(int k = coordA; k <= last; k++)
      {
        if(vec[k] == opponentID)
        {
          vec[k] = playerID;
        }
        else 
        {
          break;
        }
      }
      
      for(int k = coordA; k <= last; k++)
      {
        if(vec[k] == 0)
        {
          holes++;
        }
        else if(vec[k] == opponentID)
        {
          opp++;
        }
      }        
    }

      
    
    
    if((opp == 0) && (holes == 0))
    {
      points[counter] += 50;
    }
    else if(holes == 0)
    {
      points[counter] += 25;
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
    
    if(playerScore > opponentScore)
    {
      points[counter] += playerScore * 2;
    }
    
    if(opponentScore == 0)
    {
      points[counter] += (playerScore * playerScore);
    }
    else if(opponentScore > 1)
    {
      points[counter] += -(playerScore * playerScore);
    }
    
    vec.clear();
    counter++;
  }
}

void evaluateHorizontal(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int coordA, coordB, index, opp, holes, playerScore, opponentScore, first, last, counter = 0;;
  vector<int> vec;
  bool skipOnce;
  
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    index = 0;
    first = -1;
    last = 10;
    opp = 0;
    holes = 0;
    playerScore = 0;
    playerScore = 0;
    opponentScore = 0;
 
    //Grab values and place them in an array and a vector
    for(int j = 0; j < size; j++)
    {
      vec.push_back(board[possibleMoves[i + 1]][j]);
    }
    
    coordA = possibleMoves[i];
    coordB = possibleMoves[i + 1];
       
    vec[coordB] = playerID;

    //Replace all 3's in the vector with 0's
    for(int k = 0; k < size; k++)
    {
      if(vec[k] == 3)
      {
        vec[k] = 0;
      }
    }
    
    skipOnce = false;
    
    for(int j = coordB; j > -1; j--)
    {
      if(skipOnce == true)
      {
        if(vec[j] == playerID)
        {
          first = j;
          break;
        }
      }
      
      skipOnce = true;
    }
   
    skipOnce = false;
        
    for(int j = coordB; j < size; j++)
    {
      if(skipOnce == true)
      {
        if(vec[j] == playerID)
        {
          last = j;
          break;
        }
      }
      
      skipOnce = true;
    }      
    
    if(first != -1)
    {
      for(int k = first; k < coordB; k++)
      {
        if(vec[k] == opponentID)
        {
          vec[k] = playerID;
        }
        else 
        {
          break;
        }
      }

      for(int k = first; k < coordB; k++)
      {
        if(vec[k] == 0)
        {
          holes++;
        }
        else if(vec[k] == opponentID)
        {
          opp++;
        }
      }
    }
    
    if(last != 10)
    {
      for(int k = coordB; k <= last; k++)
      {
        if(vec[k] == opponentID)
        {
          vec[k] = playerID;
        }
        else 
        {
          break;
        }
      }
      
      for(int k = coordB; k <= last; k++)
      {
        if(vec[k] == 0)
        {
          holes++;
        }
        else if(vec[k] == opponentID)
        {
          opp++;
        }
      }        
    }

      
    
    
    if((opp == 0) && (holes == 0))
    {
      points[counter] += 50;
    }
    else if(holes == 0)
    {
      points[counter] += 25;
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
    
    if(playerScore > opponentScore)
    {
      points[counter] += playerScore * 2;
    }
    
    if(opponentScore == 0)
    {
      points[counter] += (playerScore * playerScore);
    }
    else if(opponentScore > 1)
    {
      points[counter] += -(playerScore * playerScore);
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
          points[counter] += -200;
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
          points[counter] += -200;
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
          points[counter] += -200;
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
          points[counter] += -200;
        }
      }
      else
      {
        points[counter] -= -50;
      }
    }
    
    counter++;
  }
}

void evaluateNearCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int counter = 0;

  for(int i = 0; i < possibleMoves.size(); i+= 2)
  {
    if(((possibleMoves[i] == 0) && (possibleMoves[i + 1] == 1)) || ((possibleMoves[i] == 1) && (possibleMoves[i + 1] == 0)))
    {
      //There is a possible move near corner 0 0
      if(board[0][0] == playerID)
      {
        points[counter] += 60;
      }
      else
      {
        points[counter] += -150;
      }
    }
    else if(((possibleMoves[i] == 8) && (possibleMoves[i + 1] == 0)) || ((possibleMoves[i] == 9) && (possibleMoves[i + 1] == 1)))
    {
      //There is a possible move near corner 9 0
      if(board[9][0] == playerID)
      {
        points[counter] += 60;
      }
      else
      {
        points[counter] += -150;
      }       
    }
    else if(((possibleMoves[i] == 0) && (possibleMoves[i + 1] == 8)) || ((possibleMoves[i] == 1) && (possibleMoves[i + 1] == 9)))
    {
      //There is a possible move near corner 0 9
      if(board[0][9] == playerID)
      {
        points[counter] += 60;
      }
      else
      {
        points[counter] += -150;
      }       
    }
    else if(((possibleMoves[i] == 8) && (possibleMoves[i + 1] == 9)) || ((possibleMoves[i] == 9) && (possibleMoves[i + 1] == 8)))
    {
      //There is a possible move near corner 9 9
      if(board[9][9] == playerID)
      {
        points[counter] += 60;
      }
      else
      {
        points[counter] += -150;
      }       
    }
    
    counter++;
  }  
}

void evaluateFurtherCorners(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int counter = 0;

  for(int i = 0; i < possibleMoves.size(); i+= 2)
  {
    if(((possibleMoves[i] == 2) && (possibleMoves[i + 1] == 0)) || ((possibleMoves[i] == 0) && (possibleMoves[i + 1] == 2)))
    {
      //There is a possible move near corner 0 0
      if(board[0][0] == playerID)
      {
        points[counter] += 60;
      }
      else if(board[0][0] == 0)
      {
        points[counter] += 10;
      }
      else
      {
        points[counter] += -100;
      }
    }
    else if(((possibleMoves[i] == 7) && (possibleMoves[i + 1] == 0)) || ((possibleMoves[i] == 9) && (possibleMoves[i + 1] == 2)))
    {
      //There is a possible move near corner 9 0
      if(board[9][0] == playerID)
      {
        points[counter] += 60;
      }
      else if(board[9][0] == 0)
      {
        points[counter] += 10;
      }
      else
      {
        points[counter] += -100;
      }      
    }
    else if(((possibleMoves[i] == 0) && (possibleMoves[i + 1] == 7)) || ((possibleMoves[i] == 2) && (possibleMoves[i + 1] == 9)))
    {
      //There is a possible move near corner 0 9
      if(board[0][9] == playerID)
      {
        points[counter] += 60;
      }
      else if(board[0][9] == 0)
      {
        points[counter] += 10;
      }
      else
      {
        points[counter] += -100;
      }        
    }
    else if(((possibleMoves[i] == 9) && (possibleMoves[i + 1] == 7)) || ((possibleMoves[i] == 7) && (possibleMoves[i + 1] == 9)))
    {
      //There is a possible move near corner 9 9
      if(board[9][9] == playerID)
      {
        points[counter] += 60;
      }
      else if(board[9][9] == 0)
      {
        points[counter] += 10;
      }
      else
      {
        points[counter] += -100;
      }     
    }
    
    counter++;
  }  
}