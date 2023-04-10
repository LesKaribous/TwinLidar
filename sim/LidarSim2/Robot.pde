XML xml;

class Robot {
    int id;
    PVector pose;
    Lidar lidar;

    ArrayList<Point> trajectory;

    String mode;


    Robot (int _id, float x, float y) {
        id = _id;
        pose = new PVector(x,y);
        lidar = new Lidar(1000);
        reflectors.add(new Reflector(x, y, 50));

        trajectory = new ArrayList<Point>();

        xml = loadXML("trajectories.xml");

        XML[] children = xml.getChildren("ours");

        for (int i = 0; i < children.length; i++) {
            XML[] robot = children[i].getChildren("robot");
            for(int j = 0; j < robot.length;j++){
                int idxml = robot[j].getInt("id");
                println("id : " + idxml);

                if(id == idxml){
                    XML[] point = robot[j].getChildren("point");
                    for(int k = 0; k < point.length; k++){
                        trajectory.add(new Point(point[k].getInt("x"), point[k].getInt("y")));
                    }
                }
            }
            
        }

        println("Robot set up done !");
    }

    // MOUSE | XML
    void setMode(String m){
        mode = m;
    }

    void updatePose(){
        if(mode == "MOUSE"){
            pose.set(mouseX, mouseY);
            pose.sub( (width - mp.w)/2, (height - mp.h)/2);
        }
        else if (mode == "XML") {
            pose.set(trajectory.get(0).pos.x, trajectory.get(0).pos.y);
        }

        reflectors.get(id).pos = pose.copy();
    }

    void update(){
        updatePose();

        lidar.setOrigin(pose);
        lidar.update(300);
    }

    void display(){
        pushMatrix();
        if(id != 0){
            reflectors.get(id).display();
        }

        translate((width - mp.w)/2, (height - mp.h)/2); // definition of the origin of the map at the top left corner
        
        noFill();
        strokeWeight(1);
        stroke(255);
        ellipse(pose.x, pose.y, 100,100); // plot the location of the 
        
        if(id == 0) {
            println("id print lidar : " + id);
            lidar.draw();}

        popMatrix();
    }

    void displayLocation(){
        text(pose.x, 50,50);
        text(pose.y, 50,80);
    }

}
