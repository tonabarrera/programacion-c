#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

Tabla tabla_hash;

void mostrar_conetenido(FILE *file) {
    char letra = ' ';
    Palabra aux_palabra;
    int suma = 0;

    iniciar_palabra(&aux_palabra);
    iniciar_tabla_hash(&tabla_hash);
    while (feof(file) == 0) {
        letra = fgetc(file);
        if(letra == 10) {
            letra = ' ';
        }
        if(letra != ' ') {
            if(letra != 10 && letra !=-1){
                suma += letra;
                //printf("%c\n", letra);
                guardar_letra(&aux_palabra, letra);
            }
        } else {
            //Guadrdar palabra
            guardar_palabra(&tabla_hash, &aux_palabra, suma);
            iniciar_palabra(&aux_palabra);
            suma = 0;
        }
        if(feof(file) != 0){
            guardar_palabra(&tabla_hash, &aux_palabra, suma);
            iniciar_palabra(&aux_palabra);
            suma = 0;
        }
    }
    mostar_tabla(&tabla_hash);
}

void guardar_letra(Palabra *palabra, char letra_caracter) {
    Letra *aux_letra = NULL;
    aux_letra = (Letra*) malloc(sizeof(Letra));

    if (aux_letra == NULL)
        exit(0); //Sin espacio

    aux_letra->elemento = letra_caracter;
    aux_letra->siguiente = NULL;

    if(palabra->inicio == NULL) {
        palabra->inicio = aux_letra;
    } else {
        palabra->fin->siguiente = aux_letra;
    }
    palabra->fin = aux_letra;

}

void iniciar_palabra(Palabra *palabra) {
    palabra->inicio = NULL;
    palabra->fin = NULL;
    palabra = NULL;
}

void iniciar_tabla_hash(Tabla *tabla) {
    tabla = NULL;
}

void guardar_palabra(Tabla *tabla, Palabra *palabra, int suma) {
    int indice = funcion_hash(suma);
    //printf("Incice %d\n", indice);
    ListaPalabras *aux_lista = NULL;

    aux_lista = (ListaPalabras*) malloc(sizeof(ListaPalabras));
    if(aux_lista == NULL)
        exit(0);

    aux_lista->palabra = *palabra;
    aux_lista->siguiente = NULL;

    if ((tabla->array_cubetas[indice]).primero == NULL) {
        tabla->array_cubetas[indice].primero = aux_lista;
    } else {
        tabla->array_cubetas[indice].ultimo->siguiente = aux_lista;
    }
    tabla->array_cubetas[indice].ultimo = aux_lista;
    //printf("Palabra: %c\n", tabla->array_cubetas[indice].ultimo->palabra.inicio->elemento);
}

int funcion_hash(int suma) {
    return (suma%32);
}

void mostar_tabla(Tabla *tabla) {
    printf("**\n");
    int i;
    for(i = 0; i<32; i++) {
        printf("Cubeta %d:\n", i);
        ListaPalabras *aux_lista = tabla->array_cubetas[i].primero; //incides
        while(aux_lista != NULL){
            Palabra aux_palabra = aux_lista->palabra;
            Letra *aux_letra = aux_palabra.inicio;
            while(aux_letra != NULL) {
                printf("%c", aux_letra->elemento);
                aux_letra = aux_letra->siguiente;
            }
            printf(" ");
            aux_lista = aux_lista->siguiente;
            printf("\n");
        }
    }
}
