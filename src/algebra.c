#include "algebra.h"
#include <stdio.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    Matrix add_matrix;
    if (a.rows == b.rows && a.cols == b.cols)
    {
        add_matrix.rows = a.rows;
        add_matrix.cols = a.cols;
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                add_matrix.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return add_matrix;
    }
    else
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo
    Matrix sub_matrix;
    if (a.rows == b.rows && a.cols == b.cols)
    {
        sub_matrix.rows = a.rows;
        sub_matrix.cols = a.cols;
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                sub_matrix.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return sub_matrix;
    }
    else
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    // ToDo
    Matrix mul_matrix;
    if (a.cols == b.rows)
    {
        mul_matrix.rows = a.rows;
        mul_matrix.cols = b.cols;
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < b.cols; j++)
            {
                double sum;
                sum = 0;
                mul_matrix.data[i][j] = 0;
                for (int k = 0; k < a.cols; k++)
                {
                    sum = sum + a.data[i][k] * b.data[k][j];
                }
                mul_matrix.data[i][j] = mul_matrix.data[i][j] + sum;
            }
        }
        return mul_matrix;
    }
    else
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
}

Matrix scale_matrix(Matrix a, double k)
{
    // ToDo
    Matrix scale_matrix;
    scale_matrix.rows = a.rows;
    scale_matrix.cols = a.cols;
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            scale_matrix.data[i][j] = k * a.data[i][j];
        }
    }
    return scale_matrix;
}

Matrix transpose_matrix(Matrix a)
{
    // ToDo
    Matrix transpose_matrix;
    transpose_matrix.rows = a.cols;
    transpose_matrix.cols = a.rows;

    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            transpose_matrix.data[j][i] = a.data[i][j];
        }
    }

    return transpose_matrix;
}

double det_matrix(Matrix a)
{
    // ToDo
    if (a.rows == a.cols)
    {
        double sum;
        if (a.rows == 1)
        {
            return a.data[0][0];
        }
        else if (a.rows == 2)
        {
            sum = a.data[0][0] * a.data[1][1] - a.data[1][0] * a.data[0][1];
            return sum;
        }
        else
        {
            Matrix b;
            int p = 0, q = 0;
            b = create_matrix(a.rows - 1, a.cols - 1);
            sum = 0.0;
            int fact;

            for (int j = 0; j < a.cols; j++)
            {
                for (int k = 0; k < a.cols; k++)
                {
                    if (k != j)
                    {
                        for (int m = 1; m < a.rows; m++)
                        {
                            b.data[p][q] = a.data[m][k];
                            p++;
                        }
                        q++;
                        p = 0;
                    }
                    else
                    {
                        continue;
                    }
                }
                fact = (j % 2 ? -1 : 1);
                sum += fact * a.data[0][j] * det_matrix(b);
                p = 0;
                q = 0;
            }
            return sum;
        }
    }
    else
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    if (a.rows == a.cols && det_matrix(a) != 0)
    {
        Matrix inv_matrix;
        inv_matrix.rows = a.rows;
        inv_matrix.cols = a.cols;
        Matrix b; // 伴随矩阵的转置矩阵
        b.rows = a.rows;
        b.cols = a.cols;
        Matrix c; // 子矩阵
        c.rows = a.rows - 1;
        c.cols = a.cols - 1;
        int p = 0, q = 0;
        int fact;
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                for (int m = 0; m < a.rows; m++)
                {
                    if (m != i)
                    {
                        for (int n = 0; n < a.cols; n++)
                        {
                            if (n != j)
                            {
                                c.data[p][q] = a.data[m][n];
                                q++;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        q = 0;
                        p++;
                    }
                    else
                    {
                        continue;
                    }
                }
                p = 0;
                q = 0;
                fact = (i + j) % 2 ? -1 : 1;
                b.data[i][j] = fact * det_matrix(c);
            }
        }
        Matrix d;
        d.rows = b.rows;
        d.cols = b.cols;
        d = transpose_matrix(b);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                inv_matrix.data[i][j] = 1 / det_matrix(a) * d.data[i][j];
            }
        }
        return inv_matrix;
    }
    else if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    else
    {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
}

int rank_matrix(Matrix a)
{
    // ToDo
    int rank;
    // rank取行列最小值
    if (a.rows >= a.cols)
    {
        rank = a.cols;
    }
    else
    {
        rank = a.rows;
    }
    Matrix replace; // 储存数据的矩阵
    replace.rows = 1;
    replace.cols = a.cols;
    Matrix e; // 出矩阵
    e.rows = a.rows;
    e.cols = a.cols;
    for (int i = 0; i < a.rows; i++)
    {
        e.data[0][i] = a.data[0][i];
    }
    for (int i = 0; i < rank; i++)
    {
        if (a.data[i][i] != 0)
        {
            for (int j = i + 1; j < a.rows; j++)
            {
                for (int m = 0; m < a.cols; m++)
                {
                    e.data[j][m] = a.data[j][m] - (a.data[j][i] / a.data[i][i]) * a.data[i][m];
                }
            }
        }
        else
        {
            for (int k = i + 1; k < a.rows; k++)
            {
                if (a.data[k][i] != 0)
                {
                    for (int n = 0; n < a.cols; n++)
                    {
                        replace.data[0][n] = a.data[i][n];
                        a.data[i][n] = a.data[k][n];
                        a.data[k][n] = replace.data[0][n];
                    }
                    break;
                }
                else
                {
                    continue;
                }
            }
            for (int j = i + 1; j < a.rows; j++)
            {
                for (int m = 0; m < a.cols; m++)
                {
                    e.data[j][m] = a.data[j][m] - (a.data[j][i] / a.data[i][i]) * a.data[i][m];
                }
            }
        }
    }
    rank = 0;
    for (int i = 0; i < e.rows; i++)
    {
        if (e.data[i][i] != 0)
        {
            rank++;
        }
    }

    return rank;
}

double trace_matrix(Matrix a)
{
    // ToDo
    if (a.rows == a.cols)
    {
        double trace_matrix = 0;
        for (int i = 0; i < a.rows; i++)
        {
            trace_matrix += a.data[i][i];
        }
        return trace_matrix;
    }
    else
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}