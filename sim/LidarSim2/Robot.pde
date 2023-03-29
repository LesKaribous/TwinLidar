XML xml;

class Robot {
    int id;
    PVector pose;
    Lidar lidar;

    Robot (int id, float x, float y) {
        id = id;
        pose = new PVector(x,y);
        lidar = new Lidar(1000);
    }

    void updatePose(){
        pose.set(mouseX, mouseY);

        pose.sub( (width - mp.w)/2, (height - mp.h)/2);
    }

    void update(){
        updatePose();

        lidar.setOrigin(pose);
        lidar.update(300);
    }

    void display(){
        pushMatrix();
        translate((width - mp.w)/2, (height - mp.h)/2); // definition of the origin of the map at the top left corner
        
        noFill();
        strokeWeight(1);
        stroke(255);
        ellipse(pose.x, pose.y, 100,100); // plot the location of the 

        lidar.draw();
        popMatrix();
    }

    void displayLocation(){
        text(pose.x, 50,50);
        text(pose.y, 50,80);
    }

}
