Lidar lidar = new Lidar();
boolean animate = true;

Fov fov;
PolarSystem system;
ArrayList<PolarPoint> Points;

UI ui;

int maxCount = 10000;

void setup(){
  size(1000,1000);
  
  serialBegin();
  
  ui = new UI();  
  fov = new Fov();
  system = new PolarSystem();
  Points = new ArrayList<PolarPoint>();
  sectors = new ArrayList<Sector>();
}


void draw(){
  checkSerial();
  lidarPort.clear();
  background(200);
  center();
  rotate(-PI/2);

  system.draw();
  fov.draw();     
  lidar.draw();
  ui.draw();
  drawPoints();
  drawSectors();
  
}

void mouseWheel(MouseEvent event) {
  float e = event.getCount();
  dScale -= e/100.0;
}

void keyPressed(){
  if(connected) lidarPort.write("toggleFilter\n");
}
