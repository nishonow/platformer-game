#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

void spawn_player() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            char cell = current_level.data[row * current_level.columns + column];
            if (cell == PLAYER) {
                player_pos.x = static_cast<float>(column);
                player_pos.y = static_cast<float>(row);
                return;
            }
        }
    }
}

void move_player_horizontally(float delta) {
    float next_x = player_pos.x + delta;
    if (!is_colliding({next_x, player_pos.y}, WALL)) {
        player_pos.x = next_x;
    } else {
        player_pos.x = roundf(player_pos.x);
    }
}

void show_not_enough_money_screen() {
    ClearBackground(BLACK);
    draw_text(not_enough_money);
    EndDrawing();

    while (!IsKeyPressed(KEY_ENTER)) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_text(not_enough_money);
        EndDrawing();
        StopSound(music);
    }
    PlaySound(music);
}

void dead_screen() {
    ClearBackground(BLACK);
    draw_text(dead);
    EndDrawing();
    StopSound(music);
    PlaySound(death_sound);

    while (!IsKeyPressed(KEY_ENTER)) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_text(dead);
        EndDrawing();
    }
    game_state = MENU_STATE;
    level_index = 0;
    load_level(0);
    player_score = 0;
    player_live = 3;
}

void show_victory_screen() {
    create_victory_menu_background();
    ClearBackground(BLACK);
    draw_text(victory_title);
    draw_text(victory_subtitle);
    EndDrawing();
    PlaySound(victory);

    while (!IsKeyPressed(KEY_ENTER)) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_victory_menu_background();
        draw_victory_menu();
        EndDrawing();
        StopSound(music);
    }

    game_state = MENU_STATE;
    level_index = 0;
    player_score = 0;
    player_live = 3;
}

void update_player() {
    player_pos.y += player_y_velocity;
    player_y_velocity += GRAVITY_FORCE;

    is_player_on_ground = is_colliding({ player_pos.x, player_pos.y + 0.1f }, WALL);
    if (is_player_on_ground) {
        player_y_velocity = 0;
        player_pos.y = roundf(player_pos.y);
    }

    if (is_colliding(player_pos, TRAP)) {
        player_live -= 1;
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

    if (is_colliding(player_pos, COIN)) {
        get_collider(player_pos, COIN) = ' ';
        player_score += 10;
        PlaySound(coin_sound);
    }
    // if (is_colliding(player_pos, EXIT)) {
    //     load_level(1);
    // }

    if (is_colliding(player_pos, EXIT)) {
        if (level_index == 0 && player_score >= 10) {
            load_level(1);
            PlaySound(exit_sound);
        } else if(level_index == 1 && player_score >= 60) {
            load_level(1);
            PlaySound(exit_sound);
        } else if (level_index == 2 && player_score >= 120) {
            load_level(1);
            PlaySound(exit_sound);
        } else if (level_index == 3 && player_score >= 190) {
            load_level(1);
            PlaySound(exit_sound);
        } else if (level_index == 0 && player_score <= 10) {
            show_not_enough_money_screen();
            load_level();
        } else if (level_index == 1 && player_score <= 60) {
            show_not_enough_money_screen();
            load_level();
            player_score = 10;
        } else if (level_index == 2 && player_score <= 120) {
            show_not_enough_money_screen();
            load_level();
            player_score = 60;
        } else if (level_index == 3 && player_score <= 190) {
            show_not_enough_money_screen();
            load_level();
            player_score = 120;
        }
    }
}


#endif // PLAYER_H
