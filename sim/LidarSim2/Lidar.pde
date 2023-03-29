ArrayList<Vertex> rays;

class Lidar extends Ray {
    
    Lidar (float r) {
        super(r);
        rays = new ArrayList<Vertex>();
    }

    void draw(){
        for(int i = 0; i<rays.size();i++) rays.get(i).draw();
    }
}
