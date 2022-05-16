import nn.*;
Network nn;        // Neural Network Object

float[][] inputs = new float[N][2];
float[][] target = new float[N][1];

int count;


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
