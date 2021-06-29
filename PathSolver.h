#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    PathSolver(int rows, int cols);

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
    /*
    Used for common ground between the PathSolver constructor, and its
    overloaded version
    */
    void constructorCommonality();
    
    //Ints intended for the same functionality as ENV_DIM
    int rowCount, colCount;
    
    //Two NodeLists used the forwardSearch algorithm
    NodeList* openList;
    NodeList* closedList;

    //NodeList for the solution of the maze from S to G
    NodeList* path;
    //NodeList for backtracking purposes
    NodeList* reversePath;

    Node* startNode;
    Node* goalNode;
    Node* currentPos;
    Node* emptyNode;

    //Finds the start and goal nodes in provided environment
    void findSAndG(Env env);
    
    /*
    Checks the four positions arround currentPos, adds empty positions to
    the openList
    */
    void findImmediateEmptyPos(Env env);
    
    //Checks if a coordinate in the environment is an empty/Start/Goal pos
    bool isSymbolEmpty(Env env, int row, int col, bool forwardSearch);
    
    //Adds a node to the openList
    void addEmptyNode(int row, int col, int dist);
    
    /*
    If supplied coords are the next node by following the backtracking process
    then the method adds said node to the reversePath
    */
    void addToPath(int row, int col);

    /*
    Determines whether the supplied node's distance will be next in the
    backtracking process
    */
    bool isNextNodeByDist(int row, int col, int index);
};

#endif //COSC_ASSIGN_ONE_PATHSOLVER