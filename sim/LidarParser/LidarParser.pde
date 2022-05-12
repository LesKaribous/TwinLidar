
int Nmax = 1000;
int Nmin = 5;

ClusterEngine brain;

// GUI Visibility
boolean GUIVisible = true;

void setup(){
  size(1280,800);
  //frameRate(24);
  
  brain = new ClusterEngine(50);
  createGUI();
  
  serialBegin("COM4");

}



void draw(){
  background(200);
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

      coordSystem.draw();
      
      drawPoints();
      
      for(int i=0; i<5; i++);
        brain.compute();
      
      
      //lidar.draw();
    }else brain.reset();
  }
}