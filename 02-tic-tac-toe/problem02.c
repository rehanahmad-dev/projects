#include <stdio.h>

char board[3][3];

void create_board() {
  for (int count_no1 = 0; count_no1 < 3; count_no1++) {
    for (int count_no2 = 0; count_no2 < 3; count_no2++) {
      board[count_no1][count_no2] = ' ';
    }
  }
}

void display_board() {
  printf("\nTic-Tac-Toe\n\n");
  for (int count_no1 = 0; count_no1 < 3; count_no1++) {
    for (int count_no2 = 0; count_no2 < 3; count_no2++) {
      printf(" %c ", board[count_no1][count_no2]);
      if (count_no2 < 2) {
        printf("|");
      }
    }
    printf("\n");
    if (count_no1 < 2) {
      printf("---|---|---\n");
    }
  }
  printf("\n");
}

void get_input(char player, int* row, int* col) {
  printf("Player %c's turn. Enter row (0-2) and column (0-2): ", player);
  scanf("%d %d", row, col);
}
int check_win(char player) {
  for (int count_no1 = 0; count_no1 < 3; count_no1++) {
    if (board[count_no1][0] == player && board[count_no1][1] == player &&
        board[count_no1][2] == player) {
      return 1;
    }
    if (board[0][count_no1] == player && board[1][count_no1] == player &&
        board[2][count_no1] == player) {
      return 1;
    }
  }
  if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
    return 1;
  }
  if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
    return 1;
  }
  return 0;
}

int check_draw() {
  for (int count_no1 = 0; count_no1 < 3; count_no1++) {
    for (int count_no2 = 0; count_no2 < 3; count_no2++) {
      if (board[count_no1][count_no2] == ' ') {
        return 0;
      }
    }
  }
  return 1;
}

int main() {
  char current_player;
  int row, col;
  int play_again = 1;

  while (play_again == 1) {
    create_board();
    current_player = 'X';
    int game_over = 0;

    while (!game_over) {
      display_board();
      get_input(current_player, &row, &col);

      if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
        printf("Invalid move. Try again.\n");
      } else {
        board[row][col] = current_player;
        if (check_win(current_player)) {
          display_board();
          printf("Player %c wins!\n", current_player);
          game_over = 1;
        } else if (check_draw()) {
          display_board();
          printf("It's a draw!\n");
          game_over = 1;
        } else {
          current_player = (current_player == 'X') ? 'O' : 'X';
        }
      }
    }

    do {
      printf("Do you want to play again?\nType (1 to restart, 0 to exit) : ");
      scanf("%d", &play_again);
    } while (play_again != 0 && play_again != 1);
  }

  return 0;
}
