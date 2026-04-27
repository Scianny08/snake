#ifndef CIBO_H //se NON è ancora stato definito (if not defined) un segnaposto chiamato CIBO_H
#define CIBO_H //allora definiscilo ora e leggi il codice che segue

#include <raylib.h>
#include <deque>
using namespace std;

class Cibo {
public:
    Vector2 posizione;
    Texture2D mela;
    int limiteCampo;

    //costruttore
    Cibo(deque<Vector2> corpoSnake, int limite) {
        limiteCampo = limite;

        Image imgMela = LoadImage("Grafica/mela.png");
        mela = LoadTextureFromImage(imgMela);
        UnloadImage(imgMela); //distruttore dell'immagine (inutile dopo averla texturizzata)
        
        posizione = NuovaPos(corpoSnake);
    }

    //distruttore (della texture)
    ~Cibo() {
        UnloadTexture(mela);
    }

    void Disegna(int grandezza) {
        //scala per DrawTextureEx
        float scala = (float)grandezza / mela.width * 1.1f;
        
        //centra la mela dentro la cella
        float offset = (grandezza - grandezza * 1.1f) / 2.0f;

        //moltiplico le coordinate per la grandezza in modo tale da adattarle al campo di gioco
        Vector2 posSchermo = { 
            posizione.x * grandezza + offset, 
            posizione.y * grandezza + offset 
        };

        // DrawTextureEx(texture, posizione, rotazione, scala, tinta)
        DrawTextureEx(mela, posSchermo, 0.0f, scala, WHITE);
    }

    bool ElementoInDeque(deque<Vector2> corpoSerpente, Vector2 elemento) {
        for (unsigned int i = 0; i < corpoSerpente.size(); i++) {
            if (Vector2Equals(corpoSerpente[i], elemento)) {
                return true; //trovato (non buono)
            }
        }
        return false; //non trovato (buono)
    }

    Vector2 GeneraPosRandom() {
        float x = GetRandomValue(0, limiteCampo-1);
        float y = GetRandomValue(0, limiteCampo-1);

        return Vector2{x, y};
    }

    Vector2 NuovaPos(deque<Vector2> corpoSnake) {
        Vector2 pos = GeneraPosRandom();
        //finché la posizione NON è nel corpo del serpente, continua a cercarne una nuova
        while (ElementoInDeque(corpoSnake, pos)) {
            pos = GeneraPosRandom();
        }
        return pos;
    }
};

#endif //fine controllo