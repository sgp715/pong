#include <string>
using namespace std;

class Board{

  string boardString;
  int boardWidth;
  int boardLength;

 public:
  Board();
  void printBoard();
  void placeCharacter(int x, int y, char c);

};


