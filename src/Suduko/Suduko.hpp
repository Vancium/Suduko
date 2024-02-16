#pragma once

#include <utility>
#include <vector>

typedef struct Cell {
  int x;
  int y;
  int val;
} cell_t;

class Suduko {
private:
  std::vector<cell_t> m_State;
  bool m_ValidSuduko = false;
  bool m_CompleteSuduko = false;
  std::pair<int, int> m_EmptyCell;

private:
  bool ValidRow(int row);
  bool ValidColumn(int col);
  bool ValidSquare(int row, int col);
  bool CheckRowSum(int row);
  bool CheckColSum(int col);
  bool CheckSquareSum(int row, int col);
  int FindEmptyCell(int &row, int &col);
  int ValidGuess(int row, int col, int guess);

public:
  void TestCase1();
  void TestValidCase1();
  void PrintGrid();
  static constexpr int GRID_SIZE = 9;
  Suduko();

  bool ValidSuduko();

  int Solve();
};
