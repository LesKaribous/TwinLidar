

class UI{
  
  PFont f;           // Font
  boolean paused = false;
  
  UI(){
   f = createFont("Courier",12,true); 
  }
  
  void draw(){
    pushMatrix();
    noCenter();
    stroke(0);
    noFill();
    textFont(f);
   
    text("There is " + Points.size() + " in the buffer", width-200, 20);
    text("Receiving " + serialFreq + " pt/s", width-200, 40);
    popMatrix();
  }
}
