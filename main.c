#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int cmp_int(const void* a, const void* b) {
    int first_value = *(int*)a, second_value = *(int*)b; 
    return first_value-second_value;
}
void borra_lista(Lista lista) {
    size_t l= longitud(lista); 
    int i;
    for(i = 0; i < l; i++){ 
        Elemento *ayu = quita_elemento(lista, 0);
        if (ayu != NULL){ 
            free(ayu->valor); 
            free(ayu); 
        }
    }
    free(lista); 
}

void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)) {
    size_t l = longitud(lista);
    Elemento* ayu= *lista;
    int *arreglo = malloc(sizeof(int) * l); 
    for(int i= 0; i < l; i++){
        arreglo[i]= *(int*)ayu -> valor; 
        ayu= ayu -> siguiente;
    }
    qsort(arreglo, l, sizeof(int), *cmp);
    Elemento* ayu2= *lista;
    for(int i= 0; i < l; i++){
        *(int*)ayu2 -> valor = arreglo[i]; 
        ayu2= ayu2 -> siguiente;
    }
}


Elemento* quita_elemento(Lista lista, size_t posicion) {
    
    if(*lista == NULL || posicion < 0 || posicion >= longitud(lista))
        return NULL;

    if(posicion == 0){ 
        Elemento* ayu = *lista; 
        Elemento* ayu2 = ayu->siguiente; 
        *lista = ayu2; 
        return ayu; 
    }
    
    else if(posicion == longitud(lista)-1){
        Elemento *a = *lista;
        int i;
        for(i = 0; i<longitud(lista)-2; i++)
            a = a-> siguiente;
        Elemento *b = a->siguiente; 
        Elemento *c = b;
        a->siguiente = NULL;  
        return c; 
    }
    
    else{
        Elemento *a = *lista;
        int i;
        for(i = 0; i<posicion-1; i++)
            a = a-> siguiente;
        Elemento *b = a->siguiente; 
        Elemento *c = b; 
        a->siguiente = b->siguiente;
        return c; 
    }
}

void imprime_lista_int(Lista lista) {
    Elemento* ayu = *lista;
    printf("[");
    while (ayu) {
        printf("%d", *((int*) ayu->valor));
        if (ayu->siguiente) {
            printf(", ");
        }
        ayu = ayu->siguiente;
    }
    printf("]\n");
}

Lista crea_lista() {
    Lista lista = malloc (sizeof(Lista));
    return lista;
}

size_t longitud(Lista lista) {
    Elemento* ayu = *lista;
    int longitud = 0;
    while (ayu) {
        longitud++;
        ayu = ayu->siguiente;
    }
    return longitud;
}

int inserta_elemento(Lista lista, void *valor) {
    if (valor != NULL){ 
        Elemento *new_element = malloc(sizeof(Elemento)); 
        new_element->valor = valor;
        new_element->siguiente = *lista; 
        *lista = new_element; 
    }
    return longitud(lista); 
}

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}
