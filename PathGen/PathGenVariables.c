/****************************************************
 -------------------- Variables --------------------
A bunch of variables necessary for the path generator
****************************************************/

/* Constants */
const int pathToGen = 4;//How many paths to generate each cycle?
const int pathDepth = 6;//How long should each path be?
const int fieldCheck = 28;
const byte mutationPercentage = 50;//How often should a mutation take place?

/* Variables */
bool stopFlag = false;
/* Structures */

//Main path structure
typedef struct
{
  long path;
  int fitness;
} Paths;

Paths parents[pathToGen];//Collection of current best paths
long chosen = 0;//Map of what's selected or not
long bestChosen = 0;//Map of the best current map
long lastChosen = 0;//Map of the previous session's best map
long tmpChild = 0;//Temporary Child path
long curPath = 0;//Current Seed running

//A Map of the field
static int nodes(int y, int x)
{
  switch(y)
  {
    case 0:
      switch(x)
      {case 0: return 0; case 1: return 12; break; default: break;}
    case 1:
      switch(x)
      {case 0: return 0; case 1: return 36; break; default: break;}
    case 2:
      switch(x)
      {case 0: return 0; case 1: return 108; break; default: break;}
    case 3:
      switch(x)
      {case 0: return 0; case 1: return 132; break; default: break;}
    case 4:
      switch(x)
      {case 0: return 144; case 1: return 12; break; default: break;}
    case 5:
      switch(x)
      {case 0: return 144; case 1: return 36; break; default: break;}
    case 6:
      switch(x)
      {case 0: return 144; case 1: return 108; break; default: break;}
    case 7:
      switch(x)
      {case 0: return 144; case 1: return 132; break; default: break;}

    case 8:
      switch(x)
      {case 0: return 60; case 1: return 0; break; default: break;}
    case 9:
      switch(x)
      {case 0: return 84; case 1: return 0; break; default: break;}
    case 10:
      switch(x)
      {case 0: return 60; case 1: return 144; break; default: break;}
    case 11:
      switch(x)
      {case 0: return 84; case 1: return 144; break; default: break;}

    case 12:
      switch(x)
      {case 0: return 24; case 1: return 72; break; default: break;}
    case 13:
      switch(x)
      {case 0: return 120; case 1: return 72; break; default: break;}
    case 14:
      switch(x)
      {case 0: return 54; case 1: return 72; break; default: break;}
    case 15:
      switch(x)
      {case 0: return 90; case 1: return 72; break; default: break;}

    case 16:
      switch(x)
      {case 0: return 48; case 1: return 48; break; default: break;}
    case 17:
      switch(x)
      {case 0: return 96; case 1: return 48; break; default: break;}
    case 18:
      switch(x)
      {case 0: return 48; case 1: return 96; break; default: break;}
    case 19:
      switch(x)
      {case 0: return 96; case 1: return 96; break; default: break;}

    case 20:
      switch(x)
      {case 0: return 72; case 1: return 48; break; default: break;}
    case 21:
      switch(x)
      {case 0: return 72; case 1: return 96; break; default: break;}

    case 22:
      switch(x)
      {case 0: return 72; case 1: return 72; break; default: break;}
    case 23:
      switch(x)
      {case 0: return 72; case 1: return 69; break; default: break;}
    case 24:
      switch(x)
      {case 0: return 72; case 1: return 72; break; default: break;}

    case 25:
      switch(x)
      {case 0: return 36; case 1: return 132; break; default: break;}
    case 26:
      switch(x)
      {case 0: return 72; case 1: return 48; break; default: break;}
    case 27:
      switch(x)
      {case 0: return 72; case 1: return 96; break; default: break;}

    default:
     return -99;
  }

  return -98;
}
