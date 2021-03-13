//#include <SoftwareSerial.h>


//SoftwareSerial BTSerial(3, 2);

double threshold = 515;
bool belowThreshold = true;
double BPM = 0;
double AV_BPM = 0;
double AV_GSR = 0;
double AV_BRE = 0;

double diff;
double beat_new;
double beat_old = 0;
double sec;



const int numReadings = 50;

double readingsA0[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
double totalA0 = 0;                  // the running total
double averageA0 = 0;                // the average

double readingsA1[numReadings];      // the readings from the analog input
double totalA1 = 0;                  // the running total
double averageA1 = 0;  


double readingsA2[numReadings];      // the readings from the analog input
double totalA2 = 0;                  // the running total
double averageA2 = 0;

void setup(){
  //BTSerial.begin(9600);
  Serial.begin(9600);
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readingsA0[thisReading] = 0;
    readingsA1[thisReading] = 0;
    readingsA2[thisReading] = 0;
  }
  
  
  delay(2000);

  
}


void loop(){
  double ECG = analogRead(A0);
  double GSR = analogRead(A1);
  double BRE = analogRead(A2) * 2;


  if (ECG >= threshold && belowThreshold == true){
     sec = (float)millis()/1000;
     beat_new = millis();
     diff = (beat_new - beat_old);
     beat_old = beat_new;
     if (diff != 0) BPM = 60000/diff;
     belowThreshold = false;
  }
  else if(ECG < threshold) {
    belowThreshold = true;
  }


  

  //Serial.println(AV_BPM);


  if(millis() % 100 == 0){

    if(BPM >=30 && BPM <= 200){
        // subtract the last reading:
      totalA0 = totalA0 - readingsA0[readIndex];
      totalA1 = totalA1 - readingsA1[readIndex];
      totalA2 = totalA2 - readingsA2[readIndex];
  
      
      // read from the sensor:
      readingsA0[readIndex] = BPM;
      readingsA1[readIndex] = GSR;
      readingsA2[readIndex] = BRE;
      
      // add the reading to the total:
      totalA0 = totalA0 + readingsA0[readIndex];
      totalA1 = totalA1 + readingsA1[readIndex];
      totalA2 = totalA2 + readingsA2[readIndex];

      
      // advance to the next position in the array:
      readIndex = readIndex + 1;
    
      // if we're at the end of the array...
      if (readIndex >= numReadings) {
        // ...wrap around to the beginning:
        readIndex = 0;
      }
    
      AV_BPM = totalA0 / numReadings;
      AV_GSR = totalA1 / numReadings;
      AV_BRE = totalA2 / numReadings;
       
       //Serial.print(sec);
       //Serial.print(" ");
       Serial.print(AV_BPM);
       Serial.print(",");
       Serial.print(AV_GSR);
       Serial.print(",");
       Serial.print(AV_BRE);
       //Serial.print(",");
       //Serial.print((float)millis()/1000);
       Serial.println();    
     
    }
     

  }
  


  //Serial.println(BPM);
  delay(1);



}
