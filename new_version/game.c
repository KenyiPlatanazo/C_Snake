#include "game.h"
#include "assert.h"
#include "snake.h"
#include "time.h"
#include <SDL2/SDL_video.h>

bool sdl_initialize(struct Game *game) {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return true;
  }
  game->window =
      SDL_CreateWindow(WINDOWS_TITLE, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!game->window) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return true;
  }
  game->renderer = SDL_CreateRenderer(game->window, -1, 0);
  if (!game->renderer) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return true;
  }
  init_board(game);
  return false;
}
void game_cleanup(struct Game *game, int exit_status) {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  exit(1);
}

void init_board(struct Game *game) {
  for (int i = 0; i < ROW_COUNT; i++) {
    for (int j = 0; j < COL_COUNT; j++) {
      game->board[i][j].cell.type = BOARD;
      game->board[i][j].cell.x = i;
      game->board[i][j].cell.y = j;
      game->board[i][j].rect.x = i * GRID_CELL_SIZE;
      game->board[i][j].rect.y = j * GRID_CELL_SIZE;
      game->board[i][j].rect.w = GRID_CELL_SIZE;
      game->board[i][j].rect.h = GRID_CELL_SIZE;
    }
  }
  // For the demonstration, the moving cell will always start in the middle of
  // the grid
  game->snake = init_snake();
}

// TODO: Make a better assertion to make sure the board is correctly initialized
void draw_grid(struct Game *game) {
  SDL_Color red = {255, 0, 0, 255};
  SDL_Color green = {0, 255, 0, 255};
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color black = {0, 0, 0, 255};
  SDL_RenderClear(game->renderer);
  for (int i = 0; i < ROW_COUNT; i++) {
    for (int j = 0; j < COL_COUNT; j++) {
      // Fills the cell with color
      switch (game->board[i][j].cell.type) {
      case FOOD:
        SDL_SetRenderDrawColor(game->renderer, red.r, red.g, red.b, red.a);
        break;
      case SNAKE_PART:
        SDL_SetRenderDrawColor(game->renderer, green.r, green.g, green.b,
                               green.a);
        break;
      case BOARD:
        SDL_SetRenderDrawColor(game->renderer, white.r, white.g, white.b,
                               white.a);
        break;
      }
      SDL_RenderFillRect(game->renderer, &game->board[i][j].rect);
      // Adds a black frame to each cell of the grid
      SDL_SetRenderDrawColor(game->renderer, black.r, black.g, black.b,
                             black.a);
      SDL_RenderDrawRect(game->renderer, &game->board[i][j].rect);
    }
  }
  SDL_RenderPresent(game->renderer);
}

void handle_inputs(struct Game *game, SDL_Event event) {
  switch (event.type) {
  case SDL_QUIT:
    game_cleanup(game, EXIT_SUCCESS);
    break;
  case SDL_KEYDOWN:
    move(game, event);
    break;
    /*
case SDL_MOUSEBUTTONDOWN:
  game->grid_cursor.x = (event.motion.x / GRID_CELL_SIZE) * GRID_CELL_SIZE;
  game->grid_cursor.y = (event.motion.y / GRID_CELL_SIZE) * GRID_CELL_SIZE;
  break;
    */
  default:
    break;
  }
}
void move(struct Game *game, SDL_Event event) {
  struct Cell *snake_head = game->snake->head->cell;
  struct Cell *next_cell = NULL;
  switch (event.key.keysym.scancode) {
  case SDL_SCANCODE_ESCAPE:
    game_cleanup(game, 0);
    break;
  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
    if (snake_head->y - 1 < 0) {
      game->game_over = true;
      game_cleanup(game, EXIT_SUCCESS);
    }
    next_cell = &game->board[snake_head->x][snake_head->y - 1].cell;
    // TODO: Reword this thing
    // Checks if it touches food
    /*
    if (next_cell->type == FOOD) {
      new_node(game->snake, game->board[snake_head->x][snake_head->y - 1].cell);
    } else {
      snake_head->type = BOARD;
    }
    */
    snake_head->type = BOARD;
    snake_head = next_cell;
    snake_head->type = SNAKE_PART;
    break;
  case SDL_SCANCODE_S:
  case SDL_SCANCODE_DOWN:
    if (snake_head->y + 1 >= COL_COUNT) {
      game->game_over = true;
      game_cleanup(game, EXIT_SUCCESS);
    }
    snake_head->type = BOARD;
    snake_head = &game->board[snake_head->x][snake_head->y + 1].cell;
    snake_head->type = SNAKE_PART;
    break;
  case SDL_SCANCODE_A:
  case SDL_SCANCODE_LEFT:
    if (snake_head->x - 1 < 0) {
      game->game_over = true;
      game_cleanup(game, EXIT_SUCCESS);
    }
    snake_head->type = BOARD;
    snake_head = &game->board[snake_head->x - 1][snake_head->y].cell;
    snake_head->type = SNAKE_PART;
    break;
  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:
    if (snake_head->x + 1 >= ROW_COUNT) {
      game->game_over = true;
      game_cleanup(game, EXIT_SUCCESS);
    }
    snake_head->type = BOARD;
    snake_head = &game->board[snake_head->x + 1][snake_head->y].cell;
    snake_head->type = SNAKE_PART;
    break;
  default:
    break;
  }
}

void create_food(struct Game *game) {
  srand(time(NULL));
  struct Cell *food = &game->board[rand() % ROW_COUNT][rand() % COL_COUNT].cell;
  // We try until we get a valid cell
  while (food->type != BOARD) {
    food = &game->board[rand() % ROW_COUNT][rand() % COL_COUNT].cell;
  }
  food->type = FOOD;
}

// TODO: Refactor this shit
// We assume the snake head already changed its position. This function only
// updates the rest of the snake's body
void update_snake(struct Node *node, struct Cell *previous_cell) {
  if (node != NULL) {
    return;
  }
  assert(node != NULL);
  assert(node->cell != NULL);
  node->cell = previous_cell;
  update_snake(node->next, node->cell);
}
