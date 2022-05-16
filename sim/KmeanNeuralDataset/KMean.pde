

class KMean{
  ArrayList<Cluster> clusters = new ArrayList<Cluster>();
  int variance = 0;
  
  int ClusterID = 0;
  
  KMean(){
    clusters = new ArrayList<Cluster>();
    variance = 0;
  }
  
  KMean(int k){
    clusters = new ArrayList<Cluster>();
    for(int i = 0; i < k; i++) clusters.add(new Cluster());
    variance = 0;
  }
  
  Cluster getByID(int i){
     for(int k = 0; k < clusters.size(); k++){
       if(clusters.get(k).id == i ) return clusters.get(i);
     }
     return clusters.get(0);
  }
  
  
  void draw(){
    center();
    for (int j = 0; j < clusters.size(); j++){
      clusters.get(j).draw();
    }
  }
  
  
  class Cluster{
    PVector centroid; 
    PVector dCentroid; 
    int id;
    
    color col = (int) random(#000000, #AAAAAA);
    int dispersion = 0;
    int count = 0;
    
    Cluster(){
      id = ClusterID++;
      if(ClusterID > 500) ClusterID = 0;
      
      Point t = new Point();
      centroid = t.toPVector();
      println(centroid);
      reset();
    }
    
    void add(PVector p) {
      p.sub(centroid);
      dispersion+= p.mag();
      dCentroid.add(p); 
      count++;
    }
    
    void transform() {
      if(count > 0){
        centroid.add(dCentroid.div(count).mult(0.1));
      }
    }
    
    void reset(){
      dCentroid = new PVector(0,0);
      dispersion = 0;
      count = 0;
    }
    
    boolean isEmpty(){
      return (count <= 0);
    }
    
    int variance(){
      return (dispersion*dispersion)/count; 
    }
    
    int radius(){
      return 20;
    }
    
    void draw(){
      stroke(col);
      noFill();
      int r = radius();
      translate(centroid.x, centroid.y);
      ellipse(0, 0, r, r);
      line(0,-r/10,0,r/10);
      line(-r/10,0,r/10,0);
      line(0,0,dCentroid.x, dCentroid.y);
    }
  }

  void compute(){
    if(points.size() == 0) return;
    
    boolean pause = paused;
    paused = true;

    //Assign points
    for (int i = 0; i < points.size(); i++) {
      Point p = points.get(i);
      PVector pos = p.toPVector();
      
      float closestDist = 999999;
      if(p.clusterID >= 0)
        closestDist = pos.dist(getByID(p.clusterID).centroid);
      
      for (int j = 0; j < clusters.size(); j++){
        Cluster c = clusters.get(j);
        if (pos.dist( clusters.get(j).centroid ) < closestDist){
          p.clusterID = c.id;
          p.col = c.col;
        }
      }
    }
    
    //Transform clusters and analyse variance
    for (int i = 0; i < clusters.size(); i++){
      Cluster c = clusters.get(i);
      for (int j = points.size()-1; j >=0 ; j--){
        if(points.get(j).clusterID == c.id)
          c.add(points.get(j).toPVector());
      }
      
      c.transform();
      //println(clusters.get(j).variance());
      c.reset();
    }
    paused = pause;
  }

  
}
