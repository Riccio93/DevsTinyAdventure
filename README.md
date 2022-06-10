# Dev's Tiny Adventure

## Description

In the game you play as Dev in his quest to obtain all the 150 coins scattered through the level.
Coins can be collected from both actual coin objects in the map and by defeating enemies by jumping on their head.

## Features and mechanics

### Buttons

- WASD - Movement
- SPACE - Jump, Double Jump and Wall Jump
- SHIFT - Sprint
- CTRL - Walk Slowly (handy for enemies!)
- ESC - Pause Menu
- Mouse - Navigate menus and look around

### Dev's capabilities

- Jump and double jump (hold down the button to jump higher!)
- WallJump on red brick walls
- Adjust his speed by sprinting and walking slowly

### Mechanics

- Collect a coin to obtain 1 point.
- Jump on the head of enemies to defeat them and obtain 5 coins.
- When Dev jumps on grey metal boxes they start falling after ~ 1 second leading Dev to certain doom if he's not fast!
After ~ 6 seconds said platforms reappear at the original location.
- Use the red brick walls to reach higher places.
- If you find yourself at low health you can acquire one of the hearts in the level to recover a little bit of it.
- Look out for cloud platforms, as they are essential to reach new parts of the map.

### Enemies

1. Crabs: follow a fixed patrol path and ignore the player.
The player takes damage if there's a collision with the body.
2. Monsters: patrol an area randomly and react when they see the player.
When they are close they attack biting the player and causing damage.
As for the crabs the player also takes damage if there's a collision with the body.

### Main C++ Classes
- GEPlatformerGameMode contains all the game logic, including the number of coins collected by the player and his health.
It's also used to set all the default classes like the HUD and the PlayerController.
- InGameHUD handles the UI for the game adding and removing widgets from the viewport as needed.
- MainCharacter contains all the logic for Dev's movement (running, jumping, etc.) and the handling of collisions, both with pickups and enemies.
- EnemyCharacter handles the common logic for every type enemy, like the pawn's death.
Two ulterior classes inherit from this one, RatEnemy and MonsterEnemy, that contain the dedicated logic for the particular enemy (different behavior trees, different animations, etc.)
- Pickup sets the components for every pickup in the game.
Like for the enemies two classes inherit from this one, Coin and Heart, that hold the dedicated logic for the pickup type.


### Technologies
Unreal Engine 4.27.2

### Plugins
https://github.com/SRombauts/UE4GitPlugin

### Playthrough video
https://www.youtube.com/watch?v=J-9oZJ0zXbY