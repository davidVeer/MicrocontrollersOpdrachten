#include <stdbool.h>

#ifndef GAME_H
#define GAME_H

bool GameIsRunning;

void game_init(void);
void game_run(void);
void game_over(void);
void game_display_score(void);

#endif /* game_h */