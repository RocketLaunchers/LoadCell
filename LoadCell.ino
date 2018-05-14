
/*
  Rocket Launchers Load Cell program 
  Programmer: Luis Gutierrez

  Using:
  HX711 Library and Sample Sketch they provided, then heavily modified.
  Payload Program coded / libraries used from Juan(Nick) Garcia of the Rocket Launchers

  Use:
  Reads voltage from the LoadCell, converts it to digital, using the HX711, and then uploads it to an
  SD CARD through an Arduino and its SD shield
  
  Requirements:
  Arduino SD card Shield 
  HX711 Amplifier.
  Patience with the LoadCell
  

*/

#include "HX711.h"
#include <SD.h> //SD card
#include <Time.h>
//#include <TimeLib.h>


//HX711 pins used
#define DOUT  3
#define CLK  2

// SD card
#define DS1307_I2C_ADDRESS 0x68
#define TIME_MSG_LEN 11
#define TIME_HEADER 'T'

HX711 scale(DOUT, CLK);

float calibration_factor = -12300; //-7050 default, -12300 for tightened bolt on stand

//global variables
char floatStr[9]; //SD card uses this
//char dataStr[24];
File myFile;      //SD card uses this
float x; // used for whatever, mostly the getdata.

//time section
time_t t;
double mil; // millis
double mil2; // millis into seconds without any conversion loss
   


void setup() {
  Serial.begin(9600);
  /*
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
*/

  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading, must place this first after the Serial.begin, or it will not work ¯\_(ツ)_/¯
  //Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  //Serial.println(zero_factor);

  
//////////////////////////// SD Card code ////////////////////////////////
    Serial.println("Initializing SD card...");

  
    // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
    // Note that even if it's not used as the CS pin, the hardware SS pin
    // (10 on most Arduino boards, 53 on the Mega) must be left as an output
    // or the SD library functions will not work.
    pinMode(10, OUTPUT);

    if (!SD.begin(10))
    {
        Serial.println("SD card initialization failed!");
        return;
    }

    Serial.println("initialization done.");
    floatStr[0] = '\0';
    analogReference(INTERNAL);

////////////////////////////////////////////////////////////////////////

  
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  x = scale.get_units() * -9.81; //9.81 for the conversion to newtons
  //t = now();
  mil = millis();
  mil2 = mil / 1000;
  
  //Serial.print("Reading: ");
  Serial.print(x, 3); //3 decimal points
  Serial.print("  "); //new line at the end
  Serial.println(mil2);



/*
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);


  //if the file opened okay, write to it:
  if (myFile)
  {
    
      //myFile.print("Reading: ");
      myFile.println(x, 3); //the reading from the loadcell
      //myFile.print(" newtons"); //Change this for different units, make sure you convert.
     

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






  
/*Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
*/

  /*
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
  */
}

