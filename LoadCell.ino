

/*
  Rocket Launchers Load Cell program 
  Programmer: Luis Gutierrez

  Using:
  HX711 Library and Sample Sketch they provided, then heavily modified.
  Payload Program coded / libraries used from Juan Garcia of the Rocket Launchers

  Use:
  Reads voltage from the LoadCell, converts it to digital, using the HX711, and then uploads it to an
  SD CARD through an Arduino and its SD shield
  
  Requirements:
  Arduino SD card Shield 
  HX711 Amplifier.
  

*/

#include "HX711.h"
#include <SD.h> //SD card
#include <time.h>



//HX711 pins used
#define DOUT  3
#define CLK  2

// SD card
#define DS1307_I2C_ADDRESS 0x68
#define TIME_MSG_LEN 11
#define TIME_HEADER 'T'

HX711 scale(DOUT, CLK);

//global variables
char floatStr[9]; //SD card uses this
char dataStr[24];
File myFile;      //SD card uses this
double x = 0;    //Free variable to use for whatever

//LoadCell Calibration using HX711
float calibration_factor = -12300; // -12300 worked for the stand as of 5/14/2018
//double MyArray[10];
//int Counter = 0;
//double Total = 0;

 time_t seconds = time (NULL);

/*
void updateTime()
{
    seconds = seconds + 1;
    if(seconds == 60)
    {
        minutes = minutes + 1;
        seconds = 0;

        if(minutes == 60)
        {
            hours = hours + 1;
            minutes = 0;
        }
    }
}
*/


void setup() {
  Serial.begin(9600);
  /*Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
*/

//////////////////////////// SD Card code ////////////////////////////////
    Serial.println("Initializing SD card...");

  
    // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
    // Note that even if it's not used as the CS pin, the hardware SS pin
    // (10 on most Arduino boards, 53 on the Mega) must be left as an output
    // or the SD library functions will not work.
    pinMode(10, OUTPUT);

    if (!SD.begin(10))
    {
        Serial.print("SD card initialization failed!");
        return;
    }

    Serial.println("initialization done.");
    floatStr[0] = '\0';
    analogReference(INTERNAL);

////////////////////////////////////////////////////////////////////////
    

  scale.set_scale();
  scale.tare(); //Reset the scale to z0

  long zero_factor = scale.read_average(10); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  
  
  
  
  
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  x = (scale.get_units() * -9.81); //this is where it gets its units from, 9.81 for newtons

  Serial.print("Reading: ");
  Serial.print(x); //*9.81 for newtons
  Serial.print(" newtons"); //Change this for different units, make sure you convert.
  Serial.println();
/*Serial.print("                                   calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
*/  

/*
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);


  //if the file opened okay, write to it:
  if (myFile)
  {
    
      //myFile.print("Reading: ");
      myFile.print(x); //the reading from the loadcell
      //myFile.print(" newtons"); //Change this for different units, make sure you convert.
      myFile.println();

      printf ("Number of hours since 1970 Jan 1st is %ld \n", seconds/3600);
      
  }
  else
  {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
      return;
  }


    myFile.close();

*/







  
/*

  if (Counter >= 10)
  {
    Counter = 0;
    Total = 0;
    
    for (int i = 0; i < 10; i++)
    {
      Total += MyArray[i];
    }

    Total = Total / 10;
    
    Serial.print("Reading: ");
  Serial.print(Total, 1); //*9.81 for newtons
  Serial.print(" newtons"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  }


  
  else 
  {
    MyArray[Counter] = scale.get_units() * -9.81;
    Counter++;
  }
  */


/*
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 100;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 100;
  }
*/

  
}

