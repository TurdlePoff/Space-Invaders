------------------------------------------------------------------
INSTRUCTIONS
------------------------------------------------------------------
HOW TO PLAY
------------------------------------------------------------------

	MENU
		- Navigate menu using UP and DOWN keys
		- Select an option with ENTER
		
	INSTRUCTIONS/HIGHSCORES
		- Return to main menu with ENTER
		
	GAME
		- LEFT and RIGHT to shoot
		- SPACE to shoot 
		- Clear all enemies in order to proceed in the next level
		- Enemies
			- Blue enemy - 10 pts
			- Yellow enemy - 20 pts
			- purple enemy - 40 pts
			- Red Enemy ship - ??? pts
		
	DEBUG WINDOW
		- Pauses game and allows you to change in-game variables
		- OK
			- Click ok to successfully change variables
		- CANCEL
			- Cancel all changes made in window and return to game
		- RETURN TO MAIN MENU
			- It is what it is
			
	ENDGAME
		- Activate name box by pressing ARROW keys if it isn't present
		- Name box accepts 3 UPPERCASE characters
		- Score will update to highscores after pressing ok
		
	NOTE: if using the release version, please keep the 'score.txt' in the same directory.
	
	
------------------------------------------------------------------
Things implemented
------------------------------------------------------------------

- Highscores
- Menu
- Barricades 
	- lasts throughout a whole game session and resets when a new game is started from the main menu
- Game lost 
	- a name window should pop up for user to enter a 3 letter name and will automatically update the highscores
- Instructions - view instructions in main menu
- All collisions
	- Enemy - player bullet
	- Enemy bullet - barricade
	- Player bullet - barricade
	- Player bullet - enemy ship
	- Enemy - bottom of screen
	- Enemy - Side of screens
	- Player - Side of screens
- Enemies
	- Gets faster every time they move down the screen
	- Gets faster after every level
- Animations
	- Enemy movement
	- Player dead
- UI
	- Player score
	- Level count
	- Player lives
- SOUND
	- Enemy shot sound
	- Player shooting sound
	- Barricade shot sound
	- Player dead sound
	
------------------------------------------------------------------
BY VIVIAN NGO
------------------------------------------------------------------
