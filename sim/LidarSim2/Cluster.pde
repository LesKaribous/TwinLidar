class Cluster{
  PVector origin;
  PVector force;
  int count;
  color C;
  int w;
  
    Cluster(){
        origin = new PVector(random(width), random(height));
        C = color(random(255),random(255),random(255));
        count = 0;
        force = new PVector(0,0);
        w = 20;  
    }

    void add(PVector p){
        force.add(p);
        count++;
    }
    
    void compute(){
        float stability = 1;
        for(int i = 0; i < brain.data.size(); i++)
            if(PVector.dist(brain.data.get(i).pos, origin) < 50) stability+=5;
        
        force.div(count);
        force.sub(origin);
        origin.add(force.div(stability));
        
        force = new PVector(0,0);
        count = 0;
    }
    
    void draw(){
        noFill();
        stroke(C);

        ellipse(origin.x, origin.y, w,w);
    }
    
}
