#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
 



 
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
