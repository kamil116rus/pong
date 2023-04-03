#include <stdio.h>


#define SIZE_X 80
#define SIZE_Y 25


void player_a();
void player_b();
int game();

int main() {
    if(game() == 1) {
        player_a();
    } else {
        player_b();
    }
    return 0;
}

int game() {
    int raket_a = 12, raket_b = 12; // начальные координаты ракеток по оси Y
    int ball_x = 40, ball_y = 12; // начальные координаты мяча
    int vector_x = 1, vector_y = 1; // начальное направление движения мяча по оси Х и оси Y


    return win;
}