#include <vector>
#include "Sudoku.h"

using namespace std;

vector<int> row_vec[9];
vector<int> col_vec[9];
vector<int> block_vec[9];
bool finish = false;

Sudoku::Sudoku()
{
    for(int i=0; i<sudokuSize; ++i)
        map[i] = 0;
}

void Sudoku::SetMap(const int set_map[])
{
    for(int i=0; i<sudokuSize; ++i)
        map[i] = set_map[i];
}

int Sudoku::getElement(int index)
{
    return map[index];
}

void Sudoku::setElement(int index, int value)
{
    map[index] = value;
}

int Sudoku::getFirstZeroIndex()
{
    for(int i=0; i<sudokuSize; ++i)
        if(map[i]==0)
            return i;
    return -1;
}

bool Sudoku::checkUnity(int arr[])
{
    int arr_unity[9];

    for(int i=0; i<9; ++i)
        arr_unity[i] = 0;
    for(int i=0; i<9; ++i)
        ++arr_unity[arr[i]-1];
    for(int i=0; i<9; ++i)
        if(arr_unity[i]!= 1)
            return false;
    return true;
}

bool Sudoku::isCorrect()
{
    bool check_result;
    int check_arr[9];
    int location;
    for(int i=0; i<81; i+=9)
    {
        for(int j=0; j<9; ++j)
            check_arr[j] = map[i+j];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j)
             check_arr[j] = map[i+9*j];
         check_result = checkUnity(check_arr);
         if(check_result == false)
             return false;
    }
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j)
        {
            location = 27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
            check_arr[j] = map[location];
        }
        check_result = checkUnity(check_arr);
        if(check_result ==false)
            return false;
    }
    return true;
}

bool Sudoku::solve(Sudoku question,Sudoku &answer)
{
    int firstZero;
    firstZero = question.getFirstZeroIndex();
    if(firstZero == -1)
    {
        if(question.isCorrect())
        {
            answer = question;
            return true;
        }
        else
            return false;
    }
    else
    {
        for (int num =1; num<=9; ++num)
        {
            question.map[firstZero]=num;
            if(solve(question,answer))
                return true;
        }
    return false;
    }
}

bool Sudoku::check_and_generate_info()
{
    // row
    for (int i=0; i<9; ++i)
    {
        bool check[9] = {false};
        for (int j=0; j<9; ++j)
        {
            int value = map[9*i+j] - 1;
            //If value<0 means the block is 0
            if (value < 0)
                continue;
            //Make sure no number is repeat
            if (check[value])
                return false;
            //Set the status of the choosen number to true
            check[value] = true;
        }

        for (int j=0; j<9; ++j)
        {
            //Status false means the number haven't been choosen
            //Save these number into row_vec
            if (!check[j])
                row_vec[i].push_back(j+1);
        }
    }

    // column

    for (int i=0; i<9; ++i)
    {
        bool check[9] = {false};
        for (int j= 0; j<9; ++j)
        {
            int value = map[i+9*j] - 1;
            if (value < 0)
                continue;
            if (check[value])
                return false;
            check[value] = true;
        }

        for (int j=0; j<9; j++)
        {
            if (!check[j])
                col_vec[i].push_back(j+1);
        }
    }

    // block
    for (int block=0; block<9; ++block)
    {
        bool check[9] = {false};
        int row_start = (block / 3) * 3;
        int col_start = (block % 3) * 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int value = map[9*(i+row_start)+(j+col_start)] - 1;
                if (value < 0)
                    continue;
                if (check[value])
                    return -1;
                check[value] = true;
            }
        }
        for (int j=0; j<9; ++j)
        {
            if (!check[j])
                block_vec[block].push_back(j+1);
        }
    }
    return true;
}

vector<int> Sudoku::find_same_num(vector<int>& row_v,vector<int>& col_v,vector<int>& block_v)
{
    vector<int> result;

    bool r[9] = {false};
    bool c[9] = {false};
    bool b[9] = {false};
    //Set the status of candidate number to true
    for (int i = 0; i < row_v.size(); i++)
        r[row_v[i] - 1] = true;
    for (int i = 0; i < col_v.size(); i++)
        c[col_v[i] - 1] = true;
    for (int i = 0; i < block_v.size(); i++)
        b[block_v[i] - 1] = true;

    for (int i = 0; i < 9; i++)
    {
        //Save the row+column+block candidate number into result
        if (r[i] && c[i] && b[i])
            result.push_back(i + 1);
    }

    return result;
}

int Sudoku::get_block_num(int row, int column)
{
    int r = row / 3;
    int c = column / 3;
    return r * 3 + c;
}

int Sudoku::get_empty_num(vector<int>& row_list, vector<int>& col_list)
{
    int num = 0;
    row_list.clear();
    col_list.clear();
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (map[9*i+j] == 0)
            {
                num++;
                row_list.push_back(i);
                col_list.push_back(j);
            }
        }
    }
    return num;
}

void Sudoku::runKernel(int curr_n, int total_n, vector<int>& row_list, vector<int>& col_list)
{
    if (curr_n == total_n)
    {
        finish = true;
        return;
    }

    int row = row_list[curr_n];
    int col = col_list[curr_n];
    int block = get_block_num(row, col);
    vector<int> candidates = find_same_num(row_vec[row], col_vec[col], block_vec[block]);
    if (candidates.size() == 0)
        return;

    for (int i = 0; i < candidates.size(); i++)
    {
        int value = candidates[i];
        vector<int>::iterator iter;

        //After number choosen, delete the number in candidate
        iter = find(row_vec[row].begin(),row_vec[row].end(), value);
        row_vec[row].erase(iter);

        iter = find(col_vec[col].begin(),col_vec[col].end(), value);
        col_vec[col].erase(iter);

        iter = find(block_vec[block].begin(),block_vec[block].end(), value);
        block_vec[block].erase(iter);

        //Set up the number
        map[9*row+col] = value;

        //Run for next index
        runKernel(curr_n+1, total_n, row_list, col_list);
        if(finish)
            return;

        //If curr_n+1 can't find a suitable number, then reset the previous one
        map[9*row+col] = 0;

        //Put back the number as a candidate
        row_vec[row].push_back(value);
        col_vec[col].push_back(value);
        block_vec[block].push_back(value);
    }
}
