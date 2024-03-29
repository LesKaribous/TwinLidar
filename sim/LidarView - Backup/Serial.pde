// Communication variables
import processing.serial.*;          // Import the serial library
Serial lidarPort;                       // Create the serial port object

boolean connected = false;
int baud = 115200;

public void serialBegin(){
 String port = "COM8";
 printArray(Serial.list());
 lidarPort = new Serial(this, port, baud);
 println("Serial connection has begin on port " + port);
 lidarPort.bufferUntil('\n');
}



int serialFreq = 0;
int serialCounter = 0;
int serialTimer = 0;



void checkSerial(){
  if(connected)
  while(lidarPort.available() > 0){
    String buffer = lidarPort.readStringUntil('\n');
    if(buffer == null) return;
    if(buffer.startsWith("Data.point[")){
      if(!buffer.contains("}")) return;
      String argStr = buffer.substring(buffer.indexOf("{")+1, buffer.indexOf("}")) ;
      String args[] = argStr.split(",");
      int[] value = {0,0,0,0};
      
      if(args.length == 4){
        for(int i = 0; i < 4; i++){
          value[i] = Integer.parseInt(args[i]); 
        }
      }else return;

      color c = color(255,0,0);
      if((value[3] == 1)) c = color(0,255,0);
      savePoint(new PolarPoint(value[0], value[1], value[2], c));
      
      serialCounter++;
      if(millis() - serialTimer > 500){
        serialFreq = serialCounter*2;
        serialTimer = millis();
        serialCounter = 0;
      }

    }else if(buffer.contains("fov(")){
      String argStr = buffer.substring(buffer.indexOf("(")+1, buffer.indexOf(")"));
      String args[] = argStr.split(",");
      int[] value = {0,0,0,0};
      if(args.length == 4){
        for(int i = 0; i < 4; i++){
          value[i] = Integer.parseInt(args[i]); 
        }
      }else return;
      fov.setLimit(value);  
    }
  }
}


void serialEvent(Serial p){
  if(connected == false) connected = true;
}
