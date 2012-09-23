/****************************************************
 ------------------- crossOverOne -------------------
Mix different results to create potentially better
results.  In this one, we mix 0 with 1, then 1 with 2,
ect.
****************************************************/

void crossOverOne()
{
  //Go through all the parents
  for(int y = 0; y < pathToGen-1; y++)
  {
    //Set the field to all full
    setChosenToFalse();

    //The first tile is always the starting tile
    tmpChild = insertNum(tmpChild, 0, 25);

    //Go through the length of the path
    for(int x = 1; x < pathDepth; x++)
    {
      //Find two potential targets
      byte targetA = extractNum(parents[y].path,x);
      byte targetB = extractNum(parents[y+1].path, x);

      //Find the tile to compare the target to
      byte startA = extractNum(tmpChild, x-1);

      //Check for a mutation
      int mutation = random(100);
      if(mutation<mutationPercentage)
      {
        //Find the distances between the previous tile and the new proposed tiles
        int disA = findDistance(targetA, startA);
        int disB = findDistance(targetB, startA);

        //Is targetA a better match then targetB?
        if(disA < disB)
        {
          //Check to see if targetA is a valid move
          if(isChosen(chosen, targetA) == false && checkForValidMove(targetA, startA))
          {
            tmpChild = insertNum(tmpChild, x, targetA);
            chosen = insertChosen(chosen, targetA, true);
          }
          //If targetA isn't valid, check target B
          else if(isChosen(chosen, targetB) == false && checkForValidMove(targetB, startA))
          {
            tmpChild = insertNum(tmpChild, x, targetB);
            chosen = insertChosen(chosen, targetB, true);
          }
          //If neither works, treat it as a mutation
          else
          {
            tmpChild = insertNum(tmpChild, x, findUnusedRandomNumber(y, x));
          }
        }
        //targetB is a better match then targetA
        else
        {
          //Check to see if targetB is valid
          if(isChosen(chosen, targetB) == false && checkForValidMove(targetB, startA))
          {
            tmpChild = insertNum(tmpChild, x, targetB);
            chosen = insertChosen(chosen, targetB, true);
          }
          //If targetB isn't valid, check targetA
          else if(isChosen(chosen, targetA) == false && checkForValidMove(targetA, startA))
          {
            tmpChild = insertNum(tmpChild, x, targetA);
            chosen = insertChosen(chosen, targetA, true);
          }
          //If neither works, treat it as a mutation
          else
          {
            tmpChild = insertNum(tmpChild, x, findUnusedRandomNumber(y, x));
          }
        }
      }
      //Add a mutation to the path
      else
      {
        tmpChild = insertNum(tmpChild, x, findUnusedRandomNumber(y, x));
      }
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
