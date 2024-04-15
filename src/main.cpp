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

void onUpdate(){/*
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
        
        int angle = command.substring(openBracket + 1, closedBracket).toInt();

        bool a = lidar.getDistance(angle) < 420 && lidar.getDistance(angle) > 200;
        bool b = lidar.getDistance(angle-10) < 400 && lidar.getDistance(angle-10) > 200;
        bool c = lidar.getDistance(angle+10) < 400 && lidar.getDistance(angle+10) > 200;
        bool d = lidar.getDistance(angle-30) < 380 && lidar.getDistance(angle-20) > 200;
        bool e = lidar.getDistance(angle+30) < 380 && lidar.getDistance(angle+20) > 200;

        req.reply(a || b || c || d || e);
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
