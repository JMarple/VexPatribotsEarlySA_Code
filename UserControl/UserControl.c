/****************************************************
 ------------------ Arcade Driving ------------------
****************************************************/
task ArcadeDriving
{
  while(true)
  {
    left_drive = (vexRT[Ch4] + vexRT[Ch3])/2; // (Y+X) / 2
  	right_drive = (vexRT[Ch4] - vexRT[Ch3])/2;// (Y-X) / 2
  }
}

/****************************************************
 ------------------ Tank Driving ------------------
****************************************************/
task TankDriving
{
  while(true)
  {
    left_drive = vexRT[Ch2];// (Y+X) / 2
    right_drive = vexRT[Ch3];// (Y-X) / 2
  }
}
