#include "sudoku.h"
#include <bits/stdc++.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

Sudoku::Sudoku() {}

void Sudoku::startSudoku(int size, int difficulty) {
  power_ = pow(size, 2);
  size_ = size;
  difficulty_ = difficulty;
  drawBoard();
  startFilling();
}

void Sudoku::drawBoard() {
  playersBoard_.resize(power_);
  srand(time(0));
  while (!generateBoard()) {
  }
  updateBoard(board_, true);
}

bool Sudoku::generateBoard() {
  vector<vector<int>> boxes(power_);
  vector<vector<int>> rows(power_);
  vector<vector<int>> columns(power_);

  for (int row = 0; row < power_; row++) {
    for (int column = 0; column < power_; column++) {
      int randNum;
      vector<int> tested;

      do {
        randNum = (rand() % power_) + 11;
        if (count(tested.begin(), tested.end(), randNum) == 0) {
          tested.push_back(randNum);
        }

        if (tested.size() >= power_) {
          return false;
        }

      } while (
          (count(rows.at(row).begin(), rows.at(row).end(), randNum) +
           count(columns.at(column).begin(), columns.at(column).end(),
                 randNum) +
           count(boxes.at((row / size_) * size_ + (column / size_)).begin(),
                 boxes.at((row / size_) * size_ + (column / size_)).end(),
                 randNum)) > 0);

      boxes.at((row / size_) * size_ + (column / size_)).push_back(randNum);
      rows.at(row).push_back(randNum);
      columns.at(column).push_back(randNum);
    }
  }
  board_ = rows;
  return true;
}

void Sudoku::updateBoard(vector<vector<int>> board, bool init) {
  int counter = 0;
  int rowCounter = 0;

  string topAndBottomLine = string(power_ * 3 + (size_ + 1), '-');

  for (auto i : board) {
    string print;
    for (auto y : i) {
      if (counter % size_ == 0) {
        print += "|";
      }

      string number = to_string(y % 10);

      if (init) {
        if (rand() % difficulty_ == 0) {
          print += " \033[36m" + number + "\033[0m ";
          playersBoard_.at(rowCounter).push_back(y);
        } else {
          tilesToFill_++;
          playersBoard_.at(rowCounter).push_back(0);
          print += string(3, ' ');
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
      cout << topAndBottomLine << endl;
    }
    cout << print << "|" << endl;
  }
  cout << topAndBottomLine << endl;
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
