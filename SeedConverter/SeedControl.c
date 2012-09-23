/****************************************************
 ------------------- Seed Control -------------------
Take a "seed" generatered by the genetic algorithm
and convert each part to make up an autonomous run.  

This works by looping through each element in the 
array and figuring out where it is on the field.  
Then the code determines whether or not to move in 
the x direction first or the y direction.  Then it
executes to what it believes is the best way for 
moving to the target.

//Basic Seed Control ("Path" is a structure found in GlobalVariables.c)
Syntax : AutonomousSeedControl(Path)
Example: AutonomousSeedControl(finalPath);
****************************************************/

#include "SeedFunctions.c"

void AutonomousSeedControl(Path finalPath)//Chance to "Paths finalPath".. and make sure the finalPath is a different array from the main "parents" arrays becuase it's passed by reference
{
  //Get current X and Y
  int curX = nodes(extractNum(finalPath.path, 0), 0);
  int curY = nodes(extractNum(finalPath.path, 0), 1);
  int tarX = 0;
  int tarY = 0;
  int curNode = 0;

  startDegree(0);//Which degree should we start on? (Default = 0 degrees)

  //Go through each target
  for(int k = 1; k < 6; k++)//CHANGE 6 TO PATHDEPTH WITH CORTEX
  {
    curNode = extractNum(finalPath.path,k);
    tarX = nodes(curNode, 0);
    tarY = nodes(curNode, 1);

    //One of the 4 stacks of 5
    if(curNode>=16&&curNode<=19)
    {
      if(k+1<6)//CHANGE 6 TO PATHDEPTH WITH CORTEX
      {
        if(extractNum(finalPath.path, k+1) == 20 || extractNum(finalPath.path, k+1) == 21)
        {
          //Do Y-Fix first, and then turn to prepare for the upcoming bonus sack and X-fix
          yFix(curY, tarY);
          xFix(curX, tarX);
        }
        else if(extractNum(finalPath.path, k+1) == 14 || extractNum(finalPath.path, k+1) == 15)
        {
          //Do X-Fix first, and then turn to prepare for the upcoming grouping of scakcs and Y-Fix
          xFix(curX, tarX);
          yFix(curY, tarY);
        }
      }
      else
      {
        //By default to a Y-Fix first then an X-fix
        yFix(curY, tarY);
        xFix(curX, tarX);
      }
    }
    //Left/Right wall Sacks
    else if(curNode >= 0 && curNode <= 7)
    {
      yFix(curY, tarY);
      xFix(curX, tarX);
    }
    //Up/Down wall sacks
    else if(curNode >= 8 && curNode <= 11)
    {
      xFix(curX, tarX);
      yFix(curY, tarY);
    }
    else if(curNode == 21 || curNode == 20)
    {
      yFix(curY, tarY);
      xFix(curX, tarX);
    }
	
	//Reset curX and curY
	curX = tarX;
	curY = tarY;
  }
}
