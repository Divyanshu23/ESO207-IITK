#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define mod 1000000007           // Used if at any instant during multiplication, the value gets out of bounds of signed integer
/*
 * Structure   : Cell
 * -------------------------------
 *   Used to store each cell's content of sparse matrix
 *
 *   int val   : Value of cell
 *   int rc    : Row Index or Column Index depending on what is stored for that matrix
 *   Cell* next: Pointer to next cell
 */
typedef struct Cell {
    int val;
    int rc;
    struct Cell* next;
} Cell;

/*
 * Structure              : RowColPointer
 * -------------------------------
 *   Used to store pointer to a row or column as the case may be 
 *
 *   int index            : Row index or Column index
 *   Cell* right          : Pointer to first non-zero element at row number 'index' or column number 'index'
 *   RowColPointer* bottom: Pointer to next cell
 * 
 * Matrices are stored as follows (Zero values are not stored):
 * Matrix1:                                             Matrix2:
 *                                                          
 * Row1 --> x 0 0                                       Col1 --> 0 x 0
 * Row3 --> 0 0 x                                       Col2 --> x x 0
 * Row6 --> 0 x x                                       Col4 --> 0 0 x
 * (In the above ex, Row 2 and 5 are not               (In the above ex, Col 3 and 5 are not
 * stored because of all 0 values in thesm)             stored because of all 0 values in them)
 * 
 * First Matrix is stored such that each row contains a linked list of row elements
 * Second Matrix is stored such that each column contains a linked list of column elements
 */
typedef struct RowColPointer {
    int index;
    Cell* right;
    Cell* round;
    struct RowColPointer* bottom;
} RowColPointer;

/*
 * Function : createCell
 * ---------------------------------
 * Creates a cell of matrix and returns pointer to it
 *
 *   int rc : Row index or Column index depending on what is being stored for that matrix
 *   int val: Cell Value
 * 
 *   returns       : Pointer to created Cell
 */
Cell* createCell(int rc, int val) {
    Cell* temp = (Cell*)malloc(sizeof(Cell));
    *temp = (Cell){.rc = rc, .val = val, .next = NULL};
    return temp;
}

/*
 * Function             : multiply
 * -------------------------------
 * Multiplies two sparse matrices and returns the result.
 *
 *   RowColPointer* mat1: First Matrix
 *   RowColPointer* mat2: Second MAtrix
 *
 *   returns            : Resultant Sparse Matrix
 */
RowColPointer* multiply(RowColPointer* mat1, RowColPointer* mat2) {
    RowColPointer* res = NULL;                                     // Resultant Matrix                 
    int val;                                                       // Stores result as val += mat1[i][k]*mat2[k][j] sum over k

    Cell* curr1;                                       
    Cell* curr2;               

    RowColPointer* currRowRes = NULL;                              // Current Row of the res matrix being processed                 
    Cell* currCellRes;                                             // The last inseted cell in the current row of res matrix

    RowColPointer* mat2Iterator;                                   // Used to iterate over each col of mat2. For mat1, we
                                                                   // directly use mat1 to iterate
    while (mat1 != NULL) {
        mat2Iterator = mat2;
        while (mat2Iterator != NULL) {
            curr1 = mat1->right;
            curr2 = mat2Iterator->right;
            val = 0;

            while (curr1 != NULL && curr2 != NULL) {
                if(curr1->rc == curr2->rc) {                               // Product shall be only taken when col index of current row
                    val = (val + ((curr1->val)*(curr2->val))%mod)%mod;     // of mat1 is same as row index of current col of mat2
                    curr1 = curr1->next;                   
                    curr2 = curr2->next;
                } else if(curr1->rc < curr2->rc) 
                    curr1 = curr1->next;
                else
                    curr2 = curr2->next;
            }

            if(val != 0) {
                if(currRowRes == NULL) {                                        // This is the case of first element being               
                    currRowRes = (RowColPointer*)malloc(sizeof(RowColPointer)); // inserted to res matrix
                    *currRowRes = (RowColPointer){.index = mat1->index, .right = NULL, .round = NULL, .bottom = NULL};
                    res = currRowRes;
                    currRowRes->right = createCell(mat2Iterator->index, val);
                    currCellRes = currRowRes->right;
                } else if(currRowRes->index == mat1->index) {                   // Case when the next item is to be inserted in the
                    currCellRes->next = createCell(mat2Iterator->index, val);   // current row of res matrix
                    currCellRes = currCellRes->next;
                } else {                                                        // Case when a new row is to be created and then the
                    currRowRes->bottom = (RowColPointer*)malloc(sizeof(RowColPointer));    // item needs to be inserted
                    currRowRes = currRowRes->bottom;
                    *currRowRes = (RowColPointer){.index = mat1->index, .right = NULL, .round = NULL, .bottom = NULL};
                    currRowRes->right = createCell(mat2Iterator->index, val);
                    currCellRes = currRowRes->right;
                }
            }
            mat2Iterator = mat2Iterator->bottom;
        }
        mat1 = mat1->bottom;
    }
    return res;
}

/*
 * Function       : printMatrix
 * ----------------------------------
 *  Prints the matric in format: row, column, non-zero value
 *
 *  RowColPointer* mat      : Sparse Matrix
*/
void printMatrix(RowColPointer* mat) {
    if(mat == NULL) {
        printf("NULL MATRIX!\n");
        return;
    }
    
    Cell* curr;
    while (mat != NULL) {
        curr = mat->right;
        while (curr != NULL)
        {
            printf("%d %d %d\n", mat->index+1, curr->rc+1, curr->val);
            curr = curr->next;
        }
        mat = mat->bottom;
    }
}

int main() {
    unsigned int n;
    scanf("%u", &n);

    RowColPointer* mat1 = NULL;
    RowColPointer* mat2 = NULL;

    RowColPointer* currRow = mat1;        // The current row of mat1 being processed
    Cell* currCell = NULL;                // Last inserted cell in curr row of mat1

    RowColPointer* currCol = mat2;        // Used to traverse along cols of mat2 to determing in which col the next item will be inserted

    int matNo;
    int row, col;
    int val;

    // For matrix 1, we maintain a Linked List of Rows where each Row points to a linked list of elements in that row
    // For matrix 2, we maintain a Linked List of Columns where each Column points to a linked list of elements in that Column
    // This is done because for first matrix, we need to travel along row and for second matrix, we need to travel along column
    while (true) {
        scanf("%d",&matNo);
        if(matNo == 1) {
            scanf("%d %d %d",&row, &col, &val);

            if(currRow == NULL || currRow->index != row-1) {
                if(currRow == NULL) {                                   // Case of first insertion in mat1
                    currRow = (RowColPointer*)malloc(sizeof(RowColPointer));
                    *currRow = (RowColPointer){.index = row-1, .right = NULL, .round = NULL, .bottom = NULL};
                    mat1 = currRow;
                } else {                                                // Case when next item shall be inserted by creating a row below
                    currRow->bottom = (RowColPointer*)malloc(sizeof(RowColPointer));  // and then adding to it
                    currRow = currRow->bottom;
                    *currRow = (RowColPointer){.index = row-1, .right = NULL, .round = NULL, .bottom = NULL};
                }
                currRow->right = createCell(col-1, val);
                currCell = currRow->right;
            } else {                                                    // Case when next item is to be inserted in curr row of mat1
                currCell->next = createCell(col-1, val);
                currCell = currCell->next;
            }
        } else if(matNo == 2) {
            scanf("%d %d %d",&row, &col, &val);

            currCol = mat2;
            while (currCol != NULL && currCol->bottom != NULL && currCol->bottom->index < col-1) {  //This traversal to determine 
                currCol = currCol->bottom;                                                          //the col where the next item will   
            }                                                 // be inserted can be avoided by creating a unordered_set of RowColPointer

            if(currCol == NULL) {                                                   // Case of first insertion in mat2
                currCol = (RowColPointer*)malloc(sizeof(RowColPointer));
                *currCol = (RowColPointer){.index = col-1, .right = NULL, .round = NULL, .bottom = NULL};
                mat2 = currCol;
                currCol->right = createCell(row-1, val);
                currCol->round = currCol->right;
            } else if(currCol != NULL && currCol->index == col-1) {                  // Case of insetion in curr Col
                currCol->round->next = createCell(row-1, val);
                currCol->round = currCol->round->next;
            } else if(currCol->bottom != NULL && currCol->bottom->index == col-1) {  // Case of insertion in column ahead of curr Col
                currCol = currCol->bottom;
                currCol->round->next = createCell(row-1, val);
                currCol->round = currCol->round->next;
            } else{                                                                  // Case of insertion between curr col and col ahead
                RowColPointer* temp = currCol->bottom;                               // of curr col
                currCol->bottom = (RowColPointer*)malloc(sizeof(RowColPointer));
                currCol = currCol->bottom;
                *currCol = (RowColPointer){.index = col-1, .right = NULL, .round = NULL, .bottom = temp};
                currCol->right = createCell(row-1, val);
                currCol->round = currCol->right;
            }
        } else break;
    }

    RowColPointer* res = multiply(mat1, mat2);
    printMatrix(res);
    return 0;
}