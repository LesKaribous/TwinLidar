// Communication variables
import processing.serial.*;          // Import the serial library
Serial myPort;                       // Create the serial port object

boolean connected = false;
int baud = 115200;

ArrayList<PolarPoint> PointBuffer;

public void serialBegin(String port){

 PointBuffer = new ArrayList<PolarPoint>();
 
 clicSerialBegin = true ;
 serialBegin.setCaptionLabel("re-connect");

 //printArray(Serial.list());
 myPort = new Serial(this, port, baud);
 println("Serial connection has begin on port " + port);
 myPort.bufferUntil('\n');
}

public void serialBegin(){
 if (clicSerialBegin == false)
 {
   clicSerialBegin = true ;
   serialBegin.setCaptionLabel("re-connect");
 }
 myPort = new Serial(this, Serial.list()[int(serialList.getValue())], baud);
 println("Serial connection has begin on port " + int(serialList.getValue()));
}

public void serialRefresh()
{
  clicSerialRefresh = true ;
  serialList.clear();
  serialList.addItems(Serial.list());
  println("Refreshing the serial list");
}

public void serialStop()
{
  clicSerialStop = true ;
  myPort.stop();
  connected = false;
  println("Serial connection has been stopped");
}



boolean busy = false;

void serialEvent(Serial p){
  if(!busy){
    busy = true;
    try{
    if(connected == false) connected = true;
    while(p.available() > 0){
  
      String buffer = p.readStringUntil('\n');
      //println(buffer);
          
      if(buffer.contains("Data.point[")){
        
        String argStr = buffer.substring(buffer.indexOf("{")+1, buffer.indexOf("}")) ;
        //println(argStr);
        String args[] = argStr.split(",");
        int[] value = {0,0,0};
        if(args.length == 3){
          for(int i = 0; i < 3; i++){
            value[i] = Integer.parseInt(args[i]); 
          }
        }else return;
          
        //if(value[0]/4000.0 < 0.5 && value[0]/4000.0 > 0.1 && value[2] > 200)
        PointBuffer.add(new PolarPoint(toPixel(value[0]/4000.0), (value[1]/100.0)*DEG_TO_RAD, value[2]));
      }else if(buffer.contains("fov(")){
        String argStr = buffer.substring(buffer.indexOf("(")+1, buffer.indexOf(")"));
        String args[] = argStr.split(",");
        int[] value = {0,0,0,0};
        if(args.length == 4){
          for(int i = 0; i < 3; i++){
            value[i] = Integer.parseInt(args[i]); 
          }
        }else return;
        fov.setLimit(value);
      }
    }
    }catch(Exception e){}
    busy = false;
  }
}
