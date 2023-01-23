#include "mbed.h"
#include "ULCD32PT.h"
#include <math.h>
ULCD32PT :: ULCD32PT(PinName tx, PinName rx) : lcd(tx, rx)
#if DEBUGMODE
    ,pc(USBTX, USBRX)
#endif // DEBUGMODE
{
    lcd.baud(9600);
    #if DEBUGMODE
    pc.baud(9600);
#endif
}
//**************************************************\\
int ULCD32PT :: write(char*tab, int number) // ecrit sur l'écran
{
     for (int i = 0; i < number; i++)
    {
         lcd.putc(tab[i]);
         #if DEBUGMODE
       pc.putc(tab[i]);
#endif
}
    #if DEBUGMODE
       pc.putc(lcd.getc());
#endif
//**************************************************\\
int ULCD32PT :: clear() // efface tout
{
}
}
   char tab[12] = "";
   tab[0] = 0xFF;
   tab[1] = 0xCD;
write(tab, 2);

//**************************************************\\
void ULCD32PT :: texte(int l1, int l2, int l3, int l4, int l5, int l6)
{
    char tab[12] = "";
    int l1bis = l1/10;
    int l2bis = l2/10;
    int l2bis2 = l2/100;
    tab[0] = 0x00;
    tab[1] = 0x18;
    tab[2] = l1;
    tab[3] = l1bis;
    tab[4] = l2;
    tab[5] = l2bis;
    tab[6] = l2bis2;
    tab[7] = 0x00;
    write(tab, 8);
}
//**************************************************\\
void ULCD32PT :: Smode(int num)
{
    char tab[12] = "";
    if (num == 0) tab[3] = 0x00; // Paysage
    if (num == 1) tab[3] = 0x01; // Paysage reverse
    if (num == 2) tab[3] = 0x02; // Portrait
    if (num == 3) tab[3] = 0x03; // Portrait reverse
    tab[0] = 0xFF; //cmd[MSB]  mode
    tab[1] = 0x9E;//cmd[LSB] mode
    tab[2] = 0x00;
    write(tab, 4);
    clear();
}
//**************************************************\\
*/
void ULCD32PT :: background(int color)
{
    char tab[12] = "";
    tab[0] = 0xFF; //cmd[MSB]  mode
    tab[1] = 0xA4;//cmd[LSB] mode

int rouge   = (color >> (16 + 3)) & 0x1F;
 les 5 bits pour la couleurs rouge
int vert = (color >> (8 + 2))  & 0x3F;
 bits pour la couleurs vert
int bleu  = (color >> (0 + 3))  & 0x1F;
 5 bits pour la couleurs bleu
   // On recuper
// On recuper les 6
 // On recuper les
    tab[2] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
     premiere partie du code hexa à partire de 16 bits
    tab[3] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite la
     deuxieme partie du code hexa à partire de 16 bits
    write(tab, 4);
    clear(); // obligatoire sinon le font ne change pas
}
//**************************************************\\
void ULCD32PT :: getgraph()
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xA6;
    tab[2] = 0x00;
    tab[3] = 0x00;
    write(tab, 4);
    tab[0] = 0xFF;
    tab[1] = 0xA6;
    tab[2] = 0x00;
    tab[3] = 0x01;
    write(tab, 4);
}
//**************************************************\\
void ULCD32PT :: rectangle(int x1, int y1 , int x2, int y2, int color)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xC5;

tab[2] = (x1 >> 8) & 0xFF;
tab[3] = x1;
tab[4] = (y1 >> 8) & 0xFF;
tab[5] = y1;
tab[6] = (x2 >> 8) & 0xFF;
tab[7] = x2;
tab[8] = (y2 >> 8) & 0xFF;
tab[9] = y2;
int rouge   = (color >> (16 + 3)) & 0x1F;
 les 5 bits pour la couleurs rouge
int vert = (color >> (8 + 2))  & 0x3F;
 bits pour la couleurs vert
int bleu  = (color >> (0 + 3))  & 0x1F;
 5 bits pour la couleurs bleu
   // On recuper
// On recuper les 6
 // On recuper les
    tab[10] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
     premiere partie du code hexa à partire de 16 bits
    tab[11] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite
     la deuxieme partie du code hexa à partire de 16 bits
    write(tab, 12);
}
//**************************************************\\
void ULCD32PT :: cercle(int x, int y, int rad,int color)
{
char tab[12] = "";
tab[0] = 0xFF;
tab[1] = 0xF3;
tab[2] = (x >> 8) & 0xFF;
tab[3] = x;
tab[4] = (y >> 8) & 0xFF;
tab[5] = y;
tab[6] = (rad >> 8) & 0xFF;
tab[7] = rad;
int rouge   = (color >> (16 + 3)) & 0x1F;
 les 5 bits pour la couleurs rouge
int vert = (color >> (8 + 2))  & 0x3F;
 bits pour la couleurs vert
int bleu  = (color >> (0 + 3))  & 0x1F;
 5 bits pour la couleurs bleu
        // On recuper
// get red on 5 bits
     // On recuper les 6
      // On recuper les
tab[8] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
 premiere partie du code hexa à partire de 16 bits

    tab[9] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite la
     deuxieme partie du code hexa à partire de 16 bits
    write(tab, 10);
}
//**************************************************\\
void ULCD32PT :: triangle(int x1, int y1 , int x2, int y2, int x3, int y3,
 int color)
{
char tab[17] = "";
tab[0] = 0xFF;
tab[1] = 0xA9;
tab[2] = (x1 >> 8) & 0xFF;
tab[3] = x1;
tab[4] = (y1 >> 8) & 0xFF;
tab[5] = y1;
tab[6] = (x2 >> 8) & 0xFF;
tab[7] = x2;
tab[8] = (y2 >> 8) & 0xFF;
tab[9] = y2;
tab[10] = (x3 >> 8) & 0xFF;
tab[11] = x3;
tab[12] = (y3 >> 8) & 0xFF;
tab[13] = y3;
int rouge   = (color >> (16 + 3)) & 0x1F;
 les 5 bits pour la couleurs rouge
int vert = (color >> (8 + 2))  & 0x3F;
 bits pour la couleurs vert
int bleu  = (color >> (0 + 3))  & 0x1F;
 5 bits pour la couleurs bleu
        // On recuper
// get red on 5 bits
     // On recuper les 6
      // On recuper les
tab[14] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
 premiere partie du code hexa à partire de 16 bits
tab[15] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite
 la deuxieme partie du code hexa à partire de 16 bits
    write(tab, 16);
}
//**************************************************\\
void ULCD32PT :: ligne(int x1, int y1, int x2, int y2,int color)
{
char tab[12] = "";

tab[0] = 0xFF;
tab[1] = 0xC8;
tab[2] = (x1 >> 8) & 0xFF;
tab[3] = x1;
tab[4] = (y1 >> 8) & 0xFF;
tab[5] = y1;
tab[6] = (x2 >> 8) & 0xFF;
tab[7] = x2;
tab[8] = (y2 >> 8) & 0xFF;
tab[9] = y2;
int rouge   = (color >> (16 + 3)) & 0x1F;
 les 5 bits pour la couleurs rouge
int vert = (color >> (8 + 2))  & 0x3F;
 bits pour la couleurs vert
int bleu  = (color >> (0 + 3))  & 0x1F;
 5 bits pour la couleurs bleu
        // On recuper
// get red on 5 bits
     // On recuper les 6
      // On recuper les
    tab[10] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
     premiere partie du code hexa à partire de 16 bits
    tab[11] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite
     la deuxieme partie du code hexa à partire de 16 bits
    write(tab, 12);
}
//**************************************************\\
void ULCD32PT :: moveOr(int x, int y) // déplacer l'origine
{
char tab[12] = "";
tab[0] = 0xFF;
tab[1] = 0xCC;
tab[2] = (x >> 8) & 0xFF;
tab[3] = x;
tab[4] = (y >> 8) & 0xFF;
tab[5] = y;
    write(tab, 6);
}
//**************************************************\\
 void ULCD32PT :: tailleT(int mult)
{
char tab[12] = "";

    tab[0] = 0xFF;
    tab[1] = 0xE3;
    tab[2] = 0x00;
    tab[3] = mult;
    write(tab, 4);
}
//**************************************************\\
void ULCD32PT :: colorTP(int color) // couleur du texte
{
char tab[12] = "";
tab[0] = 0xFF;
tab[1] = 0xE7;
int rouge   = (color >> (16 + 3)) & 0x1F;
 les 5 bits pour la couleurs rouge
int vert = (color >> (8 + 2))  & 0x3F;
 bits pour la couleurs vert
int bleu  = (color >> (0 + 3))  & 0x1F;
 5 bits pour la couleurs bleu
        // On recuper
// get red on 5 bits
     // On recuper les 6
      // On recuper les
tab[2] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
 premiere partie du code hexa à partire de 16 bits
tab[3] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite la
 deuxieme partie du code hexa à partire de 16 bits
    write(tab, 4);
}
//**************************************************\\
void ULCD32PT :: colorTB(int color) //couleur du fond du texte
{
char tab[12] = "";
tab[0] = 0xFF;
tab[1] = 0xE6;
int rouge   = (color >> (16 + 3)) & 0x1F;
 les 5 bits pour la couleurs rouge
int vert = (color >> (8 + 2))  & 0x3F;
 bits pour la couleurs vert
int bleu  = (color >> (0 + 3))  & 0x1F;
 5 bits pour la couleurs bleu
        // On recuper
// get red on 5 bits
     // On recuper les 6
      // On recuper les
tab[2] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
 premiere partie du code hexa à partire de 16 bits
tab[3] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite la
 deuxieme partie du code hexa à partire de 16 bits

    write(tab, 4);
}
//**************************************************\\
void ULCD32PT :: pixel(int x, int y, int color)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xC1;
    tab[2] = (x >> 8) & 0xFF;
    tab[3] = x;
    tab[2] = (y >> 8) & 0xFF;
    tab[5] = y;
    int rouge   = (color >> (16 + 3)) & 0x1F;
     les 5 bits pour la couleurs rouge
    int vert = (color >> (8 + 2))  & 0x3F;
     bits pour la couleurs vert
    int bleu  = (color >> (0 + 3))  & 0x1F;
     5 bits pour la couleurs bleu
        // On recuper
// get red on 5 bits
     // On recuper les 6
      // On recuper les
    tab[6] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
     premiere partie du code hexa à partire de 16 bits
    tab[7] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite la
     deuxieme partie du code hexa à partire de 16 bits
    write(tab, 8);
}
//*************************************\\
void ULCD32PT :: rectangleF(int x1, int y1 , int x2, int y2, int color)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xC4;
    tab[2] = (x1 >> 8) & 0xFF;
    tab[3] = x1;
    tab[4] = (y1 >> 8) & 0xFF;
    tab[5] = y1;
    tab[6] = (x2 >> 8) & 0xFF;
    tab[7] = x2;
    tab[8] = (y2 >> 8) & 0xFF;
    tab[9] = y2;

int rouge   = (color >> (16 + 3)) & 0x1F;
 les 5 bits pour la couleurs rouge
int vert = (color >> (8 + 2))  & 0x3F;
 bits pour la couleurs vert
int bleu  = (color >> (0 + 3))  & 0x1F;
 5 bits pour la couleurs bleu
        // On recuper
// get red on 5 bits
     // On recuper les 6
      // On recuper les
    tab[10] = ((rouge << 3)   + (vert >> 3)) & 0xFF;  // On récuper la
     premiere partie du code hexa à partire de 16 bits
    tab[11] = ((vert << 5) + (bleu >>  0)) & 0xFF;  // On récuper ensuite
     la deuxieme partie du code hexa à partire de 16 bits
    write(tab, 12);
}
//*********************************\\
void ULCD32PT :: phrase(char *p)   // écrire une phrase
{
    char tab[1000]= "";
    int size = strlen(p); // deplacer le curseur
    tab[0] = 0x00;
    tab[1] = 0x18;
    for (int i=0; i<size; i++) tab[2+i] = p[i];
    tab[2+size] = 0x00;
    write(tab, 3 + size);
}
//************************************\\
 void ULCD32PT :: largT(int mult)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xE4;
    tab[2] = 0x00;
    tab[3] = mult;
    write(tab, 4);
}
//**************************************\\
void ULCD32PT :: font(int num)
{
     char tab[12] = "";
    if (num == 0) tab[3] = 0x00; // Paysage

    if (num == 1) tab[3] = 0x00; // Paysage reverse
    if (num == 2) tab[3] = 0x02; // Portrait
    if (num == 3) tab[3] = 0x03; // Portrait reverse
    tab[0] = 0xFF; //cmd[MSB]  mode
    tab[1] = 0x9E;//cmd[LSB] mode
    tab[2] = 0x00;
    write(tab, 4);
clear(); }
//**********************************\\
void ULCD32PT :: Espace(int pix)
{
   char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xE2;
    tab[2] = 0x00;
    tab[3] = pix;
    write(tab, 4);
}
//***********************************\\
void ULCD32PT :: fondT(int mode)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xE5;
    tab[2] = 0x00;
    tab[3] = mode;
    write(tab, 4);
}
//************************************\\
void ULCD32PT :: Mcur(int x, int y)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xE9;
    tab[2] = (x >> 8) & 0xFF;
    tab[3] = 0x04;
    tab[4] = (y >> 8) & 0xFF;
    tab[5] = 0x06;

    write(tab, 6);
}
//************************************\\
void ULCD32PT :: italic(int num)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xDD;
    tab[2] = 0x00;
    tab[3] = num;
    write(tab, 4);
}
//************************************\\
void ULCD32PT :: opac(int num)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xDF;
    tab[2] = 0x00;
    tab[3] = num;
    write(tab, 4);
}
//************************************\\
void ULCD32PT :: under(int num)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xDB;
    tab[2] = 0x00;
    tab[3] = num;
    write(tab, 4);
}
//************************************\\
void ULCD32PT :: attrib(int num)

{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xDA;
    tab[2] = 0x00;
    tab[3] = num;
    write(tab, 4);
}
//************************************\\
void ULCD32PT :: wrap(int num)
{
    char tab[12] = "";
    tab[0] = 0xFF;
    tab[1] = 0xD9;
    tab[2] = 0x00;
    tab[3] = num;
    write(tab, 4);
}
//************************************\\
void ULCD32PT :: variable( float variable)
{
     char tab[7];
     int i = 1;
     int variablebis = variable * 10; // mettre *100 si on veut une
      variable en float pour le final
     int variablebis2 = variable;
     while (i <= 3 && variablebis != 0)
     {
         variablebis = variablebis/10;
         i++;
}
char var[i];
  sprintf(var, "%f", variable);
  tab[0] = 0x00;
  tab[1] = 0x18;
    for (int j=0; j<=2 ; j++) tab[2+j] = var[j]; // mettre i pour j<i quand
     on veut que deux

    tab[2+i] = 0x00;
    write(tab, 3 + i);
}
//****************************************
void ULCD32PT :: chiffre (int numero)
{
     char tab[7];
     int i = 1;
char num[i];
  sprintf(num, "%d", numero);
  tab[0] = 0xFF;
  tab[1] = 0xFE;
  tab[2] = 0x00;
  tab[3] = num[0];
  write(tab, 4);
}
