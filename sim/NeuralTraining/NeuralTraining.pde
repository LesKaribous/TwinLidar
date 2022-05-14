
NeuralNetwork nn;
Function function = new Function();


ArrayList<Point> points = new ArrayList<Point>();

int N = 500;

float[][] inputs = new float[N][2];
float[][] target = new float[N][1];


void setup(){
  size(800,600);
  
  nn = new NeuralNetwork(2,4,1,0.001);
  
  
  points.clear();
  
  for (int i = 0; i < N; i++) {
    Point p = new Point();
    points.add(p);
    
    inputs[i][0] = p._x;
    inputs[i][1] = p._y;
  }
  
  for (int i = 0; i < N; i++) {
    Point p = points.get(i);
    float answer = 1;
    if (p._y < function.f(p._x)) answer = -1;
    target[i][0] = answer;
  }
}


void draw(){
  background(52);
  function.draw();
  repere.draw();
  for(int i = 0; i < N; i++)
    nn.train(inputs[i], target[i]);
  
  float convergence = -(nn.mError / nn.iteration);
  print(convergence); println(": ", nn.learnRate);
  
  for(int i = 0; i < N; i++){
    strokeWeight(5);
    stroke(0);
    float[] guess = nn.feedForward(inputs[i]);

    //if (target[i][0] > 0) stroke(255,0,0);
    if (guess[0] > 0) stroke(255,0,0);
    else              stroke(0,255,0);
      points.get(i).draw();
  }
}
