
class Ray{
  PVector origin;
  PVector realOrigin;
  PVector vector;
  float range;
  boolean collision = false;
  
  Ray(float x, float y, float r){
    origin = new PVector(x,y);
    origin.sub(mp.w/2, mp.h/2);
    vector = new PVector(2000, 0);
    range = r;
  }
  
  void trace(){
   rays.add(new Vertex(origin.copy().add((width - mp.w)/2, (height - mp.h)/2), vector));
  }
  
  void update(int it){
    
    origin = new PVector(mouseX, mouseY);
    origin.sub( (width - mp.w)/2, (height - mp.h)/2);
    
    text(origin.x, 50,50);
    text(origin.y, 50,80);
    
    pushMatrix();
    translate((width - mp.w)/2, (height - mp.h)/2); // definition of the origin of the map at the top left corner
    
    noFill();
    strokeWeight(1);
    stroke(255);
    ellipse(origin.x, origin.y, 100,100); // plot the location of the robot 
    
    brain.data.clear();
    
    // add noise to the simulation
    for(int i = 0; i < noise; i++){
      brain.store(new Point());
    }
    
    // define all reflectors as not collided
    for(int i = 0; i < reflectors.size(); i++){
     reflectors.get(i).collided = false;
    }
    
    sort();
    
    for(int n = 0; n < it; n++){
      vector.rotate(TWO_PI / it);
      vector.normalize().mult(range*2);
        
      for(int i = 0; i < reflectors.size(); i++){
        PVector reflPos = reflectors.get(i).pos.copy();
        PVector reflPosRel = reflPos.copy().sub(origin);
        if(reflPosRel.mag() > reflectors.get(i).diameter){
          float projX = reflPosRel.mag() * cos(reflPosRel.heading() - vector.heading());
          if(projX < 0 || projX > vector.mag()) projX = 0;      
          PVector projPosRel = vector.copy().normalize().mult(projX);
          
          PVector dist = reflPos.copy().sub(projPosRel.copy().add(origin));
          
          float R = reflectors.get(i).diameter/2;
          if(dist.mag() <= R){
            vector.normalize().mult(projX - R * cos(asin(dist.mag()/R)));
            if(vector.mag() < range){
              reflectors.get(i).collided = true;
              
              brain.store(vector.copy());
            }
          } 
        }
      }
      trace();
    }
    popMatrix();
  }
}
