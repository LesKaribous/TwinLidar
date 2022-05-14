



class Function{
 float _a, _b, _c;
 
 Function(){
   _a = 2;
   _b = -1;
   _c = -1;
 }
 
 Function(float a, float b, float c){
   _a = a;
   _b = b;
   _c = c;
 }
  
 float f(float x){
   //return x;
   return  _a*x*x + _b*x + _c;
 }
 
 void draw(){
   /*
   float ax = -1;
   float bx = 1;
   
   float ay = f(ax);
   float by = f(bx);
   
   ax = toPixelX(ax);
   ay = toPixelY(ay);
   bx = toPixelX(bx);
   by = toPixelY(by);
   
   stroke(20,255,50);
   line(ax, ay, bx, by);
   resetStroke();
   */
   
   stroke(255,0,0);
   
   int N = 100;
   float ax = -1;
   float bx = 1;
   
   float delta = bx-ax;
   float incD = delta / N;
   float x = ax;
   
   for(int i = 0; i< N; i++){
     Point p = new Point(x,f(x));
     x+=incD;
     
     p.draw();
   }
   
   
 }
  
}
