#include "raylib.h"

#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"

void update_game()
{
    game_frame++;

    switch (game_state) {
    // TODO
        case MENU_STATE:
        if (IsKeyPressed(KEY_H)) {
            game_state = HOW_STATE;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            game_state = GAME_STATE;
            PlaySound(music);
        }
        break;
        case GAME_STATE:
        if (IsKeyPressed(KEY_ESCAPE)) {
            game_state = PAUSE_STATE;
            StopSound(music);
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            move_player_horizontally(MOVEMENT_SPEED);
        }

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            move_player_horizontally(-MOVEMENT_SPEED);
        }

        // Calculating collisions to decide whether the player is allowed to jump: don't want them to suction cup to the ceiling or jump midair
        is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
        if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && is_player_on_ground) {
            player_y_velocity = -JUMP_STRENGTH;
        }

        update_player();
        break;

        case PAUSE_STATE:
        if (IsKeyDown(KEY_ESCAPE)) {
            game_state = PAUSE_STATE;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            game_state = GAME_STATE;
            PlaySound(music);
        }
        break;

        case VICTORY_STATE:
        StopSound(music);
        if (IsKeyPressed(KEY_ENTER)) {
            game_state = MENU_STATE;
            StopSound(music);
        }
        break;
        case HOW_STATE:
        if (IsKeyPressed(KEY_B)) {
            game_state = MENU_STATE;
        }
        break;
    }


}

void draw_game()
{
    switch (game_state) {
        // TODO
        case MENU_STATE:
            ClearBackground(BLACK);
            draw_menu();
            break;
        case GAME_STATE:
            ClearBackground(BLACK);
            draw_level();
            draw_game_overlay();
            break;
        case PAUSE_STATE:
            ClearBackground(BLACK);
            draw_pause_menu();
            break;
        case VICTORY_STATE:
            draw_victory_menu();
            player_live = 3;
            player_score = 0;
            level_index = 0;
            break;
        case HOW_STATE:
            ClearBackground(BLACK);
            draw_text(how_to_play_title);
            draw_text(how_to_play_instructions);
            draw_text(how_to_play_back);
            break;
    }
}

int main()
{
    InitWindow(1200, 600, "Platformer");
    SetExitKey(0);
    SetTargetFPS(60);

    load_fonts();
    load_images();
    load_sounds();
    load_level();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        update_game();
        draw_game();

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