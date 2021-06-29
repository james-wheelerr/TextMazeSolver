#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    rowCount = ENV_DIM;
    colCount = ENV_DIM;
    constructorCommonality();
}

PathSolver::PathSolver(int rows, int cols)
{
    rowCount = rows;
    colCount = cols;
    constructorCommonality();
}

void PathSolver::constructorCommonality()
{
    startNode = nullptr;
    goalNode = nullptr;

    currentPos = nullptr;
    emptyNode = nullptr;

    openList = new NodeList();
    closedList = new NodeList();
    path = new NodeList();
    reversePath = new NodeList();
}

PathSolver::~PathSolver()
{
    delete closedList;
    closedList = nullptr;

    delete startNode;
    delete goalNode;
    startNode = nullptr;
    goalNode = nullptr;

    currentPos = nullptr;
}

void PathSolver::forwardSearch(Env env)
{
    findSAndG(env);

    openList->addElement(startNode);
    
    currentPos = startNode;

    int goalCol = goalNode->getCol();
    int goalRow = goalNode->getRow();

    while (currentPos->getCol() != goalCol || currentPos->getRow() != goalRow)
    {
        findImmediateEmptyPos(env);

        int count = 0;
        for (int i = 0; i < openList->getLength(); ++i)
        {
            int openListRow = openList->getNode(i)->getRow();
            int openListCol = openList->getNode(i)->getCol();

            if (closedList->containsNode(openListRow, openListCol) == false)
            {

                if (count == 0)
                {
                    currentPos = openList->getNode(i);
                    count++;
                }

                if (currentPos->getEstimatedDist2Goal(goalNode) >
                    openList->getNode(i)->getEstimatedDist2Goal(goalNode))
                {
                    currentPos = openList->getNode(i);
                }
            }
        }
        closedList->addElement(currentPos);
    }
    
    delete openList;
    openList = nullptr;
    currentPos = nullptr;
}

NodeList *PathSolver::getNodesExplored()
{
    nodesExplored = new NodeList(*closedList);
    return nodesExplored;
}

NodeList *PathSolver::getPath(Env env)
{
    int startCol = startNode->getCol();
    int startRow = startNode->getRow();

    int nodesExploredLength = nodesExplored->getLength();
    
    currentPos = nodesExplored->getNode(nodesExploredLength - 1);
    
    reversePath->addElement(currentPos);

    while (currentPos->getCol() != startCol || currentPos->getRow() != startRow)
    {
        int colCoord = currentPos->getCol();
        int rowCoord = currentPos->getRow();

        int upCoord = rowCoord - 1;
        int downCoord = rowCoord + 1;
        int leftCoord = colCoord - 1;
        int rightCoord = colCoord + 1;

        if (isSymbolEmpty(env, rowCoord, leftCoord, false))
        {
            addToPath(rowCoord, leftCoord);
        }

        if (isSymbolEmpty(env, upCoord, colCoord, false))
        {
            addToPath(upCoord, colCoord);
        }
        
        if (isSymbolEmpty(env, downCoord, colCoord, false))
        {
            addToPath(downCoord, colCoord);
        }
        
        if (isSymbolEmpty(env, rowCoord, rightCoord, false))
        {
            addToPath(rowCoord, rightCoord);
        }
    }

    for (int i = reversePath->getLength() - 1; i >= 0; --i)
    {
        path->addElement(reversePath->getNode(i));
    }

    delete reversePath;
    reversePath = nullptr;

    return path;
}

void PathSolver::findSAndG(Env env)
{
    char c;
    int INITIAL_DIST = 0;
    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < colCount; ++col)
        {
            c = env[row][col];
            if (c == SYMBOL_START)
            {
                startNode = new Node(row, col, INITIAL_DIST);
            }
            if (c == SYMBOL_GOAL)
            {
                goalNode = new Node(row, col, INITIAL_DIST);
            }
        }
    }
}

void PathSolver::findImmediateEmptyPos(Env env)
{
    int rowCoord = currentPos->getRow();
    int colCoord = currentPos->getCol();
    int currentDist = currentPos->getDistanceTraveled();

    int upCoord = rowCoord - 1;
    int downCoord = rowCoord + 1;
    int leftCoord = colCoord - 1;
    int rightCoord = colCoord + 1;

    if (isSymbolEmpty(env, rowCoord, leftCoord, true) &&
        openList->containsNode(rowCoord, leftCoord) == false)
    {
        addEmptyNode(rowCoord, leftCoord, currentDist + 1);
    }
    
    if (isSymbolEmpty(env, upCoord, colCoord, true) &&
        openList->containsNode(upCoord, colCoord) == false)
    {
        addEmptyNode(upCoord, colCoord, currentDist + 1);
    }

    if (isSymbolEmpty(env, downCoord, colCoord, true) &&
        openList->containsNode(downCoord, colCoord) == false)
    {
        addEmptyNode(downCoord, colCoord, currentDist + 1);
    }

    if (isSymbolEmpty(env, rowCoord, rightCoord, true) &&
        openList->containsNode(rowCoord, rightCoord) == false)
    {
        addEmptyNode(rowCoord, rightCoord, currentDist + 1);
    }
}

bool PathSolver::isSymbolEmpty(Env env, int row, int col, bool forwardSearch)
{
    bool outcome = false;
    char symbol = env[row][col];

    if (forwardSearch == true)
    {
        if (symbol == SYMBOL_EMPTY || symbol == SYMBOL_GOAL)
        {
            outcome = true;
        }
    }
    if (forwardSearch == false)
    {
        if (symbol == SYMBOL_EMPTY || symbol == SYMBOL_START)
        {
            outcome = true;
        }
    }

    return outcome;
}

void PathSolver::addEmptyNode(int row, int col, int dist)
{
    emptyNode = new Node(row, col, dist);
    openList->addElement(emptyNode);
    delete emptyNode;
    emptyNode = nullptr;
}

void PathSolver::addToPath(int row, int col)
{
    int posInNodesExplored = nodesExplored->getNodeIndex(row, col);
    if (posInNodesExplored >= 0 &&
        isNextNodeByDist(row, col, posInNodesExplored))
    {
        currentPos = nodesExplored->getNode(posInNodesExplored);
        reversePath->addElement(currentPos);
    }
}

bool PathSolver::isNextNodeByDist(int row, int col, int index)
{
    bool outcome = false;

    int distOfNextNode = nodesExplored->getNode(index)->getDistanceTraveled();
    int currentPosDist = currentPos->getDistanceTraveled();

    if (nodesExplored->containsNode(row, col) == true &&
        distOfNextNode == currentPosDist - 1)
    {
        outcome = true;
    }

    return outcome;
}