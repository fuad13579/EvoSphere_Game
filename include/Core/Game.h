#ifndef EVO_GAME_H //If header is not defined, define it to prevent multiple inclusions//
#define EVO_GAME_H//Now we define the header guard to prevent multiple inclusions of this header file//

#include <string>

struct Player
{
    std::string name;//std is a standard library that provides various functionalities, including string manipulation. Here, we are using std::string to represent the name of the player//
    bool defeated = false;//This boolean variable indicates whether the player has been defeated in the game. It is initialized to false, meaning the player is not defeated at the start of the game//
    int health = 100;
    int score = 0;
};

struct GameState
{
    Player* players = nullptr;//nullptr is a special value that indicates that the pointer does not point to any valid memory location. In this case, it means that the players array is initially empty or uninitialized//
    int playerCount = 0; 
    bool gameOver = false;
    int winnerIndex = -1;//-1 for no winner, otherwise index of the winner in the players array//
};

void initializeGameState(GameState* game, Player players[], int playerCount);
//This function initializes the game state by setting the players, player count, game over status, and winner index. It takes a pointer to a GameState structure, an array of Player structures, and the number of players as parameters. If the game pointer is null, the function returns without making any changes. The player count is set to 0 if it is negative, and the game over status is set to false. The winner index is initialized to -1, indicating that there is no winner at the start of the game.//

bool canPlayerTakeTurn(const Player* player);
//This function checks if a player can take their turn in the game. It takes a pointer to a Player structure as a parameter and returns true if the player is not null and has not been defeated, indicating that they can take their turn. Otherwise, it returns false.//

int countActivePlayers(const Player players[], int playerCount);
//This function counts the number of active players in the game. It takes an array of Player structures and the number of players as parameters. If the players array is null or the player count is less than or equal to 0, it returns 0. Otherwise, it iterates through the players array and counts how many players can take their turn (i.e., are not defeated). The function returns the count of active players.//

int findWinnerIndex(const Player players[], int playerCount);
//This function finds the index of the winner in the players array. It takes an array of Player structures and the number of players as parameters. If the players array is null or the player count is less than or equal to 0, it returns -1, indicating that there is no winner. The function iterates through the players array and checks if each player can take their turn. If a player can take their turn, it checks if a winner has already been found (i.e., winnerIndex is not -1). If a winner has already been found, it returns -1, indicating that there is no clear winner. Otherwise, it sets the winnerIndex to the current player's index. After iterating through all players, it returns the winnerIndex, which will be -1 if there is no clear winner or the index of the winning player if there is one.//

bool updateGameState(GameState* game);
//This function updates the game state based on the current status of the players. It takes a pointer to a GameState structure as a parameter. If the game pointer is null, it returns false, indicating that the update was unsuccessful. The function counts the number of active players using the countActivePlayers function. If there is only one active player left, it sets the game over status to true and finds the index of the winner using the findWinnerIndex function. It returns true if the game state was successfully updated, indicating that the game is still ongoing or has ended with a winner. Otherwise, it returns false.//

inline bool isPlayerDefeated(const Player* player)//This inline function checks if a player has been defeated in the game. It takes a pointer to a Player structure as a parameter and returns true if the player is not null and has been defeated (i.e., the defeated boolean variable is true). Otherwise, it returns false. The inline keyword suggests that the function may be expanded inline at the point of use, potentially improving performance by avoiding function call overhead.//
{
    return player != nullptr && player->defeated;
}
//Inline is used for small functions that are called frequently, as it can improve performance by avoiding the overhead of a function call. However, it is ultimately up to the compiler to decide whether to inline the function or not.//
#endif
