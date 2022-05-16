


class Point{
  float _x, _y;
 
  Point(){
    _x = random(0,1);
    _y = random(0,1);
  }
  
  Point(float x, float y){
    _x = x;
    _y = y;
  }
  
  float GetX(){
    return _x;
  }

  float GetY(){
    return _y;
  }
  
  void draw(){
    //stroke(150,40,40);
    strokeWeight(5);
    point(toPixelX(_x), toPixelY(_y));

    //resetStroke();
  }
  
};
