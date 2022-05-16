class ClusterEngine {
  ArrayList<PVector> centroids;
  int k = 50; //Number of clusters

  float variance = 0;
  float lastVariance = 999999999;

  ClusterEngine(int k_) {
    k = k_;
    centroids = new ArrayList<PVector>();
  }

  void reset() {
    centroids.clear();
    println("Reset brain at", millis());
    for(int i = 0; i < 10; i++){
      centroids.add(getRandom().pos);
    }
  }

  void compute() {
    variance = 0;
    int kill = -1;
    //Assign a cluster to each points
    for (Point p : Points) {
      float closestDist = p.pos.dist(centroids.get(p.cluster));
      
      for (int c = 0; c < centroids.size(); c++){
        if (p.pos.dist( centroids.get(c) ) < closestDist) p.cluster = c;
      }
    }

    //Move clusters
    for (PVector c : centroids) {
      PVector force = new PVector(0, 0);
      int count = 0;
      int minCount = 999999;
      
      for (Point p : Points) {
        if (centroids.get(p.cluster) == c) {
          force.add(p.pos.copy().sub(c));
          count++;
          variance += c.dist(p.pos)*c.dist(p.pos);
        }
      }
      if(count < 5){
        minCount = count; 
        kill = centroids.indexOf(c);
      }else{
        force.div(count*20);
        c.add(force); 
      } 
      translate(width/2, height/2);
      //stroke(255, random(255), random(255));
      stroke(0, 255, 255);
      //print(c.x, ":"); println(c.y);
      ellipse(c.x, c.y, 20, 20);
      resetMatrix();
    }
    if(variance < lastVariance && kill >= 0){
      centroids.remove(centroids.get(kill));
      for(Point p : Points){
        if(p.cluster == kill) p.cluster = 0; 
        else if(p.cluster > kill){
          p.cluster -= 1; 
        }
      }
      if(centroids.size() < 1)
        brain.reset();
      if(centroids.size() > 50)
        brain.reset();
    }else{
      centroids.add(getRandom().pos);
      lastVariance = variance;
    }
   
  }
 };
