#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    nodesExplored = new NodeList();
    openList = new NodeList();
}

PathSolver::~PathSolver()
{
    delete nodesExplored;
    delete openList;
}

void PathSolver::forwardSearch(Env env)
{
    Node* start = findStartOrEnd(env, SYMBOL_START);
    Node* goal = findStartOrEnd(env, SYMBOL_GOAL);

    openList->addElement(start);

    Node* nextMove = openList->getNode(0);

    //While nextMove is not the goal AND there are still nodes to explore
    while (((goal->getRow() != nextMove->getRow()) || 
            (goal->getCol() != nextMove->getCol())) && 
            nodesExplored->getLength() != openList->getLength())
    {
        if (openList->getLength() > 1) //Find the next move
        {
            int minIndex = 0;
            int minEstDist = 1000; //Initialised to something arbitrarily large
            for (int i = 0; i < openList->getLength(); i++)
            {   
                //Check if elements in openlist are already explored. 
                //If not, find the lowest minEstDist and make it the next move
                if (isNotInList(nodesExplored, openList->getNode(i)->getRow(), 
                    openList->getNode(i)->getCol()))
                {
                    if (openList->getNode(i)->getEstimatedDist2Goal(goal) < minEstDist)
                    {
                        minIndex = i;
                        minEstDist = openList->getNode(i)->getEstimatedDist2Goal(goal);
                    }
                    nextMove = openList->getNode(minIndex);
                }
            }
        }
        findMoveableNeighbourBlock(env, nextMove, openList);
        
        nodesExplored->addElement(new Node(nextMove->getRow(), 
                                  nextMove->getCol(), 
                                  nextMove->getDistanceTraveled())); 
    }
}

NodeList* PathSolver::getNodesExplored()
{
    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env)
{
    NodeList* path = new NodeList();
    Node* start = findStartOrEnd(env, SYMBOL_START);
    Node* goal = findStartOrEnd(env, SYMBOL_GOAL);
    
    Node* nextMove = nodesExplored->getNode(nodesExplored->getLength()-1);
    path->addElement(new Node(nextMove->getRow(), 
                     nextMove->getCol(), 
                     nextMove->getDistanceTraveled()));
                                                            
    if (nextMove->isSameNodeAs(goal))
    {
        while (!start->isSameNodeAs(nextMove))
        {
            for (int i = nodesExplored->getLength()-2; i >= 0; i--)
            {
                if (nodesExplored->getNode(i)->isUpperNodeOf(nextMove) && 
                        nodesExplored->getNode(i)->isOneDistanceLessOf(nextMove))
                {
                    path->addElement(nodesExplored->getNode(i));
                    nextMove = nodesExplored->getNode(i);
                }
                else if (nodesExplored->getNode(i)->isRightNodeOf(nextMove) && 
                        nodesExplored->getNode(i)->isOneDistanceLessOf(nextMove))
                {   
                    path->addElement(nodesExplored->getNode(i));
                    nextMove = nodesExplored->getNode(i);
                }
                else if (nodesExplored->getNode(i)->isLeftNodeOf(nextMove) && 
                        nodesExplored->getNode(i)->isOneDistanceLessOf(nextMove))
                {
                    path->addElement(nodesExplored->getNode(i));
                    nextMove = nodesExplored->getNode(i);
                }
                else if (nodesExplored->getNode(i)->isLowerNodeOf(nextMove) && 
                        nodesExplored->getNode(i)->isOneDistanceLessOf(nextMove))
                {
                    path->addElement(nodesExplored->getNode(i));
                    nextMove = nodesExplored->getNode(i);
                }
            }
        }
    }
    return new NodeList(*path);
}

void PathSolver::findMoveableNeighbourBlock(Env env, 
                                            Node* nextMove, 
                                            NodeList* openList)
{
    //If a neighbour block is 'empty' or 'goal' AND is not in openlist, 
    //add to openlist with distance +1
    //Check up 
    if((env[nextMove->getRow()-1][nextMove->getCol()] == SYMBOL_EMPTY || 
            env[nextMove->getRow()-1][nextMove->getCol()] == SYMBOL_GOAL) && 
            isNotInList(openList, nextMove->getRow()-1, nextMove->getCol()))
    {
        openList->addElement(new Node(nextMove->getRow()-1, 
                                      nextMove->getCol(), 
                                      nextMove->getDistanceTraveled()+1));
    }
    //Check right
    if((env[nextMove->getRow()][nextMove->getCol()+1] == SYMBOL_EMPTY || 
            env[nextMove->getRow()][nextMove->getCol()+1] == SYMBOL_GOAL) && 
            isNotInList(openList, nextMove->getRow(), nextMove->getCol()+1))
    {
        openList->addElement(new Node(nextMove->getRow(), 
                                      nextMove->getCol()+1, 
                                      nextMove->getDistanceTraveled()+1));
    }
    //Check left
    if((env[nextMove->getRow()][nextMove->getCol()-1] == SYMBOL_EMPTY || 
            env[nextMove->getRow()][nextMove->getCol()-1] == SYMBOL_GOAL) && 
            isNotInList(openList, nextMove->getRow(), nextMove->getCol()-1))
    {
        openList->addElement(new Node(nextMove->getRow(), 
                                      nextMove->getCol()-1, 
                                      nextMove->getDistanceTraveled()+1));
    }
    //Check down
    if((env[nextMove->getRow()+1][nextMove->getCol()] == SYMBOL_EMPTY || 
            env[nextMove->getRow()+1][nextMove->getCol()] == SYMBOL_GOAL) && 
            isNotInList(openList, nextMove->getRow()+1, nextMove->getCol()))
    {
        openList->addElement(new Node(nextMove->getRow()+1, 
                                      nextMove->getCol(), 
                                      nextMove->getDistanceTraveled()+1));
    }
}

bool PathSolver::isNotInList(NodeList* nodes, int row, int col)
{
    bool isNotInList = true;
    for (int i = 0; i < nodes->getLength(); i++)
    {
        if (nodes->getNode(i)->getRow() == row && nodes->getNode(i)->getCol() == col)
        {
            isNotInList = false;
        }
    }
    return isNotInList;
}

Node* PathSolver::findStartOrEnd(Env env, char symbol)
{
    int rows = 0;
    int cols = 0;
    while (env[rows] != nullptr) {rows++;}
    while (env[0][cols] != 'Q') {cols++;}

    Node* temp = new Node(0, 0, 0);
    for (int row = 0; row < rows; row++) 
    {
        for (int col = 0; col < cols; col++)
        {
            if (symbol == SYMBOL_START && symbol == env[row][col])
            {
                delete temp;
                temp = new Node(row, col, 0);
            }
            else if (symbol == SYMBOL_GOAL && symbol == env[row][col])
            {   
                delete temp;
                temp = new Node(row, col, 0);
            }
        }
    }
    return temp;
}