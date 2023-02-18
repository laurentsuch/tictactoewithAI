#include <iostream>
#include <cstdlib>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);


/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
int checkForWinner(char grid[], int dim);


/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

/**
 * @brief Get the Ai Choice for the current player and update grid object
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If an error occurred or a choice was unable to be made
 * @return false If a play was successfully made
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player);

/**
 * @brief Picks a random location for the current player and update grid
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If no viable location to be played
 * @return false If a play was successfully made
 */
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player);


/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c)
{
    int gridEntryIndex;
    // mathematical formula to relate index number from row, column, dimension numbers
    gridEntryIndex = (dim * r) + c;
    
    return grid[gridEntryIndex];
}

int idxToRow(int idx, int dim)
{
    int rowNum;
    // returns row number from index and dimension
    rowNum = idx/dim;
    
    return rowNum;
}

int idxToCol(int idx, int dim)
{
    int colNum;
    // returns column number from index and dimension
    colNum = idx % dim;

    return colNum;
}

void printTTT(char grid[], int dim)
{
  // iterates through row and columns 
  int k = 0;
  for(int j = 0; j < dim; j++) {
    // iterates through each column 
    for(int i = 0; i < dim; i++) {
      // iterates through each row 
      char result = getEntryAtRC(grid, dim, j, i);
      // stores character in index through calling function 
      grid[k] = result;
      cout << " " << grid[k] << " ";
      if(idxToCol(k, dim) < dim -1) {
        cout << "|";
        // print out vertical lines
      }
      k++;
      
    }
    if(idxToRow(k, dim) < dim) {
      cout << endl;
      int numDashes = 3 + (4*(dim-1));
      for(int h = 0; h < numDashes; h++) {
        cout << "-";
        // print out dashes 
        // mathetmatical function for number of dashes depending on dimension 
      }
    }
    cout << endl;
  }
}

int checkForWinner(char grid[], int dim)
{
  //check rows
  int counter = 0;
  for(int i = 0; i < dim*dim; i += dim) {
			for(int j = 0; j < dim; j++) {
        // iterate through each index in each row 
        if(grid[i+j] == grid[i]) {
          counter++;
          if(counter == dim) {
            if(grid[i+j] == 'X') {
              return 1;
            }
            else if(grid[i+j] == 'O') {
              return 2;
            }
          }
        }
      }
    counter = 0;
  }
    //check columns 
    for(int i = 0; i < dim; i++) {
			for(int j = i; j < dim*dim; j=j+dim) {
        // iterate through each index in each col
        if(grid[i]== grid[j]) {
          counter++;
          if(counter == dim) {
            if(grid[i] == 'X') {
              return 1;
              // if there each index is same char, then win
            }
            else if(grid[i] == 'O') {
              return 2;
            }
          }
        }
      }
    counter = 0;
	}
  //check diagonal from right to left 
  for(int k = dim-1; k <(dim*dim)-1; k += (dim-1)) {
    if(grid[dim-1] == grid[k]) {
      counter++;
      if(counter == dim) {
        if(grid[k] == 'X') {
          return 1;
        }
        else if(grid[k] == 'O') {
          return 2;
        }
      }
    }
  }
  counter = 0;
  // check diagonal from left to right 
  for(int l = 0; l < dim*dim; l+= (dim+1)) {
    if(grid[0] == grid[l]) {
      counter++;
      if(counter == dim) {
        if(grid[l] == 'X') {
          return 1;
        }
        else if(grid[l] == 'O') {
          return 2;
        }
      }
      
    }
  }
  counter = 0;
  // if no win statement, then continue game
  if(counter == 0) {
    return 0;
  }
  return 0;
  


}

bool checkForDraw(char grid[], int dim)
{
  int counter = 0;
  int lastIndexNum = (dim*dim) - 1;
  // if there is an O or X in every index of array, then draw 
  for(int i = 0; i < lastIndexNum; i++){
    if(grid[i] != '?') {
      counter++;
      if(counter == lastIndexNum) {
        return true;
      }
    }
  }
  

  // check for an X and O in the rows
  int xCountRow = 0;
  int oCountRow = 0;
  int rowCount = 0;
  for(int i = 0; i < dim*dim; i += dim) {
			for(int j = 0; j < dim; j++) {
        if(grid[i+j] == 'X') {
          xCountRow++;
        }
        if(grid[i+j] == 'O') {
          oCountRow ++;
        }
        
      }
      if(xCountRow > 0 && oCountRow > 0) {
          rowCount = rowCount + 1;
        }
      xCountRow = 0;
      oCountRow = 0;
  }
  

  int colCount = 0;
  int xColCount = 0;
  int oColCount = 0;
  // check for an X or O in the columns 
  for(int k = 0; k < dim; k++) {
			for(int l = k; l < dim*dim; l=l+dim) {
        if(grid[l] == 'X') {
            xColCount++;
        }
        if(grid[l] == 'O') {
            oColCount++;
        }
    
      }
    if(xColCount > 0 && oColCount > 0) {
          colCount = colCount + 1;
        }
      xColCount = 0;
      oColCount = 0;
	}
  // if every row and every column have an X or O, then draw
  if(colCount == dim && rowCount == dim) {
    return true;
  }
  else {
    return false;
  }
}

bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player)
{
  //check for possible wins first
  
  // count row with most X's and Os
  int counter = 0;
  int gameWinIndex = 0;
  for(int i = 0; i < dim*dim; i += dim) {
			for(int j = 0; j < dim; j++) {
        if(grid[i+j] == player) {
          counter = counter + 1;
        }
        if(grid[i+j] == '?') {
          gameWinIndex = i+j;
        }
      }
    if(counter == (dim-1)) {
        grid[gameWinIndex] = player;
        return false;
    }
    counter = 0;
  }
  // check for possible win in columns 
  int countercolWin = 0;
  int gameColWinIndex = 0;
  for(int row = 0; row < dim; row++) {
    for(int col = row; col < dim*dim; col+=dim) {
        if(grid[col] == player) {
          countercolWin = countercolWin + 1;
        }
        if(grid[col] == '?') {
          gameColWinIndex = col;
        }
    }
    if(countercolWin == (dim-1)) {
      grid[gameColWinIndex] = player;
      return false;
    }
  countercolWin = 0;
  }

  
  // checking diagonal right to left 
  int counter2 = 0;
  int gameWinIndex2=0;
  for(int k = dim-1; k < (dim*dim)-1; k = k + (dim -1)) {
    if(grid[k] == player) {
      counter2 = counter2 + 1;
    }
    else if(grid[k] == '?') {
      gameWinIndex2 = k;
    }
  }
  if(counter2 == (dim-1)) {
    grid[gameWinIndex2] = player;
    return false;
  }  

  
  
  // checking diagonal from left to right
  int counter3 = 0;
  int gameWinIndex3=0;
  for(int m = 0; m < dim*dim; m = m + (dim+1)) {
    if(grid[m] == player) {
      counter3 = counter3 + 1;
    }
    else if(grid[m] == '?') {
      gameWinIndex3 = m;
    }
  }
  if(counter3 == (dim-1)) {
    grid[gameWinIndex3] = player;
    return false;
  }

  // CHECK FOR BLOCKS
 
  //check column for blocks
  int winCount = 0;
  int winCount2 = 0;
  int blockIndex=0;
  char blockPlayer;
  for(int r = 0; r < dim; r++) {
    for(int c = r; c < dim*dim; c+=dim) {
    
        if(grid[c] == 'O') {
          winCount = winCount + 1;
          blockPlayer = 'X';
        }
        if(grid[c] == 'X') {
          winCount2 = winCount2 + 1;
          blockPlayer = 'O';
        }
        if(grid[c] == '?') {
          blockIndex = c;
        }
    }
    if((winCount2 == (dim-1) && winCount == 0)) {
      grid[blockIndex] = blockPlayer;
      return false;
    }
    else if(winCount == (dim-1) && winCount2 == 0) {
      grid[blockIndex] = blockPlayer;
      return false;
    }
    winCount = 0;
    winCount2 = 0;
    

  }
  
return true;
}

// Complete...Do not alter
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player)
{
    int start = rand()%(dim*dim);
    // look for an open location to play based on random starting location.
    // If that location is occupied, move on sequentially until wrapping and
    // trying all locations
    for(int i=0; i < dim*dim; i++) {
        int loc = (start + i) % (dim*dim);
        if(grid[ loc ] == '?') {
            grid[ loc ] = player;
            return false;
        }
    }
    // No viable location
    return true;
}


/**********************************************************
 *  Complete the indicated parts of main(), below.
 **********************************************************/
int main()
{
    // This array holds the actual board/grid of X and Os. It is sized
    // for the biggest possible case (11x11), but you should only
    // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
    char tttdata[121];

    // dim stands for dimension and is the side length of the
    // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
    int dim;
    int seed;
    // Get the dimension from the user
    cin >> dim >> seed;
    srand(seed);

    int dim_sq = dim*dim;

    for(int i=0; i < dim_sq; i++) {
        tttdata[i] = '?';
    }

    // Print one of these messages when the game is over
    // and before you quit
    const char xwins_msg[] = "X player wins!";
    const char owins_msg[] = "O player wins!";
    const char draw_msg[] =  "Draw...game over!";

    bool done = false;
    char player = 'X';
    // Show the initial starting board
    printTTT(tttdata, dim);

    while(!done) {

        //**********************************************************
        // Get the current player's input (i.e. the location they want to
        // choose to place their mark [X or O]) or choice of AI or Random
        // location and update the tttdata array.
        // Be sure to follow the requirements defined in the guide/writeup
        // for quitting immediately if the user input is out-of-bounds
        // (i.e. not in the range 0 to dim_sq-1 nor -1 nor -2) as well as
        // continuing to prompt for an input if the user chooses locations
        // that have already been chosen (already marked with an X or O).
        //**********************************************************

        // Add your code here for getting input
        int userChoice; 
        int numberTotalIndices = (dim*dim) -1;
        cout << "Player " << player << " enter your square choice [0-" << numberTotalIndices << "], -1 (AI), or -2 (Random):";
        cout << endl;
        cin >> userChoice;
        // the index user chooses must be open and viable option 
        while(tttdata[userChoice] != '?' && userChoice >= 0 && userChoice <= numberTotalIndices) {
          cout << "Player " << player << " enter your square choice [0-" << numberTotalIndices << "], -1 (AI), or -2 (Random):";
          cout << endl;
          cin >> userChoice;
        }
        // given the user choice, do x
        if(userChoice >= 0 && userChoice <= numberTotalIndices) {
          tttdata[userChoice] = player;
        }
        if(userChoice == -1) {
          getAiChoiceAndUpdateGrid(tttdata, dim, player);
        }
        if(userChoice == -2) {
          getRandChoiceAndUpdateGrid(tttdata, dim, player);

        }
        if(userChoice < -2 || userChoice > numberTotalIndices) {
          break;
        }
        
        
        



        // Show the updated board if the user eventually chose a valid location
        // (i.e. you should have quit the loop and program by now without any
        //  other output message if the user chosen an out-of-bounds input).
        printTTT(tttdata, dim);

        //**********************************************************
        // Complete the body of the while loop to process the input that was just
        //  received to check for a winner or draw and update other status, as
        //  needed.
        //
        // To match our automated checkers' expected output, you must output
        // one of the messages defined above using *one* of the cout commands
        // (under the appropriate condition) below:
        //   cout << xwins_msg << endl;  OR
        //   cout << owins_msg << endl;  OR
        //   cout << draw_msg << endl;
        //
        // Note: Our automated checkers will examine a specific number of lines
        //  at the end of the program's output and expect to see the updated board
        //  and game status message.  You may certainly add some debug print
        //  statements during development but they will need to be removed to
        //  pass the automated checks.
        //**********************************************************
      int winner = checkForWinner(tttdata, dim);
      // if there is a winner, return according message for each player 
      if(winner == 1) {
        cout << xwins_msg << endl;
        done = true;
      }
      else if(winner == 2) {
        cout << owins_msg << endl;
        done = true;
      }
      // if there is a draw (function returns true), then print draw statement 
      if(checkForDraw(tttdata, dim)) {
        cout << draw_msg << endl;
        done = true;
      }
      
      // this switches the player at end of turn
      if( player == 'X') {
        player = 'O';
      }
      else {
        player = 'X';
      }

    } // end while
    return 0;
}
