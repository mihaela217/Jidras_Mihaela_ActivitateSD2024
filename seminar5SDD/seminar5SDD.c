
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct Santier Santier;
typedef struct Nod Nod;

struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};
struct Nod {
	Santier santier;
	Nod* next;
};
Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
	Santier santier;
	santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
	strcpy(santier.numeProiect, numeProiect);
	santier.nrMuncitori = nrMuncitori;
	santier.suprafata = suprafata;
	return santier;
}
Nod* inserareInceput(Santier santier, Nod* lista) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->santier = santier;
	nod->next = lista;
	return nod;
}
void afisareSantier(Santier santier) {
	printf("Santierul %s are %d muncitori si o suprafata de %5.2f m^2", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}
void afiseazaLista(Nod* lista) {
	while (lista != NULL) {
		//procesare
		afisareSantier(lista->santier);
		lista = lista->next;
	}
}
int sumaMuncitori(Nod* lista) {
	int Suma = 0;
	while (lista != NULL) {
		Suma = Suma + lista->santier.nrMuncitori;
		lista = lista->next;
	}
	return Suma;
}
void stergereLista(Nod** lista) {
	while ((*lista) != NULL) {
		free((*lista)->santier.numeProiect);
		Nod* aux;
		aux = (*lista)->next;
		free(*lista);
		(*lista) = aux;

	}
	(*lista) = NULL;
}
//numele santier cu densitatea cea mai mare de muncitori pe metru patrat
float densitateaMuncitori(Santier santier) {
	if (santier.suprafata > 0)
	{
		return santier.nrMuncitori / santier.suprafata;
	}
	else return 0;
}
char* numeSantierDensitateMaxima(Nod* lista) {
	float max = 0;
	char* aux = NULL;
	while (lista != NULL) {
		if (densitateaMuncitori(lista->santier) > max)
		{
			max = densitateaMuncitori(lista->santier);
			aux = lista->santier.numeProiect;
		}
		lista = lista->next;
	}
	if (aux != NULL)
	{
		char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
		strcpy(numeProiectDensitate, aux);
		return numeProiectDensitate;
	}
	else return NULL;
}
int main() {
	Nod* lista = NULL;
	Santier s1 = initializareSantier("Santier 1", 5, 200);
	Santier s2 = initializareSantier("Santier 2", 10, 250);
	Santier s3 = initializareSantier("Santier 3", 20, 300);
	lista = inserareInceput(s1, lista);
	lista = inserareInceput(s2, lista);
	lista = inserareInceput(s3, lista);
	lista = inserareInceput(initializareSantier("Santier 4", 10, 34), lista);
	afiseazaLista(lista);
	int Suma = 0;
	Suma = sumaMuncitori(lista);
	printf("suma este %d", Suma);

	//printf("\n%s", numeSantierDensitateMaxima(lista));
	stergereLista(&lista);
	afiseazaLista(lista);
	//STERGEM UN NOD 
}