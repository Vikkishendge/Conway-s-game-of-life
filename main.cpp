#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

const int ROWS = 20;
const int COLS = 40;
const int GENERATIONS = 100;
const char ALIVE = 'O';
const char DEAD = '.';


void displayBoard(const vector<vector<bool>>& board) {
    system("clear"); // Use "cls" for Windows
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << (board[i][j] ? ALIVE : DEAD);
        }
        cout << endl;
    }
}


int countLiveNeighbors(const vector<vector<bool>>& board, int row, int col) {
    int count = 0;
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int k = 0; k < 8; k++) {
        int newRow = row + dx[k];
        int newCol = col + dy[k];
        if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
            count += board[newRow][newCol];
        }
    }

    return count;
}

// Compute next generation
vector<vector<bool>> nextGeneration(const vector<vector<bool>>& board) {
    vector<vector<bool>> newBoard = board;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int liveNeighbors = countLiveNeighbors(board, i, j);

            if (board[i][j]) {
                // Rule 1 or 3: underpopulation or overpopulation
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newBoard[i][j] = false;
                }
            } else {
                // Rule 4: reproduction
                if (liveNeighbors == 3) {
                    newBoard[i][j] = true;
                }
            }
        }
    }

    return newBoard;
}

// Randomly initialize the board
void initializeBoard(vector<vector<bool>>& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % 2;
        }
    }
}

int main() {
    vector<vector<bool>> board(ROWS, vector<bool>(COLS, false));
    initializeBoard(board);

    for (int gen = 0; gen < GENERATIONS; gen++) {
        displayBoard(board);
        board = nextGeneration(board);
        this_thread::sleep_for(chrono::milliseconds(200)); // Pause between generations
    }

    return 0;
}
