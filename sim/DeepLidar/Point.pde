
void drawPoints(){
  if(points.size() > 0);
  for(int i = points.size()-2; i >= 0; i--){
     points.get(i).draw();
     //points.get(i).drawCartesian();
     //if(millis() - points.get(i).birth > 800) points.remove(points.get(i));
  }
}

ArrayList<Point> selectPoint(){

  if(points.size() == 0) return new ArrayList<Point>();
  ArrayList<Point> result = new ArrayList<Point>();
      
  for(int i=points.size() - 1; i >= 0; i--){
    if(points.get(i).underMouse){
       result.add(points.get(i));
    }
  }
  return result;
}

int countPoint(){
  int result = 0;
  for(int i=points.size() - 1; i >= 0; i--){
    if(points.get(i).underMouse){
       result ++;
    }
  }
  return result;
}


void savePoint(float dist, float angle,  float intensity){
 
  
  if(dist < maxDist && dist >= minDist){
    println(maxDist);
    Point p = new Point(dist, angle/100.0*DEG_TO_RAD, intensity);
    points.add(p);
  }
}


class Point{
  float _distance, _theta;
  float _intensity;
  long birth;
  
  boolean underMouse = false;
  color col;
  
  int clusterID;
  
  Point(){
    _intensity = 100;
    _distance = random(0,maxDist);
    _theta = random(0,2*PI);
    
    birth = millis();
    clusterID = -1;
    col = color(0,255,0);
  }
  
  Point(float distance, float theta, float intensity){
    _intensity = intensity;
    _distance = distance;
    _theta = theta;
    birth = millis();
    clusterID = -1;
    col = color(255,0,0);
  }
  
  void draw(){
    strokeWeight(2);
    stroke(col);
    
    center();
    rotate(_theta);
    point(toPixel(_distance),0);
    resetMatrix();
  }
  
  void drawCartesian(){

    PVector pos = toPVector();
    PVector polarMouse = new PVector(mouseX, mouseY);
    polarMouse.sub(width/2, height/2);
    if(pos.dist(polarMouse) <= mouseRadius){
      underMouse = true;
      stroke(0,255,0);
    }else{
      underMouse = false;
      if(clusterID == -1) stroke(255,0,0);
      else stroke(col);
    }
    

    strokeWeight(2);
    center();
    
    point(pos.x,pos.y);
    resetMatrix();
  }
  
  void debug(){
    println("polar coordinate : [" + _theta + "°, " + _distance + " u]"); 
  }
  
  PVector toPVector(){
    float pixDist = toPixel(_distance);
     return new PVector((pixDist* cos(_theta)), (pixDist*sin(_theta)));
  }
  
};
