Lidar lidar = new Lidar();
boolean animate = true;

Fov fov;
PolarSystem system;
ArrayList<PolarPoint> Points;

UI ui;

int maxCount = 500;

void setup(){
  size(1000,1000);
  
  serialBegin();
  
  ui = new UI();  
  fov = new Fov();
  system = new PolarSystem();
  Points = new ArrayList<PolarPoint>();
}


void draw(){
  checkSerial();
    
  background(200);
  center();
  rotate(-PI/2);

  
  system.draw();
  fov.draw();     
  lidar.draw();
  ui.draw();
  drawPoints();
  
  
}


void keyPressed(){
  if(connected) lidarPort.write("toggleFilter\n");
}
