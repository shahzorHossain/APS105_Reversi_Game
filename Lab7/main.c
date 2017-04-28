#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



int globalVariBoardDim;

void printBoard(char board[26][26], int n) {
    int i, j;


    printf("   "); //print Header
    for (i = 0; i < n; i++)
        printf("%c", i + 97);
    printf("\n");

    for (i = 0; i < n; i++) {

        printf("%c  ", i + 97); //print column
        for (j = 0; j < n; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }
}

void initializeBoard(char board[26][26], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == n / 2 - 1) { //1st default row
                if (j == n / 2 - 1)
                    board[i][j] = 'W';
                else if (j == n / 2)
                    board[i][j] = 'B';
                else
                    board[i][j] = 'U';
            } else if (i == n / 2) {//2nd defult row
                if (j == n / 2 - 1)
                    board[i][j] = 'B';
                else if (j == n / 2)
                    board[i][j] = 'W';
                else
                    board[i][j] = 'U';
            } else
                board[i][j] = 'U';
        }
    }

}

bool positionInBounds(int N, char row, char col) {
    return row >= 0 && row < N && col >= 0 && col < N;
}

bool checkLegalInDirection(char board[26][26], int N,
        char row, char col, char colour, int deltaRow,
        int deltaCol) {
    int counter = 0;
    bool flag = false;

    if (colour == 'W') {
        while (positionInBounds(N, row + deltaRow, col + deltaCol)) {
            if (board[row + deltaRow][col + deltaCol] == 'B') {
                row = row + deltaRow;
                col = col + deltaCol;
                counter++;
            } else if ((board[row + deltaRow][col + deltaCol] == 'W') &&
                    (counter > 0))
                return true;

            else // hit immediate 'W' or a 'U' ('U can also be after counts')
                break;
        }
    } else if (colour == 'B') {
        while (positionInBounds(N, row + deltaRow, col + deltaCol)) {
            if (board[row + deltaRow][col + deltaCol] == 'W') {
                row = row + deltaRow;
                col = col + deltaCol;
                counter++;
            } else if ((board[row + deltaRow][col + deltaCol] == 'B') &&
                    (counter > 0))
                return true;


            else // hit immediate 'B' or a 'U' ('U can also be after counts')
                break;
        }
    }

    return false;
}

int numFlips(char board[26][26], int row, int col, char colour) {



    int vertical, horizontal, horiz, vertic;
    int founddir[3][3] = {0};
    int OK[3][3] = {0};
    int counter = 0;
    int countFlips = 0;

    // vertical and horizontal are deltaRow and deltaCol


    for (vertical = -1; vertical <= 1; vertical++) {
        for (horizontal = -1; horizontal <= 1; horizontal++) {

            // end all directions
            if (horizontal == 0 && vertical == 0) {
                continue;
            }
            horiz = horizontal;
            vertic = vertical;

            // for that specific direction

            while (true) {
                if (!positionInBounds(globalVariBoardDim, row + vertic,
                        col + horiz)) {
                    break;
                }
                // if it is possible then add 1 to the array at that position

                if (board[row + vertic][col + horiz] == colour) {
                    OK[vertical + 1][horizontal + 1] = 1;
                    break;
                }
                // if it is possible start counting
                if (board[row + vertic][col + horiz] != colour) {
                    if (board[row + vertic][col + horiz] == 'U') {
                        founddir[vertical + 1][horizontal + 1] = 0;
                        break;
                    }
                    founddir[vertical + 1][horizontal + 1]++;
                }
                horiz += horizontal;
                vertic += vertical;
            }
            //skip vertical && horizontal==0
        }


    }

    // for all directions
    for (vertical = -1; vertical <= 1; vertical++) {
        for (horizontal = -1; horizontal <= 1; horizontal++) {
            // end all directions
            horiz = horizontal;
            vertic = vertical;
            if (horizontal == 0 && vertical == 0) {
                continue;
            }

            // checks if it is possible in that direction, and then if so
            // counts the number of tiles in that direction and adds 1 
            // to a counter variable
            if (OK[vertical + 1][horizontal + 1]) {
                for (counter = 0; counter < founddir[vertical + 1]
                        [horizontal + 1]; counter++) {
                    countFlips++;
                    horiz += horizontal;
                    vertic += vertical;
                }
            }
        }
    }

    // returns the counter variable
    return countFlips;

}

void flip(char board[26][26], int row, int col, char colour) {

    int counter = 0;
    int horizontal;
    int vertical;
    int horiz, vertic;
    int founddir[3][3] = {0};
    int OK[3][3] = {0};

    // for all directions
    // vertical and horizontal are deltaRow and deltaCol

    for (vertical = -1; vertical <= 1; vertical++) {
        for (horizontal = -1; horizontal <= 1; horizontal++) {
            // end all directions
            if (horizontal == 0 && vertical == 0) {
                continue;
            }
            horiz = horizontal;
            vertic = vertical;
            // for that specific direction
            while (true) {
                if (!positionInBounds(globalVariBoardDim, row + vertic,
                        col + horiz)) {
                    break;
                }
                // if it is possible then add 1 to the array at that position
                if (board[row + vertic][col + horiz] == colour) {
                    OK[vertical + 1][horizontal + 1] = 1;
                    break;
                }
                // if it is possible start counting
                if (board[row + vertic][col + horiz] != colour) {
                    if (board[row + vertic][col + horiz] == 'U') {
                        founddir[vertical + 1][horizontal + 1] = 0;
                        break;
                    }
                    founddir[vertical + 1][horizontal + 1]++;
                }
                horiz += horizontal;
                vertic += vertical;
            }
            //skip vertical && horizontal==0
        }
    }
    // for all directions
    for (vertical = -1; vertical <= 1; vertical++) {
        for (horizontal = -1; horizontal <= 1; horizontal++) {
            // end all directions
            horiz = horizontal;
            vertic = vertical;
            if (horizontal == 0 && vertical == 0) {
                continue;
            }
            //checks if it is possible in that direction, and then if so
            // flips the number of tiles in that direction
            if (OK[vertical + 1][horizontal + 1] == 1) {
                for (counter = 0; counter < founddir[vertical + 1]
                        [horizontal + 1]; counter++) {
                    board[row + vertic][col + horiz] = colour;
                    horiz += horizontal;
                    vertic += vertical;
                }
            }
        }
    }

}

int main() {

    int N;
    char board[26][26];
    int availB = 0;
    int availW = 0;
    int maxFlipsB, maxFlipsW;
    char prompt;

    int row;
    int col;

    int valid = 0;
    // ask for dimensions and storing it in global variable
    printf("Enter the board dimension: ");
    scanf("%d", &N);
    globalVariBoardDim = N;

    initializeBoard(board, N);

    //first turn always goes to B
    char turn = 'B';


    printf("Computer plays (B/W) : ");
    scanf(" %c", &prompt);

    printBoard(board, N);


    while (true) {



        int i, j, x, y;

        maxFlipsW = 0;
        maxFlipsB = 0;

        int rowW = -1;
        int colW = -1;
        int rowB = -1;
        int colB = -1;


        availW = 0;
        //i and j are variables that traverse through the rows and columns
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++) {

                //ignore if landed on a color
                if (board[i][j] == 'W' || board[i][j] == 'B')
                    continue;

                //x and y are deltaRow and deltaCol
                for (x = -1; x <= 1; x++)
                    for (y = -1; y <= 1; y++) {
                        //ignore if x and y are 0
                        if (x == 0 && y == 0)
                            continue;

                        if (checkLegalInDirection(board, N, i, j, 'W',
                                x, y)) {

                            //checks to see how current flips of W compares with
                            //the next number of tiles flipped in one direction
                            if (maxFlipsW < numFlips(board, i, j, 'W')) {
                                maxFlipsW = numFlips(board, i, j, 'W');
                                rowW = i;
                                colW = j;
                            }

                            availW++;
                            break;
                        }
                    }
            }



        availB = 0;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++) {

                //skip if landed on a color
                if (board[i][j] == 'W' || board[i][j] == 'B')
                    continue;
                for (x = -1; x <= 1; x++)
                    for (y = -1; y <= 1; y++) {

                        //skip if x and y are 0
                        if (x == 0 && y == 0)
                            continue;
                        if (checkLegalInDirection(board, N, i, j, 'B',
                                x, y)) {

                            //checks to see how current flips of B compares with
                            //the next number of tiles flipped in one direction
                            if (maxFlipsB < numFlips(board, i, j, 'B')) {
                                maxFlipsB = numFlips(board, i, j, 'B');
                                rowB = i;
                                colB = j;
                            }
                            availB++;
                            break;
                        }
                    }
            }

        int counterW = 0;
        int counterB = 0;

        // checks to see if there are any available move for either player
        //and starts counting if it's true

        if (availW == 0 && availB == 0) {

            for (row = 0; row < N; row++) {
                for (col = 0; col < N; col++) {

                    //checks the number of B in the board and adds it to counter
                    if (board[row][col] == 'B')
                        counterB++;

                        // does the same for W
                    else if (board[row][col] == 'W')
                        counterW++;
                }
            }

            //declares the winner after counting each counter and comparing

            if (counterB > counterW)
                printf("B player wins.");
            else if (counterW > counterB)
                printf("W player wins.");
            else if (counterW == counterB)
                printf("Draw.");

            return 0;
        }// checks to see if any player of the two has any available moves
            // and gives the turn to the other player

        else if (turn == 'W' && availW == 0) {
            turn = 'B';
            printf("W player has no valid move.\n");
            continue;
        } else if (turn == 'B' && availB == 0) {
            turn = 'W';
            printf("B player has no valid move.\n");
            continue;
        }
        char colour;
        colour = turn;

        char line[3];

        //if computer is W
        if (prompt != turn) {
            printf("Enter move for colour %c (RowCol) : ", turn);
            scanf("%s", line);

            row = (int) (line[0] - 'a');
            col = (int) (line[1] - 'a');

        } else {
            if (prompt == 'B') {
                row = rowB;
                col = colB;
                printf("Computer places B at %c%c.\n", rowB + 'a', colB + 'a');
            } else {
                row = rowW;
                col = colW;
                printf("Computer places W at %c%c.\n", rowW + 'a', colW + 'a');
            }
        }



        //checks for legal direction and flips it if true
        if (board[row][col] == 'U') {
            for (x = -1; x <= 1; x++) {
                for (y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) //skip if x and y are 0
                        continue;
                    if (checkLegalInDirection(board, N, row, col, colour, x, y)) {

                        board[row][col] = colour;
                        flip(board, row, col, colour);
                        turn = turn == 'W' ? 'B' : 'W';
                        printBoard(board, N);
                        //makes sure that the input by the player is valid
                        valid = 1;

                    } else
                        continue;
                }
            }
        }

        if (valid != 1) {
            printf("Invalid move.\n");
            if (turn == 'W')
                printf("B player wins.");
            else if (turn == 'B')
                printf("W player wins.");

            break;
        }

        // resets valid to 0 after each iteration of whole process
        valid = 0;

    }
    return 0;
}
