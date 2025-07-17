// sudoku.h

#ifndef SUDOKU_H // include guard start
#define SUDOKU_H

#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Sudoku {
public:
  Sudoku(); // constructor declaration
  void startSudoku(int, int);
  void drawBoard(); // method declaration
  bool generateBoard(vector<vector<int>> &);
  void startFilling();
  void updateBoard(std::vector<std::vector<int>>, bool);
  void checkSolution();
  bool recursiveFind(int, int, std::vector<std::vector<int>> &);
  bool solve(vector<vector<int>> &, vector<uint16_t> &, vector<uint16_t> &,
             vector<uint16_t> &, int, int);

private:
  vector<vector<int>> board_;
  std::vector<std::vector<int>> tempBoard_;
  std::vector<std::vector<int>> playersBoard_;
  int size_;
  int difficulty_;
  int power_;
  int tilesToFill_ = 0;
  int dontTry_ = -1;
  uint16_t FULL; // 16 bits set
};

#endif // SUDOKU_H      // include guard end
