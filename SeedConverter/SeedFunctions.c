//Rotate to the correct angle of degrees
void yawFix(int degrees)
{
  if(!(robotDegrees == degrees) )
  {
    AutonomousControl(Turn, degrees - robotDegrees);
  }
}

//Rotate and drive to the target's Xvalue
void xFix(int curX, int tarX)
{
  //Are we not at the target already?
  if(!(curX==tarX))
  {
	  /** Do Yaw Fix **/
	  if(curX > tarX)//Right to target?
	    yawFix(270);
	  else if(curX < tarX )//Left to target?
	    yawFix(90);

	  /** Do X-Fix **/
	  AutonomousControl(Drive, abs(tarX-curX) );
  }
}

//Rotate and drive to the target's Y value
void yFix(int curY, int tarY)
{
  //Are we not at the target already?
  if(!(curY==tarY))
  {
	  /** Do Yaw Fix **/
	  if(curY>tarY)//Below target?
	    yawFix(0);
	  else if(curY < tarY)//Above target?
	    yawFix(180);

	  /** Do Y-Fix **/
	  AutonomousControl(Drive, abs(tarY-curY) );
  }
}
