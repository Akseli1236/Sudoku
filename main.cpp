#include "sudoku.h"
#include <ios>
#include <iostream>
#include <limits>

int validInput() {
  int value;
  while (!(std::cin >> value)) {
    std::cout << "Not a number" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return value;
}

int main() {
  Sudoku game;
  std::cout << "Choose size (max: 4): ";
  int input = validInput();
  int size = (input < 5) ? input : 4;
  std::cout << "Choose difficulty (2-size): ";
  int difficulty = validInput();
  game.startSudoku(size, difficulty);
  return 0;
}
