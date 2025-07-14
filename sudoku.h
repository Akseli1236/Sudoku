// sudoku.h

#ifndef SUDOKU_H // include guard start
#define SUDOKU_H

#include <vector>

class Sudoku {
public:
  Sudoku(); // constructor declaration
  void startSudoku(int, int);
  void drawBoard(); // method declaration
  bool generateBoard();
  void startFilling();
  void updateBoard(std::vector<std::vector<int>>, bool);
  void checkSolution();

private:
  std::vector<std::vector<int>> board_;
  std::vector<std::vector<int>> playersBoard_;
  int size_;
  int difficulty_;
  int power_;
  int tilesToFill_;
};

#endif // SUDOKU_H      // include guard end
