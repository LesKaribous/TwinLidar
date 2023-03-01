// TODO check cluster location on the map 

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
    for(int i = 0; i < brain.data.size(); i++){
      if(PVector.dist(brain.data.get(i).pos, origin) < 50) stability+=5;
    }
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

class ClusterEngine{
  ArrayList<Cluster> clusters;
  ArrayList<Point> data;

  ClusterEngine(int k){  
    clusters = new ArrayList<Cluster>();
    data = new ArrayList<Point>();    
    
    for(int i = 0; i < k; i++){
      clusters.add(new Cluster());
    }
  }
  
  void store(PVector dataPoint){
    data.add(new Point(dataPoint));
    if(data.size() > N){
      data.remove(0); 
    }
  }
  
  void store(Point dataPoint){
    data.add(dataPoint);
    if(data.size() > N){
      data.remove(0); 
    }
  }
  
 
  void compute(int n){
    NearScan scan = new NearScan();
    for(int i = 0; i < n; i++){
      for(int j = 0; j < data.size(); j++){
  
        scan.start(data.get(j).pos);

        for(int k = 0 ; k < clusters.size(); k++) 
          scan.run(clusters.get(k).origin, k);

        int index = scan.result();
        if(index != -1){
          clusters.get(index).add(data.get(j).pos);
          data.get(j).c = clusters.get(index).C;
        }
      }
      for(int j = 0; j < clusters.size(); j++){
        if(clusters.get(j).count > 0) clusters.get(j).compute();
      }
      //repelClusters();
    }
  }
  
  
  void draw(){
    pushMatrix();
    translate(lidar.origin.x, lidar.origin.y);
    for(int i = 0; i < data.size(); i++){
      strokeWeight(2);
      stroke(255,0,0);
      data.get(i).update();
      if(data.get(i).opacity < 52) data.remove(i);
      else data.get(i).draw();
      
    }
    
    for(int i = 0; i < clusters.size(); i++){
      clusters.get(i).draw();    
    }
    popMatrix();
  }
  
  
  
}
