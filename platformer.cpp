#include "raylib.h"

#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"

void update_game() {
    game_frame++;

    // TODO


    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        move_player_horizontally(MOVEMENT_SPEED);
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        move_player_horizontally(-MOVEMENT_SPEED);
    }


    is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && is_player_on_ground) {
        player_y_velocity = -JUMP_STRENGTH;
    }

    update_player();
}

void draw_game() {
    // TODO

    ClearBackground(BLACK);
    draw_level();
    draw_game_overlay();
}

int main() {
    InitWindow(1024, 480, "Platformer");
    SetExitKey(0);
    SetTargetFPS(60);

    load_fonts();
    load_images();
    load_sounds();
    load_level();


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);


        if (IsKeyPressed(KEY_H)) {
            game_state = HOW_STATE;
        }

        if (game_state == MENU_STATE) {
            if (IsKeyPressed(KEY_ENTER)) {
                game_state = GAME_STATE;
                PlaySound(music);
                load_level(0);
            } else if (IsKeyPressed(KEY_H)) {
                game_state = HOW_STATE;
            }
            draw_text(menu_title);
            draw_text(menu_option_start);
            draw_text(menu_option_how_to_play);
        } else if (game_state == HOW_STATE) {
            if (IsKeyPressed(KEY_B)) {
                game_state = MENU_STATE;
            }
            draw_text(how_to_play_title);
            draw_text(how_to_play_instructions);
            draw_text(how_to_play_back);
        } else if (game_state == PAUSE_STATE) {
            ClearBackground(BLACK);
            draw_pause_menu();
            if (IsKeyPressed(KEY_ESCAPE)) {
                game_state = GAME_STATE;
            }
        } else if (game_state == GAME_STATE) {
            update_game();
            draw_game();
            if (IsKeyPressed(KEY_ESCAPE)) {
                game_state = PAUSE_STATE;
            }
        }

        EndDrawing();
    }



    unload_level();
    unload_sounds();
    unload_images();
    unload_fonts();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
