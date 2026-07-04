#include <stdbool.h>

#ifndef game_h
#define game_h

bool GameIsRunning;

void game_init(void);
void game_run(void);
void game_over(void);
void game_display_score(void);

#endif /* game_h */