Ortho repere = new Ortho(0,0);

class Ortho{
  float _x,_y;
  
  Ortho(float x, float y){
    _x = x;
    _y = y;
  }
  
  void draw(){
    float ox = toPixelX(_x);
    float oy = toPixelY(_y);
    
    strokeWeight(5);
    point(ox, oy);
    
    strokeWeight(1);
    line(ox, toPixelY(-2), ox, toPixelY(2));
    line(toPixelX(-2), oy, toPixelX(2), oy);
    
    float incX = width/20;
    float incY = -height/20;
    for(int i = 0; i < 10; i++){
      line(ox+i*incX, oy+5, ox+i*incX, oy-5) ;
      line(ox+5, oy+i*incY, ox-5, oy+i*incY) ;
    }
    /*
    for(int i = 0; i < 10; i++){
      line(ox-i*incX, oy+5, ox-i*incX, oy-5) ;
      line(ox+5, oy-i*incY, ox-5, oy-i*incY) ;
    }
    */
  }
  
};
