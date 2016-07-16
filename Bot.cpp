#include <iostream>
#include <vector>

using namespace std;

int playerID;
const int size = 10;

int findFirstVal(int arr[size], int a);
int findLastVal(int arr[size], int a);
int findFirstVal(int arr[size], int a, int b, int c);
int findLastVal(int arr[size], int a, int b, int c);
int highestScore(vector<int>& points);
void displayBoard(int board[][size]);
void firstMove(vector<int>& possibleMoves);
void displayPoints(vector<int>& points);
void displayMoves(vector<int>& possibleMoves);
void finalOutput(vector<int>& possibleMoves, int index);
void readBoard(int board[][size], vector<int>& possibleMoves, vector<int>& points);
void evaluateCorners(vector<int>& possibleMoves, vector<int>& points);
void evaluateVerical(int board[][size], vector<int>& possibleMoves, vector<int>& points);
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
  evaluateVerical(board, moves, points); 
  evaluateHorizontal(board, moves, points); 
  
  index = highestScore(points);
  
  finalOutput(moves, index);
  //displayMoves(moves);
  //displayPoints(points);

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
      cout<<possibleMoves[i]<<" "<<possibleMoves[i + 1]<<endl;
      points[j] = 500;
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
  int counter =0;

  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
    if(((possibleMoves[i] == 1) || (possibleMoves[i] == 8))&& ((possibleMoves[i + 1] == 1) || (possibleMoves[i + 1] == 8)))
    {
      points[counter] -= 15;
    }
    else
    {
      points[counter] += 5;
    }
    
    counter++;
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
  int arr[size];
  
  int coordA, coordB;
  int hole, extra, temp, index;
  int zeroes = 0, ones = 0, twos = 0, threes = 0, counter = 0;
  int zeroA, zeroB, threeA, threeB, playerIDA, playerIDB, nonPlayerIDA, nonPlayerIDB; 
  bool flag, valFound, continuous, skipA;
  
  
  //Grab values and place them in an array
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
      for(int j = 0; j < size; j++)
      {
        arr[j] = board[j][possibleMoves[i + 1]];
      }

    coordA = possibleMoves[i];
    coordB = possibleMoves[i + 1];
    
    //Count the number of 0's, 1's, 2's, and 3's in an array
    for(int j = 0; j < size; j++)
    {
      if(arr[j] == 0)
      {
        zeroes++;
      }
      else if(arr[j] == 1)
      {
        ones++;
      }
      else if(arr[j] == 2)
      {
        twos++;
      }
      else if(arr[j] == 3)
      {
        threes++;
      }
    }  
    
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
    
    //Calculate points
    if(nonPlayerIDA == -1)
    {
      points[counter] += 20;
      
    }

    
    index = coordA;
    skipA = false;
    continuous = true;
    
    //Checks the values to the right of the array
    for(int j = coordA; j < size; j++)
    {      
      if(skipA == true)
      {
        if((arr[j] == playerID) || (arr[j] != 3))
        {
          index = i;
        }
        else
        {
          skipA = false;
          break;
        }
      }
      
      skipA = true;
    }
    
    hole = 0;
    flag = false;
    
    for(int j = index; j < size; j++)
    {
      if(skipA == true)
      {
        if(arr[j] == playerID)
        {
        }
        else if(arr[j] == 0)
        {
          hole++;
        }
        else if(arr[j] != playerID)
        {
          flag = true;
        }
      }
      
      if(flag == true)
      {
        if((j + 1) < (size - 1))
        {
          if(arr[j + 1] == 0)
          {
            points[counter] += 1;
          }
          else if((arr[j + 1] == 3))
          {
            if((j + 1) < (size - 1))
            {
              if(arr[j + 1] == 3)
              {
                points[counter] += 5;
              }
              else
              {
                points[counter] -= 7;
              }
            }
            else
            {
              points[counter] += 0;
            }
            
            break;
          }
          else 
          {
            points[counter] -= 5;
          }
        }
      }
      
      skipA = true;  
    }  

    //Checks the values to the left of the array
    
    skipA = false;
    
    for(int j = coordA; j >= 0; j--)
    {      
      if(skipA == true)
      {
        if((arr[j] == playerID) || (arr[j] != 3))
        {
          index = i;
        }
        else
        {
          skipA = false;
          break;
        }
      }
      
      skipA = true;
    }
    
    hole = 0;
    flag = false;
    
    for(int j = index; j >= 0; j--)
    {
      if(skipA == true)
      {
        if(arr[j] == playerID)
        {
        }
        else if(arr[j] == 0)
        {
          hole++;
        }
        else if(arr[j] != playerID)
        {
          flag = true;
        }
      }
      
      if(flag == true)
      {
        if((j - 1) > 0)
        {
          if(arr[j - 1] == 0)
          {
            points[counter] += 1;
          }
          else if((arr[j - 1] == 3))
          {
            if((j - 1) > 0)
            {
              if(arr[j - 1] == 3)
              {
                points[counter] += 5;
              }
              else
              {
                points[counter] -= 7;
              }
            }
            else
            {
              points[counter] += 0;
            }
            
            break;
          }
          else 
          {
            points[counter] -= 5;
          }
        }
      }
      
      skipA = true;  
    }    
    
    counter++;
  }
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
   

void evaluateVerical(int board[][size], vector<int>& possibleMoves, vector<int>& points)
{
  int arr[size];
  
  int coordA, coordB;
  int hole, extra, temp, index;
  int zeroes = 0, ones = 0, twos = 0, threes = 0, counter = 0;
  int zeroA, zeroB, threeA, threeB, playerIDA, playerIDB, nonPlayerIDA, nonPlayerIDB; 
  bool flag, valFound, continuous, skipA;
  
  
  //Grab values and place them in an array
  for(int i = 0; i < possibleMoves.size(); i+=2)
  {
      for(int j = 0; j < size; j++)
      {
        arr[j] = board[possibleMoves[i + 1]][j];
      }

    coordA = possibleMoves[i];
    coordB = possibleMoves[i + 1];
    
    //Count the number of 0's, 1's, 2's, and 3's in an array
    for(int j = 0; j < size; j++)
    {
      if(arr[j] == 0)
      {
        zeroes++;
      }
      else if(arr[j] == 1)
      {
        ones++;
      }
      else if(arr[j] == 2)
      {
        twos++;
      }
      else if(arr[j] == 3)
      {
        threes++;
      }
    }  
    
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
    
    //Calculate points
    if(nonPlayerIDA == -1)
    {
      points[counter] += 20;
      
    }

    
    index = coordB;
    skipA = false;
    continuous = true;
    
    //Checks the values to the right(Going down) of the array
    for(int j = coordB; j < size; j++)
    {      
      if(skipA == true)
      {
        if((arr[j] == playerID) || (arr[j] != 3))
        {
          index = i;
        }
        else
        {
          skipA = false;
          break;
        }
      }
      
      skipA = true;
    }
    
    hole = 0;
    flag = false;
    
    for(int j = index; j < size; j++)
    {
      if(skipA == true)
      {
        if(arr[j] == playerID)
        {
        }
        else if(arr[j] == 0)
        {
          hole++;
        }
        else if(arr[j] != playerID)
        {
          flag = true;
        }
      }
      
      if(flag == true)
      {
        if((j + 1) < (size - 1))
        {
          if(arr[j + 1] == 0)
          {
            points[counter] += 1;
          }
          else if((arr[j + 1] == 3))
          {
            if((j + 1) < (size - 1))
            {
              if(arr[j + 1] == 3)
              {
                points[counter] += 5;
              }
              else
              {
                points[counter] -= 7;
              }
            }
            else
            {
              points[counter] += 0;
            }
            
            break;
          }
          else 
          {
            points[counter] -= 5;
          }
        }
      }
      
      skipA = true;  
    }  

    //Checks the values to the left (Going up) of the array
    
    skipA = false;
    
    for(int j = coordB; j >= 0; j--)
    {      
      if(skipA == true)
      {
        if((arr[j] == playerID) || (arr[j] != 3))
        {
          index = i;
        }
        else
        {
          skipA = false;
          break;
        }
      }
      
      skipA = true;
    }
    
    hole = 0;
    flag = false;
    
    for(int j = index; j >= 0; j--)
    {
      if(skipA == true)
      {
        if(arr[j] == playerID)
        {
        }
        else if(arr[j] == 0)
        {
          hole++;
        }
        else if(arr[j] != playerID)
        {
          flag = true;
        }
      }
      
      if(flag == true)
      {
        if((j - 1) > 0)
        {
          if(arr[j - 1] == 0)
          {
            points[counter] += 1;
          }
          else if((arr[j - 1] == 3))
          {
            if((j - 1) > 0)
            {
              if(arr[j - 1] == 3)
              {
                points[counter] += 5;
              }
              else
              {
                points[counter] -= 7;
              }
            }
            else
            {
              points[counter] += 0;
            }
            
            break;
          }
          else 
          {
            points[counter] -= 5;
          }
        }
      }
      
      skipA = true;  
    }    
    
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

