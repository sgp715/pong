class Ball {

  char shape;

  int xPos;
  int yPos;
  int xDirection;
  int yDirection;
  
 public:
  char getShape();
  int getX();
  int getY();
  int getXDirection();
  int getYDirection();
  void move();
  void flipXDirection();
  void flipYDirection();
  Ball();

};
