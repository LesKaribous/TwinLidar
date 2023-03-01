
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

    noFill();
    strokeWeight(1);
    stroke(255);
    ellipse(pos.x + (width - mp.w)/2, pos.y + (height - mp.h)/2, diameter, diameter);

  }
 
}
