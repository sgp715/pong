class Ball {

  char shape;

  int xPos;
  int yPos;
  int oldX;
  int oldY;
  int xDirection;
  int yDirection;
  
 public:
  char getShape();
  int getX();
  int getY();
  int getOldX();
  int getOldY();
  int getXDirection();
  int getYDirection();
  void move();
  void flipXDirection();
  void flipYDirection();
  Ball();

};
