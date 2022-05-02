import controlP5.*;                  // Import the CP5 library
import processing.serial.*;          // Import the serial library

Serial myPort;                       // Create the serial port object
ControlP5 cp5;                       // Create the CP5 object

// Console
Textarea consoleArea;
Println console;
// Creation of the lists
ScrollableList serialList;
// Creation of the buttons
Button serialBegin;
Button serialStop;
Button serialRefresh;
// State of the buttons
boolean clicSerialBegin = false ;
boolean clicSerialStop = false ;
boolean clicSerialRefresh = false ;

// GUI Visibility
boolean GUIVisible = true;

void createGUI()
{
  //----------------------------------------------------
  // Create the GUI ControlP5 instance
  cp5 = new ControlP5(this);

  //---------------------TAB---------------------
  cp5.getTab("default")
     .activateEvent(true)
     .setLabel("Liaison Serie")
     .setId(1)
     ;
  //---------------------------------------------
  //--------------TAB GLOBAL --------------------------
  // Creation of the console
  consoleArea = cp5.addTextarea("Console")
    .setPosition(5, height-125)
    .setSize(width-10,120)
    .setLineHeight(14)
    .setColor(color(255))
    .setColorBackground(color(0,44,91,240))
    .moveTo("global")
    ;
  //--------------TAB 1 (default)--------------------------
  // List of the serial port
  serialList = cp5.addScrollableList("dropdown")
     .setCaptionLabel("Liste des liaisons serie")
     .setPosition(20, 20)
     .setSize(170, 800)
     .setBarHeight(20)
     .setItemHeight(20)
     .addItems(Serial.list())
     .setOpen(false)
     .moveTo("default")
     ;
  // create a new button with name 'serialBegin'
  serialRefresh = cp5.addButton("serialRefresh")
     .setCaptionLabel("R")
     .setPosition(20,50)
     .setSize(20,20)
     .moveTo("default")
     ;
  // create a new button with name 'serialBegin'
  serialBegin = cp5.addButton("serialBegin")
     .setCaptionLabel("Connection")
     .setPosition(60,50)
     .setSize(70,20)
     .moveTo("default")
     ;
  // create a new button with name 'serialStop'
  serialStop = cp5.addButton("serialStop")
    .setCaptionLabel("Stop")
    .setPosition(150,50)
    .setSize(40,20)
    .moveTo("default")
    ;

   //console = cp5.addConsole(consoleArea);

   println("Bievenue dans l'interface LiDar");
   println("Appuyez sur 'h' pour faire apparaitre l'aide");
   printArray(Serial.list());

   //----------------------------------------------------
   // Bring the dropdown list for serial to the front
   serialList.bringToFront();
   //----------------------------------------------------
}

void keyPressed()
{
  if ( key == 'v' ) GUIVisible = !GUIVisible;
  if ( key == 'h' )
  {
    println("Help for the beacon interface");
    println("'h' - Help");
    println("'v' - Visibility of the GUI");
  }

  cp5.get(Textarea.class, "Console")      .setVisible(GUIVisible);
  cp5.get(Button.class,   "serialBegin")  .setVisible(GUIVisible);
  cp5.get(Button.class,   "serialStop")   .setVisible(GUIVisible);
  cp5.get(Button.class,   "serialRefresh").setVisible(GUIVisible);
  cp5.get(ScrollableList.class, "dropdown").setVisible(GUIVisible);
}
