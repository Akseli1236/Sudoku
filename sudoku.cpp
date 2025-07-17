#include "sudoku.h"
#include <bits/stdc++.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

Sudoku::Sudoku() {}

void Sudoku::startSudoku(int size, int difficulty) {
  power_ = pow(size, 2);
  size_ = size;
  difficulty_ = difficulty;
  tempBoard_.resize(power_, vector<int>(power_, 0));
  FULL = (1 << power_) - 1;
  drawBoard();
  startFilling();
}

void Sudoku::drawBoard() {
  playersBoard_.resize(power_, vector<int>(power_, 0));
  srand(time(0));
  generateBoard(playersBoard_);
  board_ = playersBoard_;
  updateBoard(playersBoard_, true);
}

bool Sudoku::solve(vector<vector<int>> &board, vector<uint16_t> &rowMask,
                   vector<uint16_t> &colMask, vector<uint16_t> &boxMask,
                   int r = 0, int c = 0) {

  if (r == power_) {
    return true;
  }
  if (c == power_)
    return solve(board, rowMask, colMask, boxMask, r + 1, 0);
  if (board[r][c] != 0)
    return solve(board, rowMask, colMask, boxMask, r, c + 1);

  int boxIndex = (r / size_) * size_ + (c / size_);
  uint16_t used = rowMask[r] | colMask[c] | boxMask[boxIndex];
  uint16_t available = ~used & FULL;

  for (int num = 21; num <= power_ + 20; ++num) {
    if (num == dontTry_ && dontTry_ != -1) {
      dontTry_ = -1;
      continue;
    }
    uint16_t mask = 1 << (num - 21);

    if (available & mask) {

      board[r][c] = num;
      rowMask[r] |= mask;
      colMask[c] |= mask;
      boxMask[boxIndex] |= mask;

      if (solve(board, rowMask, colMask, boxMask, r, c + 1))
        return true;

      // We do da backtrack
      board[r][c] = 0;
      rowMask[r] ^= mask;
      colMask[c] ^= mask;
      boxMask[boxIndex] ^= mask;
    }
  }

  return false;
}

bool Sudoku::generateBoard(vector<vector<int>> &board) {
  vector<uint16_t> rowMask(power_, 0), colMask(power_, 0), boxMask(power_, 0);

  for (int r = 0; r < power_; ++r)
    for (int c = 0; c < power_; ++c)
      if (tempBoard_[r][c] != 0) {
        int val = tempBoard_[r][c];
        uint16_t mask = 1 << (val - 21);
        rowMask[r] |= mask;
        colMask[c] |= mask;
        boxMask[(r / size_) * size_ + (c / size_)] |= mask;
      }

  return solve(board, rowMask, colMask, boxMask);
}

void Sudoku::updateBoard(vector<vector<int>> board, bool init) {
  int counter = 0;
  int rowCounter = 0;

  string topAndBottomLine = string(power_ * 3 + (size_ + 1), '-');
  string finalPrint;
  for (auto i : board) {
    string print;
    for (auto y : i) {
      if (counter % size_ == 0) {
        print += "|";
      }

      string number = to_string(y % 20);

      if (init) {
        if (rand() % difficulty_ == 0) {

          print += " \033[36m" + number + "\033[0m ";
        } else {

          tempBoard_ = playersBoard_;
          tempBoard_.at(rowCounter).at(counter % power_) = 0;
          dontTry_ = y;

          if (generateBoard(tempBoard_)) {
            print += " \033[36m" + number + "\033[0m ";
          } else {
            playersBoard_.at(rowCounter).at(counter % power_) = 0;
            tilesToFill_++;
            print += string(3, ' ');
          }
        }
      } else {
        if (y == 0) {
          print += string(3, ' ');
        } else if (y > power_) {
          print += " \033[36m" + number + "\033[0m ";
        } else {
          print += " \033[32m" + number + " \033[0m";
        }
      }

      counter++;
    }
    rowCounter++;

    if ((counter - power_) % (power_ * size_) == 0) {
      finalPrint += topAndBottomLine + "\n";
    }
    finalPrint += print + "|\n";
  }
  cout << finalPrint << topAndBottomLine << endl;
}

void Sudoku::checkSolution() {
  for (auto &i : playersBoard_) {
    for (auto &n : i) {
      if (n <= power_) {
        n += 10;
      }
    }
  }

  if (playersBoard_ == board_) {
    cout << "Correct Solution!" << endl;
  } else {
    cout << "Incorrect Solution!" << endl;
    updateBoard(board_, false);
  }
}

void Sudoku::startFilling() {
  while (tilesToFill_ > 0) {
    int value;

    cout << "First enter row, then column and last chosen value" << endl;
    vector<int> rowCol;
    while (true) {
      while (!(std::cin >> value)) {
        std::cout << "Not a number" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      if (value < 1 || value > power_) {
        cout << "Invalid value" << endl;
      } else {
        rowCol.push_back(value - 1);
      }
      if (rowCol.size() >= 3) {
        break;
      }
    }
    int *chosenTile = &playersBoard_.at(rowCol.at(0)).at(rowCol.at(1));
    if (*chosenTile > power_) {
      cout << "You can't change that" << endl;
    } else {
      if (*chosenTile == 0) {
        tilesToFill_--;
      }
      *chosenTile = rowCol.at(2) + 1;
    }
    updateBoard(playersBoard_, false);
  }
  checkSolution();
}
