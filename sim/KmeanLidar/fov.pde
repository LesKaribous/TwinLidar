


class Fov{
  float angleMin, angleMax, distMin, distMax;
  
  Fov(){
     angleMin = angleMax = distMin = distMax = 0;
  }
  
  
  void setLimit(int[] value){
    if(value.length == 4){
      angleMin = value[0]/100.0f;
      angleMax = value[1]/100.0f;
      distMin = value[2]/100.0f;
      distMax = value[3]/100.0f;
    }
  }
  
  void draw(){
    strokeWeight(1);
    stroke(50);
    rotate(angleMin);
    line(distMin, 0, distMax, 0);
    rotate(angleMax-angleMin);
    line(distMin, 0, distMax, 0);
  }
  
  
};
