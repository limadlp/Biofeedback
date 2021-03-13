import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
int x2Pos = 1;
float height_old = 0;
float height_new = 0;
float BPM_old = 0;
float BPM_new = 0;
float inByte = 0;
float BPM = 0;
float BPMin = 0;
float beat_old = 0;
float[] beats = new float[500];  // Used to calculate average BPM
int beatIndex;
float threshold = 515;//400; //620.0;  //Threshold at which BPM calculation occurs
boolean belowThreshold = true;
PFont font;


int spike = 0;
int deltabpm = 10;

PrintWriter out;
PrintWriter output;
PrintWriter output2;

void setup () {
  // set the window size:
  size(1500, 1000);        
  
  // List all the available serial ports
  println(Serial.list());
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0xff);
  font = createFont("Ariel", 24, true);
  textSize(24);
  
  out = createWriter("out.txt");
  output = createWriter("BPM.txt");
  output2 = createWriter("fase.txt"); 
  delay(2000);
}


void keyReleased() {
    output2.println((float)millis()/1000);  // Writes the remaining data to the file
    //stop();  // Stops the program
}



void exit() {
    out.flush();
    out.close();
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    output2.flush();
    output2.close();
    //exit();  // Stops the program
}

void stop(){
  output.flush();
  output.close();
  out.flush();
  out.close();
  output.flush();  // Writes the remaining data to the file
  output.close();  // Finishes the file
  output2.flush();
  output2.close();
}
int tempo = 1; 
void draw () {
  
  
  //if (BPM >=30 && BPM <= 180){
     
     //Map and draw the line for new data point
     float sec = (float)millis()/1000;
     //out.println(inByte);
     out.print(sec);
     out.print(" ");
     out.println(inByte);
     
     inByte *= 8;
     
     inByte = map(inByte, 0, 1023*8, 0, height);
     height_new = (height - inByte); 
     stroke(0xff, 0, 0); 
     line((xPos - 1), height_old , xPos, height_new);
     
     
    
     
     height_old = height_new;
    
     
     
     
     
     //if (tempo%  10 == 0){
      if (xPos >= width) {
        xPos = 0;
        //fill(0xFF);
        //rect(0, 0, width, height/2);
        background(0xff);
        
        //rect(0, 0, width, height/2);
      } 
      else {
        // increment the horizontal position:
        xPos++;
      }
      // draw text for BPM periodically
      
      
      
        
        
        fill(0xFF);
        rect(0, 0, 200, 100);
        fill(0x00);
        //text("BPM: " + (int)BPM, 25, 40);
        text("BPM: " + (int)inByte, 25, 40);
        
      
      
        
        BPM_new = BPM * 5;
        if (BPM >=30 && BPM <= 180){
        stroke(0, 0, 0xff);
        //line((xPos - 1),  height- BPM_old, xPos, height - BPM_new);
        //ellipse(xPos, inByte, 10, 10);
        }
        
        BPM_old = BPM_new;
      //}
      
      //delay(200);
      tempo++;
}


void serialEvent (Serial myPort) 
{
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) 
  {
    // trim off any whitespace:
    inString = trim(inString);

    // If leads off detection is true notify with blue line
    if (inString.equals("!")) 
    { 
      stroke(0, 0, 0xff); //Set stroke to blue ( R, G, B)
      inByte = 512;  // middle of the ADC range (Flat Line)
    }
    // If the data is good let it through
    else 
    {
      stroke(0xff, 0, 0); //Set stroke to red ( R, G, B)
      inByte = float(inString); 
      
      // BPM calculation check
      if (inByte >= threshold && belowThreshold == true)
      {
        calculaBPM();
        belowThreshold = false;
      }
      else if(inByte < threshold)
      {
        belowThreshold = true;
      }
    }
  }
}
/*  
void calculateBPM () 
{  
  int beat_new = millis();    // get the current millisecond
  int diff = beat_new - beat_old;    // find the time between the last two beats
  float currentBPM = 60000 / diff;    // convert to beats per minute
  
  beats[beatIndex] = currentBPM;  // store to array to convert the average
  
  float total = 0.0;
  for (int i = 0; i < 500; i++){
    total += beats[i];
  }
  BPM = total / 500;
  beat_old = beat_new;
  beatIndex = (beatIndex + 1) % 500;  // cycle through the array instead of using FIFO queue

}
*/
void calculaBPM(){
  float diff;
  float beat_new;
  
   spike++;
   float sec = (float)millis()/1000;
   //println(sec);
   beat_new = millis();
   diff = (beat_new - beat_old)/60000;
   beat_old = beat_new;
   BPM = 1/diff;
   if(BPM >=30 && BPM <= 180){
     println(sec, BPM);
     output.print(sec);
     output.print(" ");
     output.print(BPM);
     output.println();
   }
   
}
