#ifndef GIOCO_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define GIOCO_H //allora definiscilo ora

#include <raylib.h>
#include <raymath.h>
#include <deque>
#include "Cibo.h"
#include "Snake.h"
#include "Utility.h"
using namespace std;

class Gioco {
private:
    Utility utility;

public:
    int grandezzaCella = 30;
    int numCelle = 25;
    int offset = utility.offset;
    float latoCampo = grandezzaCella*numCelle;
    
    Snake snake = Snake();
    Cibo cibo;

    Color verdechiaro = {170, 215, 81, 255};
    Color verde = {162, 209, 73, 255};
    Color verdescuro = {43, 51, 24, 255};

    bool running = true;
    int punteggio = 0;

    
    void Disegna() {
        cibo.Disegna(grandezzaCella);
        snake.Disegna(grandezzaCella, verdescuro);
    }

    void generaCibo() {
        cibo.generaCibo(snake.corpo, numCelle);
    }

    void AggiornaSerpente() {
        if (running) {
            snake.Aggiorna();
        }
    }

    void ControllaEventi() {
        ControllaComandi();
        if (running) {
            CollisioneConCibo();
            CollisioneConBordi();
            CollisioneConCorpo();
        }
    }

    void ControllaComandi() {
        //se vado in una direzione, non posso andare nella direzione opposta
        //destra
        if (snake.MuoveDestra() && snake.direzione.x != -1) {
            snake.direzione = {1, 0};
            running = true;
        }
        //sinistra
        if (snake.MuoveSinistra() && snake.direzione.x != 1) {
            snake.direzione = {-1, 0};
            running = true;
        }
        //su
        if (snake.MuoveSu() && snake.direzione.y != 1) {
            snake.direzione = {0, -1};
            running = true;
        }
        //giu
        if (snake.MuoveGiu() && snake.direzione.y != -1) {
            snake.direzione = {0, 1};
            running = true;
        }
    }

    void CollisioneConCibo() {
        if (Vector2Equals(snake.corpo[0], cibo.posizione)) {
            cibo.posizione = cibo.NuovaPos(snake.corpo);
            snake.haMangiato = true;
            punteggio++;
        } //fine if
    } //fine metodo

    void CollisioneConBordi() {
        bool toccatoDestra = (snake.corpo[0].x == numCelle);
        bool toccatoSinistra = (snake.corpo[0].x == -1);
        bool toccatoSotto = (snake.corpo[0].y == numCelle);
        bool toccatoSopra = (snake.corpo[0].y == -1);

        if (toccatoDestra || toccatoSinistra || toccatoSotto || toccatoSopra) {
            GameOver();
        }
    }

    void CollisioneConCorpo() {
        deque<Vector2> senzaTesta = snake.corpo;
        senzaTesta.pop_front();

        if (utility.ElementoInDeque(snake.corpo[0], senzaTesta)) {
            GameOver();
        }
    }

    void GameOver() {
        running = false;
        snake.Reset();
        cibo.posizione = cibo.NuovaPos(snake.corpo);
        punteggio = 0;
    }

    void DisegnaScacchiera() {
        int x, y;
        Color colore;
        for (int i=0; i<numCelle; i++) {
            for (int j=0; j<numCelle; j++) {
                colore = verdechiaro;
                if ((i+j) % 2 == 0) {
                    colore = verde;
                }

                x = i*grandezzaCella + offset;
                y = j*grandezzaCella + offset;
                DrawRectangle(x, y, grandezzaCella, grandezzaCella, colore);
            }
        }
    }

    void DisegnaCampo() {
        //Bordo esterno: rettangolo, spessore, colore
        //uso di offset-5 per centrare il bordo rispetto al campo da in altro a sinistra
        //se non usassi -5 (meno lo spessore) il bordo entrebbe nel campo da gioco
        //+10 viene usato perché sono già andato indietro di 5
        //lo spessore essendo di 5 devo sommarlo a 5 perché altrimenti entrebbe nel campo da gioco giù a destra
        Rectangle bordo = {(float)offset-5, (float)offset-5, latoCampo+10, latoCampo+10};
        DrawRectangleLinesEx(bordo, 5, verdescuro);

        DisegnaScacchiera();
    }
    
};

#endif