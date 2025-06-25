#include "sudoku.h"
#include <iostream>
#include <limits>
#include <ios>

int validInput(){
  int value;
  while (!(std::cin >> value)){
    std::cout << "Not a number" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return value;
}


int main(){
  Sudoku game;
  std::cout << "Choose size (default 3): ";
  int size = validInput();
  std::cout << "Choose difficulty (2-size): ";
  int difficulty = validInput();
  game.startSudoku(size, difficulty);
  return 0;
}

