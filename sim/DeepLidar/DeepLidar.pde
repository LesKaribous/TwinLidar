
int N = 800;
float maxDist = 1000.0;
float minDist = 200.0;

ArrayList<Point> points = new ArrayList<Point>();
ArrayList<ArrayList<Point>> validData = new ArrayList<ArrayList<Point>>();
ArrayList<ArrayList<Point>> badData = new ArrayList<ArrayList<Point>>();

void setup(){
  size(1000,1000);
  frameRate(30);
  serialBegin();
  
  //nn = new Network(2,30);
  f = createFont("Courier",12,true);
}



void draw(){
  background(200);
  drawPoints();
  drawUI();
}
