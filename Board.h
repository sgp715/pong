#include <string>
#include "Ball.h"


using namespace std;


class Board{

  string boardString;
  int boardWidth;
  int boardLength;
  Ball gameBall;

 public:
  Board();
  void moveBall();
  void play();
  void placeCharacter(int x, int y, char c);

};


