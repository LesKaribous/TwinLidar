
boolean bad = false;
boolean paused = false;

PFont f;           // Font
int mouseRadius = 20;


void initUI(){
 f = createFont("Courier",12,true); 
}

void drawUI(){
  resetMatrix();
  stroke(0);
  noFill();
  textFont(f);
  
  coordSystem.draw();  

  text(bad ? "Click on bad clusters" : "Click on valid training cluster",10,20);
  
  text("Valid clusters : " + validData.size(),10,60); 
  if(validData.size() > 0) text("last contains " + validData.get(validData.size()-1).size() + " points",150,60);
  text("Bad clusters : " + badData.size(),10,80);
  if(badData.size() > 0) text("last contains " + badData.get(badData.size()-1).size() + " points",150,80);
  
  text("There is " + points.size() + " in the buffer", width-200, 20);
  text("Receiving " + serialFreq + " pt/s", width-200, 40); 
  
  stroke(bad ? color(255,50,50) : color(50,255,50));
  translate(mouseX, mouseY);
  text(countPoint() + " points", 20, 20);
  
  stroke(bad ? color(255,50,50) : color(50,255,50));
  strokeWeight(2);
  circle(0,0,20); 
}

void mousePressed(){
  ArrayList<Point> buffer = selectPoint();
   
  if(buffer.size() == 0) return;
  if(bad){
    badData.add(buffer);
  }else{
    validData.add(buffer);
  }
  
  
}

void keyPressed(){
  switch(key){
    case ' ':
      bad = !bad;
    break;
    case 'p':
      paused = !paused;
    break;
  }
}
