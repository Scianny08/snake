#ifndef SNAKE_H //se NON è ancora stato definito (if not defined) un simbolo/identificatore chiamato SNAKE_H
#define SNAKE_H //allora definiscilo ora

#include "Utility.h"
#include <raylib.h>
#include <raymath.h>
#include <deque> //deque: struttura che permette di fare pop e push sia in testa sia in coda
using namespace std;

class Snake {
public:
    //testa, corpo, coda
    deque<Vector2> corpo = {
        Vector2{6, 9}, //testa [0]
        Vector2{5, 9}, //corpo [1]
        Vector2{4, 9}  //coda  [2]
    };
    Vector2 direzione = {1, 0};
    bool haMangiato = false;

    void Disegna(int grandezzaCella, Color colore) {
        unsigned int i; //unsigned perché corpo.size() restituisce un senza-segno
        //float perché Rectangle è composto da float
        float x, y, posX, posY;
        float grandCella = (float)grandezzaCella;

        for (i=0; i<corpo.size(); i++) {
            x = corpo[i].x;
            y = corpo[i].y;
            posX = x*grandCella + Utility::offset;
            posY = y*grandCella + Utility::offset;

            Rectangle cella = Rectangle{posX, posY, grandCella, grandCella};

            //Rectangle rett, float rotondita, int segmenti, Color colore
            //la rotondità determina quanto è curvo l'angolo (da 0 a 1)
            //i segnmenti quanto è liscia la curva
            DrawRectangleRounded(cella, 0.5, 6, colore);
        }
    }

    void Aggiorna() {
        //somma vettori
        //es. testa serpente in {7,9} + {1,0} (direzione: destra) = aggiungi in testa alla deque a destra {8,9}
        corpo.push_front(Vector2Add(corpo[0], direzione)); //aggiungi avanti

        if (haMangiato) {
            haMangiato = false;
        } else {
            corpo.pop_back(); //tolgo dietro perché sono andato avanti
        }
    }

    void Reset() {
        //posizione, dimensione e direzione iniziali
        corpo = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direzione = {1, 0};
    }

    //comandi
    bool MuoveSu() {return IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);}
    bool MuoveGiu() {return IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);}
    bool MuoveDestra() {return IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);}
    bool MuoveSinistra() {return IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);}
};

#endif