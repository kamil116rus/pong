#include <stdio.h>

#define SIZE_X 80
#define SIZE_Y 25

void player_a();
void player_b();
int game();
void draw(int raket_a, int raket_b, int score_a, int score_b, int ball_x,
          int ball_y);

int main() {
  if (game() == 1) {
    player_a();
  } else {
    player_b();
  }
  return 0;
}

int game() {
  int win;
  int raket_a = 12, raket_b = 12; // начальные координаты ракеток по оси Y
  int ball_x = 40, ball_y = 12; // начальные координаты мяча
  int vector_x = 1,
      vector_y = 1; // начальное направление движения мяча по оси Х и оси Y
  int score_a = 0, score_b = 0; // счет игры
  int end_of_game = 0;          // флаг окончания игры
                                // while(!end_of_game) {
  printf("\033[0d\033[2J");     // чистка экрана
  draw(raket_a, raket_b, score_a, score_b, ball_x, ball_y);
  //}

  return win;
}

void draw(int raket_a, int raket_b, int score_a, int score_b, int ball_x,
          int ball_y) {
  for (int i = 0; i < SIZE_Y; i++) {
    for (int j = 0; j < SIZE_X; j++) {
      if (j == SIZE_X - 1) {
        printf("*\n");
      } else if (i == 0 || j == 0 || i == SIZE_Y - 1) {
        printf("*");
      }else if((i == raket_a  || i - 1 = raket_a || i + 1 == raket_a) && j == 3) {
        printf("|");
      } else if((i == raket_b  || i - 1 = raket_b || i + 1 == raket_b) && j == SIZE_X - 4) {
        printf("|");
      } else if(i == ball_y && j == ball_x) {
        printf("o");
      } else if(i == SIZE_X / 4 && j == SIZE_Y / 4) {///////////////////////////////////////////////////
        printf("|");
      }else {
        printf(" ");
      }
    }
  }
}