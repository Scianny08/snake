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
public:
    //static const permette l'uso esterno
    static const int grandezzaCella = 30;
    static const int numCelle = 25;

    double ultimoAggiornamentoTempo = 0;
    Snake snake = Snake();
    Cibo cibo = Cibo(snake.corpo, numCelle);
    Color verde = {173, 204, 96, 255};
    Color verdescuro = {43, 51, 24, 255};
    bool running = true;

    void Disegna() {
        cibo.Disegna(grandezzaCella);
        snake.Disegna(grandezzaCella, verdescuro);
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
        if (snake.MuoveDestra() && snake.direzione.x != -1) {
            snake.direzione = {1, 0};
            running = true;
        }
        // SINISTRA: Puoi andare a sinistra solo se NON stai andando a destra
        if (snake.MuoveSinistra() && snake.direzione.x != 1) {
            snake.direzione = {-1, 0};
            running = true;
        }
        // SOPRA: Puoi andare sopra solo se NON stai andando sotto
        if (snake.MuoveSopra() && snake.direzione.y != 1) {
            snake.direzione = {0, -1};
            running = true;
        }
        // SOTTO: Puoi andare sotto solo se NON stai andando sopra
        if (snake.MuoveSotto() && snake.direzione.y != -1) {
            snake.direzione = {0, 1};
            running = true;
        }
    }

    void CollisioneConCibo() {
        if (Vector2Equals(snake.corpo[0], cibo.posizione)) {
            cibo.posizione = cibo.NuovaPos(snake.corpo);
            snake.aggiuntaPezzo = true;
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

        if (Utility::ElementoInDeque(snake.corpo[0], senzaTesta)) {
            GameOver();
        }
    }

    void GameOver() {
        running = false;
        snake.Reset();
        cibo.posizione = cibo.NuovaPos(snake.corpo);
    }

    bool EventTriggered(double intervallo) {
        double tempoAttuale = GetTime();
        double tempoTrascorso = tempoAttuale - ultimoAggiornamentoTempo;
        
        if (tempoTrascorso >= intervallo) {
            ultimoAggiornamentoTempo = tempoAttuale;
            return true;
        }
        return false;
    }

};

#endif