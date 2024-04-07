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

void onIntercomConnected();
void onIntercomDisconnected();
void onIntercomRequest(Request&);
void onIntercomRequestReply(Request&);

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
	intercom.setConnectLostCallback(onIntercomDisconnected);
    intercom.setConnectionSuccessCallback(onIntercomConnected);
    intercom.setRequestCallback(onIntercomRequest);

	lidar.setHeading(180);
    lidar.setFOV(360);

	Console::info("OS") << "Boot finished" << Console::endl;
}

void onUpdate(){
    static long lastReq = 0;
    if(millis() - lastReq > 50){
        //intercom.sendRequest("lidar2main", 100, onIntercomRequestReply);
        //Console::println("*");
        lastReq = millis();
    }
}

void onIntercomConnected(){
//yay!
}

void onIntercomDisconnected(){
//huh!
}

void onIntercomRequestReply(Request& req){

}

void onIntercomRequest(Request& req){
    String command = req.getContent();

	if (command.startsWith("displayIntercom"))
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
    else if (command.startsWith("setRobotPosition"))
    {
        String argString = command.substring(command.indexOf("(") + 1, command.indexOf(")"));
        std::vector<String> args = CommandHandler::extractArguments(argString);
        if(args.size() == 3){
            float x = args[0].toFloat();
            float y = args[1].toFloat();
            float z = args[3].toFloat();

            if(x > 10 && x < 3000 && y > 10 && y < 2000){
                lidar.setPosition(x, y, z);
            }
        }
    }
}
