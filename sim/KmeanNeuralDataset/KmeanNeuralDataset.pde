
int N = 1000;
int maxDist = 1000;
int minDist = 200;

ArrayList<Point> points = new ArrayList<Point>();
ArrayList<ArrayList<Point>> validData = new ArrayList<ArrayList<Point>>();
ArrayList<ArrayList<Point>> badData = new ArrayList<ArrayList<Point>>();

KMean clustering = new KMean(5);

void setup(){
  size(1000,1000);
  frameRate(30);
  serialBegin();
  init();
}



void draw(){
  background(200);
  drawPoints();
  
  a.draw();
  
  if(detect()){
    paused = true;
    println("Beacon detected !"); 
  }
  drawUI();
}
