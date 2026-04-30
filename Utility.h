#ifndef UTILITY_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define UTILITY_H //allora definiscilo ora

#include <raylib.h>
#include <raymath.h>
#include <deque>
using namespace std;

class Utility {
public:
    //offset per contorno del campo
    int offset = 75;
    double ultimoAggiornamentoTempo = 0;

    //uso di static per evitare di creare un oggetto di classe Utility
    bool ElementoInDeque( Vector2 elemento, deque<Vector2> deque) {
        for (unsigned int i = 0; i < deque.size(); i++) {
            if (Vector2Equals(deque[i], elemento)) {
                return true; //trovato
            }
        }
        return false; //non trovato
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

