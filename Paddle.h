class Paddle {

  char shape;
  
  int xPos;
  int yPositions[4];

  int yDirection;

 public:
  Paddle();
  char getShape();
  int getX();
  int * getYs();
  int getYDirection();
  void flipYDirection();
  void move();
  

};
