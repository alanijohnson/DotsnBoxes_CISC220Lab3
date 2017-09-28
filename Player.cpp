/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: Alani
 * 
 * Created on March 8, 2017, 7:41 PM
 */

#include <cstring>
#include "Player.hpp"
#include "cell.hpp"
using namespace std;
Player::Player() {
// constructor for an actual human, that uses cin to ask the user for their name and the character they want to
//use in the game, and initializes the name and c fields to the entered information. It also initializes score to 0, and 
//isComputer to false.
    score = 0;
    isComputer = false;
}
Player::Player(string n, char ic, bool x) {
// constructor that takes as input parameters a name string, a character ic, and a Boolean value x and sets the name,
//the c, and the isComputer fields accordingly. It initializes the score to 0
    name = n;
    c = ic;
    isComputer = x;
    score = 0;
            
}