
class Lidar{
  float animation = 0;
  
  Lidar(){}
  
   
  void draw(){   
    pushMatrix();
    fill(0);
    stroke(0);
    strokeWeight(4);
    //line(5,7,10,3);
    //line(5,-7,10,-3);
     
    strokeWeight(1);
    //circle(10,0,4);
    circle(10);
    
    if(animate){
      strokeWeight(2);
      stroke(255);
      point(cos(animation)*9.5, sin(animation)*9.5);
      strokeWeight(0.2);
      stroke(255,0,0);
      line(cos(animation)*9, sin(animation)*9, cos(animation)*1000, sin(animation)*1000);
     
      animation += 0.4;
    }
    popMatrix();
  }
  
  
  
  

};
