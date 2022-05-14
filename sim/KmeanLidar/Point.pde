ArrayList<Point> Points = new ArrayList<Point>();

void drawPoints(){
  if(Points.size() > 0);
  for(Point p : Points){
     p.draw();
  }
}

Point getRandom(){
  int random = int( random( Points.size() ) );
  if(random <= 0) random = 0;
  return Points.get( random );
}

void randomize(){
  for(int i=0; i < 100; i++){
    Points.add(new Point()); 
  }
}

class Point{
  PVector pos;
  color c;
  int opacity;
  int cluster = 0;
  
  Point(){
    pos = new PVector();
    pos.x = random(-1,1);
    pos.y = random(-1,1);
    c = color(255,0,0);
    opacity = 255;
  }
  
  Point(float x, float y){
    pos = new PVector();
    pos.x = x;
    pos.y = y;
    c = color(255,0,0);
    opacity = 255;
  }
  
  Point(PVector origin){
    pos = new PVector();
    pos.x = origin.x;
    pos.y = origin.y;
    c = color(255,0,0);
    opacity = 255;
  }
  
  void update(){
    opacity -= 5;
    if(opacity < 0) opacity = 0;
  }
  
  void draw(){
    translate(width/2, height/2);
    strokeWeight(2);
    stroke(c, opacity);
    point(pos.x,pos.y);
    //line(0,0,pos.x,pos.y);
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
    point(_distance,0);
    strokeWeight(4);
    
    stroke(0);
    point(0,0); 
    resetStroke();
    resetMatrix();
  }
  
  void debug(){
    println("polar coordinate : [" + _theta + "°, " + _distance + " u]"); 
  }
  
  Point toPoint(){
     return new Point((_distance* cos(_theta)), (_distance*sin(_theta)));
  }
  
};
