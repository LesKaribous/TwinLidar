
class Ray{
  PVector origin;
  PVector vector;
  float range;
  boolean collision = false;
  
  Ray(float r){
    origin = new PVector();

    vector = new PVector(2000, 0);
    range = r;
  }

  void setOrigin(PVector o){
    origin.set(o);
  }
  
  void trace(){
    rays.add(new Vertex(origin.copy(), vector));
  }
  
  void update(int it){
    pushMatrix();

    // brain.data.clear();
    
    // // add noise to the simulation
    // for(int i = 0; i < noise; i++){
    //   brain.store(new Point());
    // }
    
    // define all reflectors as not collided
    for(int i = 0; i < reflectors.size(); i++){
     reflectors.get(i).collided = false;
    }
    
    sort();
    
    for(int n = 0; n < it; n++){
      vector.rotate(TWO_PI / it);
      vector.normalize().mult(range);

      for(int i = 0; i < reflectors.size(); i++){
        PVector reflPosRel = reflectors.get(i).pos.copy().sub(origin);

        if(reflPosRel.mag() > reflectors.get(i).diameter){ 
          float projX = reflPosRel.mag() * cos(reflPosRel.heading() - vector.heading());

          if(projX < 0 || projX > vector.mag()) projX = 0;

          PVector projPosRel = vector.copy().normalize().mult(projX);

          PVector dist = reflPosRel.copy().sub(projPosRel.copy());
          
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

// This loop update reflectors array in order to get the closest first
void sort(){
  ArrayList<Reflector> unsortedReflectors = reflectors ;
  ArrayList<Reflector> sortedReflectors = new ArrayList<Reflector>() ;
  
  while(unsortedReflectors.size() > 0){
    float min = 99999;
    Reflector buffer = new Reflector(0,0,0);
   
    for(int i = 0; i < unsortedReflectors.size(); i++){
      float dist = PVector.dist(unsortedReflectors.get(i).pos, robot.pose);
      if(dist < min){
        min = dist;
        buffer = unsortedReflectors.get(i);
      }
    }
    sortedReflectors.add(buffer);
    unsortedReflectors.remove(buffer);
  }
  
  reflectors = sortedReflectors;
}