/****************************************************
 ------------------ crossOverThree ------------------
Mix different results to create potentially better
results.  In this one, we mix 0 with 1, then 0 with 2,
ect.
****************************************************/

void crossOverThree()
{
  //Go through all the parents
  for(int y = 0; y < pathToGen - 1; y++)
  {
    //Set the field to all full
    setChosenToFalse();

    //The first tile is always the starting tile
    tmpChild = insertNum(tmpChild, 0, 25);

    //Go through the length of the path
    for(int x = 1; x < pathDepth; x++)
    {
        tmpChild = insertNum(tmpChild, x, findUnusedRandomNumber(y, x);
    }

    //Find the distance of the new path
    int tmpDist = 0;

    for(int x = 0; x < pathDepth-1; x++)
      tmpDist += findDistance(extractNum(tmpChild, x), extractNum(tmpChild, x+1));

    //Go through the current paths and see if this one is better
    for(int x = 0; x < pathToGen; x++)
    {
      //Did we find a match?
      if(parents[x].fitness > tmpDist)
      {
	      //If this is the best match, update the best map
	      if(x==0)
		    {
		      bestChosen = chosen;
	    	}

        //Replace the current data with the new path data
        parents[x].fitness = tmpDist;

        parents[x].path = tmpChild;
      }
      break;
    }
  }
}
