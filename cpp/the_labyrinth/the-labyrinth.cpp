#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Structure containing basic information about a node
 */
struct Node {
    Node(int col, int row, char c, struct Node* prev):x(col), y(row), character(c), previous(prev){}
    int x;
    int y;
    char character;
    struct Node* previous;
};

/**
 * Function to check the neighbors of a node
 * current - Pointer to the current Node
 * maze - Reference on the vector containing the information about the labyrinth
 * nodes - Reference on the vector containing all the nodes detected
 * visited - Reference on the matrix to know if a node has already been detected
 */
void checkNeighbors(Node* current, vector<string>& maze, vector<Node*>& nodes, vector<vector<bool>>& visited) {

	/* We check every nodes around the current and add it to the list of nodes
	   if it is not a wall and if it has not been added yet. */

    if(maze[current->y-1][current->x] != '#' && !visited[current->y-1][current->x]){
        visited[current->y-1][current->x] = true;
        nodes.push_back(new Node(current->x, current->y-1, maze[current->y-1][current->x], current)); 
    }
    if(maze[current->y+1][current->x] != '#' && !visited[current->y+1][current->x]){
        visited[current->y+1][current->x] = true;
        nodes.push_back(new Node(current->x, current->y+1, maze[current->y+1][current->x], current));
    }
    if(maze[current->y][current->x-1] != '#' && !visited[current->y][current->x-1]){
        visited[current->y][current->x-1] = true;
        nodes.push_back(new Node(current->x-1, current->y, maze[current->y][current->x-1], current));
    }
    if(maze[current->y][current->x+1] != '#' && !visited[current->y][current->x+1]){
        visited[current->y][current->x+1] = true;
        nodes.push_back(new Node(current->x+1, current->y, maze[current->y][current->x+1], current));
    }
}

/**
 * Recursive method to get the next node to move
 * current - Pointer to the node to check
 */
Node* getNextNode(Node* current) {
    if(current->previous->previous == NULL) // Check if the previous node is the start node
        return current;

    getNextNode(current->previous);
}

/**
 * Function using a BFS (Breadth-First Search) to get the information about the next node
 * maze - Reference on the vector containing the information about the labyrinth
 * goal - character that we have to reach
 * rows - Number of rows in the labyrinth
 * columns - Number of columns in the labyrinth
 * start - Pointer to the first node
 */
Node* bfs(vector<string>& maze, char goal, int rows, int columns, Node* start) {

	// Matrix to know if a node has already been visited
    vector<vector<bool>> tabVisited(rows, std::vector<bool>(columns, false));
    tabVisited[start->y][start->x] = true;

    vector<Node*> nodes; // List of nodes detected
    int it = 0; // Iterator
    nodes.push_back(start);

    do {
    	// Check the neighbors of the actual node
        checkNeighbors(nodes[it], maze, nodes, tabVisited);

        // Check if the neighbors added match the goal
        for (int i = it; i < nodes.size(); i++) {
            if(nodes[i]->character == goal) {
                return getNextNode(nodes[i]);
            } 
        }

        it++;
        
    }while(it <= (nodes.size() - 1)); // Check all the nodes in the list

    cerr << "failed got next" << endl;

    return NULL; // Return a NULL pointer if the BFS failed

} 

int main()
{
    int R; // number of rows.
    int C; // number of columns.
    int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    cin >> R >> C >> A; cin.ignore();
    bool controlReached = false;

    // game loop
    while (1) {
        int KR; // row where Kirk is located.
        int KC; // column where Kirk is located.
        cin >> KR >> KC; cin.ignore();

        vector<string> labyrinth; // Vector containing a scheme of the labyrinth

        for (int i = 0; i < R; i++) {
            string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            cin >> ROW; cin.ignore();
            labyrinth.push_back(ROW);
        }

        Node first{KC, KR, labyrinth[KR][KC], NULL}; // Creation of the first node

        if(labyrinth[KR][KC] == 'C') // Kirk has reached the control room
            controlReached = true;

        Node* finalNode;

        // Use the BFS to get the next node
        if(controlReached) {
            finalNode = bfs(labyrinth, 'T', R, C, &first);
        } else {
            finalNode = bfs(labyrinth, '?', R, C, &first);
            if(finalNode == NULL)
                finalNode = bfs(labyrinth, 'C', R, C, &first);
        }


        if (finalNode != NULL) {
            if (finalNode->x > KC) {
                cout << "RIGHT" << endl;
            } else if(finalNode->x < KC) {
                cout << "LEFT" << endl; 
            } else if(finalNode->y > KR) {
                cout << "DOWN" << endl;
            } else {
                cout << "UP" << endl;
            }
        } else {
            cerr << "final node null" << endl;
        }
        

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // Kirk's next move (UP DOWN LEFT or RIGHT).
    }
}
