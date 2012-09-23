/****************************************************
 ----------------- Global Variables -----------------
****************************************************/

/*** Flags ***/
const bool release = false;//Release mode for the error console?
const bool inverseFuncDrive = false;//Drive with inverse function?
const bool vamfunPTC = false;//Drive with Vamfun's PTC model to prevent overheating?

/*** Constants ***/
const int lineThreshold = 800;//What the light threshold should be
const int Accel_num = 3;//Number of items to filter at once
const int sonarSensorsOffset = 16;//Inches apart between sonar sensors

/*** Misc Values ***/
int sensorUpdateCount = 0;
int robotDegrees = 0;//0 = forward, 270 = left, 90 = right
int fieldX = 0;
int fieldY = 0;

/*** Controls ***/
int left_drive = 0;
int right_drive = 0;
int lift_drive = 0;
int lEncoder = 0;
int rEncoder = 0;

/*** Structures ***/
//Structure for filtering data
typedef struct
{
  int array[Accel_num];
  int accel;
} Accel; //Accleration arrays

//Structure for holding seeds
typedef struct
{
 long path;
} Path;

//PID structure for sharing between functions easily
typedef struct
{
  int P;
  int I;
  int D;
  int Error;
  int Integral;
  int Derivative;
  int PreviousError;
} PID;

/* Structure variables */
Accel lSonar;
Accel rSonar;
Accel bSonar;

/*** ENUMS ***/
//Control enums for AutonomousControl
typedef enum
{
  Drive = 0,
  Turn = 1,
  SkidTurn = 2
} autoCont;
