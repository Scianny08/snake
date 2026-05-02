#ifndef GIOCO_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define GIOCO_H //allora definiscilo ora

#include <raylib.h>
#include <raymath.h>
#include <deque>

#include "Mela.h"
#include "Birra.h"
#include "Polpette.h"

#include "Snake.h"

#include "Utility.h"

using namespace std;

class Gioco {
private:
    Utility utility;
    Cibo* puntatoreCibo = nullptr; //puntatore alla classe cibo

public:
    int grandezzaCella = 30;
    int numCelle = 20;
    int offset = utility.offset;
    
    Snake snake = Snake();

    Mela mela;
    Polpette polpette;
    Birra birra;
    int tipoCibo = 0;

    Color verdechiaro = {170, 215, 81, 255};
    Color verde = {162, 209, 73, 255};
    Color verdescuro = {43, 51, 24, 255};

    bool running = false;
    int punteggio = 0;

    float calcolaCampoGioco() {
        return grandezzaCella*numCelle;
    }

    void Disegna() {
        puntatoreCibo->Disegna(grandezzaCella);
        snake.Disegna(grandezzaCella, verdescuro);
    }

    void generaCibo() {
        //distruzione: se il puntatore non è vuoto, elimina il vecchio oggetto
        if (puntatoreCibo != nullptr) {
            delete puntatoreCibo;
            puntatoreCibo = nullptr; // reset a null
        }

        int chanceSpawining = GetRandomValue(1, 100);

        if (chanceSpawining <= 70) {
            tipoCibo = 0; //mela 70%
        } else if (chanceSpawining <= 90) {
            tipoCibo = 1; //birra 20%
        } else {
            tipoCibo = 2; //polpette 10%
        }

        switch (tipoCibo) {
            case 0: puntatoreCibo = new Mela(); break;
            case 1: puntatoreCibo = new Birra(); break;
            case 2: puntatoreCibo = new Polpette(); break;
        }
        puntatoreCibo->genera(snake.corpo, numCelle);
    }

    void AggiornaSerpente() {
        if (running) {
            snake.Aggiorna();
        }
    }

    int ControllaCollisioni() {
        if (running) {
            CollisioneConCibo();
            
            if (CollisioneConCorpo()) {
                return 1;
            }

            if (CollisioneConBordi()) {
                return 2;
            }
        }
        return 0;
    }

    void ControllaComandi() {
        //se vado in una direzione, non posso andare nella direzione opposta
        //destra
        if (snake.MuoveDestra() && snake.direzione.x != -1) {
            snake.direzione = {1, 0};
        }
        //sinistra
        if (snake.MuoveSinistra() && snake.direzione.x != 1) {
            snake.direzione = {-1, 0};
        }
        //su
        if (snake.MuoveSu() && snake.direzione.y != 1) {
            snake.direzione = {0, -1};
        }
        //giu
        if (snake.MuoveGiu() && snake.direzione.y != -1) {
            snake.direzione = {0, 1};
        }
    }

    void CollisioneConCibo() {
        if (Vector2Equals(snake.corpo[0], puntatoreCibo->posizione)) {
            puntatoreCibo->posizione = puntatoreCibo->NuovaPos(snake.corpo);

            snake.haMangiato = true;

            punteggio++;

            //quale cibo?
            switch (tipoCibo) {
                case 0: //mela
                    snake.velocita = 200; //normale
                    snake.crescita = 1;
                    break;

                case 1:
                    snake.velocita = 150; //aumenta
                    snake.crescita = 2; //diventa ciccione
                    break;

                case 2:
                    snake.velocita = 400; //diminuisce
                    snake.crescita = 3; //diventa un obeso
                    break;
            }

            //cancella vecchio cibo
            generaCibo();
        } //fine if
    } //fine metodo

    bool CollisioneConBordi() {
        bool toccatoDestra = (snake.corpo[0].x >= numCelle);
        bool toccatoSinistra = (snake.corpo[0].x < 0);
        bool toccatoSotto = (snake.corpo[0].y >= numCelle);
        bool toccatoSopra = (snake.corpo[0].y < 0);

        if (toccatoDestra || toccatoSinistra || toccatoSotto || toccatoSopra) {
            GameOver();
            return true; //collisione
        }
        return false;
    }

    bool CollisioneConCorpo() {
        deque<Vector2> senzaTesta = snake.corpo;
        senzaTesta.pop_front();

        if (utility.ElementoInDeque(snake.corpo[0], senzaTesta)) {
            GameOver();
            return true; //collisione
        }
        return false;
    }

    void resetPunti() {
        punteggio = 0;
    }
    
    void GameOver() {
        running = false;
        snake.Reset();
        puntatoreCibo->posizione = puntatoreCibo->NuovaPos(snake.corpo);
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
        Rectangle bordo = {(float)offset-5, (float)offset-5, calcolaCampoGioco()+10, calcolaCampoGioco()+10};
        DrawRectangleLinesEx(bordo, 5, verdescuro);

        DisegnaScacchiera();
    }
    
};

#endif