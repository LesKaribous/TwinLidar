// Communication variables
import processing.serial.*;          // Import the serial library
Serial myPort;                       // Create the serial port object

int baud = 115200;

public void serialBegin() {
  myPort = new Serial(this, Serial.list()[1], baud);
  println("Serial connection has begin on port COM3");
  myPort.bufferUntil('\n');
}



int serialFreq = 0;
int serialCounter = 0;
int serialTimer = 0;

boolean busy = false;
void serialEvent(Serial p) {
  if (!paused) {
    try {
      
      int ptLimit = 0;
      while (p.available() > 0 && ptLimit < 300) {
        String buffer = p.readStringUntil('\n');
        if (buffer.contains("Data.point[")) {
          String argStr = buffer.substring(buffer.indexOf("{")+1, buffer.indexOf("}")) ;
          String args[] = argStr.split(",");

          int[] value = {0, 0, 0};
          if (args.length >= 3) {
            for (int i = 0; i < 3; i++) {
              value[i] = Integer.parseInt(args[i]);
            }
            
          } else return;

          if(value[2] > 180){ //remove bad points
            savePoint(value[0], value[1], value[2]);
            while (points.size() > N) points.remove(0);
              serialCounter++;
              if(millis() - serialTimer > 500){
                serialFreq = serialCounter*2;
                serialTimer = millis();
                serialCounter = 0;
              }
          }
        }
      }
      myPort.clear();
    }catch(Exception e) {e.printStackTrace();}  
  }else myPort.clear();
}
