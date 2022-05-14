

class NearScan{
  float dist = 999999; 
  int index = -1;
  PVector origin;
  
  NearScan(){
    dist = 999999; 
    index = -1;
  }
  
  void start(PVector p){
    dist = 999999; 
    index = -1;
    origin = p; 
  }
  
  void run(PVector pos, int i){

    if(origin.dist(pos) < dist){ 
      dist = origin.dist(pos);
      index = i;
    }
  }
  
  int result(){
    return index;
  }
}
