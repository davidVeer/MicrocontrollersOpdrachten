#ifndef GAME_H
#define GAME_H

#include <button.h>

void game_init(void);
void game_run(void);
void game_over(void);
void game_display_score(void);
void button_pressed(int row);
void game_tick(void);

#endif /* game_h */