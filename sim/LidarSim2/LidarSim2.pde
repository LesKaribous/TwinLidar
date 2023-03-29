ArrayList<Reflector> reflectors;

Map mp = new Map(900,600);

Robot robot;

ClusterEngine brain;

int N = 500;

void setup(){
    size(1400,900);
    frameRate(60);

    randomSeed(58);

    brain = new ClusterEngine(1);

    robot = new Robot(0, width/2, height/2);

    reflectors = new ArrayList<Reflector>();

    reflectors.add(new Reflector(50, 30, 50));
}

void draw(){
    rays.clear();
    background(52);
    mp.draw();

    robot.update();
    robot.displayLocation();

    brain.compute(10);

    robot.display();

    for (int i = 0; i < reflectors.size(); ++i) reflectors.get(i).display();

    brain.draw();

}

