/****************************************************
 --------------- Autonomous Functions ---------------
 
 A grouping of functions needed for the autonomous
 mode
 
  //Convert inches to degrees
  Syntax : int inToDeg(int inches)

  //Convert degrees to inches
  Syntax : int degToIn(int degrees)
  
  //Set turning angle
  Syntax : void startDegree(int deg)
  
  //Clip the robot degrees
  Syntax : void clipRobotDegrees()
  
  //Clip a number between low and high
  Syntax : void clipNum(int num, int low, int high)
  
  //Combine Ideal PID and PID request by the user
  Syntax : PID combinePID(int userP, int userI, int userD, int ideal P, int idealI, int idealD)
  
  //Set PID depending on user input
  Syntax : PID getPID(autoCont control, int P, int I, int D)
  
  //Apply programmable brakes to the wheel
  Syntax : void applyBrakes();
 
****************************************************/

//Convert inches to degrees
int inToDeg(int inches)//Max 90 inches
{
  //ASSUMING 2.75 INCH WHEELS
  if(inches>90)//Due to PIC 16-bit, anything over 90 will overflow
    return -1;//Remove with CORTEX
  else
    return( ( (inches*360) / 86 ) * 10 );//86 in reality = 86.35, with cortex, switch to (inches*360)/8.635;
}

//Convert degrees to inches
int degToIn(int degrees)
{
  //ASSUMING 2.75 INCH WHEELS
  return ( 86*degrees/3600 );
}

//Which way are we starting on the starting tile?
void startDegree(int deg)
{
  robotDegrees = deg;
}

//Check to make sure that robotdegress isn't over 360;
void clipRobotDegrees()
{
  if(robotDegrees>=360)
    robotDegrees -= 360;
  if(robotDegrees<0)
    robotDegrees += 360;
}

//Limit a number between low and high
int clipNum(int num, int low, int high)
{
  if(num<=low)
    return low;
  else if(num>=high)
    return high;
  else
    return num;
}

//Take in user PID and combine it with the ideal PID to get a final PID
void combinePID(PID pid, int userP, int userI, int userD, int idealP, int idealI, int idealD)
{
  //Make temporary PID variable
  
  //Check P
  if(userP==-1)
    pid.P = idealP;
  else
    pid.P = userP;
	
  //Check I
  if(userI==-1)
    pid.I = idealI;
  else
    pid.I = userI;
	
  //Check D
  if(userD==-1)
    pid.D = idealD;
  else
    pid.D = userD;
}

//Set PID depending on user input
void getPID(autoCont control, PID pid, int P, int I, int D)
{
  //Set PID on user input
  pid.P = P;
  pid.I = I;
  pid.D = D;
  
  //Combine PID's to get final PID
  if(control == Drive) 
	combinePID(pid, P, I, D, 6, 0, 4);  
	
  else if(control == SkidTurn)  
    combinePID(pid, P, I, D, 8, 0, 3);//Makig P = 6, I = 0.1, and D = 4 or 3 will probably make this more accurate
  
  else if(control == Turn)  
    combinePID(pid, P, I, D, 6, 0, 4);  
}

//Apply brakes to robot after completing a move
void applyBrakes()
{
	//Gently go backwards to make the robot stop
    left_drive = -15;
    right_drive = -15;
    wait1Msec(150);
    left_drive = 0;
    right_drive = 0;
}

