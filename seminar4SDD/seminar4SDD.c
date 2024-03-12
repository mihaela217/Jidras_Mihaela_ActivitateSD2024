﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

struct Masina {
    int id;
    char* producator;
    int nrUsi;
    float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
    struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
    if (aux == NULL) {
        printf("Alocare memorie esuată\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *nrMasini; i++) {
        aux[i] = masini[i];
    }
    aux[*nrMasini] = m;
    (*nrMasini)++;
    free(masini);
    return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
    FILE* file = fopen(numeFisier, "r");
    if (file == NULL) {
        printf("Nu se poate deschide fișierul %s\n", numeFisier);
        exit(EXIT_FAILURE);
    }
    char buffer[100];
    char delimitare[] = ",\n";
    struct Masina* masini = NULL;
    (*nrMasini) = 0;
    while (fgets(buffer, 100, file) != NULL) {
        char* element = strtok(buffer, delimitare);
        struct Masina m;
        m.id = atoi(element);
        element = strtok(NULL, delimitare);
        m.producator = malloc(strlen(element) + 1);
        if (m.producator == NULL) {
            printf("Alocare memorie esuata\n");
            exit(EXIT_FAILURE);
        }
        strcpy(m.producator, element);
        element = strtok(NULL, delimitare);
        m.nrUsi = atoi(element);
        element = strtok(NULL, delimitare);
        m.pret = atof(element);
        masini = adaugareInVector(masini, m, nrMasini);
    }
    fclose(file);
    return masini;
}

struct Masina* masiniMulteUsi(struct Masina* masini, int* nrMasini) {
    int nrMasiniNoi = 0;
    for (int i = 0; i < *nrMasini; i++) {
        if (masini[i].nrUsi > 2) {
            nrMasiniNoi++;
        }
    }
    struct Masina* masiniUsi = (struct Masina*)malloc(sizeof(struct Masina) * nrMasiniNoi);
    if (masiniUsi == NULL) {
        printf("Alocare memorie esuată\n");
        exit(EXIT_FAILURE);
    }
    int j = 0;
    for (int i = 0; i < *nrMasini; i++) {
        if (masini[i].nrUsi > 2) {
            masiniUsi[j] = masini[i];
            j++;
        }
    }
    return masiniUsi;
}

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol) {
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < nrCol[i]; j++) {
            printf("Id: %d, Producator: %s, NrUsi: %d, Pret: %.2f\n",
                matrice[i][j].id, matrice[i][j].producator,
                matrice[i][j].nrUsi, matrice[i][j].pret);
        }
    }
}

float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane, int nrUsi) {
    float pretTotal = 0;
    int index = nrUsi - 2;

}

struct Masina cautaMasinaId(struct Masina* masini, int nrMasini, int idCautat) {
    for (int i = 0; i < nrMasini; i++) {
        if (masini[i].id == idCautat) {
            return masini[i];
        }
    }
    struct Masina masinaNegativa;
    masinaNegativa.id = -1;
    return masinaNegativa;
}

int main() {
    struct Masina** matrice;
    int nrLinii = 3;
    int* nrCol;
    nrCol = (int*)malloc(sizeof(int) * nrLinii);
    if (nrCol == NULL) {
        printf("Alocare memorie esuată\n");
        exit(EXIT_FAILURE);
    }
    matrice = (struct Masina*)malloc(sizeof(struct Masina) * nrLinii);
    if (matrice == NULL) {
        printf("Alocare memorie esuată\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nrLinii; i++) {
        nrCol[i] = 0;
        matrice[i] = NULL;
    }

    int nrMasini;
    struct Masina* masini = citireFisier("exemplu.txt", &nrMasini);
    if (masini != NULL) {
        struct Masina* masiniUsi = masiniMulteUsi(masini, &nrMasini);

        int idCautat = 123;
        struct Masina masinaGasita = cautaMasinaId(masini, nrMasini, idCautat);
        if (masinaGasita.id != -1) {
            printf("Masina cu ID-ul %d a fost gasita: Producator: %s, NrUsi: %d, Pret: %.2f\n",
                masinaGasita.id, masinaGasita.producator, masinaGasita.nrUsi, masinaGasita.pret);
        }
        else {
            printf("Nu s-a gasit nicio masina cu ID-ul %d.\n", idCautat);
        }

        free(masini);
        free(masiniUsi);
    }

    for (int i = 0; i < nrLinii; i++) {
        free(matrice[i]);
    }
    free(matrice);
    free(nrCol);
    return 0;
}