
class Reflector{
  public PVector pos;
  public float diameter;
  
  public boolean collided = false;
  
  Reflector(float x, float y, float d){
    pos = new PVector(x, y);
    diameter = d;
  }
  
  void display(){
    if(!collided) fill(255);
    else fill(60,200,60);
    stroke(200);
    //ellipse(pos.x, pos.y, diameter, diameter);
    
    int w = 100;
    noFill();
    strokeWeight(1);
    stroke(255);
    ellipse(pos.x, pos.y, w, w);

  }
 
}
