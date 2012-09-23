/****************************************************
                Path Generator V0.4                 
                 By Justin Marple

   Started - July  24th, 2012
   Updated - September 1st, 2012

   Property of Vex Team 1615
   Contact:
     jmredsoxfan1010@gmail.com

 Info: This program uses a genetic algorithm to 
 continuesly try to find an ideal path for the game
 "sack attack".  This will likely give a different 
 path every time it is run.  
 
 //Starting generator
 Syntax : startTask(pathGen);
 
 //Stop,reset and get back best path from generator
 Syntax : capturePathAndReset();
****************************************************/

//Include files
#include "PathGenVariables.c";//Contains all the variables needed for generating the path
#include "PathGenLib.c";//Library of functions for the path generator
#include "PathGenStart.c";//Function for creating a new batch of paths
#include "PathGenCrossOverOne.c";//Function for breeding paths
#include "PathGenCrossOverTwo.c";//Function for bredding paths
#include "PathGenCrossOverThree.c";//Function for bredding paths

task pathGen()
{
  while(true)
  {
    //Wait for an "OK" from the program to start this loop
    if(!stopFlag)
	{
      //Create new paths
      startGenerations();
  
      //Keep breeding new paths until told to stop
      while(!stopFlag)
      {
        crossOverOne();
        crossOverTwo();
        crossOverThree();
		
		wait1Msec(1);
      }
    }
  }
}
