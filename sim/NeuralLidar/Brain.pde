
class NeuralNetwork{
  int inputs = 0,
      hiddens = 0,
      outputs = 0;
      
  float learnRate = 0.01;
     
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
    for(int i = 0; i < newM.col; i++){
      for(int j = 0; j < newM.row; j++) newM.matrix[i][j] = dSigmoid(newM.matrix[i][j]);
    }
    return newM;
  }
  
  float sigmoid(float sum) {
    float y = 1 / (1 + pow(2.718281828459045, -sum));
    return y;
  }
  
  // This is the Sigmoid derivative!
  float dSigmoid(float x){
    return x * (1 - x);
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
    for(float[] row : wih.matrix){
      for(float e : row) e = mutate(e);
    }
    
    for(float[] row : who.matrix){
      for(float e : row) e = mutate(e);
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
    Matrix _target = fromArray(tOutput);
    Matrix _inputs = fromArray(tInputs);
    
    Matrix _hidden_outputs = dot(wih, _inputs);
    _hidden_outputs = activate(_hidden_outputs);
    
    Matrix _outputs = dot(who, _hidden_outputs);
    _outputs = activate(_outputs);
    
    Matrix _errors = _target.copy();
    _errors.sub(_outputs);
    
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
