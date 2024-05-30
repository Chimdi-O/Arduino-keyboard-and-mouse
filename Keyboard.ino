#include <LIS3DHTR.h>

#include "LIS3DHTR.h"
#include <Wire.h>
LIS3DHTR<TwoWire> LIS;
#define WIRE Wire

const int button1Pin = 2; 
const int button2Pin = 3; 
const int button3Pin = 4; 
const int button4Pin = 5; 
double hardwareState[5]; // this will be int the format w,a,s,d,x_accel,y_accel


void setup() {
  Serial.begin(2400);
  pinMode(button1Pin,INPUT); 
  pinMode(button2Pin,INPUT);
  pinMode(button3Pin,INPUT); 
  pinMode(button4Pin,INPUT);

  while (!Serial)
  {
  };
  LIS.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); 
  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);

}

void loop() {

  int button1 = digitalRead(button1Pin);
  int button2 = digitalRead(button2Pin);
  int button3 = digitalRead(button3Pin);
  int button4 = digitalRead(button4Pin);


  if ( (button1 == HIGH) or (button2 == HIGH) or (button3 == HIGH) or (button4 == HIGH) ) { 

      if (button1 == HIGH) { 
        hardwareState[0] = 1;
   
      }else{ 
        hardwareState[0] = 0;
      }
      
      if (button2 == HIGH) { 
        hardwareState[1] = 1;

      } else{ 
        hardwareState[1] = 0;
      }
      
      if (button3 == HIGH) { 
        hardwareState[2] = 1;

      }else{ 
        hardwareState[2] = 0;
      }
       
       if (button4 == HIGH) { 
        hardwareState[3] = 1;
      }else{ 
        hardwareState[3] = 0;
      }

  }else{
    hardwareState[0] = 0;
    hardwareState[1] = 0;
    hardwareState[2] = 0;
    hardwareState[3] = 0;
    }

  if (!LIS)
  {
    Serial.println("LIS3DHTR didn't connect.");
    while (1)
      ;
    return;
  }
  //3 axis
   hardwareState[4] = LIS.getAccelerationX();
   hardwareState[5] = LIS.getAccelerationY();

   

   for( int i = 0; i < 4; ++i){ 
    Serial.print((int)hardwareState[i]);
    Serial.print("/");
   }
   
   Serial.print("|");
   Serial.print(hardwareState[4]);
    Serial.print("/");
   Serial.println(hardwareState[5]);
}
