

class Map{
 int w, h;
 
 Map(int _w, int _h){
  w = _w;
  h = _h;
 }
 
 
 void draw(){
   pushMatrix();
   center();
   
   translate(-w/2, -h/2);
   rect(0,0,w,h);
    
    
   popMatrix(); 
 }
  
}
