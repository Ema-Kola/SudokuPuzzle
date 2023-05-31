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
