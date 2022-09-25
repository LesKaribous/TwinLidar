

void drawVector(PVector vector){
  fill(200,60,60);
  stroke(200,60,60);
    // draw the line
  line(0, 0, vector.x , vector.y);

  pushMatrix();
    translate(vector.x, vector.y);
    rotate(atan2(vector.x,vector.y));
    triangle(0, 0, -10, 5, -10, -5);
  popMatrix(); 
}

void drawVector(PVector origin, PVector vector){
  fill(200,60,60);
  stroke(200,60,60);
    // draw the line
  line(origin.x, origin.y, vector.x + origin.x , vector.y + origin.y);

  pushMatrix();
    translate(vector.x + origin.x, vector.y + origin.y);
    rotate(atan2(vector.y,vector.x));
    triangle(0, 0, -10, 5, -10, -5);
  popMatrix(); 
}


void drawAngle(PVector origin, PVector vecA, PVector vecB){
  noFill();
  stroke(60,200,60);
  
  float radius = 100 + vecA.mag() * 0.2;
  arc(origin.x, origin.y, radius, radius, atan2(vecA.y, vecA.x), atan2(vecB.y, vecB.x));
}
