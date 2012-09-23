/****************************************************
 ------------------- Update Motors ------------------

A task to constantly update the motors.  This will
also monitor PTC temperatures to make sure we don't
overheat the motors.
****************************************************/
//#include "PTCmonitor.c"

//Function Prototype
int linearDrive(int cmd);

task updateMotors()
{
  while(true){

    //Remove annoying "humming" noise the motors make when theres small amount of power run to them
    if(abs(left_drive)<5)
     left_drive = 0;

    if(abs(right_drive)<5)
     right_drive = 0;	
	
    motor[driveLeft1] = left_drive;
    motor[driveLeft2] = left_drive;
    motor[driveRight1] = right_drive;
    motor[driveRight2] = right_drive;
    motor[liftLeft1] = lift_drive;
    motor[liftLeft2] = lift_drive;
    motor[liftRight1] = lift_drive;
    motor[liftRight2] = lift_drive;
	
    //Don't hog up the CPU
	wait1Msec(2);
  }
}

//Convert the command to drive make the drive linear.  Without it, acceleration would look similar to : http://www.vexforum.com/showpost.php?p=303628&postcount=7
int linearDrive(int cmd)
{
  //Are we told to adjust the drive?
  if(inverseFuncDrive)
  {
    //Inverse function of PTC controller
    return 1.57 * (103.458 - 0.004 * sqrt(628800000 - 4760000 * cmd) );
  }
  //If not, return the original command
  else
  {
    return cmd;
  }
}