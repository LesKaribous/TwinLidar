
float Tstep = 10;
float Astep = (50/2)/(maxDist/2);

Area a;

class Area{
  float minA, maxA;
  float minD, maxD;
  float objectWidth;
  
  Area(){
     minA = maxA = minD = maxD = 0;
     objectWidth = 0;
  }
  
  Area(float _minA, float _minD, float _objectWidth){
     minA = _minA;
     minD = _minD;
     objectWidth = _objectWidth;
     maxD = minD + _objectWidth;
     maxA = minA + _objectWidth/maxD;
  }
  
  void stepDist(){
    minD += Tstep;
    maxD = minD + objectWidth;
    maxA = minA + objectWidth/maxD;
  }
  
  void setAngle(){
    minA += Astep/2;
    maxA += Astep/2;
  }
  
  void resetDist(){
    minD = minDist;
    maxD = minD + objectWidth;
    maxA = objectWidth/maxD;
  }
  
  boolean isInArea(Point p){
    return p._distance < maxD && p._distance >= minD && p._theta < maxA && p._theta >= minA;
  }
  
  void draw(){
    center();
    stroke(0);
    noFill();
    strokeWeight(1);
    line(cos(minA) * minD, sin(minA) * minD, cos(minA) * maxD, sin(minA) * maxD);
    line(cos(maxA) * minD, sin(maxA) * minD, cos(maxA) * maxD, sin(maxA) * maxD);
    arc(0,0,maxD, maxD, minA, maxA);
    arc(0,0,minD, minD, minA, maxA);
  }
};



int countPoint(Area a){
  int result = 0;
  for(int i=points.size() - 1; i >= 0; i--){
    if(a.isInArea(points.get(i))){
       result ++;
    }
  }
  return result;
}



void init(){
   a = new Area(0, minDist, 50);
}


float angle = 0; 

boolean detect(){
  if(paused) return false;
  
  a.setAngle();
  a.stepDist();
  
  if(a.minD > maxDist){
    a.resetDist();
    if(angle > 2*PI) angle -= 2*PI;
  }
  
  if(countPoint(a) > 20) return true;
  return false;
}
