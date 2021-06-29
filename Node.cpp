#include "Node.h"
#include <iostream>
#include "math.h"

Node::Node(int row, int col, int dist_traveled)
{    
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::Node(Node &other) :
    row(other.row),
    col(other.col),
    dist_traveled(other.dist_traveled)
{ 
}

Node::~Node(){
}

int Node::getRow(){
    return this->row;
}

int Node::getCol(){
    return this->col;
}

int Node::getDistanceTraveled(){
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled++;
}

int Node::getEstimatedDist2Goal(Node* goal){
    
    int colP = this->col;
    int rowP = this->row;
    int colG = goal->getCol();
    int rowG = goal->getRow();
    
    int manhattenDist = abs(colP-colG) + abs(rowP - rowG);
    int estimatedDist2Goal = this->getDistanceTraveled() + manhattenDist;
    
    return estimatedDist2Goal; 
}                           