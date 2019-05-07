// the regular Adafruit "TouchScreen.h" library only works on AVRs

// different mcufriend shields have Touchscreen on different pins
// and rotation.
// Run the TouchScreen_Calibr_native sketch for calibration of your shield

#include <MCUFRIEND_kbv.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>

MCUFRIEND_kbv tft; 
SoftwareSerial mySerial(52, 50);
TinyGPS gps;// hard-wired for UNO shields anyway.
#include <TouchScreen.h>


// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 200
#define MAXPRESSURE 1000

//Lap Counter Variables

;


int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID, oldcolor, currentcolor;
const int TS_LEFT=90,TS_RT=1360;

void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);


  Serial.println("uBlox Neo 6M");
  Serial.print("Testing TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
  Serial.print("Sizeof(gpsobject) = "); Serial.println(sizeof(TinyGPS));
  Serial.println();

                                //Initialize LCD
 
   
}




  


void loop()
{
  bool newdata = false;
  unsigned long start = millis();
   while (millis() - start < 500) {
    if (mySerial.available()) {
      char c = mySerial.read();
      // Serial.print(c);  // uncomment to see raw GPS data
      if (gps.encode(c)) {
        newdata = true;
        // break;  // uncomment to print new data immediately!
      }
    }
  }

  // Every 5 seconds we print an update
  
  
  if (newdata) {
    Serial.println("Acquired Data");
    Serial.println("-------------");
    gpsdump(gps);
    Serial.println("-------------");
    Serial.println();
  }
  uint16_t tmp;

 ID = tft.readID();
    tft.begin(ID);
    Serial.begin(9600);
    
show_tft;

   
  
   

    

 
 
  




   
    
  
} 








void gpsdump(TinyGPS &gps)
{
  long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  gps.get_position(&lat, &lon, &age);
  Serial.print("Lat/Long(10^-5 deg): "); Serial.print(lat); Serial.print(", "); Serial.print(lon); 
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");
  
  // On Arduino, GPS characters may be lost during lengthy Serial.print()
  // On Teensy, Serial prints to USB, which has large output buffering and
  //   runs very fast, so it's not necessary to worry about missing 4800
  //   baud GPS characters.

 gps.f_get_position(&flat, &flon, &age);
  Serial.print("Lat/Long(float): "); printFloat(flat, 5); Serial.print(", "); printFloat(flon, 5);
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");

  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  Serial.print("Date: "); Serial.print(static_cast<int>(month)); Serial.print("/"); 
    Serial.print(static_cast<int>(day)); Serial.print("/"); Serial.print(year);
  Serial.print("  Time: "); Serial.print(static_cast<int>(hour)); Serial.print(":"); 
    Serial.print(static_cast<int>(minute)); Serial.print(":"); Serial.print(static_cast<int>(second));
    Serial.print("."); Serial.print(static_cast<int>(hundredths));
  Serial.print("  Fix age: ");  Serial.print(age); Serial.println("ms.");
 



  Serial.print("Alt(cm): "); Serial.print(gps.altitude()); Serial.print(" Course(10^-2 deg): ");
    Serial.print(gps.course()); Serial.print(" Speed(10^-2 knots): "); Serial.println(gps.speed());
  Serial.print("Alt(float): "); printFloat(gps.f_altitude()); Serial.print(" Course(float): ");
    printFloat(gps.f_course()); Serial.println();
  Serial.print("Speed(knots): "); printFloat(gps.f_speed_knots()); Serial.print(" (mph): ");
    printFloat(gps.f_speed_mph());
   
  Serial.print(" (mps): "); printFloat(gps.f_speed_mps()); Serial.print(" (kmph): ");
    printFloat(gps.f_speed_kmph()); Serial.println();

  gps.stats(&chars, &sentences, &failed);
  Serial.print("Stats: characters: "); Serial.print(chars); Serial.print(" sentences: ");
    Serial.print(sentences); Serial.print(" failed checksum: "); Serial.println(failed);
}

void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0) {
     Serial.print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
  }
  

  void show_tft(void)
{
    long lat, lon;
  float flat, flon;
  unsigned long date, time, age, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  
    tft.setRotation(1);
    tft.setCursor(0, 0);
    tft.setTextSize(4);
    
    tft.setTextColor(BLUE);
    tft.print(F("    EVER   "));
    
   
    tft.println("");
    
    tft.setTextSize(4);
    tft.println("");
    tft.setTextSize(4);
    tft.println("   Speed:" + String(gps.f_speed_kmph()));
    tft.println("");
    tft.setTextSize(2);

    tft.setTextColor(RED);
    tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
    tft.print("lap");
   
    tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(0, (tft.height() * 6) / 8);
    tft.print("distance:" + String(gps.f_course()));
   
    
    
}





  

