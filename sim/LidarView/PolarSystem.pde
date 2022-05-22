class PolarSystem{
  
  float radius;
  int subdivision;
  
  PolarSystem(){
    radius = (width/2) - 50;
    subdivision = 20;
  }
    
  void draw(){
     pushMatrix();
    
     noFill();
     strokeWeight(1);
     stroke(180);
     
     float dR = radius/subdivision;
     float dRpix = dR/dScale;
     
     
     for(int i = 1; i <= subdivision; i++){
       circle(dR*i);
       pushMatrix();
       translate(dR*i,0);
       rotate(PI/4);
       text(int(dRpix*i), 0,0);
       popMatrix();
     }
     
     stroke(190);
     
     for(int i = 0; i < 18; i++){
       text(int(i*10), radius+20,0);
       rotate(-10*DEG_TO_RAD);
       line(0,0,0,radius);
     }
     for(int i = 18; i > 0; i--){
       text(int(-i*10), radius+20,0);
       rotate(-10*DEG_TO_RAD);
       line(0,0,0,radius);
     }
     popMatrix();
  }
};
