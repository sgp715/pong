class Paddle {

 protected:
  char shape;
  
  int xPos;
  int yPositions[5];
  int paddleLength;

  int yDirection;

 public:
  Paddle();
  Paddle(int startingX, int startingY);
  char getShape();
  int getX();
  int * getYs();
  int getPaddleLength();
  int getYDirection();
  void setYDirection(int);
  void flipYDirection();
  virtual void move();
  

};


class PlayerPaddle: public Paddle {

  

};


class ComputerPaddle: public Paddle {

};

