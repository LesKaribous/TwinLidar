ArrayList<PolarPoint> Points = new ArrayList<PolarPoint>();

void drawPoints(){
  for(int i = 0; i < Points.size(); i++){
     Points.get(i).draw(); 
  }
}

void randomize(){
  for(int i=0; i < 100; i++){
    Points.add(new PolarPoint()); 
  }
}

class Point{
  PVector pos;
  
  Point(){
    pos = new PVector();
    pos.x = random(-1,1);
    pos.y = random(-1,1);
  }
  
  Point(float x, float y){
    pos = new PVector();
    pos.x = x;
    pos.y = y;
  }
  
  Point(PVector origin){
    pos = new PVector();
    pos.x = origin.x;
    pos.y = origin.y;
  }
  
  void draw(){
    center();
    point(pos);
    resetMatrix();
  }
  
};


class PolarPoint{
  float _distance, _theta;
  int _intensity;
  
  PolarPoint(){
    _intensity = 100;
    _distance = random(-0.8,0.8);
    _theta = random(-0.8,0.8);
  }
  
  PolarPoint(float distance, float theta, int intensity){
    _intensity = intensity;
    _distance = distance;
    _theta = theta;
  }
  
  void draw(){
    center();
    rotate(_theta);
    strokeWeight(2);
    stroke(map(_intensity, 0,100,0,150),0,0);
    point(toPixel(_distance),0);
    strokeWeight(4);
    
    stroke(0);
    point(0,0); 
    resetStroke();
    resetMatrix();
  }
  
  void debug(){
    println("polar coordinate : [" + _theta + "°, " + _distance + " u]"); 
  }
  
};
