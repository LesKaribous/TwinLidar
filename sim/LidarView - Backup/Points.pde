
void drawPoints(){
  for(PolarPoint p : Points){
    p.draw();
  }
}

void savePoint(PolarPoint p){
  if(Points.size() >= maxCount) Points.remove(0);
  Points.add(p);
}

class PolarPoint{
  float _distance, _theta;
  float _intensity;
  color col;
  
  PolarPoint(){
    _intensity = 0;
    _distance = 0;
    _theta = 0;
    
    col = color(0,255,0);
  }
  
  PolarPoint(float distance, float theta, float intensity, color filter){
    _intensity = intensity;
    _distance = distance * dScale;
    _theta = theta * aScale;
    col = filter;
  }
  
  void draw(){
    pushMatrix();
    strokeWeight(3);
    stroke(col);
    noFill();

    rotate(_theta);
    point(_distance,0);
    popMatrix();
  }
   
}
