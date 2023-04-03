ArrayList<Reflector> reflectors;

Map mp = new Map(900,600);

Robot robot0, robot1;

ClusterEngine brain;

int N = 500;

void setup(){
    size(1400,900);
    frameRate(60);

    randomSeed(58);

    reflectors = new ArrayList<Reflector>();

    brain = new ClusterEngine(1);

    robot0 = new Robot(0, width/2, height/2);
    robot0.setMode("MOUSE");

    robot1 = new Robot(1, width/2, height/2);
    robot1.setMode("XML");

}

void draw(){
    background(52);
    mp.draw();

    robot0.update();
    robot0.displayLocation();

    robot1.update();

    robot0.display();
    robot1.display();


    if(frameCount % 30 == 0){
      thread("brainThread");
    }

    brain.draw();
}

void brainThread(){
  brain.compute(10);  
}

void keyPressed(){
  if(key == 'q'){
    exit();
  }
}
