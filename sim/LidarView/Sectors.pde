

ArrayList<Sector> sectors;

void drawSectors(){
  for(Sector sec : sectors){
    if(sec._count > 0)
      sec.draw(); 
  }
}

class Sector{
  int _id;
  int _count; float _average;
  
  Sector(int id, int count, float average){
    _id = id;
    _count = count;
    _average = average;
  }
  
  
  void draw(){
    float angleStart = _id * (360/sectors.size());
    
    stroke(255,100,100);
    strokeWeight(2);
    pushMatrix();
    rotate(DEG_TO_RAD*(-angleStart ) - DEG_TO_RAD*((360/sectors.size())-1)/2.0);
    line(0, 0, _average*dScale, 0);
    
    //arc(0, 0, _min, _min, -(360/sectors.size()), 0);
    //arc(0, 0, _max, _max, -(360/sectors.size()), 0);
    
    popMatrix();
  }
  
  
}
