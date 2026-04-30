#include <raylib.h>
#include "Gioco.h"
#include "Utility.h"
using namespace std;

int main () {
    int latoCampo = Gioco::latoCampo;
    int offset = Utility::offset;

    InitWindow(2*offset+latoCampo, 2*offset+latoCampo, "Snake");
        Gioco gioco = Gioco();

        SetTargetFPS(30);

        while (WindowShouldClose() == false) {
            BeginDrawing();
            // 1. gestione eventi
                gioco.ControllaEventi();
                
            // 2. aggiornare posizioni
                //il serpentesi muove ogni 200 millisecondi 
                //altrimenti si muoverebbe agli fps settati
                if (gioco.EventTriggered(0.2)) gioco.AggiornaSerpente();

            // 3. disegnare
                ClearBackground(gioco.verde);
                gioco.DisegnaCampo();
                gioco.Disegna();

            EndDrawing();
        }

    CloseWindow();
    return 0;
}