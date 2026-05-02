#ifndef MELA_H //se NON è ancora stato definito (if not defined) un segnaposto chiamato CIBO_H
#define MELA_H //allora definiscilo ora e leggi il codice che segue

#include <raylib.h>
#include <deque>
#include "Utility.h"
#include "Cibo.h"
using namespace std;

class Mela: public Cibo {
    public:
        Image caricaImmagine() override {
            return LoadImage("Grafica/mela.png");
        }
};

#endif