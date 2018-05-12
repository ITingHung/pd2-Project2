#ifndef SUDOKUSETUP_H
#define SUDOKUSETUP_H

#include <QDebug>
#include <vector>

#include "mainwindow.h"

using namespace std;

class Sudoku
{
public:
    Sudoku();
    void SetMap(const int set_map[]);
    int getElement(int index);
    void setElement(int index, int value);
    int getFirstZeroIndex();
    bool isCorrect();
    bool solve(Sudoku question,Sudoku &answer);
    bool check_and_generate_info();
    void runKernel(int curr_n, int total_n,vector<int>& row_list, vector<int>& col_list);
    int get_empty_num(vector<int>& row_list, vector<int>& col_list);
    static const int sudokuSize = 81;

private:
    bool checkUnity(int arr[]);
    vector<int> find_same_num(vector<int>& row_v,vector<int>& col_v,vector<int>& block_v);
    int get_block_num(int row, int column);
    int map[sudokuSize];
};

#endif // SUDOKUSETUP_H
