
float dScale = 0.25;
float aScale = -DEG_TO_RAD/100;

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
