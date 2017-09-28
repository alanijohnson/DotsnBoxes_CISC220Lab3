/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cell.hpp
 * Author: Alani
 *
 * Created on March 8, 2017, 7:43 PM
 */

#ifndef CELL_HPP
#define CELL_HPP
class cell {
 friend class Player; //allows player objects to have access to private fields
 friend class movesList; // for Extra Credit: allows potentialmoves class to access x, y , val;
 friend class Game;
 int x; //for x coord
 int y; // for y coord
public:
 cell(); //initializes x and y to -1 (not on board)
 cell(int a, int b); // initializes x to a and y to b
 void resetCell(int a, int b); // resets cell, x = a, y = b
};
#endif

