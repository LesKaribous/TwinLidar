PolarSystem coordSystem = new PolarSystem();

class PolarSystem{
  float radius = maxDist;
  int subdivision = 20;
  
  PolarSystem(){}
    
  void draw(){
     center();
    
        
     float dR = radius/subdivision;
     int dRpix = (int)toPixel(dR);
     for(int i = 1; i <= subdivision-1; i++){
       strokeWeight(1);
       stroke(0);
       fill(0);
       text(int(dR*i), dRpix*i,0);
       noFill();  
       strokeWeight(0.2);
       stroke(80);
       circle(dR*i);
       line( dRpix*i/2 - 5, 0,   dRpix*i/2 + 5 ,0);
       line(-dRpix*i/2 - 5, 0,  -dRpix*i/2 + 5 ,0);
       line(0,  dRpix*i/2 - 5, 0,  dRpix*i/2 + 5);
       line(0, -dRpix*i/2 - 5, 0, -dRpix*i/2 + 5);
     }
     resetMatrix();
  }
};
