#include "Suduko.hpp"
#include <cstdio>
#include <set>
#include <utility>
#include <vector>

Suduko::Suduko() {
  m_State = std::vector<cell_t>(GRID_SIZE * GRID_SIZE);
  m_EmptyCell = std::make_pair(-1, -1);

  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      m_State.at(y * GRID_SIZE + x) = {.x = x, .y = y, .val = 0};
    }
  }
}
//  {3, 0, 6, 5, 0, 8, 4, 0, 0},
void Suduko::TestCase1() {
  int grid[GRID_SIZE][GRID_SIZE] = {
      {3, 0, 6, 5, 0, 8, 4, 0, 0}, {5, 2, 0, 0, 0, 0, 0, 0, 0},
      {0, 8, 7, 0, 0, 0, 0, 3, 1}, {0, 0, 3, 0, 1, 0, 0, 8, 0},
      {9, 0, 0, 8, 6, 3, 0, 0, 5}, {0, 5, 0, 0, 9, 0, 6, 0, 0},
      {1, 3, 0, 0, 0, 0, 2, 5, 0}, {0, 0, 0, 0, 0, 0, 0, 7, 4},
      {0, 0, 5, 2, 0, 6, 3, 0, 0}};

  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      m_State.at(y * GRID_SIZE + x).val = grid[x][y];
      m_State.at(y * GRID_SIZE + x).x = x;
      m_State.at(y * GRID_SIZE + x).y = y;
    }
  }
}

void Suduko::TestValidCase1() {
  int grid[GRID_SIZE][GRID_SIZE] = {
      {9, 7, 4, 2, 3, 6, 1, 5, 8}, {6, 3, 8, 5, 9, 1, 7, 4, 2},
      {1, 2, 5, 4, 8, 7, 9, 3, 6}, {3, 1, 6, 7, 5, 4, 2, 8, 9},
      {7, 4, 2, 9, 1, 8, 5, 6, 3}, {5, 8, 9, 3, 6, 2, 4, 1, 7},
      {8, 6, 7, 1, 2, 5, 3, 9, 4}, {2, 5, 3, 6, 4, 9, 8, 7, 1},
      {4, 9, 1, 8, 7, 3, 6, 2, 5},
  };
  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      m_State.at(y * GRID_SIZE + x).val = grid[x][y];
    }
  }
}

bool Suduko::CheckRowSum(int row) {
  int sum = 0;
  for (int y = 0; y < GRID_SIZE; y++) {
    sum += m_State.at(y * GRID_SIZE + row).val;
  }

  if (sum != 45) {
    return false;
  }
  return true;
}
bool Suduko::CheckColSum(int col) {
  int sum = 0;
  for (int x = 0; x < GRID_SIZE; x++) {
    sum += m_State.at(col * GRID_SIZE + x).val;
  }
  if (sum != 45) {
    return false;
  }
  return true;
}

bool Suduko::CheckSquareSum(int row, int col) {
  // get x, y value of subgrid
  // TODO this assumes the grid is a 9 X 9, use recursion maybe
  int x, y;
  int sum = 0;
  if (col <= 2) {
    x = 1;
  } else if (col <= 5) {
    x = 4;
  } else {
    x = 7;
  }
  if (row <= 2) {
    y = 1;
  } else if (row <= 5) {
    y = 4;
  } else {
    y = 7;
  }

  // loop around x,y value
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      sum += m_State.at((i + x) * GRID_SIZE + (j + y)).val;
    }
  }

  if (sum != 45) {
    return false;
  }
  return true;
}

bool Suduko::ValidSuduko() {
  // check all rows & columns

  for (int i = 0; i < GRID_SIZE; i++) {
    if (!ValidRow(i)) {
      return false;
    }
    if (!ValidColumn(i)) {
      return false;
    }
  }
  for (int i = 0; i < GRID_SIZE; i += 3) {
    for (int j = 0; j < GRID_SIZE; j += 3) {
      if (!ValidSquare(i, j)) {
        return false;
      }
    }
  }

  // check all squares
  return true;
}

bool Suduko::ValidRow(int row) {

  if (!CheckRowSum(row)) {
    return false;
  }

  std::set<int> nums;
  for (int y = 0; y < GRID_SIZE; y++) {
    nums.insert(m_State.at(y * GRID_SIZE + row).val);
  }

  if (nums.size() != 9) {
    return false;
  }
  return true;
}

bool Suduko::ValidColumn(int col) {

  if (!CheckColSum(col)) {
    return false;
  }

  std::set<int> nums;
  for (int x = 0; x < GRID_SIZE; x++) {
    nums.insert(m_State.at(col * GRID_SIZE + x).val);
  }
  if (nums.size() != 9) {
    return false;
  }
  return true;
}

bool Suduko::ValidSquare(int row, int col) {
  if (!CheckSquareSum(row, col)) {
    return false;
  }

  int x, y;
  if (col <= 2) {
    x = 1;
  } else if (col <= 5) {
    x = 4;
  } else {
    x = 7;
  }
  if (row <= 2) {
    y = 1;
  } else if (row <= 5) {
    y = 4;
  } else {
    y = 7;
  }

  std::set<int> nums;

  // loop around x,y value
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      nums.insert(m_State.at((i + x) * GRID_SIZE + (j + y)).val);
    }
  }
  if (nums.size() != 9) {
    return false;
  }
  return true;
}

void Suduko::PrintGrid() {

  for (int x = 0; x < GRID_SIZE; x++) {

    if (x % 3 == 0 && x != 0) {
      printf("---------------------\n");
    }

    for (int y = 0; y < GRID_SIZE; y++) {
      if (y != 0 && y % 3 == 0) {
        printf("| %d ", m_State.at(x + y * GRID_SIZE).val);
      } else if (y == GRID_SIZE - 1) {
        printf("%d\n", m_State.at(x + y * GRID_SIZE).val);
      } else {

        printf("%d ", m_State.at(x + y * GRID_SIZE).val);
      }
    }
  }
  printf("\n");
}

int Suduko::FindEmptyCell(int &row, int &col) {
  for (row = 0; row < GRID_SIZE; row++) {
    for (col = 0; col < GRID_SIZE; col++) {
      if (!m_State.at(col * GRID_SIZE + row).val) {
        return 1;
      }
    }
  }
  return 0;
}

int Suduko::ValidGuess(int row, int col, int guess) {

  int x = row / 3 * 3;
  int y = col / 3 * 3;

  for (int i = 0; i < GRID_SIZE; i++) {
    // Check row
    if (m_State.at(i * GRID_SIZE + row).val == guess)
      return 0;
    if (m_State.at(col * GRID_SIZE + i).val == guess)
      return 0;
    if (m_State.at((y + (i / 3)) * GRID_SIZE + (x + (i % 3))).val == guess)
      return 0;
  }
  return 1;
}

int Suduko::Solve() {
  int row, col;

  if (!FindEmptyCell(row, col))
    return 1;

  for (int guess = 1; guess < 10; guess++) {
    if (ValidGuess(row, col, guess)) {
      m_State.at(col * GRID_SIZE + row).val = guess;
      if (Solve())
        return 1;

      m_State.at(col * GRID_SIZE + row).val = 0;
    }
  }
  return 0;
}
