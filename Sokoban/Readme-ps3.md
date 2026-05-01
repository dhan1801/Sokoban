# PS3b: Sokoban

## Contact  
Name: Dhanvika Nakka  
Section: 302  
Time to Complete: 14 hours  

## Description  
This project implements both parts (A and B) of the Sokoban game using C++ and SFML. The game loads level files and visually renders puzzles with grid-based elements like walls, boxes, storage targets, and the player. In Part B, gameplay mechanics such as movement, box pushing, collision handling, and win detection were added. Extra features include a move counter, undo/redo system, victory sound, and animated visual effects upon winning.

### Features  

- The level layout is represented using `std::vector<std::string>`, providing a simple yet effective way to model the grid.
- Sprites are mapped to characters (e.g., '#', '.', 'A', '@') using `std::map`, which simplifies rendering by associating characters with corresponding textures.
- The `Sokoban` class inherits from `sf::Drawable`, allowing the level to be rendered directly onto the window.
- The move counter updates each time the player moves using either arrow keys or WASD.
- The game automatically checks for win conditions and displays a "You Win!" message when successful.
- Player movement includes complete collision detection with walls, boundaries, and boxes.
- A stack-based undo/redo system tracks state changes and allows reversing or reapplying moves.

#### Part A  
- Successfully loads level data from `.lvl` files.  
- Properly renders the grid including player, walls, boxes, and storage areas.  
- Background floor tiles are drawn first to ensure a clean layout.  
- The game window resizes dynamically based on the level’s width and height.  
- Move counter is implemented to track user input, though movement logic was added later.

#### Part B  
- Implements player movement using the arrow keys and WASD (Up, Down, Left, Right).
- Movement logic ensures players cannot move through walls or push multiple boxes.
- Boxes are pushed only if the tile beyond them is empty or a storage area.
- All movement respects grid boundaries — neither player nor boxes can move off-screen.
- Implements a `movePlayer(Direction)` method and `isWon()` condition to detect game victory.
- Pressing `R` resets the game to its original state.
- Undo (`Z`) and redo (`Y`) functionality allow players to reverse and reapply moves.
- Win detection handles both balanced and unbalanced numbers of boxes and storage tiles.

### Memory  
Level data is stored in `std::vector<std::string>`, avoiding the need for raw or smart pointers. Textures are loaded once and reused to optimize memory efficiency. Undo/redo functionality is managed with two stacks, storing copies of the grid and player state.

### Lambdas and Algorithms  
- Lambda expressions are used in sorting and testing scenarios.  
- Standard algorithms (e.g., `std::remove`) are used for cleaning up level input lines during file parsing.

### Issues  
- A rendering bug caused the player sprite to have a black background, fixed by ensuring floor tiles are drawn underneath all elements.
- Parsing logic required careful handling to ensure each line in the level file matched the expected width.
- Initial movement attempts allowed invalid moves; added complete collision logic and edge checking.
- Tests initially passed broken implementations; more rigorous test cases were added.

### Extra Credit  
- Player sprite updates to face the most recent direction of movement.  
- A victory fanfare plays when the player wins.  
- Undo (`Z`) and redo (`Y`) allow players to reverse and reapply moves.  
- Move counter added using SFML’s text rendering features.  
- Disco lights: On winning, the game screen cycles through vibrant background colors to create a celebratory "disco" effect. This adds visual excitement and clearly signals success to the player.  
- Test suite includes comprehensive edge cases to catch broken implementations.

## Acknowledgements  
- Instructor lectures and documentation  
- SFML documentation: https://www.sfml-dev.org/  
- Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban  
- Victory audio file : https://mixkit.co/free-sound-effects/win/

