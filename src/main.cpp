#include "os/console.h"
#include "os/os.h"
#include "utils/commandHandler.h"

#include "services/lidar/lidar.h"
#include "services/pixel/pixel.h"
#include "services/intercom/intercom.h"

static OS& os = OS::instance();

static Lidar& lidar = Lidar::instance();
static Pixel& pixel = Pixel::instance();
static Intercom& intercom = Intercom::instance();

void onBoot(); //Execute once at boot
void onUpdate(); //Execute before robotProgram (idle loop)

void onIntercomRequest(Request&);

void setup(){
	Console::init();
    Console::setLevel(ConsoleLevel::INFO);

	os.setRountine(OS::BOOT, onBoot);				//Execute once						(setup)
	os.setRountine(OS::RUNNING, onUpdate);			//Execute during match				(loop)
}

void loop(){
	os.run();	//update the services and run the current routine
}

void onBoot(){
	os.attachService(&lidar);
	os.attachService(&pixel);
	os.attachService(&intercom);
    intercom.setRequestCallback(onIntercomRequest);

	Console::info("OS") << "Boot finished" << Console::endl;
}

void onUpdate(){
    /*
    static long lastReq = 0;
    if(millis() - lastReq > 1000){
        lastReq = millis();
        Console::println(String(lidar.getPosition()));
    }*/
}


void onIntercomRequest(Request& req){
    String command = req.getContent();

    if (command.startsWith("setRobotPosition"))
    {
        int openBracket = command.indexOf("(");
        int closedBracket = command.indexOf(")");
        if(openBracket == -1 || closedBracket == -1)return;

        String argString = command.substring(openBracket + 1, closedBracket);

        std::vector<String> args;
        int comma;
        
        comma = argString.indexOf(",");if(comma == -1) return;
        args.push_back(argString.substring(0, comma));
        argString = argString.substring(comma+1);

        comma = argString.indexOf(",");if(comma == -1) return;
        args.push_back(argString.substring(0, comma));
        argString = argString.substring(comma+1);

        args.push_back(argString);
        
        if(args.size() == 3){
            float x = args[0].toFloat();
            float y = args[1].toFloat();
            float z = args[2].toFloat();

            lidar.setPosition(x, y, z);

            req.reply("OK");
        }
        //req.reply("NOK");
    }else if (command.startsWith("checkObstacle"))
    {
        int openBracket = command.indexOf("(");
        int closedBracket = command.indexOf(")");
        if(openBracket == -1 || closedBracket == -1)return;
        
        String argString = command.substring(openBracket + 1, closedBracket);

        std::vector<String> args;
        int comma;
        
        comma = argString.indexOf(",");if(comma == -1) return;
        args.push_back(argString.substring(0, comma));
        argString = argString.substring(comma+1);

        args.push_back(argString);


        if(args.size() == 2){
            float angle = args[0].toInt();
            float distMax = args[1].toInt(); //550

            /*
            Console::print("a:");
            Console::println(angle);
            Console::print("d:");
            Console::println(distMax);
            /**/

            //Dist + deccel dist
            bool a = lidar.getDistance(angle) < distMax;
            bool b = lidar.getDistance(angle-10) < distMax;
            bool c = lidar.getDistance(angle+10) < distMax;
            bool d = lidar.getDistance(angle-20) < distMax -20;
            bool e = lidar.getDistance(angle+20) < distMax -20;
            bool f = lidar.getDistance(angle-30) < distMax -35;
            bool g = lidar.getDistance(angle+30) < distMax -35;
            bool h = lidar.getDistance(angle-40) < distMax -55;
            bool i = lidar.getDistance(angle+40) < distMax -55;

            constexpr int minPoint = 2;
            bool ca = lidar.getCount(angle) > minPoint;
            bool cb = lidar.getCount(angle-10) > minPoint;
            bool cc = lidar.getCount(angle+10) > minPoint;
            bool cd = lidar.getCount(angle-20) > minPoint;
            bool ce = lidar.getCount(angle+20) > minPoint;
            bool cf = lidar.getCount(angle-30) > minPoint;
            bool cg = lidar.getCount(angle+30) > minPoint;
            bool ch = lidar.getCount(angle-40) > minPoint;
            bool ci = lidar.getCount(angle+40) > minPoint;

            req.reply((a && ca) || (b && cb) || (c && cc) || (d && cd) || (e && ce) || (f && cf) || (g && cg) || (h && ch) || (i && ci));

        }else req.reply(0);
}else if (command.startsWith("getDistance"))
    {
        int openBracket = command.indexOf("(");
        int closedBracket = command.indexOf(")");
        if(openBracket == -1 || closedBracket == -1)return;
        
        int angle = command.substring(openBracket + 1, closedBracket).toInt();
        req.reply(lidar.getDistance(angle));
    }
	else if (command.startsWith("displayIntercom"))
    {
        pixel.setMode(Pixel::INTERCOM);
        Console::println("displayIntercom");
        req.reply("OK");
    }
    else if (command.startsWith("displayLidar"))
    {
        pixel.setMode(Pixel::LIDAR);
        Console::println("displayLidar");
        req.reply("OK");
    }
    
}
