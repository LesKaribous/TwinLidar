Table dataSaver;

void savePoints(){
  
  for(int i = 0; i < Points.size(); i++){
    TableRow row = dataSaver.addRow();
    Point p = Points.get(i);
    row.setInt("ID", i);
    row.setFloat("x", p.pos.x);
    row.setFloat("y", p.pos.y);
    //row.setFloat(p._intensity);
    
  }
}
