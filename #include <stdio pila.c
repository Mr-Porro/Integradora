#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM 5

////////// TDA Libro //////////
typedef struct Libro{
    int clave, num_pags;
    char titulo[50], autor[50], editorial[50];
} Libro;

////////// TDA Pila //////////
typedef struct Pila{
    Libro libros[MAX_TAM];
    int tope;
} Pila;

////////// Funciones //////////
void inicializar(Pila *p){
    p->tope = -1; 
}

int vacia(Pila *p){
    if(p->tope == -1) {return 1;}
    else {return 0;}
}

int llena(Pila *p){
    if(p->tope == MAX_TAM-1) {return 1;}
    else {return 0;}
}

void push(Pila *p, Libro l){
    p->tope++;
    p->libros[p->tope] = l;
}

void pop(Pila *p){
    printf("[!] El libro con clave [%d] ha sido eliminado\n", p->libros[p->tope].clave);
    p->tope--;
}

void tope(Pila *p){
    printf("  Clave:\t%d\n", p->libros[p->tope].clave);
    printf("  Titulo:\t%s\n", p->libros[p->tope].titulo);
    printf("  Paginas:\t%d\n", p->libros[p->tope].num_pags);
    printf("  Autor:\t%s\n", p->libros[p->tope].autor);
    printf("  Editorial:\t%s\n", p->libros[p->tope].editorial);
}

void imprimirPila(Pila *p){
    if(vacia(p)) {printf("[!] Pila vacia\n");}
    else{
        for(int i=p->tope; i>=0; i--){
            printf("\n--Posicion [%d]\n", i);
            printf("  Clave:\t%d\n", p->libros[i].clave);
            printf("  Titulo:\t%s\n", p->libros[i].titulo);
            printf("  Paginas:\t%d\n", p->libros[i].num_pags);
            printf("  Autor:\t%s\n", p->libros[i].autor);
            printf("  Editorial:\t%s\n", p->libros[i].editorial);
        }
    }
}

void buscarLibro(Pila *p, int c){
    int fnd=0;
    if(vacia(p)) {printf("[!] Pila vacia\n");}
    else{
        for(int i=p->tope; i>=0; i--){
            if(p->libros[i].clave == c){
                fnd++;
                printf("\n--Posicion [%d]\n", i);
                printf("  Clave:\t%d\n", p->libros[i].clave);
                printf("  Titulo:\t%s\n", p->libros[i].titulo);
                printf("  Paginas:\t%d\n", p->libros[i].num_pags);
                printf("  Autor:\t%s\n", p->libros[i].autor);
                printf("  Editorial:\t%s\n", p->libros[i].editorial);
            }
        }
        if(fnd==0) {printf("\n[!] El libro con la clave [%d] no existe\n", c);}
    }
}

////////// Main //////////
int main(){
    int menu=1;
    int opc, clv;
    char rsp;
    Libro libro;
    Pila pila;

    inicializar(&pila);
    
    while(menu == 1){
        printf("\n-- MENU --\n\n");
        printf(" 1. Insertar libro (Push)\n");
        printf(" 2. Eliminar libro (Pop)\n");
        printf(" 3. Buscar libro\n");
        printf(" 4. Imprimir libros\n");
        printf(" 5. Inicializar\n");
        printf(" 6. Vacia\n");
        printf(" 7. Llena\n");
        printf(" 8. Tope\n");
        printf(" 9. SALIR\n\n");
        printf("--Ingresa una opcion > ");

        scanf("%d", &opc);
        printf("\n");

        switch(opc){
            case 1:
                if(llena(&pila)) {printf("[!] Pila llena\n");}
                else{
                    printf("--Ingresa los datos del libro\n");
                    printf("  Clave >\t");
                    scanf("%d", &libro.clave);
                    printf("  Titulo >\t");
                    scanf(" %[^\n]", libro.titulo);
                    printf("  Paginas >\t");
                    scanf("%d", &libro.num_pags);
                    printf("  Autor >\t");
                    scanf(" %[^\n]", libro.autor);
                    printf("  Editorial >\t");
                    scanf(" %[^\n]", libro.editorial);

                    push(&pila, libro);
                }
                break;

           case 2:
                if(vacia(&pila)) {printf("[!] Pila vacia\n");}
                else{
                    pop(&pila);
                }
                break;

            case 3:
                if(vacia(&pila)) {printf("[!] Pila vacia\n");}
                else{
                    printf("--Ingresa la clave del libro > ");
                    scanf("%d", &clv);
                    buscarLibro(&pila, clv);
                }
                break;

            case 4:
                imprimirPila(&pila);
                break;

            case 5:
                inicializar(&pila);
                printf("[!] Pila inicializada\n");
                break;

            case 6:
                if(vacia(&pila)) {printf("[!] Pila vacia\n");}
                else{printf("[!] Pila NO vacia\n");}
                break;

            case 7:
                if(llena(&pila)) {printf("[!] Pila llena\n");}
                else{printf("[!] Pila NO llena\n");}
                break;

            case 8:
                if(vacia(&pila)) {printf("[!] Pila vacia\n");}
                else{
                    printf("--Libro en tope:\n");
                    tope(&pila);
                }
                break;

            case 9:
                printf("--Seguro que quieres salir? (s/n) > ");
                scanf(" %c", &rsp);
                if(rsp == 's') {
                    printf("\n[!] Saliendo del programa ...\n\n");
                    menu = 0;
                }
                break;

            default:
                printf("[!] Opcion incorrecta\n");
                break;
        }
    }

    return 0;
}