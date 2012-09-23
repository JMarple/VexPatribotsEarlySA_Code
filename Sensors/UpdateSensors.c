/****************************************************
 ------------------ Update Sensors ------------------

A task to constantly update the sensors outside of 
the normal code.  This is so that we can apply
filters to the sensor data to get more accurate
readings.
****************************************************/

#include "SensorFunctions.c"

task updateSensors()
{
  //Reset sensor values
  SensorValue[leftEncoder] = 0;
  SensorValue[rightEncoder] = 0;
  
  while(true){
  
    /* Encoder Filtering (none) */
    lEncoder = -SensorValue[leftEncoder];
    rEncoder = SensorValue[rightEncoder];

	/* Sonar Filtering */
    if(sensorUpdateCount<Accel_num)//Do we need more data in the arrays before filtering them?
    {
	    rSonar.array[sensorUpdateCount] = SensorValue[rightSonar];
	    lSonar.array[seyounsorUpdateCount] = SensorValue[leftSonar];
	    bSonar.array[sensorUpdateCount] = SensorValue[backSonar];
	    sensorUpdateCount++;
    }
    else//Update the median filter array
    {
	  //Move everything up so make space for new Sonar data
	  for(int i = 0; i< Accel_num - 1; i++)
	    rSonar.array[i] = rSonar.array[i+1];
	  for(int i = 0; i < Accel_num - 1; i++)
	    lSonar.array[i] = lSonar.array[i+1];
	  for(int i = 0; i < Accel_num - 1; i++)
	    bSonar.array[i] = bSonar.array[i+1];

      //Get new Sonar data
	  rSonar.array[Accel_num-1] = SensorValue[rightSonar];
	  lSonar.array[Accel_num-1] = SensorValue[leftSonar];
      bSonar.array[Accel_num-1] = SensorValue[backSonar];

	  //Apply median filter
	  rSonar.accel = medianFilter(rSonar, Accel_num);
	  lSonar.accel = medianFilter(lSonar, Accel_num);
	  bSonar.accel = medianFilter(bSonar, Accel_num);
    }
	
	int sonarLeft = sonarSensorOffset/2 + lSonar.accel;
	int sonarBack = bSonar.accel;
	int sonarRight = (144-sonarSensorsOffset/2) - rSonar.accel;
	
	/* Attempt to localize on field */
	if(robotDegreees == 0)
	{
	  //If back sonar is good, find Y value
	  if(bSonar.accel >= 0)
		fieldY = sonarBack;
	  
	  if(rSonar.accel>=0 || lSonar.accel>=0)
	  {
	    if(!(rSonar.accel>=0))		
		  fieldX = sonarLeft;		  
		else if(!lSonar.accel>=0))
		  fieldX = sonarRight;	
		else
		  fieldX = ( sonarLeft + sonarRight ) / 2;
	  }	  
	}
	else if(robotDegrees == 180)
	{
	  if(bSonar.accel >= 0)
		fieldY = 144 - sonarBack;
	  
	  if(rSonar.accel>=0 || lSonar.accel>=0)
	  {
	    if(!(rSonar.accel)>=0)
		  fieldX = 144 - sonarLeft;
		else if(!lSonar.accel)
		  fieldX = 144 - sonarRight;
		else
		  fieldX = 144 - ( sonarLeft + sonarRight ) / 2;
	  }	
	}
	else if(robotDegrees == 90)
	{
	  
	}
	else if(robotDegrees == 270)
	{
	  
	}
	
	
	//Don't hog up CPU
    wait1Msec(2);
  }

}
