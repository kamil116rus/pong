#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>      // для system
#include <sys/select.h>  // для kbhit
#include <termios.h>     // для kbhit
#include <unistd.h>      // для паузы

#define SIZE_X 80
#define SIZE_Y 25
#define MAX_SPEED 20000
#define MIN_SPEED 200000
#define STEP_SPEED 10000

void player_a();
void player_b();
int game();
void draw(int raket_a, int raket_b, int score_a, int score_b, int ball_x, int ball_y);
void ball(int raket_a, int raket_b, int *ball_x, int *ball_y, int *vector_x, int *vector_y);
int raket_a_yes(int raket_a, int ball_x, int ball_y, int vector_x, int vector_y);
int raket_b_yes(int raket_a, int ball_x, int ball_y, int vector_x, int vector_y);
char raket(int *raket_a, int *raket_b, int *speed);
int kbhit();
void counter(int *ball_x, int *ball_y, int raket_a, int raket_b, int *score_a, int *score_b);

int main() {
    if (game() == 1) {
        player_a();
    } else {
        player_b();
    }
    return 0;
}

int game() {
    int win = 0, speed = 150000;
    int raket_a = 12, raket_b = 12;  // начальные координаты ракеток по оси Y
    int ball_x = 40, ball_y = 12;    // начальные координаты мяча
    int vector_x = 1, vector_y = 1;  // начальное направление движения мяча
    int score_a = 0, score_b = 0;    // счет игры
    int end_of_game = 0;             // флаг окончания игры
    while (!end_of_game) {
        printf("\033[0d\033[2J");  // чистка экрана
        draw(raket_a, raket_b, score_a, score_b, ball_x, ball_y);
        char c = raket(&raket_a, &raket_b, &speed);
        printf("as");
        ball(raket_a, raket_b, &ball_x, &ball_y, &vector_x, &vector_y);
        counter(&ball_x, &ball_y, raket_a, raket_b, &score_a, &score_b);
        usleep(speed);
        if (c == 'q' || (score_a = 21 || score_b == 21)) {
            end_of_game = 1;
        }
    }
    if (score_a > score_b) {
        win = 1;
    } else {
        win = 2;
    }
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

// Функция считывания клавиатуры и изменения положения ракеток
char raket(int *raket_a, int *raket_b, int *speed) {
    system("stty -icanon crtkill");
    char c;
    while (kbhit() != 0) {
        switch (c = tolower(getchar())) {
            case 'a':
                if (*raket_a > 2) *raket_a -= 1;
                break;
            case 'b':
                if (*raket_a < SIZE_Y - 3) *raket_a += 1;
                break;
            case 'k':
                if (*raket_b > 2) *raket_b -= 1;
                break;
            case 'm':
                if (*raket_b < SIZE_Y - 3) *raket_b += 1;
                break;
            case 'f':
                if (*speed > MIN_SPEED) *speed -= STEP_SPEED;
                break;
            case 'v':
                if (*speed < MAX_SPEED) *speed += STEP_SPEED;
                break;
        }
    }
    return c;
}

int kbhit() {  // Функция kbhit() возвращает истину, если нажата какая-либо
               // клавиша на клавиатуре.
    struct timeval tv;  // В против­ном случае возвращается 0.
    fd_set fds;  //  В любом случае код клавиши не удаляется из входного буфера.
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

// Функция подсчета голов
void counter(int *ball_x, int *ball_y, int raket_a, int raket_b, int *score_a, int *score_b) {
    if (*ball_x == 1) {
        *score_b += 1;
        *ball_x = SIZE_X - 5;
        *ball_y = raket_b;
    }
    if (*ball_x == SIZE_X - 2) {
        *score_a += 1;
        *ball_x = 4;
        *ball_y = raket_a;
    }
}

void player_a() { printf("WIN 1"); }

void player_b() { printf("WIN 2"); }