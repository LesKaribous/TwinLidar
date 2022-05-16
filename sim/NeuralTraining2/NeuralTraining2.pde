import nn.*;

Network nn;        // Neural Network Object
Function function = new Function();
ArrayList<Point> points = new ArrayList<Point>();

PFont f;           // Font
int N = 250;
int count;         // Total training interations

float[][] inputs = new float[N][2];
float[][] target = new float[N][1];


void setup(){
  size(800,600);
  
  nn = new Network(2,30);
  f = createFont("Courier",12,true);
  
  points.clear();
  
  for (int i = 0; i < N; i++) {
    Point p = new Point();
    points.add(p);
    
    inputs[i][0] = p._x;
    inputs[i][1] = p._y;
  }
  
  for (int i = 0; i < N; i++) {
    Point p = points.get(i);
    float answer = 0;
    if (p._y > function.f(p._x)) answer = 1;
    target[i][0] = answer;
  }
}


void draw(){
  background(180);
  function.draw();
  repere.draw();
  
  int trainingIterationsPerFrame = 10;
  for (int i = 0; i < trainingIterationsPerFrame; i++) {
    // Pick a random training input
    int pick = int(random(inputs.length));
    // Grab that input
    float[] inp = (float[]) inputs[pick]; 

    // Train the net
    float result = nn.train(inp, target[pick][0]);
    count++;
  }
  
  for(int i = 0; i < N; i++){
    strokeWeight(5);
    stroke(0);
    float guess = nn.feedForward((inputs[i]));
    //float guess = target[i][0];

    //if (target[i][0] > 0) stroke(255,0,0);
    if (guess > 0.5) stroke(0,255,0);
    else              stroke(255,0,0);
      points.get(i).draw();
  }
  
  networkStatus();
}


void networkStatus() {
  resetMatrix();
  float mse = 0.0;

  textFont(f);
  fill(0);
  text("Your friendly neighborhood neural network solving the problem.",10,20);
  text("Total iterations: " + count,10,40);

  for (int i = 0; i < inputs.length; i++) {
    float[] inp = (float[]) inputs[i]; 
    float known = target[i][0];
    float result = nn.feedForward(inp);
    mse += (result - known)*(result - known);
  }

  float rmse = sqrt(mse/4.0);
  text("Root mean squared error: " + nf(rmse,1,5), 10,60);

}
