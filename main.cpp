#include <raylib.h>
#include "Gioco.h"
#include "Utility.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
using namespace std;


int main () {
    Gioco gioco;
    Utility utility;

    int offset = utility.offset;
    float latoCampo = 2*offset+gioco.campo;
    double velocitaSerpente = 200; //millisecondi

    float btnGiocaLarghezza = 200;
    float btnGiocaAltezza = 60;
    const char* nomeGioco = "Snake Matico";
    const char* msgMorte = "";
    float larghezzaNomeGioco60 = 0;
    float larghezzaMsgMorte = 0;
    int tipoCollisione = 0; //1: corpo, 2: bordi

    InitWindow(latoCampo, latoCampo, nomeGioco);
        SetTargetFPS(30);

        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
        gioco.generaCibo(); //primo cibo

        while (WindowShouldClose() == false) {
            BeginDrawing();
            
            // 1. gestione eventi
                gioco.ControllaComandi();
                
            // 2. aggiornare posizioni
                //il serpente si muove ogni velocitaSerpente millisecondi
                //altrimenti si muoverebbe agli fps settati
                //devo controllare se il gioco runna altrimenti faccio controlli inutili
                if (utility.EventTriggered(velocitaSerpente/1000) && gioco.running) {
                    gioco.AggiornaSerpente();
                    //il controllo avviene dopo il movimento e prima del disegno,
                    //in questo modo il serpente non esce dal campo se va contro il bordo
                    tipoCollisione = gioco.ControllaCollisioni();
                }

            // 3. disegnare
                ClearBackground(gioco.verde);

                gioco.DisegnaCampo();
                gioco.Disegna();

                if (!gioco.running) {
                    //NON RUNNING

                    //sfondo scuro
                    DrawRectangle(0, 0, latoCampo, latoCampo, {0, 0, 0, 192});

                    //definizione del rettangolo gioca per riusarlo
                    Rectangle rectGioca = {
                        latoCampo/2 - btnGiocaLarghezza/2, //x
                        latoCampo/2 - btnGiocaAltezza/2,   //y
                        btnGiocaLarghezza,                 //larghezza
                        btnGiocaAltezza                    //altezza
                    };

                    //controllo hover
                    if (CheckCollisionPointRec(GetMousePosition(), rectGioca)) {
                        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); //cambia in manina
                    } else {
                        SetMouseCursor(MOUSE_CURSOR_DEFAULT); //torna freccia
                    }

                    larghezzaNomeGioco60 = MeasureText(nomeGioco, 60);
                    DrawText(nomeGioco, latoCampo/2-larghezzaNomeGioco60/2, 200, 60, WHITE);

                    if (tipoCollisione != 0) { //se sono morto
                        if (tipoCollisione == 1) { //da corpo
                            msgMorte = "Hai sbattuto contro te stesso. Hai perso.";
                        } else if (tipoCollisione == 2) { //da bordi
                            msgMorte = "Hai urtato contro il bordo. Hai perso.";
                        }

                        larghezzaMsgMorte = MeasureText(msgMorte, 20);
                        DrawText(msgMorte, latoCampo/2-larghezzaMsgMorte/2, 300, 20, WHITE);
                    }

                    //disegno bottone e gestione del clic
                    if (GuiButton(rectGioca, "Gioca")) {
                        gioco.running = true;
                        SetMouseCursor(MOUSE_CURSOR_DEFAULT); //cursore normale quando clicco su gioca
                    }
                } else {
                    //RUNNING

                    //cursore normale durante la partita
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                    //nome gioco e punti
                    //testo, x, y, fontsize, colore
                    DrawText(nomeGioco, offset-5, 10, 35, WHITE);
                    DrawText(TextFormat("Punteggio: %i", gioco.punteggio), offset-5, 45, 20, WHITE);
                }

            EndDrawing();   
        }

    CloseWindow();
    return 0;
}