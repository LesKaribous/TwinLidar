

class Lidar extends Ray {
    
    Lidar (float r) {
        super(r);
    }

    void draw(){
        for(int i = 0; i<rays.size();i++) rays.get(i).draw();
        rays.clear();
    }
}
