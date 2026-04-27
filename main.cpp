#include <iostream>
#include <raylib.h>
#include "Gioco.h"
using namespace std;

int main () {
    int latoCampo = Gioco::grandezzaCella * Gioco::numCelle;

    InitWindow(latoCampo, latoCampo, "Snake");
        Gioco gioco = Gioco();
        //riferimenti agli attributi di Gioco
        Snake &snake = gioco.snake; 

        SetTargetFPS(30);

        while (WindowShouldClose() == false) {
            BeginDrawing();
            // 1. gestione eventi
                //se vado in una direzione, non posso andare nella direzione opposta
                if (snake.MuoveDestra() && snake.direzione.x != -1)  snake.direzione = {1, 0};  //destra
                if (snake.MuoveSinistra() && snake.direzione.x != 1) snake.direzione = {-1, 0}; //sinistra
                if (snake.MuoveSopra() && snake.direzione.y != 1)    snake.direzione = {0, -1}; //sopra
                if (snake.MuoveSotto() && snake.direzione.y != -1)   snake.direzione = {0, 1};  //sotto

                gioco.CollisioneConCibo();
                
            // 2. aggiornare posizioni
                //il serpentesi muove ogni 200 millisecondi 
                //altrimenti si muoverebbe agli fps settati
                if (gioco.EventTriggered(0.2)) snake.AggiornaPos();

            // 3. disegnare
                ClearBackground(gioco.verde);
                gioco.Disegna();

            EndDrawing();
        }

    CloseWindow();
    return 0;
}