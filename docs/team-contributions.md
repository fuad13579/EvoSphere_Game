# EvoSphere Team Contributions

## Purpose

This document defines who is responsible for each part of EvoSphere. It helps the team divide work clearly and prepares each member for presentation Q&A.

Each member must be able to explain the files and logic they worked on.

---

## Team Strategy

The project is divided by systems, not by random files.

```text
Shahriar: Board and Movement
Fuad: Player, Evoran, Battle, Capture
Musfiq: Game Flow, Console, Events, Integration
```

This division matches the terminal MVP architecture:

```text
Core/     = game objects
Systems/  = gameplay rules
Console/  = terminal input/output
data/     = fixed game data
```

---

# Member 1 — Board and Movement Lead

## Main Responsibility

Member 1 owns the board structure, tile system, and movement logic.

## Files

```text
include/Core/Tile.h
src/Core/Tile.cpp

include/Core/Board.h
src/Core/Board.cpp

include/Systems/MovementSystem.h
src/Systems/MovementSystem.cpp

include/Systems/TeleportSystem.h
src/Systems/TeleportSystem.cpp

include/data/BoardData.hpp
src/data/BoardData.cpp
```

## Tasks

- Create tile structure.
- Create 40-tile board.
- Add tile types.
- Add board wrapping.
- Add Energy Orb movement.
- Detect passing Origin Gate.
- Add Origin Gate rewards.
- Add teleport terminal positions.
- Implement teleport logic.
- Support tile ownership updates.

## Must Be Able to Explain

- Why the board has 40 tiles.
- How a tile stores its type and owner.
- How player movement wraps after tile 39.
- How passing Origin Gate is detected.
- How teleport chooses another terminal.
- Why board logic is separate from console printing.


---

# Member 2 — Player, Evoran, Battle, and Capture Lead

## Main Responsibility

Member 2 owns the creature logic and player state.

## Files

```text
include/Core/Evoran.h
src/Core/Evoran.cpp

include/Core/Player.h
src/Core/Player.cpp

include/Core/Guardian.h
src/Core/Guardian.cpp

include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp

include/Systems/CaptureSystem.h
src/Systems/CaptureSystem.cpp

include/Systems/EvolutionSystem.h
src/Systems/EvolutionSystem.cpp

include/data/EvoranDatabase.hpp
src/data/EvoranDatabase.cpp
```

## Tasks

- Create Evoran model.
- Create Player model.
- Add starter Evorans.
- Add wild Evorans.
- Add evolved form data.
- Add Guardian Evorans.
- Implement Evoran HP and damage.
- Implement Avatar Point damage.
- Implement battle-before-capture logic.
- Implement one-step evolution.

## Must Be Able to Explain

- What an Evoran stores.
- Difference between Avatar Points and Evoran HP.
- How damage is calculated.
- Why capture requires battle first.
- How evolution changes Evoran stats.
- How captured Evorans become owned by players.

## Example Q&A Preparation

### Question
Why does EvoSphere use battle-before-capture instead of random capture?

### Answer
Battle-before-capture makes the game more strategic. Players must use their owned Evorans to weaken wild Evorans before capturing them, which fits the Pokémon-inspired creature-battle identity better than pure random chance.

---

# Member 3 — Game Flow, Console, Events, and Integration Lead

## Main Responsibility

Member 3 owns the game loop, turn system, terminal interface, events, win condition, and integration between all systems.

## Files

```text
include/Core/Game.h
src/Core/Game.cpp

include/Core/TurnManager.h
src/Core/TurnManager.cpp

include/Core/EventCard.h
src/Core/EventCard.cpp

include/Systems/EventSystem.h
src/Systems/EventSystem.cpp

include/Console/ConsoleGame.hpp
src/Console/ConsoleGame.cpp

include/Console/ConsoleInput.hpp
src/Console/ConsoleInput.cpp

include/Console/ConsoleRenderer.hpp
src/Console/ConsoleRenderer.cpp

include/data/EventDatabase.hpp
src/data/EventDatabase.cpp

src/main.cpp
```

## Tasks

- Create terminal game loop.
- Ask player count.
- Ask avatar names.
- Handle starter selection.
- Show player status.
- Manage turn order.
- Resolve landed tile actions.
- Trigger event system.
- Check defeat and winner.
- Keep terminal output readable.
- Integrate code from Member 1 and Member 2.

## Must Be Able to Explain

- How the full turn loop works.
- Why `main.cpp` is small.
- How `ConsoleGame` connects to `Game`.
- How defeated players are skipped.
- How the winner is decided.
- Why console rendering is separate from core logic.

## Example Q&A Preparation

### Question
Why should `ConsoleRenderer` be separate from `Game`?

### Answer
`Game` should control game state and rules, while `ConsoleRenderer` only prints information. This separation makes the game easier to convert into a GUI later because the GUI can replace the console renderer without rewriting the core logic.

---

# Shared Responsibilities

All members are responsible for:

```text
- Pulling latest dev before starting work
- Creating small commits
- Writing clear commit messages
- Opening pull requests to dev
- Reviewing teammates' code
- Testing their own features
- Explaining their own code during Q&A
```

---

# Branch Ownership

For the first development stage, the team may use three larger feature branches:

```text
feature/board-system
feature/creature-system
feature/gameflow-system
```

## Branch Mapping

| Branch | Owner | Main Work |
|---|---|---|
| `feature/board-system` | Member 1 | Board, Tile, Movement, Teleport |
| `feature/creature-system` | Member 2 | Player, Evoran, Battle, Capture, Evolution, Guardian |
| `feature/gameflow-system` | Member 3 | Turn flow, Console UI, Events, Win condition, Integration |

---

# Individual Contribution Log

Each member should update this section before presentation.

## Member 1 Contribution Log

| Date | Work Done | Commit/PR |
|---|---|---|
| TBD | TBD | TBD |

## Member 2 Contribution Log

| Date | Work Done | Commit/PR |
|---|---|---|
| TBD | TBD | TBD |

## Member 3 Contribution Log

| Date | Work Done | Commit/PR |
|---|---|---|
| TBD | TBD | TBD |

---


---

