#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help.h"

FILE *fi, *fo;
int Nr_Moto = 0;
bool Fisier; //true daca e fisier si false daca e consola
Moto *Elem;

void Nucleu(){ //aici se afla nucleul intregului program! de aici puteam apela orice functie (NU DIN MAIN!) pentru a evita multe erori care apar
    Info_user();
    Afisare_date(Elem);
}

void Info_user(){ //returneaza arrayul cu elemente
    int Select1, Select2;

    printf("Alegeti modul de citire/scriere:\n");
    printf("1. Fisiere\n2. Consola\n");
    while (scanf("%d", &Select1) && Select1 != 1 && Select1 != 2);
    printf("Ati ales varianta %d!\n", Select1);

    printf("\n\nAlegeti modul de memorare a datelor:\n");
    printf("1. Vector de N motociclete\n");
    printf("2. Vector cu un numar necunoscut de motociclete\n");
    printf("3. Alocare dinamica pentru N motociclete\n");
    printf("4. Alocare dinamica pentru un numar necuoscut de motociclete\n");
    while (scanf("%d", &Select2) && (Select2 < 1 || Select2 > 4));

    printf("Ati ales tipul de memorare %d!\n", Select2);
    printf("\n\n");

    if (Select1 == 1){
        char Nume_file_input[50], Nume_file_output[50];
        printf("Introduceti numele fisierului de input: ");
        scanf("%s", Nume_file_input);

        while ((fi = fopen(Nume_file_input, "r")) == 0){
            printf("Eroare citire fisier! (Nu aveti creat acest fisier in folder!)\n");
            printf("Introduceti numele fisierului de input: ");
            scanf("%s", Nume_file_input);
        }

        printf("Introduceti numele fisierului de output: ");
        scanf("%s", Nume_file_output);
        fo = fopen(Nume_file_output, "w");

        Fisier = true;
        Citire_date_fisier(Select2);
        fclose(fi);

    }else{
        Fisier = false;
        printf("Introduceti datele:\n");
        Citire_date_consola(Select2);
    }
}

void Citire_date_fisier(int Selected){
    switch (Selected){
        case 1:{ //cazul in care avem vector cu numar n de elemente
            int i, rand; //rand nu are nici o valoare aici, dar trebuie declarat pentru functia Citire_moto_fisier
            fscanf(fi, "%d", &Nr_Moto);

            Moto Vector[Nr_Moto];

            for (i = 0; i < Nr_Moto; ++i){
                Citire_moto_fisier(&Vector[i], &rand);
            }

            get_Vector(Vector);
            break;
        }

        case 2:{ //cazul in care avem un vector un numar necunoscut de elemente
            int isEOF = 0;
            Moto Vector[1010]; //declaram un vector cu un numar de elemente (random)

            while (1){
                Citire_moto_fisier(&Vector[Nr_Moto], &isEOF);
                if (isEOF) break;
                ++Nr_Moto;
            }

            get_Vector(Vector);
            break;
        }

        case 3:{
            int i, rand;
            fscanf(fi, "%d", &Nr_Moto);

            Moto* Vector = (Moto *)malloc(Nr_Moto * sizeof(Moto));

            for (i = 0; i < Nr_Moto; ++i){
                Citire_moto_fisier(&Vector[i], &rand);
            }

            get_Vector(Vector);
            break;
        }

        case 4:{
            int isEOF = 0;

            Moto* Vector = (Moto *)malloc(sizeof(Moto)); //incepem cu o singura motocicleta

            while (1){
                Citire_moto_fisier(&Vector[Nr_Moto], &isEOF);
                if (isEOF) break;
                ++Nr_Moto;
                Vector = realloc(Vector, (Nr_Moto + 1) * sizeof(Moto));
            }

            get_Vector(Vector);
            break;
        }
    }
}

void Citire_date_consola(int Selected){
    switch (Selected){
        case 1:{
            int i, rand;
            scanf("%d", &Nr_Moto);

            Moto Vector[Nr_Moto];

            for (i = 0; i < Nr_Moto; ++i){
                Citire_moto_consola(&Vector[i], &rand);
            }

            get_Vector(Vector);
            break;
        }

        case 2:{
            printf("Deoarece ati ales Consola + Citirea pana la EOF, tastati combinatia CTRL+Z (Windows) sau CTRL+D (Linux) pentru a marca EOF-ul!!!\n");
            int isEOF = 0;
            Moto Vector[1010];

            while (1){
                Citire_moto_consola(&Vector[Nr_Moto], &isEOF);
                if (isEOF) break;
                ++Nr_Moto;
            }

            get_Vector(Vector);
            break;
        }

        case 3:{
            int i, rand;
            scanf("%d", &Nr_Moto);

            Moto* Vector = (Moto *)malloc(Nr_Moto * sizeof(Moto));

            for (i = 0; i < Nr_Moto; ++i){
                Citire_moto_consola(&Vector[i], &rand);
            }

            get_Vector(Vector);
            break;
        }

        case 4:{
            printf("Deoarece ati ales Consola + Citirea pana la EOF, tastati combinatia CTRL+Z (Windows) sau CTRL+D (Linux) pentru a marca EOF-ul!!!\n");
            int isEOF = 0;

            Moto* Vector = (Moto *)malloc(sizeof(Moto));

            while (1){
                Citire_moto_consola(&Vector[Nr_Moto], &isEOF);
                if (isEOF) break;
                ++Nr_Moto;
                Vector = realloc(Vector, (Nr_Moto + 1) * sizeof(Moto));
            }

            get_Vector(Vector);
            break;
        }
    }
}

void Citire_moto_fisier(Moto *P, int *isEOF){

    int has_attach, type, d, m, y;

    char c = getc(fi);
    if (c == EOF){
        *isEOF = 1;
        return ;
    }
    while (c == ' ' || c == '\n') c = getc(fi); //Citirea caracterului ce determina categoria
    P->Categorie = c;

    fscanf(fi, "%d", &P->An_fabricatie);
    fscanf(fi, "%lf", &P->Pret_motocicleta);
    fscanf(fi, "%d", &has_attach);
    P->Attach = (has_attach ? true : false); //stabileste valoarea pentru attach(citind ca integer pe has_attach) si daca e 1, atunci e cu attach, daca 0 e fara
    fscanf(fi, "%d", &type);
    P->Tip_moto = (type == 0 ? offroad : city); //stabileste valoarea din enum pentru tipul motocicletei
    fscanf(fi, "%lf", &P->Extra_info.Greutate); //nu conteaza ce variabila (Greutate/Viteza maxima) citim, fiindca au aceeasi valoare (union)
    fscanf(fi, "%d%d%d", &d, &m, &y); //citirea pentru campul de biti (nu se poate lua adresa din acel camp, de aia folosim alta metoda ajutatoare)
    P->ZLA.zi = d, P->ZLA.luna = m, P->ZLA.an = y;// assignam valorilor din campul de biti valoarea corespunzatoare

    fscanf(fi,"%s", P->Marca_moto); //citirea fara spatii
    c = getc(fi); //skip la spatiu

    fgets(P->Tara_origine, 30, fi); //citirea cu spatii
    if (P->Tara_origine[strlen(P->Tara_origine) - 1] == '\n' || P->Tara_origine[strlen(P->Tara_origine) - 1] == ' ')
        P->Tara_origine[strlen(P->Tara_origine) - 1] = 0; //sterge newlineul sau spatiul de la sfarsti daca exista
}

void Citire_moto_consola(Moto *P, int *isEOF){

    int has_attach, type, d, m, y;

    char c = getchar();
    if (c == EOF){
        *isEOF = 1;
        return ;
    }
    while (c == ' ' || c == '\n' || c == '\t'){
        c = getchar();
        if (c == EOF){
        *isEOF = 1;
        return ;
        }
    }
    P->Categorie = c;

    scanf("%d", &P->An_fabricatie);
    scanf("%lf", &P->Pret_motocicleta);
    scanf("%d", &has_attach);
    P->Attach = (has_attach ? true : false);
    scanf("%d", &type);
    P->Tip_moto = (type == 0 ? offroad : city);
    scanf("%lf", &P->Extra_info.Greutate);
    scanf("%d%d%d", &d, &m, &y);
    P->ZLA.zi = d, P->ZLA.luna = m, P->ZLA.an = y;

    scanf("%s", P->Marca_moto);
    scanf("%[^\n]s", P->Tara_origine);
}


void get_Vector(Moto* P){ //ne permite sa avem vectorul in format global (putem lucra cu el indiferent cum a fost creat)

    int i;
    Elem = (Moto *) malloc(Nr_Moto * sizeof(Moto));

    for(i = 0; i < Nr_Moto; i++){
        Elem[i] = P[i];
    }
}

void Afisare_date(Moto *P){
    if (Fisier == true) Afisare_date_fisier(P);
    else Afisare_date_consola(P);
}

void Afisare_date_fisier(Moto *P){
    for (int i = 0; i < Nr_Moto; ++i){
        if (i) fprintf(fo, "---------------------------------------------\n");
        fprintf(fo, "Motocicletei %d ii corespund urmatoarele date:\n", i + 1);
        fprintf(fo, "Categorie: %c\n", P[i].Categorie);
        fprintf(fo, "Marca: %s\n", P[i].Marca_moto);
        fprintf(fo, "Tara: %s\n", P[i].Tara_origine);
        fprintf(fo, "An fabricare: %d\n", P[i].An_fabricatie);
        fprintf(fo, "Pret: %lf\n", P[i].Pret_motocicleta);

        if (P[i].Attach == true) fprintf(fo, "Poate avea attach\n");
        else fprintf(fo, "Nu poate avea attach\n");

        if (P[i].Tip_moto == offroad){
            fprintf(fo, "Tip offroad\n");
            fprintf(fo, "Greutatea: %lf\n", P[i].Extra_info.Greutate);
        }
        else{
            fprintf(fo, "Tip city\n");
            fprintf(fo, "Viteza maxima: %lf\n", P[i].Extra_info.Viteza_maxima);
        }

        fprintf(fo, "Inregistrare la data de: %d/%d/%d\n", P[i].ZLA.zi, P[i].ZLA.luna, P[i].ZLA.an);
    }
}

void Afisare_date_consola(Moto *P){
    for (int i = 0; i < Nr_Moto; ++i){
        printf("---------------------------------------------\n");
        printf("Motocicletei %d ii corespund urmatoarele date:\n", i + 1);
        printf("Categorie: %c\n", P[i].Categorie);
        printf("Marca: %s\n", P[i].Marca_moto);
        printf("Tara: %s\n", P[i].Tara_origine);
        printf("An fabricare: %d\n", P[i].An_fabricatie);
        printf("Pret: %lf\n", P[i].Pret_motocicleta);

        if (P[i].Attach == true) printf("Poate avea attach\n");
        else printf("Nu poate avea attach\n");

        if (P[i].Tip_moto == offroad){
            printf("Tip offroad\n");
            printf("Greutatea: %lf\n", P[i].Extra_info.Greutate);
        }
        else{
            printf("Tip city\n");
            printf("Viteza maxima: %lf\n", P[i].Extra_info.Viteza_maxima);
        }

        printf("Inregistrare la data de: %d/%d/%d\n", P[i].ZLA.zi, P[i].ZLA.luna, P[i].ZLA.an);
    }
}
