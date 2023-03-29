
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


    noFill();
    strokeWeight(1);
    stroke(255);
    ellipse(pos.x + (width - mp.w)/2, pos.y + (height - mp.h)/2, diameter, diameter);
  }
 
}

void mousePressed(){
    println("[Event] : Mouse pressed !");
    
    if(mousePressed && mouseButton == LEFT ){
      reflectors.add(new Reflector(mouseX - (width - mp.w)/2 , mouseY - (height - mp.h)/2, 50));
    }else if(mousePressed && mouseButton == RIGHT && reflectors.size() > 0){
      
      NearScan scan = new NearScan();
      scan.start(new PVector(mouseX, mouseY));
      for(int k = 0; k < reflectors.size(); k++) scan.run(reflectors.get(k).pos, k); 
        
      reflectors.remove(scan.result());
    }
    
    print("[Info] : "); 
    print(reflectors.size()); 
    println(" in scene with ", brain.data.size(), " points");
    
    background(52);
  
}
