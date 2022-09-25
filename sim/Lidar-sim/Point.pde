
class Point{
  PVector pos;
  int opacity;
  color c;
  
  Point(){
    pos = new PVector(random(width), random(height));
    c = color(255);
    opacity = 255;
  }
  
  Point(PVector p){
    pos = p.copy();
    c = color(255);
    opacity = 255;
  }
  
  Point(float x, float y){
    pos.x = x;
    pos.y = y;
    c = color(255);
    opacity = 255;
  }
  
  void update(){
    opacity -= 1;
    if(opacity < 0) opacity = 0;
  }
  
  void draw(){
    stroke(c, opacity);
    //stroke(c);
    point(pos.x, pos.y);
  }
  
}
