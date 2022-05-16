
void center(){
  translate(width/2, height/2); 
}

float toPixel(float value){
  return map(value, 0.0, maxDist, 0.0, width/2.0);
}

PVector toPixel(PVector value){
  return new PVector(toPixel(value.x), toPixel(value.y));
}

float toUnit(float value){
  return map(value, 0.0, width/2, 0.0, maxDist);
}

void circle(float r){
  r = toPixel(r)*2;
  ellipse(0,0,r,r);
}

void circlePx(float r){
  ellipse(0,0,r*2,r*2);
}

void circle(float x, float y, float r){
  ellipse(x,y,r*2,r*2);
}

void circlePx(float x, float y, float r){
  ellipse(x,y,r*2,r*2);
}

void pointPx(PVector pos){
  point(pos.x, pos.y);
}

void point(PVector pos){
  pos = toPixel(pos);
  point(pos.x, pos.y+(height/2-width/2));
}

void line(PVector a, PVector b){
  a = toPixel(a);
  b = toPixel(b);
  line(a.x, a.y, b.x, b.y);
}

void resetFill(){
  fill(255);
}
