#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>





int isSafeOriginal(int N,int puzzle[N][N], int row, int col, int num)
{

    // If we find the same number in the same row , we return 0
    for (int x = 0; x <= N-1 && x!=col ; x++)
        if (puzzle[row][x] == num){
            //printf("same row");
            return 0;
        }


    //If we find the same num in the same column , we return 0
    for (int x = 0; x <= N-1 && x!=row; x++)
        if (puzzle[x][col] == num)
            return 0;

    //If we find the same num in the small submatrix, we return 0
    int sq=sqrt(N);
    int startRow = row - row % sq, startCol = col - col % sq;

    for (int i = 0; i < sq; i++)
        for (int j = 0; j < sq; j++)
            if ((i + startRow)!=row && (j + startCol)!= col && puzzle[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}


int isValidOriginal(int N,int puzzle[N][N])
{

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int num=puzzle[i][j];
            if(puzzle[i][j]>0){
                if(isSafeOriginal(N, puzzle, i, j, puzzle[i][j])==0){
                    return 0;
                }
            }
        }
    }
    return 1;
}



int isNumber(char* inputString)
{

    //go through each character
    //location in the array until
    //we reach the null character (end of input)
    for (int i = 0; inputString[i]!='\000'; i++)
    {
        if(isdigit(inputString[i])==0)//if the current character is not a digit....
            return 0; //return false and end function here

    }

    return 1;//return true since the entire array contained numeric characters
}



// Checks whether it is 'legal' to assign num to the given row, col  0 4
int isSafe(int N,int puzzle[N][N], int row, int col, int num)
{

    // If we find the same number in the same row , we return 0
    for (int x = 0; x <= N-1; x++)
        if (puzzle[row][x] == num){
            //printf("same row");
            return 0;
        }


    //If we find the same num in the same column , we return 0
    for (int x = 0; x <= N-1; x++)
        if (puzzle[x][col] == num)
            return 0;

    //If we find the same num in the small submatrix, we return 0
    int sq=sqrt(N);
    int startRow = row - row % sq, startCol = col - col % sq;

    for (int i = 0; i < sq; i++)
        for (int j = 0; j < sq; j++)
            if (puzzle[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}


/* This function takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
int solveSudoku(int N, int puzzle[N][N], int row, int col)
{

    // Check if we have reached the (N-1)th row
    // and Nth column (0
    // indexed matrix) , we are
    // returning true to avoid
    // further backtracking
    if (row == N - 1 && col == N)
        return 1;

    //  Check if column value  becomes N,
    //  we move to next row and
    //  column start from 0
    if (col == N)
    {
        row++;
        col = 0;
    }

    // Check if the current position
    // of the grid already contains
    // value >0, we iterate for next column
    if (puzzle[row][col] > 0)
        return solveSudoku(N,puzzle, row, col + 1);

    for (int num = 1; num <= N; num++)
    {

        // Check if it is safe to place
        // the num (1-N)  in the
        // given row ,col  ->we move to next column
        if (isSafe(N,puzzle, row, col, num)==1)
        {
            /* assigning the num in the
               current (row,col)
               position of the grid
               and assuming our assigned num
               in the position
               is correct     */
            puzzle[row][col] = num;

            //  Checking for next possibility with next
            //  column
            if (solveSudoku(N, puzzle, row, col + 1)==1)
                return 1;
        }

        // Removing the assigned num ,
        // since our assumption
        // was wrong , and we go for next
        // assumption with
        // diff num value
        puzzle[row][col] = 0;
    }
    return 0;
}







int main()
{
    int N;
    printf("Welcome to Sudoku Solver! What size puzzle will we be solving today?");
    printf("\nPress 1-Size 9x9");
    printf("\nPress 2-Size 16x16");
    printf("\nAny other key will terminate the program. \n");
    char x;
    scanf("%c",&x);
    if(x=='1'){
        N=9;
    }else if(x=='2'){
        N=16;
    }else{
        return 0;
    }

    int grid[N][N];


    return 0;

}
