Simple Platformer
=================

<p align="center">
  <img src="https://i.imgur.com/UGrwiAa.png" alt="Game Screenshot" width="700">
</p>



## Added elements

* New Levels: Added 4 extra levels to the game.

* New Game Elements: Added traps, player live

* Next Level Screen: Added new screen to move to next level if player does not have enough coins programm load the same level untill player has enough coins.

* New Game Over Screen: Added new Game Over Screen.

* New Sounds: Added sounds such as death sound, victory sound.

* Music: Added new background music

* New Mechanics: TODO


## Added codes
* Background image of the screen using `DrawTexture` from raylib.
```
DrawTexture(menu_back, 0, 0, WHITE);
```
* Logic of moving to next level.
```
switch (level_index) {
            case 0:
                if (player_score >= 10) {
                    load_level(1);
                    PlaySound(exit_sound);
                } else {
                    show_not_enough_money_screen();
                    load_level();
                }
            break;
            case 1:
                if (player_score >= 60) {
                    load_level(1);
                    PlaySound(exit_sound);
                } else {
                    show_not_enough_money_screen();
                    load_level();
                    player_score = 10;
                }
            break;
            case 2:
                if (player_score >= 120) {
                    load_level(1);
                    PlaySound(exit_sound);
                } else {
                    show_not_enough_money_screen();
                    load_level();
                    player_score = 60;
                }
            break;
.....
```

* Logic for player live count

```
if (is_colliding(player_pos, TRAP)) {
        player_live -= 1;
        if (player_live == 2 || player_live == 1) {
            PlaySound(death_sound);
        }
        if (is_colliding(player_pos, TRAP) && player_live == 0) {
            dead_screen();
        } else {
            switch (level_index) {
                case 0: player_score = 0; load_level(); break;
                case 1: player_score = 10; load_level(); break;
                case 2: player_score = 60; load_level(); break;
                case 3: player_score = 120; load_level(); break;
            }
        }
    }
```

## Projecr structure: 

```
.
└── <repository>
    ├── data
    │   ├── fonts
    │   │   └── ...
    │   ├── images
    │   │   └── ...
    │   ├── music
    │   │   └── ...
    │   └── sounds
    │       └── ...
    ├── platformer.cpp
    ├── globals.h
    ├── <various header files>.h
    ├── ... (.idea, .gitignore, CMakeLists.txt, other directories)
    └── Readme.md
```

## Links

### raylib

* [Wiki](https://github.com/raysan5/raylib/wiki)
* [Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)
* [Examples](https://www.raylib.com/examples.html)

### Tools

* [Pixabay](https://pixabay.com/)


