/*welcome the the game of life 
the functions used in this code are : 
    
    
    
1.  initialize_user_input():
2.  initialize_random_values():
3.  initialize():
4.  count_neighbours(int x, int y): 
5.  insert_into_secondary_array(int x, int y):
6.  delete_from_secondary_array(int x, int y): 
7.  insert_into_neighbour_array(int x, int y): 
8.  delete_from_neighbour_array(int x, int y):
9.  is_alive(int x, int y): 
10. will_be_alive(int x, int y): 
11. update(): 
12. print(): 
13. is_stable(): 
14. count_live_cells(): 
15. is_empty():
16. is_full(): 
17. iterations(): 
18. call(): 

*/

#include <iostream>
#include <cstdlib>
#include <ctime>


//rows = 10 and col = 10
const int R = 10;
const int C = 10;
const int MAX_LIVE_CELLS = R * C;
//
int grid[R][C];
int secondary_array[MAX_LIVE_CELLS][2];
int live_cells = 0;
int neighbour_array[R * C][2];
int neighbour_cells = 0;


//for the user to enter the input of 1. live cells  2.coordinates  3. number of generations (asked in iltration function) 
void initialize_user_input() {

    for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                grid[i][j] = 0;
            }
        }
        int live_cells_input;
        std::cout << "Enter the number of live cells: ";
        std::cin >> live_cells_input;
        for (int i = 0; i < live_cells_input; i++) {
            int x, y;
            std::cout << "Enter the coordinates of live cell " << i + 1 << ": ";
            std::cin >> x >> y;
            grid[x][y] = 1;
            secondary_array[live_cells][0] = x;
            secondary_array[live_cells][1] = y;
            live_cells++;
        }

}

//i wanted to test my code so the better way was to ask user to generate randome values
void initialize_random_values() {

    srand(time(0));
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                grid[i][j] = rand() % 2;
                if (grid[i][j] == 1) {
                    secondary_array[live_cells][0] = i;
                    secondary_array[live_cells][1] = j;
                    live_cells++;
                }
            }
        }

}

//choice for input  
void initialize() {
    int w;
    
    std::cout << "Do you want the computer to generate random values or you want to enter the places of live cells yourself? (0 for random, 1 for user input): ";
    
    std::cin >> w;

    if (w == 0) {
        initialize_random_values();
    } 
    else {
        initialize_user_input();
    }
}

//will count neighbours for you and stor in array 
int count_neighbours(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int new_x = x + i;
            int new_y = y + j;
            if (new_x >= 0 && new_x < R && new_y >= 0 && new_y < C) {
                if (grid[new_x][new_y] == 1) {
                    count++;
                    neighbour_array[neighbour_cells][0] = new_x;
                    neighbour_array[neighbour_cells][1] = new_y;
                    neighbour_cells++;
                }
            }
        }
    }
    return count;
}

void insert_into_secondary_array(int x, int y) {
    if (live_cells < MAX_LIVE_CELLS) {
        secondary_array[live_cells][0] = x;
        secondary_array[live_cells][1] = y;
        live_cells++;
    }
}

void delete_from_secondary_array(int x, int y) {
    for (int i = 0; i < live_cells; i++) {
        if (secondary_array[i][0] == x && secondary_array[i][1] == y) {
            for (int j = i; j < live_cells - 1; j++) {
                secondary_array[j][0] = secondary_array[j + 1][0];
                secondary_array[j][1] = secondary_array[j + 1][1];
            }
            live_cells--;
            break;
        }
    }
}

void insert_into_neighbour_array(int x, int y) {
    if (neighbour_cells < R * C) {
        neighbour_array[neighbour_cells][0] = x;
        neighbour_array[neighbour_cells][1] = y;
        neighbour_cells++;
    }
}

void delete_from_neighbour_array(int x, int y) {
    for (int i = 0; i < neighbour_cells; i++) {
        if (neighbour_array[i][0] == x && neighbour_array[i][1] == y) {
            for (int j = i; j < neighbour_cells - 1; j++) {
                neighbour_array[j][0] = neighbour_array[j + 1][0];
                neighbour_array[j][1] = neighbour_array[j + 1][1];
            }
            neighbour_cells--;
            break;
        }
    }
}


//Checks if a given cell is alive.
bool is_alive(int x, int y) {
    if (x >= 0 && x < R && y >= 0 && y < C) {
        return grid[x][y] == 1;
    } else {
        return false;
    }
}

//Checks if a given cell will be alive in the next generation.
bool will_be_alive(int x, int y) {
    int neighbours = count_neighbours(x, y);
    if (is_alive(x, y)) {
        return (neighbours == 2 || neighbours == 3);
    } else {
        return (neighbours == 3);
    }
}

//Updates the grid based on the rules of the Game of Life.
void update() {
    int new_grid[R][C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            new_grid[i][j] = will_be_alive(i, j) ? 1 : 0;
        }
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
    live_cells = 0;
    neighbour_cells = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == 1) {
                insert_into_secondary_array(i, j);
            }
        }
    }
}

//Prints the current state of the grid.
void print() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//Checks if the grid has reached a stable state.
bool is_stable() {
    int new_grid[R][C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            new_grid[i][j] = will_be_alive(i, j) ? 1 : 0;
        }
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] != new_grid[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int count_live_cells() {
    return live_cells;
}


//Checks if the grid is empty.
bool is_empty() {
    return live_cells == 0;
}

//Checks if the grid is full.
bool is_full() {
    return live_cells == R * C;
}

//Runs the Game of Life for a specified number of iterations and prints stages.
int iterations() {
    int iterations;
    std::cout << "Enter the number of iterations: ";
    std::cin >> iterations;
    int i;
    for (i = 0; i < iterations; i++) {
        std::cout << "Stage " << i + 1 << ":" << std::endl;
        if (is_stable()) {
            break;
        }
        update();
        print();
    }
    return i + 1;
}

//Main function that calls other functions to initialize, update, and print the grid.
void call() {
    initialize();
    print();
    iterations();
    std::cout << "Number of live cells: " << count_live_cells() << std::endl;
    if (is_empty()) {
        std::cout << "The grid is empty." << std::endl;
    } else if (is_full()) {
        std::cout << "The grid is full." << std::endl;
    } else {
        std::cout << "The grid is stable but not empty or full." << std::endl;
    }
    std::cout << "Coordinates of live cells: ";
    for (int i = 0; i < live_cells; i++) {
        std::cout << "(" << secondary_array[i][0] << "," << secondary_array[i][1] << ") ";
    }
    std::cout << std::endl;
     std::cout << std::endl;
    std::cout << "The Final Grid is : " << std::endl;
    print();
}



int main() {
    call();
    return 0;
}

