
int Nmax = 1000;
int Nmin = 5;

// GUI Visibility
boolean GUIVisible = true;

NeuralNetwork brain;

void setup(){
  size(1280,800);
  //frameRate(24); 
  
  int[] layers = new int[3];
  layers[0] = 30;
  layers[1] = 30;
  layers[2] = 1;
  
  brain = new NeuralNetwork(20, 30, 1, 0.01);
  
  //createGUI();
  
  //serialBegin("COM4");
}


void draw(){
  
  
  float[] data = new float[20];
  
  for(int i = 0; i < data.length ; i++) 
    data[i] = random(50);
    
  println(brain.feedForward(data));
}

/*
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
      
      for(int i=0; i<5; i++);
        brain.compute();
      
      
      lidar.draw();
    }else brain.reset();
  }
}
*/
