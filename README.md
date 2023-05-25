# Cub3d 
A simple interactive 3D FPP game using ray-casting, inspired by the world famous Wolfenstein 3D game 

## About the game 
On launch, the player is spawned in a 3D world where they can move around and explore the map. The direction the player faces (N/S/E/W) is specified by the map file and can be modified (examples of map files can be found [here](https://github.com/MehrinFirdousi/cub3d/tree/master/maps)). The player can navigate the world using the WASD keys, and can shift their point of view using the up, down, left and right keys. The point of view can also be moved using the mouse. A minimap of the game world is displayed on the top-left corner and can be toggled on and off. Doors are present to separate parts of the map and can be opened and closed. 

## Demo - Movement in game using keys only

https://github.com/MehrinFirdousi/cub3d/assets/88845742/a4873b0a-70a0-4fe3-80ba-6572219ddbad

## Demo - Mouse movement

https://github.com/MehrinFirdousi/cub3d/assets/88845742/0fbc1b93-f3b4-42f3-a58e-fce104300f0b

## Features
* Minimap with a field of view - can be toggled on and off
* Mouse movement and rotation in addition to default key movement
* Wall collisions
* Textured walls
* Doors that can open and close
* Shadows for walls 
* Animated torch sprite 

## Key guide
* E - Open/close doors
* TAB - Toggle the minimap on/off 
* SHIFT (on hold) - Slow down movement when walking 
* Up arrow key - Look up
* Down arrow key - Look down
* Left arrow key - Look left
* Right arrow key - Look right
* W - Move forward
* A - Move left
* S - Move backward
* D - Move right

## Implementation
This game uses ray-casting techniques to render a 3D world based on calculations performed on a top-level (2D) representation of the world. This process involves shooting rays through each pixel of an image plane from the camera (eye position) and then checking if the ray intersects with obstacles (walls/doors) in the map. The game is written in C and uses a basic graphics library - Minilibx.

## How to run
The code can be compiled and executed on a Mac or Linux environment as follows:
```bash
git clone https://github.com/MehrinFirdousi/cub3d.git
cd cub3d
make
./cub3d maps/subject.cub
```

To compile on Windows, you will need to have WSL installed and a few additional dependencies to open a graphics window through WSL. Use this [guide](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps).
