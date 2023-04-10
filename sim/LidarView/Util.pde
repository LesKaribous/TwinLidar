
float dScale = 0.2;
float aScale = DEG_TO_RAD;

void center(){
  translate(width/2, height/2); 
}

void noCenter(){
  translate(-width/2, -height/2); 
}

void circle(float r){
  r = r*2;
  ellipse(0,0,r,r);
}
