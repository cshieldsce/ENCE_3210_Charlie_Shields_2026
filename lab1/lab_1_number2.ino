#include <math.h>
float cosine[361];

void setup() {
  Serial.begin(9600);
  
  for (int degrees=0; degrees<=360; degrees++) {  // for loop from 0 to 360
     float radians = degrees * ( 3.14 / 180.0);   // convert degrees to radians
     cosine[degrees] = cos(radians);              // calculate cosine
     Serial.print(degrees);
     Serial.print(", ");
     Serial.println(cosine[degrees]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
