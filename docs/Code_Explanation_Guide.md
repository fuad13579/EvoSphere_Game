## Game.h / Game.cpp

Purpose:
Stores and updates the overall game state, including players, game status, and
the winner.

Important structures:

- `Player`: stores player information such as name, health, score, and defeated
  status.
- `GameState`: stores the player list, player count, game-over status, and
  winner index.

Important functions:

- `initializeGameState()`: connects the players to the game and resets the
  game status.
- `isPlayerDefeated()`: checks whether a player has been defeated.
- `canPlayerTakeTurn()`: checks whether a player is allowed to take a turn.
- `countActivePlayers()`: counts how many players are still active.
- `findWinnerIndex()`: finds the index of the last active player.
- `updateGameState()`: checks whether the game is over and identifies the
  winner.

How it works:

The game stores the players in `GameState`. After a player is defeated,
`updateGameState()` counts the active players. When only one player remains,
the game ends and that player becomes the winner.

## Player.h / Player.cpp

Purpose:
Stores player information such as name, Avatar Points, Evolution Gems, current
board position, and owned Evorans.

Important functions:

- `takeDamage()`: reduces Avatar Points.
- `addEvoran()`: adds a captured Evoran to the player.
- `isDefeated()`: checks whether Avatar Points are 0 or below.
