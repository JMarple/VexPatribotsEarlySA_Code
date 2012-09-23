
//if we are in release mode, then don't stop the robot in the middle of the run if there is an error

void ERROR_REPORT(bool flag, string errorMessage)
{
  //Was there an error?
  if(!flag)
  {
    //Write error to debug stream
    writeDebugStreamLine(errorMessage);

    if(!release)
    {
      //TODO: Write code to stop motors and such to let you know there was an error
    }
  }
}

void INFO_REPORT(string infoMessage)
{
  writeDebugStreamLine(infoMessage);
}
