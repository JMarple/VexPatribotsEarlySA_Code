/****************************************************
 --------------------- Library ---------------------
A mixed library of functions used in other files

  int fixedPointSqrt(int num);
  int findDistance(byte node1, byte node2);
  void setChosenToFalse();
  bool checkForValidMove(byte nodeA, byte nodeB);
  byte findUnusedRandomNumber(int y, int x);
****************************************************/

/** Find Distance **/
//Pretty inaccurate, but the best I can deal with fixed point
int fixedPointSqrt(int num)
{
  int x = num/2;//Starting point

  int lc = 0;

  while(lc++<10)
  {
    x = (x + num/x)/2;
  }
  return x;
}

//Find the distance between two numbers
int findDistance(byte node1, byte node2)
{
  int x1 = nodes(node1, 0);
  int x2 = nodes(node2, 0);
  int y1 = nodes(node1, 1);
  int y2 = nodes(node2, 1);
  return fixedPointSqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}

/** setChoosenTofalse **/
//Reset the field
void setChosenToFalse()
{
  chosen = lastChosen;
}

/** Check for Valid move **/
//Check the proposed path to make sure it's valid
bool checkForValidMove(byte nodeA, byte nodeB)
{
  //Check to see if the path is running into the posts underneigth
  if( (nodeA >= 12 && nodeA <= 15)  &&  (nodeB >= 12 && nodeB <= 15) )
  {
    return false;
  }
  //Check to see if the path is jumping from one side of the field to the other
  if( (nodes(nodeA, 1) > 72 && nodes(nodeB, 1) < 72) || (nodes(nodeA, 1) < 72 && nodes(nodeB, 1) > 72) )
  {
    return false;
  }

  return true;
}

//Insert a 5-bit number into a long variable
long insertNum(long path, int section, int num)
{
  //Convert numbers so that we go from start to finish, not vice versa
  section = 5 - section;
  section*=5;

  //Overwrite the section we want to edit to zeros
  path = path & ~ (31<<section);

  //Add i to the path
  num = num<<section;
  path += num;
  return path;
}

//Extract a 5-bit number from a long variable
int extractNum(long path, int section)
{
  //Convert numbers so that we go from start to finish, not vice versa
  section = 5 - section;
  section*=5;

  //Get specified bits by first finding it, then moving it back into a 5-bit number
  return (int) ( (path & (31<<section) ) >> section);
}


//Mark a spot on the field as taken
long insertChosen(long field, int section, bool insert)
{
  section = 33 - section;

  field = field & ~ (1<<section);

  int num = 0;
  if(insert)
    num = 1;

  num = num<<section;
  field += num;
  return field;
}

//Get a position on the field
bool isChosen(long field, int num)
{
  num = 33 - num;
  return ( field & (1<<num) ) != 0;
}

/** Find unused spots on the field **/
byte findUnusedRandomNumber(int y, int x)
{
  int lc = 0;
  //Start with a random number and count up from that number
  byte target = random(21);

  while(true)
  {
    //check the current target
    if(isChosen(chosen,target) == false && checkForValidMove(target, isChosen(tmpChild, x-1)))
    {
      insertChosen(chosen, target, true);
      return target;
    }

    //If the target wasn't correct, add one and check again
    target++;
    //Reset the target if it's too high
    if(target>21)
      target = 0;

    //Loop counter to make sure we don't go in an infinite loop
    lc++;
    if(lc>22)
      return 25;
  }
}

//Capture the current best path
long CapturePathAndReset(long datPath)
{
  //BROKEN
  //BROKEN
  //BROKEN

  //Tell generator to stop
  stopFlag = true;

  //Wait for CPU to finish up current loop
  wait1Msec(10);

  //Copy best field map
  lastChosen = bestChosen;

  //Copy best Path to current array
  datPath = parents[0].path;

  //Allow for new
  stopFlag = false;

  return datPath;
}
