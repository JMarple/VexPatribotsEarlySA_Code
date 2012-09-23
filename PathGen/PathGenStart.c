/****************************************************
 ----------------- startGenerations -----------------
Create a new series of paths that are completely
random.
****************************************************/

//Refresh the arrays with new, random paths
void startGenerations()
{
  for(int y = 0; y < pathToGen; y++)
  {
    //Reset the field
    setChosenToFalse();

    //First tile is always the starting tile
    parents[y].path = insertNum(parents[y].path, 0, 25);
    for(int x = 1; x < pathDepth; x++)
    {
      byte randomNum;
      int lc = 0;

      while(true)
      {
        randomNum = random(21);
        //Check to see if the random number is valid
        if(isChosen(chosen, randomNum) == false && checkForValidMove(randomNum, extractNum(parents[y].path,x-1)))
        {
          chosen = insertChosen(chosen, randomNum, true);
          break;
        }
        //A loop counter to check for accidental infinte loops
        if(lc++>50)
        {
          randomNum = 25;
          break;
        }
      }
      parents[y].path = insertNum(parents[y].path, x, randomNum);
    }

    //Count up the distance and then put it into the array
    int tmpDist = 0;

    for(int k = 1; k < pathDepth; k++)
      tmpDist += findDistance(extractNum(parents[y].path, k-1), extractNum(parents[y].path, k));

    parents[y].fitness = tmpDist;
  }

}
