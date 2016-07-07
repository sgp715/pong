class Paddle {

  char shape;
  
  int xPos;
  int yPositions[4];
  int paddleLength;

  int yDirection;

 public:
  Paddle();
  char getShape();
  int getX();
  int * getYs();
  int getPaddleLength();
  int getYDirection();
  void flipYDirection();
  void move();
  

};
