PolarSystem coordSystem = new PolarSystem();

class PolarSystem{
  
  float radius = 0.8;
  int subdivision = 20;
  
  PolarSystem(){}
    
  void draw(){
     center();
    
     noFill();
     strokeWeight(0.2);
     stroke(80);
     
     float dR = radius/subdivision;
     float dRpix = toPixel(dR);
     for(int i = 1; i <= subdivision; i++){
       circle(dR*i);
       line( dRpix*i/2 - 5, 0,   dRpix*i/2 + 5 ,0); 
       line(-dRpix*i/2 - 5, 0,  -dRpix*i/2 + 5 ,0);
       line(0,  dRpix*i/2 - 5, 0,  dRpix*i/2 + 5);
       line(0, -dRpix*i/2 - 5, 0, -dRpix*i/2 + 5);
     }
     resetMatrix();
     resetStroke();
  }
};
