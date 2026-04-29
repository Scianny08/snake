#ifndef UTILITY_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define UTILITY_H //allora definiscilo ora

#include <raylib.h>
#include <raymath.h>
#include <deque>
using namespace std;

class Utility {
public:
    //uso di static per evitare di creare un oggetto di classe Utility
    static bool ElementoInDeque( Vector2 elemento, deque<Vector2> deque) {
        for (unsigned int i = 0; i < deque.size(); i++) {
            if (Vector2Equals(deque[i], elemento)) {
                return true; //trovato
            }
        }
        return false; //non trovato
    }
};
#endif

