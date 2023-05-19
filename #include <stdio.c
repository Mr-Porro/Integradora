#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un libro
struct Libro {
    int clave;
    char titulo[100];
    int numPaginas;
    char autor[100];
    char editorial[100];
    struct Libro* siguiente;
    struct Libro* anterior;
};

// Define la estructura de la lista
struct Lista {
    struct Libro* primera;
    struct Libro* ultima;
};

// Funcion para inicializar la lista
void inicializarLista(struct Lista* lista) {
    lista->primera = NULL;
    lista->ultima = NULL;
}

// Funcion para verificar si la lista esta vacia
int listaVacia(struct Lista lista) {
    return (lista.primera == NULL);
}

// Funcion para insertar un libro al final de la lista
void insertarLibro(struct Lista* lista, struct Libro libro) {
    struct Libro* nuevoLibro = (struct Libro*)malloc(sizeof(struct Libro));
    *nuevoLibro = libro;
    nuevoLibro->siguiente = NULL;
    nuevoLibro->anterior = NULL;

    if (listaVacia(*lista)) {
        lista->primera = nuevoLibro;
        lista->ultima = nuevoLibro;
    } else {
        nuevoLibro->anterior = lista->ultima;
        lista->ultima->siguiente = nuevoLibro;
        lista->ultima = nuevoLibro;
    }
    printf("\nLibro insertado con exito.\n");
}

// Funcion para buscar un libro por clave
void buscarLibro(struct Lista lista, int clave) {
    struct Libro* actual = lista.primera;

    while (actual != NULL) {
        if (actual->clave == clave) {
            printf("Libro encontrado:\n\n");
            printf("Clave: %d\n", actual->clave);
            printf("Titulo: %s\n", actual->titulo);
            printf("Numero de paginas: %d\n", actual->numPaginas);
            printf("Autor: %s\n", actual->autor);
            printf("Editorial: %s\n", actual->editorial);
            return;
        }
        actual = actual->siguiente;
    }
    printf("\nNo se encontro ningun libro con la clave especificada.\n");
}

// Funcion para borrar un libro por clave
void borrarLibro(struct Lista* lista, int clave) {
    struct Libro* actual = lista->primera;

    while (actual != NULL) {
        if (actual->clave == clave) {
            if (actual->anterior != NULL) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                lista->primera = actual->siguiente;
            }

            if (actual->siguiente != NULL) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                lista->ultima = actual->anterior;
            }

            free(actual);
            printf("\nLibro borrado con exito.\n");
            return;
        }
        actual = actual->siguiente;
    }
    printf("\nNo se encontro ningun libro con la clave especificada.\n");
}

// Función para verificar si una clave de libro ya existe en la lista
int claveExiste(struct Lista lista, int clave) {
    struct Libro* actual = lista.primera;

    while (actual != NULL) {
        if (actual->clave == clave) {
            return 1; // La clave ya existe en la lista
        }
        actual = actual->siguiente;
    }

    return 0; // La clave no existe en la lista
}

int main(int argc, char* argv[]) {
    struct Lista lista;
    inicializarLista(&lista);

    int opcion;
    struct Libro libro;
    
    do {
        system("cls");
        printf("+-------------Menu-------------+\n");
        printf("| 1. Insertar libro            |\n");
        printf("| 2. Buscar por clave de libro |\n");
        printf("| 3. Borrar libro              |\n");
        printf("| 4. Salir                     |\n");
        printf("+------------------------------+\n\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Consumir el carácter de nueva línea residual en el búfer de entrada

        switch (opcion) {
            case 1:
                system("cls");
                do{
                	printf("Ingrese la clave del libro: ");
                	scanf("%d", &libro.clave);
                	getchar(); // Consumir el carácter de nueva línea residual en el búfer de entrada
                
               		if (claveExiste(lista, libro.clave)) {
                		printf("la clave del libro ya existe en la lista.\n");
					}
				}while (claveExiste(lista, libro.clave));
                
                printf("Ingrese el titulo del libro: ");
                fgets(libro.titulo, sizeof(libro.titulo), stdin);
                libro.titulo[strcspn(libro.titulo, "\n")] = '\0'; // Eliminar el carácter de nueva línea del título
                printf("Ingrese el numero de paginas del libro: ");
                scanf("%d", &libro.numPaginas);
                getchar(); // Consumir el carácter de nueva línea residual en el búfer de entrada
                printf("Ingrese el nombre del autor: ");
                fgets(libro.autor, sizeof(libro.autor), stdin);
                libro.autor[strcspn(libro.autor, "\n")] = '\0'; // Eliminar el carácter de nueva línea del autor
                printf("Ingrese el nombre de la editorial: ");
                fgets(libro.editorial, sizeof(libro.editorial), stdin);
                libro.editorial[strcspn(libro.editorial, "\n")] = '\0'; // Eliminar el carácter de nueva línea de la editorial

                insertarLibro(&lista, libro);
            	
                system("pause");
                break;
            case 2:
                system("cls");
                printf("Ingrese la clave del libro a buscar: ");
                scanf("%d", &libro.clave);
                buscarLibro(lista, libro.clave);
                system("pause");
            break;
            case 3:
                system("cls");
                printf("Ingrese la clave del libro a borrar: ");
                scanf("%d", &libro.clave);
                borrarLibro(&lista, libro.clave);
                system("pause");
            break;
            case 4:
                system("cls");
                printf("Saliendo del programa...\n");
                system("pause");
            break;
            default:
                printf("Opcion invalida. Elija una opcion del 1 al 4\n");
                system("pause");
        }
    } while (opcion != 4);

    // Liberar la memoria utilizada por los libros restantes en la lista
    struct Libro* actual = lista.primera;
    while (actual != NULL) {
        struct Libro* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    return 0;
}