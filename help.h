#ifndef _HELP_H
#define _HELP_H

typedef enum new_data_type{false, true} bool;

typedef struct caract_moto
{
    char Categorie; //caracter (A, B, C, etc.)
    char Tara_origine[30]; //sir de caracter cu spatii
    char Marca_moto[30]; //sir de catacter fara spatii

    int An_fabricatie; //numar intreg
    double Pret_motocicleta; //numar cu virgula mobila
    bool Attach; // variabila boolean (definita cu enum!)

    enum Type{ //enumeratie pentru tipul motocicletei
        offroad,
        city
    } Tip_moto;

    union Motocicleta{ //uniune imbricata
        double Viteza_maxima; //daca moto e de tip city
        double Greutate; //daca moto e de tip offroad
    } Extra_info;

    struct DMY{ //campuri pe biti pentru ziua, luni si anul inregistrarii motocicletei
        unsigned int zi : 5;
        unsigned int luna : 4;
        unsigned int an : 15;
    } ZLA;

} Moto;

void Nucleu();

void Info_user();

void Citire_date_fisier(int);
void Citire_date_consola(int);
void Citire_moto_fisier(Moto *, int*);
void Citire_moto_consola(Moto *, int*);

void get_Vector(Moto *);

void Afisare_date(Moto *);
void Afisare_date_consola(Moto *);
void Afisare_date_fisier(Moto *);

#endif
