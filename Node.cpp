#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled; 
}

Node::~Node()
{
    // Nothing to delete
}

int Node::getRow()
{
    return row;
}

int Node::getCol()
{
    return col;
}

int Node::getDistanceTraveled()
{
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal)
{
    int manhattan_Distance = abs(col - goal->getCol()) + 
                                abs(row - goal->getRow());
    return dist_traveled + manhattan_Distance;
}

bool Node::isSameNodeAs(Node* toCompare)
{
    return (row == toCompare->getRow()) && (col == toCompare->getCol());
}

bool Node::isUpperNodeOf(Node* toCompare)
{
    return (row == toCompare->getRow()-1) && (col == toCompare->getCol());
}

bool Node::isRightNodeOf(Node* toCompare)
{
    return (row == toCompare->getRow()) && (col == toCompare->getCol()+1);
}

bool Node::isLeftNodeOf(Node* toCompare)
{
    return (row == toCompare->getRow()) && (col == toCompare->getCol()-1);
}

bool Node::isLowerNodeOf(Node* toCompare)
{
    return (row == toCompare->getRow()+1) && (col == toCompare->getCol());
}

bool Node::isOneDistanceLessOf(Node* nodeToCompare)
{
    return dist_traveled == nodeToCompare->getDistanceTraveled()-1;
}