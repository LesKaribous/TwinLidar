
float toPixelX(float value){
  return map(value, -1, 1, 0, width);
}

float toPixelY(float value){
  return map(value, -1, 1, height, 0);
}

float toOrthoX(float value){
  return map(value, 0, width, -1, 1);
}

float toOrthoY(float value){
  return map(value, height, 0, -1, 1);
}

void resetStroke(){
    strokeWeight(1);
    stroke(0); 
}
