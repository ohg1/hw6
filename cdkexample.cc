// Jiwon Topper
// jxt171830@utdallas.edu
// CS3377.002

#include <fstream>
#include <iostream>
#include <sstream>
#include "cdk.h"
#include "BinaryFileRecord.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contenets"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e", "f"};
  const char 		*columnTitles[] = {"0", "a", "b", "c", "d", "e", "f"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

//BinaryFileHeader
BinaryFileHeader *header = new BinaryFileHeader();
ifstream binInfile("cs3377.bin", ios::in | ios::binary);
binInfile.read((char*)header, sizeof(BinaryFileHeader));

//display header contenets
//use stringstream to format hex number
stringstream ss;
//magic number
ss << "Magic: 0x" << uppercase <<  hex << header->magicNumber;
const char* arg = ss.str().c_str();
setCDKMatrixCell(myMatrix, 1, 1, arg);
//version number
stringstream ver;
ver << "Version: " << fixed  << header->versionNumber;
arg = ver.str().c_str();
setCDKMatrixCell(myMatrix, 1, 2, arg );
//number of records
stringstream rec;
rec << "NumRecords: " << header->numRecords;
arg = rec.str().c_str();
setCDKMatrixCell(myMatrix, 1, 3, arg);

// get input from cs3377.bin
BinaryFileRecord *myRecord = new BinaryFileRecord();
int records = header->numRecords;
for(int i=1; i <= records; i++)
{

	binInfile.read((char*)myRecord, sizeof(BinaryFileRecord));
	//get the length of string
	stringstream len;
	len << "strlen: " << (int)myRecord->strLength;
	arg = len.str().c_str();
	//print the size
	setCDKMatrixCell(myMatrix, i+1, 1, arg);
	//print char*
	setCDKMatrixCell(myMatrix, i+1, 2, myRecord->stringBuffer );
}


  /*
   * Dipslay a message
   */
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
