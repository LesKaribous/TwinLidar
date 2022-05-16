



class Function{
 float _a, _b, _c;
 
 Function(){
   _a = 0.8;
   _b = 0.2;
   _c = 0.5;
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
   float ax = 0;
   float bx = 1;
   
   float delta = bx-ax;
   float incD = delta / N;
   float x = ax;
   
   for(int i = 0; i< N-1; i++){
     Point pA = new Point(x,f(x));
     x+=incD;
     Point pB = new Point(x,f(x));
     
     strokeWeight(1);
     stroke(52);
     linePixel(pA._x, pA._y, pB._x, pB._y);
   }
   
   
 }
  
}
