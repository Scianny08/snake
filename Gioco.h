#ifndef GIOCO_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define GIOCO_H //allora definiscilo ora

#include <raylib.h>
#include <raymath.h>
#include "Cibo.h"
#include "Snake.h"
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

    void Disegna() {
        cibo.Disegna(grandezzaCella);
        snake.Disegna(grandezzaCella, verdescuro);
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

    void CollisioneConCibo() {
        if (Vector2Equals(snake.corpo[0], cibo.posizione)) {
            cibo.posizione = cibo.NuovaPos(snake.corpo);
            snake.aggiuntaPezzo = true;
        } //fine if
    } //fine metodo
};

#endif