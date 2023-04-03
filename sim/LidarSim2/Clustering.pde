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
        }
    }
  
  
    void draw(){
        pushMatrix();
        translate(robot0.pose.x, robot0.pose.y); // TODO use robot id 

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