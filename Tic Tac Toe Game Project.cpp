#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

const int SIZE = 3;

struct Point {
    int x, y;
};

class Game {
private:
    char board[SIZE][SIZE];
    int scores[2];

public:
    Game() {
        initializeBoard();
        scores[0] = scores[1] = 0;
    }

    void initializeBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = '1' + i * SIZE + j;
            }
        }
    }

    void drawBoard() const {
        std::cout << "\n " << RED << "Tic Tac Toe" << RESET << "\n\n";
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                std::cout << " " << board[i][j] << " ";
                if (j < SIZE - 1) std::cout << "|";
            }
            std::cout << "\n";
            if (i < SIZE - 1) {
                for (int k = 0; k < SIZE * 4 - 1; k++) {
                    std::cout << "-";
                }
                std::cout << "\n";
            }
        }
        std::cout << "\nScore - X: " << scores[0] << ", O: " << scores[1] << "\n";
    }

    bool isValidMove(const Point& move) const {
        return move.x >= 0 && move.x < SIZE &&
               move.y >= 0 && move.y < SIZE &&
               board[move.x][move.y] != 'X' && board[move.x][move.y] != 'O';
    }

    void makeMove(char symbol, const Point& move) {
        board[move.x][move.y] = symbol;
    }

    bool hasWon(char symbol) const {
        // Check rows and columns
        for (int i = 0; i < SIZE; i++) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
            if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
        }

        // Check diagonals
        if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
            (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
            return true;
        }

        return false;
    }

    bool isDraw() const {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') return false;
            }
        }
        return true;
    }

    void playGame() {
        srand(time(0));
        int currentPlayer = rand() % 2;
        Point move;

        while (true) {
            system(CLEAR_COMMAND);
            drawBoard();

            std::cout << (currentPlayer ? GREEN : RED) << "Player " << (currentPlayer + 1) << "'s turn." << RESET << std::endl;

            do {
                int input;
                std::cout << "Enter your move (1-" << SIZE * SIZE << "): ";
                std::cin >> input;

                move.x = (input - 1) / SIZE;
                move.y = (input - 1) % SIZE;

                if (!isValidMove(move)) {
                    std::cout << RED << "Invalid move! Try again." << RESET << std::endl;
                }
            } while (!isValidMove(move));

            char symbol = currentPlayer ? 'O' : 'X';
            makeMove(symbol, move);

            system(CLEAR_COMMAND);
            drawBoard();

            // Simplified animation effect
            std::cout << "\rMaking move...";
            std::cout.flush();
            if (hasWon(symbol)) {
                system(CLEAR_COMMAND);
                drawBoard();
                std::cout << (currentPlayer ? GREEN : RED) << "Player " << (currentPlayer + 1) << " wins!" << RESET << std::endl;
                scores[currentPlayer]++;
                break;
            } else if (isDraw()) {
                system(CLEAR_COMMAND);
                drawBoard();
                std::cout << YELLOW << "It's a draw!" << RESET << std::endl;
                break;
            }

            currentPlayer = !currentPlayer;
        }

        playAgain();
    }

    void playAgain() {
        char choice;
        std::cout << BLUE << "Do you want to play again? (y/n)" << RESET << std::endl;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            initializeBoard();
            playGame();
        } else {
            std::cout << MAGENTA << "Thanks for playing!" << RESET << std::endl;
        }
    }
};

void welcomeScreen() {
    system(CLEAR_COMMAND);
    std::cout << CYAN << R"(

   _____ _           _       _ 
  / ____| |         (_)     | |
 | |    | |_ __ ___  _ _ __ | |_ ___ _ __  
 | |    | | '_ ` _ \| | '_ \| __/ _ \ '__|
 | |____| | | | | | | | |_) | ||  __/ |   
  \_____|_|_| |_| |_|_| .__/ \__\___|_|
                          | |              
                          |_|              

)" << RESET << std::endl;
}

int main() {
    welcomeScreen();
    Game game;
    game.playGame();
    return 0;
}
