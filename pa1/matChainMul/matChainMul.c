#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
unsigned int cost (
    unsigned int matrixCount,
    unsigned int* rowSizes,
    unsigned int* colSizes
) {
    if ( matrixCount==1 ) { // Base case.
        return 0; // No multplication to be done.
    } else {

        unsigned int numPossibleSplits = matrixCount-1; // Think: if there are two matrices to multiply, there is one way to split.
        // AB: (A)(B)
        // ABC: (A)(BC) and (AB)(C)

        unsigned int costs[numPossibleSplits];
        for ( unsigned int split=0; split<numPossibleSplits; split++ ) {

            unsigned int l = rowSizes[0];
            assert ( colSizes[split] == rowSizes[split+1] );//保证矩阵能相乘
            unsigned int m = colSizes[split];
            unsigned int n = colSizes[matrixCount-1];

            costs[split] =
                cost( split+1, rowSizes, colSizes ) + // cost of left subchain
                l * m * n + // cost of multiplying the two chains
                cost( matrixCount-split-1, rowSizes+split+1, colSizes+split+1 ); // cost of right subchain
        }

        unsigned int minCost = costs[0];
        for ( unsigned int split=1; split<numPossibleSplits; split++ ) {
            if ( costs[split]<minCost ) {
                minCost = costs[split];
            }
        }

        return minCost;
    }
}

int main(int argc, char* argv[]) {

    unsigned int matrixCount;
    unsigned int* rowSizes;
    unsigned int* colSizes;

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    if (!fscanf(fp, "%d\n", &matrixCount)) {
        perror("reading the number of matrices failed");
        exit(EXIT_FAILURE);
    }
    rowSizes = calloc( matrixCount, sizeof(int) );
    colSizes = calloc( matrixCount, sizeof(int) );
   unsigned int rows, cols;


int jieguo[INT8_MAX][INT8_MAX][INT8_MAX]; int jie=0;
    for (unsigned int matIndex=0; matIndex<matrixCount; matIndex++) {

         
        if (!fscanf(fp, "%d %d\n", &rows, &cols)) {
            perror("reading the dimensions of matrix failed");
            exit(EXIT_FAILURE);
        }
        int ma[rows][cols];
        
        rowSizes[matIndex] = rows;
        colSizes[matIndex] = cols;
        
        //printf("%d ",rows);printf("%d ",cols);
        for(int shu=0;shu<rows;shu++){
            
        
            for(int heng=0;heng<cols;heng++){
                int colnumber;
                fscanf(fp, "%d ", &colnumber);
                ma[shu][heng]=colnumber;
                
            }

            fscanf(fp, "\n");
            
        }
        
        
        
        
        if(matIndex==0){
           
            for(int r=0;r<rows;r++){
             for(int c=0;c<cols;c++){
                jieguo[jie][r][c]=ma[r][c];
          // printf("%d",jieguo[(jie)][r][c]);
            }}
        }
            

           
           
           

        if(matIndex>0){
            for(int r=0;r<rowSizes[0];r++){
                for(int c=0;c<cols;c++){
                    int sum=0;
                    for(int ro=0;ro<rows;ro++){
                    
                    sum = sum + jieguo[jie-1][r][ro]*ma[ro][c];
                    // printf("%d",jieguo[jie-1][r][ro]*ma[ro][c]);
                    }
                    jieguo[jie][r][c]=sum;
                }
            }
        }
    
    
     jie=jie+1;
    
    
    
    }

    printf("%d\n", cost(matrixCount, rowSizes, colSizes) );

   

    for(int i=0;i<rowSizes[0];i++){
       for(int j=0;j<colSizes[matrixCount-1];j++){
            printf("%d ",jieguo[jie-1][i][j]);
       }
        printf("\n");
    }

    free(colSizes);
    free(rowSizes);
    fclose(fp);

    exit(EXIT_SUCCESS);
}


