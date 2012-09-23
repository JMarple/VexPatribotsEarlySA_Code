/****************************************************
 ---------------- Autonomous Control ----------------

This function supports a function that allows for
robots to be easily programmed with minimal
programming knowledge.

//Basic Autonomous Control
Syntax : AutonomousControl(Control, # Inches);
Example: AutonomousControl(Drive, 12);

//Autonomous Control with custom PID
Syntax : AutonomousControl(Control, # Inches, P, I, D);
Example: AutonomousControl(Drive, 12, 4, 0 6);

//Autonomous Control with custom PID and Speed
Syntax : AutonomousControl(Control, # Inches, topSpeed, P, I, D);
Example: AutonomousControl(Drive, 12, 127, 4, 0 6);

//Autonomous Control with custom Speed
Syntax : AutonomousControl(Control, # Inches, Speed);
Example: AutonomousControl(Drive, 12, 127);
****************************************************/

#include "AutonomousFunctions.c"

void AutonomousControl(autoCont control, int inches, int topSpeed, int P, int I, int D)
{
  //Clip the robot Degrees method between 0 and 360 degrees
  clipRobotDegrees();

  //Reset the encoder sensors
  SensorValue[leftEncoder] = 0;
  SensorValue[rightEncoder] = 0;

  //Reset Line offset to help with aligning during autonomous
  bool lineOffset = false;//Line found?
  int lineOffsetValue = 0;//Degrees that we're off by
  int lineStart = 0;//Count up how long it's been since one side crossed the line

  //Set the PID depending on
  PID k;
  getPID(control, k, P, I, D);
  k.Error = 0;
  k.Integral = 0;
  k.Derivative = 0;
  k.PreviousError = 0;

  //How much of each sensor should we consider?
  int encoderValue = 10;
  int backSonarvalue = 10;
  int sensorValueCount = 0;
  int sensorValues = 0;

  /********************************
   -------- DRIVE FORWARD --------
  ********************************/
  if(control == Drive)
  {
    //TODO: Choose which wall and sonar based on degrees rotated
    int wallDistance = rSonar.accel;

	//Wall PID constants
	PID w;
	w.P = 30;
	w.I = 1;
	w.D = 2;
	w.Error = 0;
	w.Integral = 0;
	w.Derivative = 0;
	w.PreviousError = 0;

    while(true){

      /* Check for Line */
      if(robotDegrees % 90 == 0 && SensorValue[leftLine]!=-1 && SensorValue[rightLine] != -1)
      {
	    //If line not found yet
        if(!lineOffset)
        {
		      //Is line found by both line sensors at the same time?
          if(SensorValue[leftLine] <= lineThreshold && SensorValue[rightLine] <= lineThreshold)
          {
            lineOffset = true;
            lineOffsetValue = 0;
          }
		      //Is the left side crossing the line first
          else if(SensorValue[leftLine] <= lineThreshold)
          {
            lineOffset = true;
            lineOffsetValue = -1;
            lineStart = (lEncoder+rEncoder)/2;
          }
		      //Is the right side crossing the line first
          else if(SensorValue[rightLine] <= lineThreshold)
          {
            lineOffset = true;
            lineOffsetValue = -2;
            lineStart = (lEncoder+rEncoder)/2;
          }
        }

		//Have we found a line yet?
        if(lineOffset)
        {
		  //Line was spotted in the left, so we need to find when it crosses the right side
          if(lineOffsetValue == -1)
          {
		    //Have we found the line?
            if(SensorValue[rightLine] <= lineThreshold)
            {
			  //Set the line offset
              lineOffsetValue = (lEncoder + rEncoder)/2 - lineStart;
              //Perform turn
            }
          }
		  //Line wsa spotted on the right side, so we need to find when it crosses the left side
          else if(lineOffsetValue == -2)
          {
		    //Have we found the line?
            if(SensorValue[leftLine] <= lineThreshold)
            {
			  //Set the line offset
              lineOffsetValue = (lEncoder + rEncoder)/2 - lineStart;
              //Perform turn
            }
          }
        }
      }

	  /* TODO: Use sonar sensors to help with calculation */
      sensorValues += (rEncoder+lEncoder)/2*encoderValue;
      sensorValueCount += encoderValue;

	  //Need to take in account for when we don't start at 0.. (ie if we want to go 10 inches.. we'd need to go from 40->50 inches, not 0->50 inches
      /*if(bSonar.accel>0){
        sensorValues += inToDeg(bSonar.accel) * backSonarValue;
        sensorValueCount += backSonarValue;
      } */
      sensorValues = sensorValues/sensorValueCount;


	  /* Calculate Error */
      k.Error = inToDeg(inches) - sensorValues;

	  /* Calculate Integral */
      k.Integral = k.Integral + k.Error;

	  /* Calculate Derivative */
      k.Derivative = k.PreviousError - k.Error;
      k.PreviousError = k.Error;

	  //Get speed
      int speed = ((k.Error*k.P) + (k.Integral*k.I) + (k.Derivative*k.D) )/10;

	    //Clip speed between -127 and 127
	    speed = clipNum(speed, -127, 127);


	    /* Calculate PID from Wall */
      //If the correct wall is being looked at
      if(robotDegrees == 90){
        w.Error = wallDistance - rSonar.accel;
      }
	    //Wall Integral
      w.Integral = w.Integral + w.Error;

	    //Wall Derivitive
      w.Derivative = w.PreviousError - w.Error;
      w.PreviousError = w.Error;

	    //Calculate offset
      int offset = ( (w.Error*w.P) + (w.Integral*w.I) + (w.Derivative*w.D) )/10;

	    //Clip offset
	    offset = clipNum(offset, -50, 50);

	    //Update Motor Values
      left_drive = clipNum(speed + offset, -topSpeed, topSpeed);
      right_drive = clipNum(speed - offset, -topSpeed, topSpeed);

	    //Check to see if we're within an okay amount to move on to the next move
      if(abs(k.Error)<25)
        break;
    }

	  //Apply Brakes
    applyBrakes();
  }


  /********************************
   ---------- SKID TURN ----------
  ********************************/
  else if(control == SkidTurn)
  {
    //Update Robot Degrees since we're turning
    robotDegrees += inches;

    while(true)
    {
      //Try to stay away from anything higher then 322 degrees!
      //error = ( (10145*degValue) /1800 ) - (rEncoder-lEncoder)/2;
      //10145 = amount of degress for 5 revolutions of the entire robot, 5 revolutions = 1800 degrees
	    //10145 = 5 full revolutinos (calculated on whiteboard)
      //Divide by 10 to stay within the relms of '16 bit' (anything less then ~32,000)... will make things a little inaccurate though

	    //1/2 Circumference = PI * Distance between left/right wheels
	    //5 revolutions = 1/2 Circumference * 5
	    //5 revolutions / Wheel Circumference * 360 degrees = Encoder Value for 5 revolutions
	    //Encoder Value = (5rev * degrees)/1800

	    /* Calculate Error */
      k.Error = (( (1085) * (inches/10) )/18) - (-rEncoder+lEncoder)/2;

      /* Calculate Integral */
      k.Integral = k.Integral+k.Error;

	    //Clip Integral
      k.Integral = clipNum(k.Integral, -500, 500);

      /* Calculate Derivative */
      k.Derivative = k.Error - k.PreviousError;
      k.PreviousError = k.Error;

      //SET MOTOR VALUE
      int speed = (int)(((k.P*k.Error)+(k.I*k.Integral)/10+k.D*k.Derivative)/10);//Divide by 10 since Kp, Ki, and Kd had to be multiplied by 10 to deal with floats

	    //Clip speed
      speed = clipNum(speed, -topSpeed, topSpeed);

	    //Update Motors
      left_drive = speed;
      right_drive = -speed;

	    //Check to see if we're within an okay amount to move on to the next move
      if(abs(k.Error)<25)
        break;
    }

	  //Apply Brakes
    applyBrakes();
  }


  /********************************
   ------------- TURN -------------
  ********************************/
  else if(control==Turn)
  {
    //Update Robot degrees since we're turning
    robotDegrees += inches;

	  PID s;
	  s.Error = 0;
	  s.Integral = 0;
	  s.Derivative = 0;
	  s.PreviousError = 0;

	const turnAmount = 2080;//How many rotations for a 180 degree turn?
	
    //move left drive
    while(true)
    {
	  /* Calculate Error */
	  if(inches > 0)
		  k.Error = (inches * turnAmount)/180 - lEncoder;
	  else if(inches < 0)
	    k.Error = (inches * turnAmount)/180 - rEncoder;

	  //No integral or deriviative?
	  //Speed?
      int speed = k.Error;

      //Clip speed
      speed = clipNum(speed, -topSpeed, topSpeed);

	    /* Calculate Second Error for wheel that should be still! */
      if(inches > 0)
	    s.Error = 0 - rEncoder;
	  else if(inches < 0)
	    s.Error = 0 - lEncoder;

	  /* Calculate Second Integral */
      s.Integral = s.Integral + s.Error;
      s.Integral = clipNum(s.Integral, -200, 200);

	  /* Calculte Second Derivative */
      s.Derivative = s.Error - s.PreviousError;
      s.PreviousError = s.Error;

	    //Set speed
      int stopSpeed = (s.Error*10 + s.Derivative*2)/10;
      stopSpeed = clipNum(stopSpeed, -topSpeed, topSpeed);

	  //Update Motors
	  if(inches > 0)
	  {
		  left_drive = speed;
		  right_drive = stopSpeed;
	  }
	  else if(inches < 0)
	  {
	    left_drive = stopSpeed;
	  	right_drive = speed;
	  }

    //Check to see if we're within an okay amount to move on to the next move
    if(abs(k.Error)<25)
      break;
    }

    applyBrakes();
  }
}

//A simpler version of AutonomousControl without a PID option (using default PID) or Speed (+- 127)
void AutonomousControl(autoCont control, int inches)
{
  AutonomousControl(control, inches, 127, -1, -1, -1);//-1 means we're using the default version of that PID
}

//A simpler version of AutonomousControl without a PID option (using default PID)
void AutonomousControl(autoCont control, int inches, int speed)
{
  AutonomousControl(control, inches, speed, -1, -1, -1);
}

//A simpler version of AutonomousControl without a Speed option (+- 127)
void AutonomousControl(autoCont control, int inches, int P, int I, int D)
{
  AutonomousControl(control, inches, 127, P, I, D);
}
