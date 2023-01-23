#include "mbed.h"
#ifndef MBED_ULCD32PT_H
#define MBED_ULCD32PT_H
//debugmode = 1 activer , debugmode = 0 desactiver
#ifndef DEBUGMODE
#define DEBUGMODE 0
#endif
//on définie les couleurs
#define WHITE 0xFFFFFC
#define BLACK 0x000000
#define RED   0xFF2300
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define LGREY 0x00BFBF
#define DGREY 0x005F5F
class ULCD32PT {
    public :
    ULCD32PT(PinName tx, PinName rx);
//graphique
    void rectangle(int x1, int y1 , int x2, int y2,int color); // faire un
     rectangle
    void rectangleF(int x1, int y1 , int x2, int y2,int color); // faire un
     rectangle remplis
    void cercle(int x, int y, int rad,int color); // Circle at X=100 (Hex
     0x00, 0x64), Y=300 (Hex 0x01, 0x2C), of Radius=20 (0x00, 0x14)
    void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int
     color); // Page 47 du doc
    void ligne(int x1, int y1, int x2, int y2, int color); // faire un
     ligne
    void putP(int x, int y, int color); // Mettre un pixel au cordonné x, y
    void moveOr(int x, int y); // déplacer l'origine du curseur
    void pixel(int x, int y, int color);
    //texte
    void variable(float variable ); // ecrire une variable
    void texte(int l1, int l2, int l3, int l4, int l5, int l6); // envoyer
     un texte caract = 'C','0' ...
    void tailleT(int mult); //0x02 = Hauteur du texte
    void colorTP(int color); // couleur texte
    void colorTB(int color); // couleur de l'arrière plan du texte
    void fondT(int mode); // 0x00 = 1 = OFF, 0x01 = 0 = ON
    void underT(int mode); //0x01 = 1 = ON, 0x00 = 0 = OFF
    void multiT(int value); // Page 34 de la DOC*/
    void phrase(char *); // ecrire un long texte
    void largT(int mult); // largeur du texte
    void Espace(int pix); // Espacement des charactères
    void wrap(int num); // ???
    void attrib(int num); // voir les styles du text
    void under(int num); // sousligné 1 = ON , 0 = OFF
    void opac(int num); // opacité  1 = Opac, 0 = Transparant
    void italic(int num); // italique 1 = ON, 0 = OFF
    void chiffre (int numero); // affiche un simple numéro
    //setup
    void font(int num); // 0 = FONT1, 1 = FONT2, 2 = FONT3
    void getgraph(); // recuper les infos de l'écran
    void background(int color); // couleur du fond (sans prendre en compte
     le texte
    int clear(); // Effacer tout l'écran
    void getset(int mode); // 1 = 0x01 = get Y ; 0 = 0x01 = X ???
    void Mcur(int line, int col); //deplacer le curseur
    void changecolor(int Old, int New); // changer la couleur "Old" par la
     couleur "New"
    void contrast(int cons); // 0x01 = contraste à 1 donc rentrer 1 ect ...
    void Smode(int mode); // 0 = Landscape, 1 = Landscave reverse, 2 =
     Portrait, 3 = Portrait reverse
    void baudrate(int speed); // Transmission en bauds
    void mode(int num);
    int write(char *, int); // NE PAS UTILISER
private :
int color(void);
int num(void);
Serial      lcd;
#if DEBUGMODE
Serial pc;
#endif // DEBUGMODE
};
#endif