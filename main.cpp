/*
COSC1076 - Advanced Programming Techniques
Assignment 1
Quoc Tran s3827826
*/

/*
Milestone 2
To start I made a function to scan the map for 'S' and 'G' and added 'S' to the
open list. I then made a new node called nextMove that gets a node from the
open list with the lowest minDistance. This node is then checked for neighbours
to add to the open list. The current node is then added to the explored list
and nextMove is updated with another node from the open list. If the next move
is 'G' then the goal is found. If the explored list and open list are the same
size, then all possible nodes have been explored and the goal is not reachable.
Either way the algorithm ends. To find a neighbour of the of the current node,
I checked each four directions for a '.' and checked if that position was
already in the open list. If it wasn't then I added it in. This part caused me
a huge headache because I had all four checks in 'if elses' which stopped
scanning once it found one neighbour. This lead to single paths being found
before crashing at a dead end. After debugging a while I found the error in
logic and changed them all to if statements.
'if'.
*/

/*
Milestone 3
Here I started with the end of the explored list which would be the goal if the
goal was reachable. I made a check to see if the goal was indeed first before
continuing to find the path, otherwise an empty path was returned. From here,
each element in the explored list is scanned, starting from the second last
element to the first element. Each is checked to see if it was a neighbour and
one distance less. This would be the path node before it. This process is
continued until the start node is reached. This final path is returned and
printed out in the main. The print method uses the same iteration method
starting from the end of the list, which is now the start of the path, and
prints out the directional arrows accordingly. 
*/

/*
Milestone 4
Here I had the issue of being able to read the file in only once to work out the
dimensions and not being able to store it into the env. I tried to figure out
ifstream to close and open files again but didn't manage to. Instead I stored
what I read into a single string. I worked out how many rows by counting '\n'
and adding one at the very end. I then divided the length of the string by the
rows to find the columns. In the make_env funcion, I added a row and column to
add a nullptr at the end of the rows and the character 'Q' at the end of the
columns so I could work out the number of rows and columns in other functions
when needed without having to pass rows and cols everywhere. I still had to
create a new initialiser for nodelist that takes rows and columns to work out a
suitable size and added rows and cols as parameters to some of the existing
functions in main. I originally created an overload constructor for the
pathsolver and node list to pass in the new rows and cols values. After checking
on the discussion board I realised it was preferred to create a dynamically
growing array. So I implemented a simple increase by one array. I did my
best to ensure the were no lost pointers or unreachable memory on the heap.
*/


#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"


std::string findDimensions(int &rows, int &cols);
Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);

// Read a environment from standard input.
void readEnvStdin(Env env, int rows, int cols, std::string mapString);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, int rows, int cols, NodeList* solution);


int main(int argc, char** argv)
{
    int rows = 0;
    int cols = 0;
    
    std::string mapString = findDimensions(rows, cols);
    Env env = make_env(rows, cols);
    
    readEnvStdin(env, rows, cols, mapString);

    // Solve using forwardSearch
    PathSolver* pathSolver = new PathSolver(); 
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    NodeList* solution = pathSolver->getPath(env); 
    printEnvStdout(env, rows, cols, solution);


    delete_env(env, rows, cols);
    delete pathSolver;
    delete exploredPositions;
    delete solution;

    return EXIT_SUCCESS;
}

std::string findDimensions(int &rows, int &cols)
{
    std::string newString = "";
    char c;
    while (std::cin.get(c))
    { 
        if (c == '\n')
            rows++;
        else
            newString += c;
    }
    rows++;
    cols = newString.length()/ rows;

    return newString;
}

void readEnvStdin(Env env, int rows, int cols, std::string mapString)
{
    int stringIndex = 0;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            env[row][col] = mapString[stringIndex];
            stringIndex++;
        }
    }
}

void printEnvStdout(Env env, int rows, int cols, NodeList* solution) 
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            for (int i = solution->getLength()-2; i > 0; i--)
            {
                if (solution->getNode(i)->isUpperNodeOf(solution->getNode(i-1)))
                {
                    env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = 'v';
                }
                else if (solution->getNode(i)->isRightNodeOf(solution->getNode(i-1)))
                {
                    env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '<';
                }
                else if (solution->getNode(i)->isLeftNodeOf(solution->getNode(i-1)))
                {
                    env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '>';
                }
                else if (solution->getNode(i)->isLowerNodeOf(solution->getNode(i-1)))
                {
                    env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '^';
                }
            }
            std::cout << env[row][col];
        }
        if (row < rows-1)
        {
            std::cout << "\n";
        }
    }
}

Env make_env(const int rows, const int cols) 
{
    Env env = nullptr;

    if (rows >= 0 && cols >= 0) 
    {
        env = new char*[rows+1];
        for (int i = 0; i != rows; ++i)
        {
            env[i] = new char[cols+1];
        }
        env[rows] = nullptr;
        env[0][cols] = 'Q';
    }
    return env;
}

void delete_env(Env env, int rows, int cols) 
{
    if (rows >= 0 && cols >= 0) 
    {
        for (int i = 0; i != rows; ++i) 
        {
            delete env[i];
        }
        delete env;
    }    
    return;
}