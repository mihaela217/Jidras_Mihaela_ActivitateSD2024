#include <stdio.h>
#include <stdlib.h>


typedef struct Santier Santier;
typedef struct NodLdi NodLdi;
typedef struct ListaDubla ListaDubla;

struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

struct NodLdi {
    NodLdi* prev;
    NodLdi* next;
    Santier info;
};

struct ListaDubla {
    NodLdi* prim;
    NodLdi* ultim;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;
    return santier;
}

void afisareSantier(Santier santier)
{
    printf("Santierul %s are %d muncitori si %.2f m^2 suprafata\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}

float densitateMuncitori(Santier santier) {
    if (santier.suprafata > 0) {
        return santier.nrMuncitori / santier.suprafata;
    }
    else return 0;
}

int calcNrTotalMuncitori(ListaDubla lista)
{
    int suma = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next)
    {
        suma += i->info.nrMuncitori;
    }
    return suma;
}

int calculNrMuncitoriSuprafata(ListaDubla lista, float suprafataMax) {
    int suma = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next)
    {
        if (i->info.suprafata < suprafataMax) {
            suma += i->info.nrMuncitori;
        }
    }
    return suma;
}

void inserareInceput(ListaDubla* lista, Santier s)
{
    NodLdi* aux = (NodLdi*)malloc(sizeof(NodLdi));
    aux->info = s;
    aux->next = lista->prim;
    aux->prev = NULL;
    if (lista->prim != NULL) {
        lista->prim->prev = aux;
    }
    else {
        lista->ultim = aux;
    }
    lista->prim = aux;
}

void afisareLdiDeLaInceput(ListaDubla lista) {
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        afisareSantier(nod->info);
    }
}

void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier)
{
    NodLdi* nod = lista->prim;
    while (nod != NULL) {
        if (strcmp(nod->info.numeProiect, numeSantier) == 0) {
            if (nod->prev == NULL) {
                lista->prim = nod->next;
            }
            else {
                nod->prev->next = nod->next;
            }
            if (nod->next == NULL) {
                lista->ultim = nod->prev;
            }
            else {
                nod->next->prev = nod->prev;
            }
            free(nod->info.numeProiect);
            free(nod);
            return;
        }
        nod = nod->next;
    }
    printf("Santierul %s nu a fost gasit.\n", numeSantier);
}

void stergereCompleta(ListaDubla* lista)
{
    if (lista != NULL) {
        NodLdi* aux = lista->prim;
        while (aux != NULL) {
            free(aux->info.numeProiect);
            NodLdi* temp = aux->next;
            free(aux);
            aux = temp;
        }
        lista->prim = NULL;
        lista->ultim = NULL;
    }
}

int main() {
    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 12, 400);
    Santier s3 = initializareSantier("Santier 3", 15, 200);
    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);
    printf("Lista initiala:\n");
    afisareLdiDeLaInceput(lista);

    int nrMuncitori = calcNrTotalMuncitori(lista);
    printf("Nr muncitori: %d\n", nrMuncitori);

    stergereCompleta(&lista);
    afisareLdiDeLaInceput(lista);

    return 0;
}
