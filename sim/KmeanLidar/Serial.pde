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
        if(args.length >= 3){
          for(int i = 0; i < 3; i++){
            value[i] = Integer.parseInt(args[i]); 
          }
        }else return;
          
        //if(value[0]/4000.0 < 0.5 && value[0]/4000.0 > 0.1 && value[2] > 200)
        PointBuffer.add(new PolarPoint(toPixel(value[0]/4000.0), (value[1]/100.0)*DEG_TO_RAD, value[2]));
      }
    }
    }catch(Exception e){}
    busy = false;
  }
}











void serialEventB(Serial p)
{
  if(connected == false) connected = true;
   
  int pack_type   = 0;
  int data_length = 0;
  int start_angle = 0;
  int stop_angle  = 0;

  if(p.available() >= 10){
    if(p.readChar() == 0xAA && p.readChar() == 0x55){
      char[] headerBuffer = new char[8];
      for(int i = 0; i < 8; i++){
        headerBuffer[i] = p.readChar();
      }
        
      pack_type = headerBuffer[0];
      data_length = headerBuffer[1];
      start_angle = headerBuffer[3] << 8 + headerBuffer[2];
      stop_angle = headerBuffer[5] << 8 + headerBuffer[4];
      
      int delta = stop_angle - start_angle;
      if(stop_angle < start_angle)
          delta =  0xB400 - start_angle + stop_angle;
  
        float angle_per_sample = 0;
        if(delta > 1)
          angle_per_sample = delta / (data_length-1);
      
      println("[Serial] Header : t=", pack_type, " l=", data_length, " a0=", start_angle, " a1=", stop_angle);
      
      for(int i = 0; i < data_length; i++){
        int data0 = int(p.readChar());
        int data1 = int(p.readChar());
        int data2 = int(p.readChar());
        
        int distance = (data2  << 8) + data1 ;
        float angle = (start_angle + angle_per_sample * i);
        float anglef = TWO_PI * (angle / 0xB400);
        
        println("[Serial] Data : p", i,":[",data0,", ",distance/300.0,", ",anglef, "]");
        Points.add(new PolarPoint(distance/300.0, anglef, data0).toPoint());
      }
    }
  } 
}
