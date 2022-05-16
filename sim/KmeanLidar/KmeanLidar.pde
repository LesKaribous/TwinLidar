
int Nmax = 500;
int Nmin = 5;

ClusterEngine brain;

// GUI Visibility
boolean GUIVisible = true;

void setup(){
  size(1280,800);
  
  brain = new ClusterEngine(50);
  createGUI();
  
  serialBegin("COM3");

}


float lastFrame = 0;
void draw(){
  if(PointBuffer.size() > 0 && !busy){
    busy = true;
    for(PolarPoint pp : PointBuffer){ 
      Points.add(pp.toPoint());
    };
      
    PointBuffer.clear();
    busy = false;
  }
  
  while(Points.size() >= Nmax && Points.size()> Nmin){
    Points.remove(0); 
  }
  
  for(int i = 0; i < Points.size(); i++){
    Point p = Points.get(i);
    p.update();
    if(p.opacity == 0){
      Points.remove(p);
      i--;
    }
  }  
  
  
  if(Points.size() > Nmin/2){
    if(brain.centroids.size() > 0){
      background(200);
      coordSystem.draw();
      
      drawPoints();
      
      //for(int i=0; i<5; i++);
        //brain.compute();
      
      
      lidar.draw();
    }else brain.reset();
  }
  
  println("Framerate : " + 6000 / (millis() - lastFrame));
  lastFrame = millis();
}
