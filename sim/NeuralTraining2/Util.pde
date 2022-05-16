
float toPixelX(float value){
  return map(value, 0, 1, 0, width);
}

float toPixelY(float value){
  return map(value, 0, 1, height, 0);
}

float toOrthoX(float value){
  return map(value, 0, width, 0, 1);
}

float toOrthoY(float value){
  return map(value, height, 0, 0, 1);
}

void resetStroke(){
    strokeWeight(1);
    stroke(0); 
}

void linePixel(float xa, float ya, float xb, float yb){
  line(toPixelX(xa), toPixelY(ya), toPixelX(xb), toPixelY(yb));
}
