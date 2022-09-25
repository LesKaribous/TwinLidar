

class Vertex{
 float x1, y1, x2, y2;
 
 Vertex(PVector origin, PVector vector){
   x1 = origin.x;
   y1 = origin.y;
   x2 = origin.x + vector.x;
   y2 = origin.y + vector.y;
 }
 
 Vertex(float xa, float ya, float xb, float yb){
   x1 = xa;
   y1 = ya;
   x2 = xb;
   y2 = yb;
 }
 
 void draw(){
   strokeWeight(0.5);
   stroke(200, 60, 60);
   line(x1,y1,x2, y2); 
 }
  
  
}
