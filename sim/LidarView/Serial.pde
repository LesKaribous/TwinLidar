// Communication variables
import processing.serial.*;          // Import the serial library
Serial lidarPort;                       // Create the serial port object

boolean connected = false;
int baud = 115200;

public void serialBegin() {
  String port = "COM5";
  printArray(Serial.list());
  lidarPort = new Serial(this, port, baud);
  println("Serial connection has begin on port " + port);
  lidarPort.bufferUntil('\n');
}



int serialFreq = 0;
int serialCounter = 0;
int serialTimer = 0;

void checkSerial() {
  if (connected)
    while (lidarPort.available() > 0) {
      String buffer = lidarPort.readStringUntil('\n');
      if (buffer == null) return;
      if (buffer.startsWith(">lidar:")) {
        String dataStr = buffer.substring(buffer.indexOf(":")+1, buffer.indexOf("|np")) ;
        
        String args[] = dataStr.split(";");
        
        for (String pointStr : args) {
          String argsP[] = pointStr.split(":");
          float[] value = {0, 0};
          
          if (argsP.length == 2) {

            for (int i = 0; i < 2; i++) {
              value[i] = Float.parseFloat(argsP[i]);
            }
                    
            savePoint(new PolarPoint(value[1], value[0], 255, color(255, 0, 0)));
            serialCounter++;
            if (millis() - serialTimer > 500) {
              serialFreq = serialCounter*2;
              serialTimer = millis();
              serialCounter = 0;
            }
          }
        }
      }else if (buffer.startsWith(">fov:")) {
        String dataStr = buffer.substring(buffer.indexOf(":")+1, buffer.indexOf("|np")) ;
        
        String args[] = dataStr.split(";");
        if(args.length == 2){
          String angleArg[] = args[0].split(":");
          String distArg[] = args[1].split(":");
         
          int value[] = {0,0,0,0};
          if (angleArg.length == 2 && distArg.length == 2) {
  
            
            value[0] = (int)Float.parseFloat(angleArg[0]);
            value[1] = (int)Float.parseFloat(angleArg[1]);
            value[2] = (int)Float.parseFloat(distArg[0]);
            value[3] = (int)Float.parseFloat(distArg[1]);
            
           fov.setLimit(value);

          }
        }
      }else if (buffer.startsWith(">sectors:")) {
        String dataStr = buffer.substring(buffer.indexOf(":")+1, buffer.indexOf("|np")) ;
        
        String args[] = dataStr.split(";");
        
        
        sectors.clear();
        for (String sectorsStr : args) {
          String argsP[] = sectorsStr.split(":");
          
          //println(argsP);
          
          float[] value = {0, 0, 0, 0, 0};
          if (argsP.length == 5) {

            for (int i = 0; i < 5; i++) {
              value[i] = Float.parseFloat(argsP[i]);
            }
            //println(value);
          }
          
          sectors.add(new Sector(int(value[0]), int(value[1]), value[2], value[3], value[4]));
        }
      }
    }
}





/*




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
 }else if(buffer.contains("count(")){
 String argStr = buffer.substring(buffer.indexOf("(")+1, buffer.indexOf(")"));
 String args[] = argStr.split(",");
 int[] value = {0};
 if(args.length == 1){
 for(int i = 0; i < 1; i++){
 value[i] = Integer.parseInt(args[i]);
 }
 }else return;
 //println(value[0]);
 }
 }
 }
 */

void serialEvent(Serial p) {
  if (connected == false) connected = true;
}
