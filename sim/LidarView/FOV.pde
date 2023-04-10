class Fov{
  float angleMin, angleMax, distMin, distMax;
  
  Fov(){
     angleMin = 0;
     angleMax = 360;
     distMin = 200;
     distMax = 500;
  }
  
  
  void setLimit(int[] value){
    if(value.length == 4){
      angleMin = value[0];
      angleMax = value[1];
      distMin = value[2];
      distMax = value[3];
    }
  }
  
  void draw(){
    pushMatrix();
    strokeWeight(1);
    stroke(50);
    rotate(angleMin*aScale);
    line(distMin*dScale, 0, distMax*dScale, 0);
    rotate((angleMax-angleMin)*aScale);
    line(distMin*dScale, 0, distMax*dScale, 0);
    popMatrix();
  }
  
  
};
