class Matrix{
 int row = 0, col = 0;
 
 float[][] matrix;
 
 
  Matrix(int _row, int _col){
    row = _row;
    col = _col;
    
    matrix = new float[row][col];
    
    for (int i = 0; i < row; i++) {
      matrix[i] = new float[col];
      for (int j = 0; j < col; j++) {
        matrix[i][j] = 0;
      }
    }
  }
  
  void randomize(){
    for (var i = 0; i < row; i++) {
      for (var j = 0; j < col; j++) {
        matrix[i][j] = randomGaussian();
      }
    }
  }
  
  float[] toArray(){
    float[]arr = new float[row*col];
    for (var i = 0; i < row; i++) {
      for (var j = 0; j < col; j++) {
        arr[i*col + j] = matrix[i][j];
      }
    }
    return arr;
  }
  
  Matrix transpose(){
    var result = new Matrix(col, row);
    for (var i = 0; i < col; i++) {
      for (var j = 0; j < row; j++) {
        result.matrix[i][j] = matrix[j][i];
      }
    }
    return result;
  }
  
  Matrix copy() {
    var result = new Matrix(row, col);
    for (var i = 0; i < result.row; i++) {
      for (var j = 0; j < result.col; j++) {
        result.matrix[i][j] = matrix[i][j];
      }
    }
    return result;
  }
  
  void add(Matrix other) { 
    for (var i = 0; i < row; i++) {
      for (var j = 0; j < col; j++) {
        this.matrix[i][j] += other.matrix[i][j]; 
      }
    }
  }
  
  void add(float other){
    for (var i = 0; i < row; i++) {
      for (var j = 0; j < col; j++) {
        this.matrix[i][j] += other;
      }
    } 
  }
  
  void mult(Matrix other) { 
    for (var i = 0; i < row; i++) {
      for (var j = 0; j < col; j++) {
        this.matrix[i][j] *= other.matrix[i][j]; 
      }
    }
  }
  
  void mult(float other){
    for (var i = 0; i < row; i++) {
      for (var j = 0; j < col; j++) {
        this.matrix[i][j] *= other;
      }
    } 
  }
  
  void sub(Matrix other) { 
    for (var i = 0; i < row; i++) {
      for (var j = 0; j < col; j++) {
        this.matrix[i][j] -= other.matrix[i][j]; 
      }
    }
  }
  
  void sub(float other){
    for (var i = 0; i < row; i++) {
      for (var j = 0; j < col; j++) {
        this.matrix[i][j] -= other;
      }
    } 
  }
}



// Turn a 1 dimensional array into a matrix
Matrix fromArray(float[] array) {
  Matrix m = new Matrix(array.length, 1);
  for (var i = 0; i < array.length; i++) {
    m.matrix[i][0] = array[i];
  }
  return m;
}

// Turn a 1 dimensional array into a matrix
float[] toArray(Matrix mat) {
  float[] result = new float[mat.row*mat.col];
  for (var i = 0; i < mat.row; i++) {
    for (var j = 0; j < mat.col; j++) {
      result[i*mat.col + j] = mat.matrix[i][j];
    }
  } 
  return result;
}





Matrix dot(Matrix a, Matrix b){
  if (a.col != b.row) {
    print("Incompatible matrix sizes : ", a.col);
    println(", ", b.row);
    return a;
  }
  // Make a new matrix
  var result = new Matrix(a.row, b.col);
  for (var i = 0; i < a.row; i++) {
    for (var j = 0; j < b.col; j++) {
      // Sum all the rows of A times columns of B
      var sum = 0;
      for (var k = 0; k < a.col; k++) {
        sum += a.matrix[i][k] * b.matrix[k][j];
      }
      // New value
      result.matrix[i][j] = sum;
    }
  }
  return result;
}
