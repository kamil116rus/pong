#include <stdio.h>

#define SIZE_X 80
#define SIZE_Y 25

void player_a();
void player_b();
int game();
void draw(int raket_a, int raket_b, int score_a, int score_b, int ball_x, int ball_y);
void ball(int raket_a, int raket_b, int *ball_x, int *ball_y, int *vector_x, int *vector_y);
int raket_a_yes(int raket_a, int ball_x, int ball_y, int vector_x, int vector_y);
int raket_b_yes(int raket_a, int ball_x, int ball_y, int vector_x, int vector_y);

int main() {
    if (game() == 1) {
        player_a();
    } else {
        player_b();
    }
    return 0;
}

int game() {
    int win = 0;
    int raket_a = 12, raket_b = 12;  // начальные координаты ракеток по оси Y
    int ball_x = 40, ball_y = 12;    // начальные координаты мяча
    // int vector_x = 1,
    // vector_y = 1; // начальное направление движения мяча по оси Х и оси Y
    int score_a = 0, score_b = 0;  // счет игры
    // int end_of_game = 0;          // флаг окончания игры
    // while(!end_of_game) {
    printf("\033[0d\033[2J");  // чистка экрана
    draw(raket_a, raket_b, score_a, score_b, ball_x, ball_y);

    //}

    return win;
}

void draw(int raket_a, int raket_b, int score_a, int score_b, int ball_x, int ball_y) {
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            if (j == SIZE_X - 1) {
                printf("*\n");
            } else if (i == 0 || j == 0 || i == SIZE_Y - 1) {
                printf("*");
            } else if ((i == raket_a || i - 1 == raket_a || i + 1 == raket_a) && j == 3) {
                printf("|");
            } else if ((i == raket_b || i - 1 == raket_b || i + 1 == raket_b) && j == SIZE_X - 4) {
                printf("|");
            } else if (i == ball_y && j == ball_x) {
                printf("o");
            } else if (i == SIZE_Y / 4 && j == SIZE_X / 4 && score_a >= 10) {
                printf("%d", score_a / 10);
            } else if (i == SIZE_Y / 4 && j == (SIZE_X / 4) + 1) {
                printf("%d", score_a % 10);
            } else if (i == SIZE_Y / 4 && j == SIZE_X - (SIZE_X / 4) && score_a >= 10) {
                printf("%d", score_b / 10);
            } else if (i == SIZE_Y / 4 && j == (SIZE_X - (SIZE_X / 4)) + 1) {
                printf("%d", score_b % 10);
            } else if (j == SIZE_X / 2) {
                printf("|");
            } else {
                printf(" ");
            }
        }
    }
}

void ball(int raket_a, int raket_b, int *ball_x, int *ball_y, int *vector_x, int *vector_y) {
    if (*ball_y == 1 || *ball_y == SIZE_Y - 2) {  //меняем направление при касании краев
        *vector_y *= -1;
    } else if (raket_a_yes(raket_a, *ball_x, *ball_y, *vector_x, *vector_y) == 1) {
        *vector_x *= -1;
    } else if (raket_a_yes(raket_a, *ball_x, *ball_y, *vector_x, *vector_y) == 2) {
        *vector_x *= -1;
        *vector_y *= -1;
    } else if (raket_b_yes(raket_b, *ball_x, *ball_y, *vector_x, *vector_y) == 1) {
        *vector_x *= -1;
    } else if (raket_b_yes(raket_b, *ball_x, *ball_y, *vector_x, *vector_y) == 2) {
        *vector_x *= -1;
        *vector_y *= -1;
    }
    *ball_x += *vector_x;
    *ball_y += *vector_y;
}
int raket_a_yes(int raket_a, int ball_x, int ball_y, int vector_x, int vector_y) {
    int temp = 0;
    if (ball_x == 4 && vector_x == -1) {
        if (ball_y == raket_a || ball_y == raket_a - 1 || ball_y == raket_a + 1) {
            temp = 1;
        } else if ((ball_y == raket_a - 2 && vector_y == 1) || (ball_y == raket_a + 2 && vector_y == -1)) {
            temp = 2;
        }
    }
    return temp;
}

int raket_b_yes(int raket_b, int ball_x, int ball_y, int vector_x, int vector_y) {
    int temp = 0;
    if (ball_x == SIZE_X - 5 && vector_x == 1) {
        if (ball_y == raket_b || ball_y == raket_b - 1 || ball_y == raket_b + 1) {
            temp = 1;
        } else if ((ball_y == raket_b - 2 && vector_y == 1) || (ball_y == raket_b + 2 && vector_y == -1)) {
            temp = 2;
        }
    }
    return temp;
}

void player_a() { printf("WUN 1"); }

void player_b() { printf("WUN 2"); }