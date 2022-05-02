
int N = 2000;

void setup(){
  size(1280,800);
  //frameRate(24);
  createGUI();
  
  serialBegin("COM4");
  cp5.get(Textarea.class, "Console").setVisible(false);
}



void draw(){
  background(200);
  coordSystem.draw();
  
  drawPoints();
  //lidar.draw();
 

}
