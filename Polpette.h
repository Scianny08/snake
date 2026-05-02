#ifndef POLPETTE_H //se NON è ancora stato definito (if not defined) un segnaposto chiamato CIBO_H
#define POLPETTE_H //allora definiscilo ora e leggi il codice che segue

#include <raylib.h>
#include <deque>
#include "Utility.h"
#include "Cibo.h"
using namespace std;

class Polpette: public Cibo {
    public:
        Image caricaImmagine() override {
            return LoadImage("Grafica/polpette.png");
        }
};

#endif