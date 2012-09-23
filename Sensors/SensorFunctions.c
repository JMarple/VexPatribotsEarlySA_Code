/****************************************************
 ----------------- Sensor Functions -----------------

A series of functions that help with applying filters 
to the sensor data (Note that the merge sort 
functions were copied and then modified from the 
internet)
****************************************************/

/**** Median Filter ****/
//Merge function of the mergeSorting
void mergeArrays(Accel _array, int startL, int stopL, int startR, int stopR)
{
  int right[Accel_num];
  int left[Accel_num];

  int k = startR;
	for(int i = 0 ; i < (stopR - startR); ++i)
	{
	  right[i] = _array.array[k]; ++k;
	}
	k = startL;
	for(int i = 0; i< (stopL - startL); ++i)
	{
	  left[i] = _array.array[k]; ++k;
	}
	  //Adding sentinel values
	  right[stopR - startR] = 32767;
	  left[stopL - startL] = 32767;

	   for(int k = startL, m = 0, n = 0; k < stopR; ++k) {
	      if(left[m] <= right[n]) {
	          _array.array[k] = left[m];
	          m++;
	      }
	      else {
	          _array.array[k] = right[n];
	          n++;
	      }
	  }
}

void mergeSort(Accel result, Accel _array, int n)
{
  for (int i = 0; i < n; i++)//Tranfer data from other array so that the original data isn't sorted
    result.array[i] = _array.array[i];

	// The size of the sub-arrays . Constantly changing .
	int step = 1;
	// startL - start index for left sub-array
	// startR - start index for the right sub-array
	int startL, startR;

	while(step < n) {
	  startL = 0;
	  startR = step;
	  while(startR + step <= n) {
	    mergeArrays(result, startL, startL + step, startR, startR + step);
	    // System.out.printf("startL=%d, stopL=%d, startR=%d, stopR=%dn",
	    // startL, startL + step, startR, startR + step);
	    startL = startR + step;
	    startR = startL + step;
	  }
	  // System.out.printf("- - - with step = %dn", step);
	  if(startR < n) {
	    mergeArrays(result, startL, startL + step, startR, n);
	    // System.out.printf("* startL=%d, stopL=%d, startR=%d, stopR=%dn",
	    // startL, startL + step, startR, array.length);
	  }
	  step *= 2;
  }
}

//Filter through data to get a result back
int medianFilter(Accel data, int data_count)//Return back the value of the median of the data
{
  Accel result;//Accel to keep sorted data
  mergeSort(result, data, data_count);

  int median;

  //Is data only a size of 2?
  if(data_count % 2 != 0)
  {
	median = result.array[data_count/2];
  }
  else
  {
	int mid = data_count/2;
	int first = result.array[mid];
	int second = result.array[mid+1];
	median = (first+second)/2;
  }
  return median;
}