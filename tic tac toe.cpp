#include <iostream>
#include <string>

// coded this the HARD way intentionally, could have used hash maps, vectors, smart pointers, std array and more to make this a lot easier! >:)

// ideally id put the function definitions and declarations in seperate files BUT i was in a rush! ill redo in future! 

class Player {
private:
    char marker = NULL;
public:
    Player(char marker) {
        this->marker = marker;
    }
    char getMarker() {
        return this->marker;
    }
};

// create a class to return two values essentially since i cant use sizeof on a pointer :(
class pArrayCountPair {
public:
    std::string* pointingAt = nullptr;
    int count = 0;
};

struct Board {
    bool gameRunning = true;
    std::string slots[9] = {
        "~", "~", "~",
        "~", "~", "~",
        "~", "~", "~",
    };
    bool checkSpot(std::string position);
    void makeMove(Player player, std::string position);
    pArrayCountPair* getOpenSpots();
    void print() {
        std::cout << std::endl;
        std::cout << "### SHOWING BOARD ###" << std::endl;
        std::cout << std::endl;
        char letters[] = {'A', 'B', 'C'};
        std::cout << "      1  2  3" << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < sizeof(slots) / sizeof(slots[0]); i++) {
            if (i % 3 == 0) {
                std::cout << "   " << letters[i / 3];
            }
            std::cout << "  " << (slots[i]) << "";
            if ((i + 1) % 3 == 0) {
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
        std::cout << "#####################" << std::endl;
        std::cout << std::endl;
    }
    void showFormat() {
        std::cout << "Here is the format of the board:" << std::endl;
        std::cout << std::endl;
        std::cout << "      1  2  3" << std::endl;
        std::cout << std::endl;
        std::cout << "   A  ~  ~  ~" << std::endl;
        std::cout << std::endl;
        std::cout << "   B  ~  ~  ~" << std::endl;
        std::cout << std::endl;
        std::cout << "   C  ~  ~  ~" << std::endl;
        std::cout << std::endl;
    }
};

class TicTacToe {
public:
    Board board; // current board being played
    static const bool WinCases[][9];
    static const int GetPositionByCode(std::string code);
    static const void scanForWinner(Board &b, Player player);
    static const std::string getCodeByPosition(int pos);
};   

const std::string TicTacToe::getCodeByPosition(int pos) {
    if (pos < 4) {
        return ("A" + (pos % 3 == 0 ? "3" : std::to_string(pos % 3)));
    }
    else if (pos < 7) {
        return ("B" + (pos % 3 == 0 ? "3" : std::to_string(pos % 3)));
    }
    else {
        return ("C" + (pos % 3 == 0 ? "3" : std::to_string(pos % 3)));
    }
}

pArrayCountPair *Board::getOpenSpots() {
    std::string* tempTable = new std::string[9];
    int count = 0;
    for (int i = 0; i < 9; i++) {
        if (slots[i].c_str()[0] == '~') {
            tempTable[count] = TicTacToe::getCodeByPosition(i+1); // cant start at 0 for the getcodebypos algor
            count += 1;
        }
    }
    pArrayCountPair* ret = new pArrayCountPair;
    ret->count = count;
    ret->pointingAt = new std::string[count];
    for (int i = 0; i < count; i++) {
        ret->pointingAt[i] = tempTable[i];
    }
    delete[] tempTable;
    
    return ret;
}

bool Board::checkSpot(std::string position) {
    if (position[0] != 'A' && position[0] != 'B' && position[0] != 'C')
        return false;
    if (position[1] != '1' && position[1] != '2' && position[1] != '3')
        return false;
    return this->slots[TicTacToe::GetPositionByCode(position)] == "~";
}

void Board::makeMove(Player player, std::string position) {
    const int pos = TicTacToe::GetPositionByCode(position);
    this->slots[pos] = player.getMarker();
    std::cout << "Player " << player.getMarker() << " moved to " << position << std::endl;
}

const int TicTacToe::GetPositionByCode(std::string code) {
    int x;
    switch (code[0]) {
    case 'A':
        x = 0;
        break;
    case 'B':
        x = 3;
        break;
    case 'C':
        x = 6;
        break;
    default:
        x = -1;
    }
    
    int y = std::stoi(&code[1])-1;
    return x + y;
}

const bool TicTacToe::WinCases[][9] = {
    {true, true, true,
    false, false, false,
    false, false, false},

    {false, false, false,
    true, true, true,
    false, false, false},

    {false, false, false,
    false, false, false,
    true, true, true},

    {true, false, false,
    false, true, false,
    false, false, true},

    {false, false, true,
    false, true, false,
    true, false, false},

    {true, false, false,
    true, false, false,
    true, false, false},

    {false, true, false,
    false, true, false,
    false, true, false},

    {false, false, true,
    false, false, true,
    false, false, true},
};

const void TicTacToe::scanForWinner(Board &b, Player player) {
    // run after every turn, turn of the last player
    // convert board into true falses for player
    bool comparitiveSlotsp1[9];
    for (int i = 0; i < 9; i++) {
        comparitiveSlotsp1[i] = (b.slots[i].c_str()[0] == player.getMarker());
    }
    for (int i = 0; i < 8; i++) { // win cases
        int matches = 0;
        for (int ii = 0; ii < 9; ii++) {
            // actual win case
            if (TicTacToe::WinCases[i][ii] == true && comparitiveSlotsp1[ii] == TicTacToe::WinCases[i][ii]) {
                matches += 1;
            }
        }
        if (matches == 3) {
            b.gameRunning = false;
            std::cout << "Player " << player.getMarker() << " wins!" << std::endl;
            return;
        }
        matches = 0;
    }

    // gameRunning = false only if a winner is detected
}

int main()
{
    std::srand(std::time(nullptr));

    std::string input = "";

    Board board;
    Player player('X');
    Player computer('O');

    std::cout << std::endl;
    std::cout << "### TIC TAC TOE ###" << std::endl;
    std::cout << std::endl;

    board.showFormat();

    Player *turn = &player;

    while (board.gameRunning) {
        turn = &player;
        std::cout << "Player " << turn->getMarker() << ", make your move! (eg. A3)" << std::endl;
        std::cin >> input;
        while (!board.checkSpot(input)) {
            std::cout << "Invalid position at " << input << "! Please type a valid position." << std::endl;
            std::cout << "Player " << turn->getMarker() << ", make your move! (eg. A3)" << std::endl;
            std::cin >> input;
        }
        board.makeMove(*turn, input);
        board.print();
        TicTacToe::scanForWinner(board, *turn);

        // only coding this cuz no multiplayer yet, in future remove
        
        if (board.gameRunning) {
            turn = &computer;
            // have computer pick random point
            pArrayCountPair *openSpots = board.getOpenSpots();
            // choose random string from openSpots
            if (openSpots->count <= 0) {
                board.gameRunning = false;
                std::cout << "There was a tie!" << std::endl;
                break;
            }
            std::string compChoice = openSpots->pointingAt[std::rand() % openSpots->count];
            
            board.makeMove(*turn, compChoice);
            
            board.print();
            
            TicTacToe::scanForWinner(board, *turn);
            delete[] openSpots->pointingAt;
            delete[] openSpots;
        }
    }
    return 0;
}