#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
void printEnvStdout(Env env, NodeList *solution);

/*
Methods taken from milestone4 header file
- make_env allocates memory on the heap as needed for a non-fixed size
  environment
- delete_env frees memory allocated for the storage of a non-fixed size
  environment
*/
Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);

/*
Helper method that stores the environment as a string for later use
method simultaneously stores the number of rows & columns in the maze
*/
void storeMazeInfo(std::string* mazeStrPtr, int* rowPtr, int* colPtr);

/*
These two methods are used for the reading in / printing out (by standard
input/output) of mazes that are not of the conventional 20x20 dimension
*/
void readEnv(Env env, std::string mazeAsString, int rowCount, int colCount);
void printEnv(Env env, NodeList *solution, int rowCount, int colCount);

int main(int argc, char **argv)
{
    int rowCount = 0;
    int colCount = 0;

    int* rowPtr = &rowCount;
    int* colPtr = &colCount;

    std::string mazeAsString = "";
    std::string* mazeStrPtr = &mazeAsString;

    storeMazeInfo(mazeStrPtr, rowPtr, colPtr);
    
    Env env = make_env(rowCount, colCount);
    readEnv(env, mazeAsString, rowCount, colCount);
    
    PathSolver *pathSolver = new PathSolver(rowCount, colCount);
    pathSolver->forwardSearch(env);
    
    NodeList *exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    NodeList *solution = pathSolver->getPath(env);

    printEnv(env, solution, rowCount, colCount);

    delete_env(env, rowCount, colCount);

    delete pathSolver;
    delete exploredPositions;
    delete solution; 
}

//Used prior to milestone 4 for reading in fixed size environments
void readEnvStdin(Env env)
{
    char c;
    for (int row = 0; row < ENV_DIM; ++row)
    {
        for (int col = 0; col < ENV_DIM; ++col)
        {
            std::cin >> c;
            env[row][col] = c;
        }
    }
}

void readEnv(Env env, std::string mazeAsString, int rowCount, int colCount)
{
    char c;
    int stringPos = 0;
    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < colCount; ++col)
        {
            c = mazeAsString[stringPos];
            env[row][col] = c;
            ++stringPos;
        }
    }
}
//Used prior to milestone 4 for printing out fixed size environments
void printEnvStdout(Env env, NodeList *solution)
{
    int index = 0;
    int nextNodeCol = 0;
    int nextNodeRow = 0;

    for (int row = 0; row < ENV_DIM; ++row)
    {
        for (int col = 0; col < ENV_DIM; ++col)
        {
            if (solution->containsNode(row, col) &&
                env[row][col] != SYMBOL_START &&
                env[row][col] != SYMBOL_GOAL)
            {
                index = solution->getNodeIndex(row, col);

                nextNodeCol = solution->getNode(index + 1)->getCol();
                nextNodeRow = solution->getNode(index + 1)->getRow();

                if (nextNodeRow == row - 1)
                {
                    env[row][col] = '^';
                }
                else if (nextNodeRow == row + 1)
                {
                    env[row][col] = 'V';
                }
                else if (nextNodeCol == col - 1)
                {
                    env[row][col] = '<';
                }
                else if (nextNodeCol == col + 1)
                {
                    env[row][col] = '>';
                }
            }

            std::cout << env[row][col];
        }
        if (row < ENV_DIM - 1)
        {
            std::cout << std::endl;
        }
    }
}

void printEnv(Env env, NodeList *solution, int rowCount, int colCount)
{
    int index = 0;
    int nextNodeCol = 0;
    int nextNodeRow = 0;

    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < colCount; ++col)
        {
            if (solution->containsNode(row, col) &&
                env[row][col] != SYMBOL_START &&
                env[row][col] != SYMBOL_GOAL)
            {
                index = solution->getNodeIndex(row, col);

                nextNodeCol = solution->getNode(index + 1)->getCol();
                nextNodeRow = solution->getNode(index + 1)->getRow();

                if (nextNodeRow == row - 1)
                {
                    env[row][col] = '^';
                }
                else if (nextNodeRow == row + 1)
                {
                    env[row][col] = 'V';
                }
                else if (nextNodeCol == col - 1)
                {
                    env[row][col] = '<';
                }
                else if (nextNodeCol == col + 1)
                {
                    env[row][col] = '>';
                }
            }

            std::cout << env[row][col];
        }
        if (row < rowCount - 1)
        {
            std::cout << std::endl;
        }
    }
}

Env make_env(const int rows, const int cols)
{
    Env env = nullptr;

    if (rows >= 0 && cols >= 0)
    {
        env = new char *[rows];
        for (int i = 0; i != rows; ++i)
        {
            env[i] = new char[cols];
        }
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

void storeMazeInfo(std::string* mazeStrPtr, int* rowPtr, int* colPtr)
{
    std::string maze = "";
    std::string tmp = "";

    int colCount = 0;
    int rowCount = 1;
    
    char c;
    while (std::cin.get(c))
    {
        if (c == '\n')
        {
            ++rowCount;
        }
        else
        {
            tmp = c;
            maze.append(tmp);
            if (rowCount == 1)
            {
                ++colCount;
            } 
        }
    }

    *mazeStrPtr = maze;
    *rowPtr = rowCount;
    *colPtr = colCount;
}