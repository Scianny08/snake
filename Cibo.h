#ifndef CIBO_H //se NON è ancora stato definito (if not defined) un segnaposto chiamato CIBO_H
#define CIBO_H //allora definiscilo ora e leggi il codice che segue

#include <raylib.h>
#include <deque>
#include "Utility.h"
using namespace std;

class Cibo {
private:
    Utility utility;

protected:
    // Metodo virtuale puro: rende la classe "Modello" (Astratta)
    virtual Image caricaImmagine() = 0;

public:
    Vector2 posizione;
    Texture2D texture;
    int limiteCampo;

    void genera(deque<Vector2> corpoSnake, int limite) {
        if (texture.id > 0) {
            UnloadTexture(texture);
        }
        
        limiteCampo = limite;

        Image img = caricaImmagine();
        texture = LoadTextureFromImage(img);
        UnloadImage(img); //distruttore dell'immagine (inutile dopo averla texturizzata)
        
        posizione = NuovaPos(corpoSnake);
    }


    //distruttore (della texture)
    virtual ~Cibo() {
        UnloadTexture(texture);
    }

    void Disegna(int grandezza) {
        //aumento percentuale
        float perc = 1.1;

        //scala per DrawTextureEx
        float scala = (float)grandezza / texture.width * perc;

        Vector2 posSchermo;

        //Calcolo coordinata x

        //trovo l'inizio della cella corretta sulla griglia (il punto in alto a sinistra)
        posSchermo.x = posizione.x * grandezza; 
        //aggiungo il margine esterno del gioco
        posSchermo.x += utility.offset; 
        //mi sposto nel punto centrale della cella
        posSchermo.x += (grandezza / 2.0f); 
        //torno indietro di metà della larghezza dell'immagine per centrarla
        posSchermo.x -= (scala * texture.width / 2.0f); 


        //Calcolo coordinata y
        
        //trovo l'inizio della cella corretta sulla griglia (il punto in alto a sinistra)
        posSchermo.y = posizione.y * grandezza; 
        //aggiungo il margine esterno del gioco
        posSchermo.y += utility.offset; 
        //mi sposto nel punto centrale della cella
        posSchermo.y += (grandezza / 2.0f); 
        //torno indietro di metà dell'altezza dell'immagine per centrarla
        posSchermo.y -= (scala * texture.height / 2.0f);

        // DrawTextureEx(texture, posizione, rotazione, scala, tinta)
        DrawTextureEx(texture, posSchermo, 0.0f, scala, WHITE);
    }

    Vector2 GeneraPosRandom() {
        float x = GetRandomValue(0, limiteCampo-1);
        float y = GetRandomValue(0, limiteCampo-1);

        return Vector2{x, y};
    }

    Vector2 NuovaPos(deque<Vector2> corpoSnake) {
        Vector2 pos = GeneraPosRandom();
        //finché la posizione NON è nel corpo del serpente, continua a cercarne una nuova
        while (utility.ElementoInDeque(pos, corpoSnake)) {
            pos = GeneraPosRandom();
        }
        return pos;
    }
};

#endif //fine controllo