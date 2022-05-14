import java.lang.Math;

class NeuralNetwork{
  int inputs = 0,
      hiddens = 0,
      outputs = 0;
      
  float learnRate = 0.1;
     
  float mError = 0;
  float iteration = 0;
     
  Matrix wih = new Matrix(hiddens, inputs);
  Matrix who = new Matrix(outputs, hiddens);
     
   NeuralNetwork(int _inputs, int _hiddens, int _outputs, float lr){
     inputs = _inputs;
     hiddens = _hiddens;
     outputs = _outputs;
     
     wih = new Matrix(hiddens, inputs);
     who = new Matrix(outputs, hiddens);
  
     learnRate = lr;
     wih.randomize();
     who.randomize();
   }

   NeuralNetwork(NeuralNetwork cpy){
     inputs = cpy.inputs;
     hiddens = cpy.hiddens;
     outputs = cpy.outputs;
     
     wih = cpy.wih.copy();
     who = cpy.who.copy();
     
     learnRate = cpy.learnRate;
   }
  
  
  Matrix activate(Matrix m){
    Matrix newM = m.copy();
    for(int i = 0; i < newM.row; i++){
      for(int j = 0; j < newM.col; j++) newM.matrix[i][j] = sigmoid(newM.matrix[i][j]);
    }
    return newM;
  }
  
  Matrix derivative(Matrix m){
    Matrix newM = m.copy();
    for(int i = 0; i < newM.row; i++){
      for(int j = 0; j < newM.col; j++) newM.matrix[i][j] = dSigmoid(newM.matrix[i][j]);
    }
    return newM;
  }
  
  float sigmoid(float x) {
    return x;
    //return 1 / (1 + pow(2.718281, -x));
    //return (float)Math.tanh(x);
    //if (x < -1) return -1;
    //else return x;
  }
  
  // This is the Sigmoid derivative!
  float dSigmoid(float x){
    return 1;
    //return x * (1 - x);
    //return 1 / (pow((float)Math.cosh(x), 2));
    //if (x < -1) return 0;
    //else return 1;
    //if (x > 0) return 1;
    //else return -1;
  }
  
  float mutate(float x) {
    if (random(1) < 0.1) {
      float offset = randomGaussian() * 0.5;
      float newx = x + offset;
      return newx;
    } else {
      return x;
    }
  }


  NeuralNetwork copy(){
    return new NeuralNetwork(this); 
  }
  
  void mutate(){
    for (var i = 0; i < wih.row; i++) {
      for (var j = 0; j < wih.col; j++) {
        wih.matrix[i][j] = mutate(wih.matrix[i][j]);
      }
    }
    
    for (var i = 0; i < who.row; i++) {
      for (var j = 0; j < who.col; j++) {
        who.matrix[i][j] = mutate(who.matrix[i][j]);
      }
    }
  }


  float[] feedForward(float[] tInputs){
    Matrix _inputs = fromArray(tInputs);
    
    Matrix _hidden = dot(wih, _inputs);
    _hidden = activate(_hidden);
    
    Matrix _output = dot(who, _hidden);
    _output = activate(_output);
    
    return toArray(_output);
  }
  
  
  void train(float[] tInputs, float[] tOutput){
    iteration++;
    Matrix _target = fromArray(tOutput);
    Matrix _inputs = fromArray(tInputs);
    
    Matrix _hidden_outputs = dot(wih, _inputs);
    _hidden_outputs = activate(_hidden_outputs);
    
    Matrix _outputs = dot(who, _hidden_outputs);
    _outputs = activate(_outputs);
    
    Matrix _errors = _target.copy();
    _errors.sub(_outputs);
    
    float[] error =_errors.toArray();
    for(float e : error) mError += e;
    
    Matrix whoT = who.transpose();
    Matrix hiddenError = dot(whoT, _errors);
    
    Matrix gradient_output = derivative(_outputs);
    
    gradient_output.mult(_errors);
    gradient_output.mult(learnRate);
    
    Matrix gradient_hidden = derivative(_hidden_outputs);
    
    gradient_hidden.mult(hiddenError);
    gradient_hidden.mult(learnRate);
    
    Matrix hidden_outputs_T = _hidden_outputs.transpose();
    Matrix deltaW_output = dot(gradient_output, hidden_outputs_T);
    who.add(deltaW_output);
    
    
    Matrix inputs_T = _inputs.transpose();
    Matrix deltaW_hidden = dot(gradient_hidden, inputs_T);
    wih.add(deltaW_hidden);
  }
}
