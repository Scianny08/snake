#include <raylib.h>
#include "Gioco.h"
#include "Utility.h"
using namespace std;

int main () {
    Gioco gioco;
    Utility utility;
    float latoCampo = gioco.latoCampo;
    int offset = utility.offset;

    InitWindow(2*offset+latoCampo, 2*offset+latoCampo, "Snake");

        gioco.generaCibo();
        SetTargetFPS(30);

        while (WindowShouldClose() == false) {
            BeginDrawing();
            // 1. gestione eventi

                gioco.ControllaEventi();
                
            // 2. aggiornare posizioni
                //il serpentesi muove ogni 200 millisecondi 
                //altrimenti si muoverebbe agli fps settati
                if (utility.EventTriggered(0.2)) gioco.AggiornaSerpente();

            // 3. disegnare
                ClearBackground(gioco.verde);
                
                gioco.DisegnaCampo();

                //testo, x, y, fontsize, colore
                DrawText("Snake Matico", offset-5, 10, 35, WHITE);
                DrawText(TextFormat("Punteggio: %i", gioco.punteggio), offset-5, 45, 20, WHITE);

                gioco.Disegna();

            EndDrawing();
        }

    CloseWindow();
    return 0;
}