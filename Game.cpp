#include "Game.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

/*Game() - sets up the game
         ask the user for board size, number of players, number of computer
         players. If the user enters 6 or more for the number of the computers
         asks for a new input.
         Calls makeBoard() and getPlayers().
         Randomly decides who starts the game
         starts game by calling playGame()
  input - none
  return - void*/
Game::Game() {
    // for non-automatized version – asks for board size, num players, num of computer players, and then initializes
    // everything
    
    srand(time(NULL)); //randomizes the random int
    //game set up - describes the game rules
    cout << "Dots & Boxes" << endl << "x - left to right" << endl << "y - top to bottom" << endl << "(0,0) top left corner" << endl << endl;
    cout << "Game Setup:" << endl;
    cout << "Board Size (3-11): ";
    cin >> size; //set board size from input
    cout << size << endl; //print input
    cout << "Number of Players (2-5): "; 
    cin >> numPlayers;
    cout << numPlayers << endl;
    cout << "Number of Computer Players: ";
    cin >> compplayers;
    cout << compplayers << endl;
    
    //check to ensure the computer input is less than the total number of players
    //or more than 5 inputs and asks user to input compplayers again
    while (compplayers > numPlayers || compplayers > 5) {
        cout << "Computer Players must be less than 5 and less than total players." << endl << "Try again: ";
        cin >> compplayers;
        cout << compplayers << endl;
    }

    makeBoard(); //generate the 2D array using the board size
    getPlayers(); //generate the players for the game
    turn = rand() % numPlayers; //randomly decide which player goes first
    won = false;
    playGame(); //start the game;
}

/*Game(bool b) - sets up the game
 *               when bool is true:
 *                  computer only game of 2 players
 *                  board size is random inbetween 3 & 11
 *                  set up the players
 *                  start the game - playGame()
 *               when false:
 *                  calls Game() function
  input - bool b
  return - void*/
Game::Game(bool b) {
    //for the automated version – if b is true, randomly generate the size of the board, set the num of players and the
    //num of compplayers to 2, and the, of course initialize everything
    
    //sets up the random number generator to be zero
    srand(time(NULL));
    
    if (b) {
        numPlayers = 2;
        compplayers = 2;
        size = rand() % 9 + 3;
        makeBoard();
        turn = rand() % numPlayers;
        won = false;
        getPlayers();
        playGame();
    } else {
        Game();
    }
}

/*makeBoard() - sets up the 2D array that is the board
 *              dynamically generates a square board of size by size
 *              each cell initally contains char 'c'
  input - none
  return - void*/
void Game::makeBoard() {
    //dynamically create an array of size size to store the addresses of the arrays
    board = new char*[size];
    
    //dynamically create arrays to store characters
    for (int i = 0; i < size; i++) {
        board[i] = new char[size]; //
    }
    //fill the arrays with char '.'
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '.';
        }
    }
}

/*printBoard() - prints the board
  input - none
  return - void
 */
void Game::printBoard() {
    //Note: I’m giving you this one
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j] << "   ";
        }
        cout << endl;
    }
}

/*getPlayers() - this method dynamically generates an array of players
 *               if the player is human:
 *                  ask for player name and assign it and ask for player character
 *               if the player is computer:
 *                  choose player name and character from array (only 5)
 *                  
 *               checks to make sure computer character is different than the existing characters in the game
 *               if human inputs existing character, ask for new one
 *              
  input - none
  return - void
 */
void Game::getPlayers() {
    //This method dynamically generates an array of players, and then, for each element in the array, creates a new
    //player object with a name and a character. For the number of players that are computers, I used an array of names
    // and an array of characters, and then just selected the next name and character in the list for my player object.
    // for humans I called the Player constructor with no input parameters (that one asked the user for their name and
    // their preference character.
    string compnames[5] = {"Computer1", "Computer2", "Computer3", "Computer4", "Computer5"}; //list of computer player names
    char playerChar[5] = {'o', 'x', '*', '#', '@'}; //list of computer player characters
    players = new Player*[numPlayers]; //dynamically creates an array of players
    int addedPlayers = 0; //count the number of players that have been added to the array
    //while loop to add all human players
    while (addedPlayers < numPlayers - compplayers) { //numPlayers - compplayers is the number of human players
        players[addedPlayers] = new Player();
        cout << "What is player's name?" << endl;
        cin >> players[addedPlayers]->name;
        cout << players[addedPlayers]->name << endl;
        
        int count = 0;
        bool tf1;
        do { //do while loop makes sure all characters in game are different
            if (count == 0) { //first time asking for character
                cout << "What is player's character?" << endl;
            } else { //multiple times asking for character
                cout << "Character Taken. Insert New Character" << endl;
            }
            
            cin >> players[addedPlayers]->c; //input character
            cout << players[addedPlayers]->c << endl; //print character
            tf1 = false; //reset bool to false after choosing new character 
            //iterate through all players characters and check if the characters are the same
            //if characters are the same bool becomes true and ask for new character
            for (int i = 0; i < addedPlayers; i++) {
                if (players[i]->c == players[addedPlayers]->c) {
                    tf1 = true;
                }
            }
            count++;
        } while (tf1);

        addedPlayers++;
    }
    //add computers to list
    while (addedPlayers < (numPlayers)) {
        players[addedPlayers] = new Player();
        players[addedPlayers]->name = compnames[addedPlayers - (numPlayers - compplayers)];
        players[addedPlayers]->isComputer = true;

        int val = -1;
        char tempchar;
        bool tf;
        //choose character from computer character list and ensure character is
        //different than characters already in the game
        do {
            tempchar = playerChar[val + 1];
            tf = false;
            for (int i = 0; i < addedPlayers; i++) {
                if (players[i]->c == tempchar) {
                    tf = true;
                    val++;
                }
            }
        } while (tf);
        players[addedPlayers]->c = tempchar;
        addedPlayers++;
    }
    //print out all the players
    cout << endl << "Players:" << endl;
    printPlayers();

}

/*printPlayers() - prints the players names and character separated by a dash
  input - none
  return - void
 */
void Game::printPlayers() {
    for (int i = 0; i < (numPlayers); i++) {
        cout << players[i]->name << " - " << players[i]->c << endl;
    }
}

/*playGame() -  game play
 *              loops for each turn till board is full
 *              prints board
 *              asks user where they want to place their piece; computer random space generated
 *              checks to ensure space is available for play
 *                  if it is, character is placed
 *                      checks to see if a square was completed
 *                          if square completed player gets another turn, get a point
 *                          if square not completed next players turn
 *                  if space unavailable, asks user to choose new space, new random space is generated for computer
 * 
  input - none
  return - void
 */
void Game::playGame() {
    //This is the heart of the game. I called this method directly from my Game constructor(s) as the very last thing.
    //This method loops until the board is full.
    // In each loop, the next player either chooses where to place their character (if human) or the x,y coordinates are
    // randomly generated (and checked to make sure the player isn’t overwriting a piece already on the board).
    //It checks to see if the new piece completes a square, and, if so, that player’s score goes up by 1 and that player
    // takes another turn. At the end of each round, the board is printed out and each player’s name and score is printed.
    //Your code goes here
    
    int moves = size*size; //total number of moves in the game
    int x = 0; //initialize coordinates
    int y = 0;
    cout << endl << "Start Game!";
    
    //loops until there aren't anymore moves
    while (moves > 0) {
        cout << endl;
        printBoard();
        cout << endl;
        cout << players[turn % numPlayers]->name << "'s turn." << endl; //print who's turn it is
        
        //moves for human vs computer
        if (!(players[turn % numPlayers]->isComputer)) { //player is human
            cout << "choose x: "; //ask player for x coordinate
            cin >> x;
            cout << x;
            cout << " choose y: "; //ask player for y coordinate
            cin >> y;
            cout << y << endl;
            
            //loops until move is allowed (space isn't already occupied)
            while (moveTaken(x, y)) { //move is unavailable
                cout << "choose new x: ";
                cin >> x;
                cout << x;
                cout << " choose new y: ";
                cin >> y;
                cout << y << endl;
            }
            placeMove(x, y, players[turn % numPlayers]); //place the players character at their position
        } else { //player is computer
            findMoves(players[turn % numPlayers]); //generate moves
        }
        
        //print the score for all players at the end of the round
        cout << "Score:" << endl; 
        for (int i = 0; i < numPlayers; i++) {
            cout << players[i]->name << ": " << players[i]->score << endl;
        }
        moves--; //decrease move by 1
    }
    
    //end of game - no more moves
    won = true;
    cout << endl;
    printBoard(); //print the final board
    cout << endl << "GAME OVER!!" << endl;

    //print the winners
    getWinner();



    //Note: for the extra credit version, the findMoves method returns a dynamically created array of 3 different moveLists.
    // The first of the 3 contains the list of moves that would complete a square. The second of the 3 contains a list of
    // neutral moves, and the third of the 3 contains the list of moves that place a third corner on a square (which are bad
    // moves because the next player will then be able to complete a square.
    // In this version, the next move is chosen by first trying to pick (randomly) among potential moves that would
    // complete a square, and then by trying to pick a move that is, in essence, neutral, and then last, it chooses from the
    // list of bad moves as a last resort.

}

/*findMoves(Player *p) - generates random x,y coordinates  until an availiable moveis found
 *                       and places the move on the board
  input - Player - current player in the game
  return - void
 */
void Game::findMoves(Player *p) {
    // Regular version, this method continues to generate random x,y values until that cell on the
    // board is empty, then places the player's character v on the board, and checks to see if a
    // square is completed using checkFour.
    int x = rand() % size;
    int y = rand() % size;
    while (moveTaken(x, y)) {
        x = rand() % size;
        y = rand() % size;
    }
    cout << "x: " << x << "  y: " << y << endl;
    placeMove(x, y, p);
}

/*moveTaken(int, int) - checks to see if the character on the board is '.' indicating available
 *                      also checks to ensure the coordinate is within the board
  input - int x - x coordinate
 *        int y - y coordinate
  return - bool
 *         true - coordinate not within board or coordinate already occupied
 *         false - move is available
 */
bool Game::moveTaken(int x, int y) {
    //returns true if space is occupied
    //returns false if space is free
    if (x >= size || y >= size) { //ensures input is within board size
        return true;
    }
    if (board[y][x] == '.') { //checks to see if a players character occupies the cell
        return false;
    } else {
        return true;
    }
}

/*placeMove(int, int, Player) - puts the players character at the specified 
 *                              coordinate and increases players score if the
 *                              placement completes a square. If it doesn't turn
 *                              is increased.
  input - int x - x coordinate
 *        int y - y coordinate
 *        Player* p - pointer to player
  return - void
 */
void Game::placeMove(int x, int y, Player *p) {
    board[y][x] = p->c;
    if (checkFour(x, y)) {
        (p->score)++;
    } else {
        turn++;
    }
}

// movesList * Game::findMoves(char v) {
// The extra credit version of this method – this method dynamically creates a list of 3 movesList objects. It then goes
// through the entire board and classifies each possible move left on the board as being either good (will complete a
// square, in which case it’s added to the new list of movesLists at [0], neutral (doesn’t do anything), in which it’s
// added to the second of the movesLists, or bad (3/4 of a square), in which case it’s added to the third of the
// movesLists.
// This method uses checkFour() method to determine whether a move is good, checkThree to determine if a move is
// bad, and if neither of those is true, then the move is considered neutral.
// This method returns the list of three movesList objects.
//}

/*checkFour(int, int) - checks to see if placing a piece at a coordinate will make a square
  input - int x - x coordinate
 *        int y - y coordinate
  return - bool
 *         true - square complete
 *         false - doesn't complete a square
 */
bool Game::checkFour(int x, int y) {
    // this method checks to see if placing a piece at x and y on the board will complete a square, and, if so, it
    // returns true. Otherwise it returns false.
    if (x == 0) {
        if (y == 0) { //top left corner
            return checkDownRight(x, y);
        } else if (y == (size - 1)) { //bottom left corner
            return checkUpRight(x, y);
        } else { //left edge
            return (checkUpRight(x, y) || checkDownRight(x, y));
        }
    } else if (x == (size - 1)) {
        if (y == 0) { //top right corner
            return checkDownLeft(x, y);
        } else if (y == (size - 1)) { //bottom right corner
            return checkUpLeft(x, y);
        } else { // right edge
            return ((checkUpLeft(x, y)) || (checkDownLeft(x, y)));
        }
    } else if (y == 0) { //top edge (no corners)
        return (checkDownLeft(x, y) || checkDownRight(x, y));
    } else if (y == (size - 1)) { //bottom edge
        return (checkUpRight(x, y) || checkUpLeft(x, y));
    } else { //anywhere in the middle
        return (checkUpRight(x, y) || checkUpLeft(x, y) || checkDownLeft(x, y) || checkDownRight(x, y));
    }
}

/*getWinner() - determines and prints the winners
  input - none
  return - void
 */
void Game::getWinner() {
    // This method determines which of the players in the array of Players has the highest score, and prints out 
    // that player’s name and their score.
    int highscore = 0; // initialize high score
    
    //determine what the highscore of the game is
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->score > highscore) {
            highscore = players[i]->score;
        }
    }

    cout << "High Score: " << highscore << endl << "Winner(s):" << endl;
    
    //print out all players with the high score - code necessary for tie
    for (int i = 0; i < numPlayers; i++) {  
        if (players[i]->score == highscore) {
            cout << players[i]->name << endl;
        }
    }
}


//bool Game::checkThree(int x, int y) {
// Only needed for Extra Credit
// This method determines whether placing a piece on the board at x and y will complete ¾ of a square and, if so, it
// returns true. Otherwise it returns false.
//}

/*checkDownLeft(int x, int y) - checks to see if square is complete when coordinate
 *                  is in upper Right Hand corner of square
  input - int x - x coordinate
 *        int y - y coordinate
  return - bool
 *         true - square complete
 *         false - doesn't complete a square
 */
bool Game::checkDownLeft(int x, int y) {
    if ((board[y + 1][x - 1] != '.')&&(board[y + 1][x] != '.')&&(board[y][x - 1] != '.')) {
        return true;
    } else {
        return false;
    }
}

/*checkDownRight(int x, int y) - checks to see if square is complete when coordinate
 *                  is in upper Left Hand corner of square
  input - int x - x coordinate
 *        int y - y coordinate
  return - bool
 *         true - square complete
 *         false - doesn't complete a square
 */
bool Game::checkDownRight(int x, int y) {
    if ((board[y + 1][x + 1] != '.')&&(board[y + 1][x] != '.')&&(board[y][x + 1] != '.')) {
        return true;
    } else {
        return false;
    }
}

/*checkUpRight(int x, int y) - checks to see if square is complete when coordinate
 *                  is in lower left Hand corner of square
  input - int x - x coordinate
 *        int y - y coordinate
  return - bool
 *         true - square complete
 *         false - doesn't complete a square
 */
bool Game::checkUpRight(int x, int y) {
    if ((board[y - 1][x + 1] != '.')&&(board[y - 1][x] != '.')&&(board[y][x + 1] != '.')) {
        return true;
    } else {
        return false;
    }
}

/*checkUpLeft(int x, int y) - checks to see if square is complete when coordinate
 *                  is in lower Right Hand corner of square
  input - int x - x coordinate
 *        int y - y coordinate
  return - bool
 *         true - square complete
 *         false - doesn't complete a square
 */
bool Game::checkUpLeft(int x, int y) {
    if ((board[y - 1][x - 1] != '.')&&(board[y - 1][x] != '.')&&(board[y][x - 1] != '.')) {
        return true;
    } else {
        return false;
    }
}