

ArrayList<Sector> sectors;

void drawSectors(){
  for(Sector sec : sectors){
    if(sec._count > 0)
      sec.draw(); 
  }
}

class Sector{
  int _id;
  int _count; float _average; float _min; float _max;
  
  Sector(int id, int count, float average, float min, float max){
    _id = id;
    _count = count;
    _average = average;
    _min = min;
    _max = max;
  }
  
  color getColor(){
    color a = color(0,0,255);
    color b = color(255,0,0);
    return lerpColor(a, b, map(_min, fov.distMin, fov.distMax, 1, 0));
    
  }
  
  
  void draw(){
    float angleStart = _id * (360/sectors.size());
    
    stroke(getColor());
    strokeWeight(2);
    pushMatrix();
    rotate(DEG_TO_RAD*(angleStart + 1) + DEG_TO_RAD*((360/sectors.size())-1)/2.0);
    line(fov.distMin*dScale, 0, _max*dScale, 0);
    
    //arc(0, 0, _min, _min, -(360/sectors.size()), 0);
    //arc(0, 0, _max, _max, -(360/sectors.size()), 0);
    
    popMatrix();
  }
  
  
}
