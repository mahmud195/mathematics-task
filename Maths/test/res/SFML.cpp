// Recursive Division (Predictable) algorithm in C++
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// A structure to represent a cell in the maze
struct Cell {
    int x, y; // coordinates
    bool top_wall, bottom_wall, left_wall, right_wall; // flags to indicate if the cell has walls
};

// A utility function to create a new cell
Cell* createCell(int x, int y) {
    Cell* newCell = new Cell;
    newCell->x = x;
    newCell->y = y;
    newCell->top_wall = true;
    newCell->bottom_wall = true;
    newCell->left_wall = true;
    newCell->right_wall = true;
    return newCell;
}

// A utility function to print the maze
void printMaze(Cell* maze[], int width, int height) {
    // print the top border
    for (int i = 0; i < width * 2 + 1; i++) {
        cout << "-";
    }
    cout << "\n";

    // print the maze
    for (int i = 0; i < height; i++) {
        // print the left border
        cout << "|";
        for (int j = 0; j < width; j++) {
            // print the cell
            cout << " ";
            // print the right wall
            if (maze[i][j].right_wall)
                cout << "|";
            else
                cout << " ";
        }
        cout << "\n";
        // print the bottom wall
        cout << "+";
        for (int j = 0; j < width; j++) {
            if (maze[i][j].bottom_wall)
                cout << "-";
            else
                cout << " ";
            cout << "+";
        }
        cout << "\n";
    }
}

// A utility function to remove the wall between two cells
void removeWall(Cell* a, Cell* b) {
    // find the relative position of the two cells
    int x = a->x - b->x;
    int y = a->y - b->y;
    // remove the wall
    if (x == 1) { // a is on the left of b
        a->right_wall = false;
        b->left_wall = false;
    }
    else if (x == -1) { // a is on the right of b
        a->left_wall = false;
        b->right_wall = false;
    }
    else if (y == 1) { // a is above b
        a->bottom_wall = false;
        b->top_wall = false;
    }
    else if (y == -1) { // a is below b
        a->top_wall = false;
        b->bottom_wall = false;
    }
}

// The main function to generate the maze using Recursive Division (Predictable) algorithm
void generateMaze(Cell* maze[], int width, int height, int x1, int y1, int x2, int y2) {
    // check if the region is too small to divide
    if (x2 - x1 < 2 || y2 - y1 < 2) {
        return;
    }

    // choose a random point along the edge of the region
    int x, y;
    bool horizontal;
    if (rand() % 2 == 0) { // choose a horizontal line
        horizontal = true;
        x = x1 + rand() % (x2 - x1);
        y = y1 + 1 + rand() % (y2 - y1 - 2);
    }
    else { // choose a vertical line
        horizontal = false;
        x = x1 + 1 + rand() % (x2 - x1 - 2);
        y = y1 + rand() % (y2 - y1);
    }

    // draw the line across the region, leaving a gap for a passage
    if (horizontal) { // draw a horizontal line
        for (int i = x1; i <= x2; i++) {
            if (i != x) { // leave a gap at x
                removeWall(maze*[y][i], maze*[y - 1][i]); // remove the bottom wall of the cell above the line
            }
        }
    }
    else { // draw a vertical line
        for (int i = y1; i <= y2; i++) {
            if (i != y) { // leave a gap at y
                removeWall(maze*[i][x], maze*[i][x - 1]); // remove the right wall of the cell left of the line
            }
        }
    }

    // recursively divide the subregions created by the line
    if (horizontal) { // divide the top and bottom subregions
        generateMaze(maze, width, height, x1, y1, x2, y - 1); // top subregion
        generateMaze(maze, width, height, x1, y + 1, x2, y2); // bottom subregion
    }
    else { // divide the left and right subregions
        generateMaze(maze, width, height, x1, y1, x - 1, y2); // left subregion
        generateMaze(maze, width, height, x + 1, y1, x2, y2); // right subregion
    }
}

// Driver code
int main() {
    // initialize the random seed
    srand(time(NULL));

    // get the width and height of the maze
    int width, height;
    cout << "Enter the width and height of the maze: ";
    cin >> width >> height;

    // create a dynamically allocated array of cells
    Cell* maze[50][50];

    // initialize the maze with cells
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            maze[i][j] = createCell(j, i);
        }
    }

    // generate the maze
    generateMaze(*maze, width, height, 0, 0, width - 1, height - 1);

    // print the maze
    printMaze(*maze, width, height);

    // delete the maze
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete maze[i][j];
        }
    }

    return 0;
}
