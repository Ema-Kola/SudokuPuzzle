#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

/* A function to print the matrix containing the puzzle */
void print(int N, int arr[N][N])
{
    int i, j;
    int sq=sqrt(N);
    if(N==9)
        printf("-------------------------------------\n");
    else
        printf(" ---------------------------------------------------------------\n");
        
     for (i = 0; i < N; i++)
      {
          printf("|");
          for (j = 0; j < N; j++){
              printf("%d\t",arr[i][j]);
              if (((j+1)%sq)==0)
              {
                  printf("|");
              }
          }
              
              
         printf("\n");
          if(((i+1)%sq)==0)
          {
              if(N==9)
                  printf("-------------------------------------\n");
              else
                  printf(" ---------------------------------------------------------------\n");
          }
       }
}



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

void terminalInput(int N, int grid[N][N]){
    char input[50]; //string used to store user input
    int  inputAsAnInteger;//used store the converted input  as an integer
    
    while(1){//loop 'infinitely'{
        printf("Enter the puzzle (entering 'e' will terminate the program): \n");
        int flag=1;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                
                scanf("%s",input);//get input from user
                if(strcmp(input, "e")==0){
                    return;
                }
                inputAsAnInteger=atoi(input);//convert input to integer
                if (!isNumber(input))//if the input is not a number......
                {
                    flag=0;
                }
                else//input is a number
                {
                    inputAsAnInteger=atoi(input);//convert input to integer
                    if(inputAsAnInteger<0 || inputAsAnInteger>N){
                        flag=0;
                    }else{
                        grid[i][j]=inputAsAnInteger;
                        
                    }
                }
            }
        }
        if(flag==1 && isValidOriginal(N, grid)==1){
            break;
        }else{
            printf("\nInvalid input entered. If you do not want to reenter the puzzle press 'e' \n");
        }
    }

    printf("\nThe puzzle you entered: \n");
    print(N, grid);
    printf("\nIs this the correct puzzle?\n\
If the puzzle is correct, press 1.\n\
If you want to reenter the information, press 0.\n\
Any other key will end the program. \n\
    ");
    
    int x;
    scanf("%d", &x);
    if(x==1){
        if (solveSudoku(N,grid, 0, 0)==1){
            printf("\nThis is your solved puzzle: \n");
            print(N,grid);
            return;
        }else{
            printf("\nNo solution exists. ");
            return;
        }
    }else if(x==0){
           terminalInput(N, grid);
    }else{
            return;
    }
}


void testing9x9(){
    int N=9;
    int grid[9][9]={{3, 0, 6, 5, 0, 8, 4, 0, 0},
{5, 2, 0, 0, 0, 0, 0, 0, 0},
{0, 8, 7, 0, 0, 0, 0, 3, 1},
{0, 0, 3, 0, 1, 0, 0, 8, 0},
{9, 0, 0, 8, 6, 3, 0, 0, 5},
{0, 5, 0, 0, 9, 0, 6, 0, 0},
{1, 3, 0, 0, 0, 0, 2, 5, 0},
{0, 0, 0, 0, 0, 0, 0, 7, 4},
{0, 0, 5, 2, 0, 6, 3, 0, 0}
};
    int s=solveSudoku(N,grid,0,0);
    int sureSolution[9][9]={{3,1,6,5,7,8,4,9,2},
{5,2,9,1,3,4,7,6,8},
{4,8,7,6,2,9,5,3,1},
{2,6,3,4,1,5,9,8,7},
{9,7,4,8,6,3,1,2,5},
{8,5,1,7,9,2,6,4,3},
{1,3,8,9,4,7,2,5,6},
{6,9,2,3,5,1,8,7,4},
{7,4,5,2,8,6,3,1,9}};
    int test=0;
    for(int i=0; i<N;i++)
    {
        for(int j=0; j<N;j++)
        {
            if (grid[i][j]!=sureSolution[i][j])
                test=1;
        }
    }
    if (test==0)
        printf("Test passed for 9x9 puzzle.");
    else
        printf("Test failed for 9x9 puzzle.");
    return;

}



void testing16x16()
{
    int N=16;
    int grid[16][16]= {{1,0,0,2,3,4,0,0,12,0,6,0,0,0,7,0},
 {0,0,8,0,0,0,7,0, 0,3,0,0,9,10,6,11 },
 {0,12,0,0,10,0,0,1,0,13,0,11,0,0,14,0},
 {3,0,0,15,2,0,0,14,0,0,0,9,0,0,12,0},
 {13,0,0,0,8,0,0,10,0,12,2,0,1,15,0,0},
 {0,11,7,6,0,0,0,16,0,0,0,15,0,0,5,13},
 {0,0,0,10,0,5,15,0,0,4,0,8,0,0,11,0},
 {16,0,0,5,9,12,0,0,1,0,0,0,0,0,8,0},
 {0,2,0,0,0,0,0,13,0,0,12,5,8,0,0,3},
 {0,13,0,0,15,0,3,0,0,14,8,0,16,0,0,0},
 {5,8,0,0,1,0,0,0,2,0,0,0,13,9,15,0},
 {0,0,12,4,0,6,16,0,13,0,0,7,0,0,0,5},
 {0,3,0,0,12,0,0,0,6,0,0,4,11,0,0,16},
 {0,7,0,0,16,0,5,0,14,0,0,1,0,0,2,0},
 {11,1,15,9,0,0,13,0,0,2,0,0,0,14,0,0},
 {0,14,0,0,0,11,0,2,0,0,13,3,5,0,0,12},
 };
    int s=solveSudoku(N,grid,0,0);
    int sureSolution[16][16]={{1,5,10,2,3,4,9,11,12,16,6,14,15,13,7,8},
 {14,16,8,13,5,15,7,12,4,3,1,2,9,10,6,11 },
 {9,12,4,7,10,16,6,1,8,13,15,11,3,5,14,2},
 {3,6,11,15,2,13,8,14,7,5,10,9,4,16,12,1},
 {13,4,14,3,8,7,11,10,5,12,2,6,1,15,16,9},
 {8,11,7,6,4,1,2,16,9,10,14,15,12,3,5,13},
 {12,9,1,10,13,5,15,6,3,4,16,8,14,2,11,7},
 {16,15,2,5,9,12,14,3,1,11,7,13,10,6,8,4},
 {6,2,16,14,11,9,4,13,15,1,12,5,8,7,10,3},
 {7,13,9,1,15,2,3,5,11,14,8,10,16,12,4,6},
 {5,8,3,11,1,10,12,7,2,6,4,16,13,9,15,14},
 {15,10,12,4,14,6,16,8,13,9,3,7,2,11,1,5},
 {2,3,5,8,12,14,10,15,6,7,9,4,11,1,13,16},
 {10,7,13,12,16,3,5,9,14,8,11,1,6,4,2,15},
 {11,1,15,9,6,8,13,4,16,2,5,12,7,14,3,10},
 {4,14,6,16,7,11,1,2,10,15,13,3,5,8,9,12}
};
int test=0, failpos[N][N];
    for(int i=0; i<N;i++)
    {
        for(int j=0; j<N;j++)
        {
            if (grid[i][j]!=sureSolution[i][j]){
                test=1;

                }
        }
    }
    if (test==0)
        printf("Test passed for 16x16 puzzle.");
    else
        printf("Test failed for 16x16 puzzle.");
    return;}

int main()
{
	//if you want to test the 2 main solving features remove the two 
	//below
    //testing9x9();
    //testing16x16();

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
    terminalInput(N,grid);


    return 0;

}
