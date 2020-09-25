/*
This program reads information from a file "matrix.txt" 
in which the first element of the first row is the size of the matrix, 
the next row elements of the matrix. 
The screen displays a matrix of eigenvectors, 
on the main diagonal which are the eigenvalues.
*/


#include <cstdlib>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

void MatrixShow(double** matrix, int size)
{
	for (int i = 0; i < size; i++) {
		cout << "L: " << matrix[i][i] << " V: (";
		for (int j = 0; j < size; j++) {
			cout << matrix[j][i] << " ";
		}
		cout << ")" << endl;
	}
}

void ReadFile(double** pointer1, int size, ifstream &in)
{
    
    int i, j;
    for (i = 0; i < size; i++) 
        for (j = 0; j < size; j++) 
            in >> pointer1[i][j];
}

void MemoryAllocation(double**& matrix, int size)
{
    matrix = new double*[size];
    for (int i = 0; i < size; i++)
        matrix[i] = new double[size];
}

void MatrixMult(double** matrix1, double** matrix, double** matrix4, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            matrix4[i][j] = 0;
            for (int k = 0; k < size; k++)
                matrix4[i][j] += matrix1[i][k] * matrix[k][j];
        }
}

void CalculateMatix(double** matrix1, double** matrix, int size)
{
    double max_elem = matrix1[0][1];
    int h = 1;
    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++)
            if (fabs(matrix1[i][j]) > max_elem) {
                max_elem = fabs(matrix1[i][j]);
                k = i;
                h = j;
            }
    }
    double fi = 0.5 * atan((2 * max_elem) / (matrix1[k][k] - matrix1[h][h]));

    if (matrix1[k][k] == matrix1[h][h]) {
        fi = 0.785;
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 1;
            }
            else
                matrix[i][j] = 0;

            matrix[k][h] = -sin(fi);
            matrix[h][k] = sin(fi);
            matrix[h][h] = cos(fi);
            matrix[k][k] = cos(fi);
        }
}

double SumElement(double** matrix1, int size)
{
    double sum = 0;
    int i, j;
    for (i = 0; i < size; i++) 
        for (j = i + 1; j < size - 1; j++)
            sum += (matrix1[i][j]) * (matrix1[i][j]);
    return sum;
}

void Transposition(double** matrix1, double** matrix, double** T, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            T[i][j] = matrix1[j][i];
            matrix[i][j] = matrix1[j][i];
            matrix[i][j] = T[i][j];
        }
}

void MatrixSwap(double** matrix1, double** matrix, double** T, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            T[i][j] = matrix1[i][j];
            matrix[i][j] = matrix1[i][j];
            matrix[i][j] = T[i][j];
        }
}

void MaxElement(double** matrix1, int size)
{
    double max_elem = matrix1[0][1];
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++)
            if (matrix1[i][j] > max_elem) {
                max_elem = matrix1[i][j];
            }
    }
}

int Control(double** matrix1, int size)
{
    double s = 0.0;
    s = SumElement(matrix1, size);
    if (s != 0)
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (matrix1[i][j] != matrix1[j][i]) {
                    cout << " \nMatrix is not symmetric \n";
                    //break;
                    return 0;
                }
}

int main(int argc, char* argv[])
{
    int size = 0;
    double Eps = 0.001;
    double** matrix1;
    double** matrix2;
    double** matrix2T;
    double** matrix3;
    double** matrix4;
    double** T1;
    double** T2;
    ifstream in("matrix.txt");
    if (!in.is_open()) {
        cout << "\nCan not open the file \n";
        return 0;
    }
    in >> size;
    
    MemoryAllocation(matrix1, size);
	MemoryAllocation(matrix2, size);
    MemoryAllocation(matrix2T, size);
    MemoryAllocation(matrix3, size);
    MemoryAllocation(matrix4, size);
    MemoryAllocation(T1, size);
    MemoryAllocation(T2, size);
    
    ReadFile(matrix1, size, in);
    in.close();
    int fl = Control(matrix1, size);
    if (!fl) return 0;
	
    double s = SumElement(matrix1, size);
    for (int i = 0; sqrt(s) > Eps; i++) {
        CalculateMatix(matrix1, matrix2, size);
        Transposition(matrix2, matrix2T, T1, size);
        MatrixMult(matrix2T, matrix1, matrix3, size);
        MatrixMult(matrix3, matrix2, matrix4, size);
        MatrixSwap(matrix4, matrix1, T2, size);
        s = SumElement(matrix1, size);
    }
    MatrixShow(matrix1, size);
    //system("PAUSE");
    return EXIT_SUCCESS;
}
