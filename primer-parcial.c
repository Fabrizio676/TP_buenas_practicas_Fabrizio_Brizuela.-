/*
* Primer parcial - Gestión simple de libros (versión con #define)
* Autor: Fabri
* Fecha: 2025-08-27
*
* Cambios principales:
* - Se reemplazaron los valores "hardcodeados" por #define (MAX_LIBROS, MAX_TITULO, etc.)
* - Se agregó comprobación de límites al cargar libros
* - El nombre del archivo de salida ahora viene de un #define
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Configuración (evitar hardcodeo) */
#define MAX_LIBROS 100
#define MAX_TITULO 100
#define MAX_AUTOR 50
#define ARCHIVO_LIBROS "LibrosGuardados.txt"

/* Estructura que representa un libro */
struct Libros {
	char Titulo[MAX_TITULO];
	char Autor[MAX_AUTOR];
	int Ano;
};

/* Arreglo global de libros */
struct Libros lista[MAX_LIBROS];

/* Prototipos de funciones */
void CargarLibros(struct Libros *lista, int *total);
void MostrarLibros(struct Libros *lista, int total);
void BuscarLibro(struct Libros *lista, int total);
void GuardarArchivo(struct Libros *lista, int total);

int main(int argc, char *argv[]) {
	int total = 0;
	int opcion = 0;
	
	do {
		printf("-----MENU-----\n");
		printf("1. Cargar libros\n");
		printf("2. Mostrar libros en pantalla\n");
		printf("3. Buscar libros\n");
		printf("4. Guardar archivo\n");
		printf("5. Salir del programa\n");
		printf("-----MENU-----\n");
		printf("¿Qué opción desea elegir? ");
		if (scanf("%d", &opcion) != 1) {
			/* entrada inválida: limpiar buffer */
			printf("Entrada inválida. Intente de nuevo.\n");
			int c; while ((c = getchar()) != '\n' && c != EOF) ;
			opcion = 0;
			continue;
		}
		getchar(); /* consumir '\n' */
		printf("\nEligió la opción: %d\n", opcion);
		
		switch (opcion) {
		case 1:
			CargarLibros(lista, &total);
			break;
		case 2:
			MostrarLibros(lista, total);
			break;
		case 3:
			BuscarLibro(lista, total);
			break;
		case 4:
			GuardarArchivo(lista, total);
			break;
		case 5:
			printf("Saliendo del programa\n");
			break;
		default:
			printf("Opción inválida. Elija una opción entre 1 y 5.\n");
		}
	} while (opcion != 5);
	
	return 0;
}

void CargarLibros(struct Libros *lista, int *total) {
	struct Libros m;
	
	if (*total >= MAX_LIBROS) {
		printf("La lista de libros está llena (MAX_LIBROS = %d).\n", MAX_LIBROS);
		return;
	}
	
	printf("Ingrese el Título del libro: ");
	if (fgets(m.Titulo, sizeof(m.Titulo), stdin) == NULL) {
		printf("Error leyendo el título.\n");
		return;
	}
	m.Titulo[strcspn(m.Titulo, "\n")] = '\0';
	
	printf("Ingrese el nombre del Autor del libro: ");
	if (fgets(m.Autor, sizeof(m.Autor), stdin) == NULL) {
		printf("Error leyendo el autor.\n");
		return;
	}
	m.Autor[strcspn(m.Autor, "\n")] = '\0';
	
	printf("Ingrese el Año del libro: ");
	if (scanf("%d", &m.Ano) != 1) {
		printf("Año inválido. Operación cancelada.\n");
		int c; while ((c = getchar()) != '\n' && c != EOF) ;
		return;
	}
	getchar(); /* consumir '\n' */
	
	lista[*total] = m;
	(*total)++;
	printf("Sus datos fueron guardados...\n");
}

void MostrarLibros(struct Libros *lista, int total) {
	if (total == 0) {
		printf("No hay libros cargados\n");
		return;
	}
	
	for (int i = 0; i < total; i++) {
		printf("-----Libro %d-----\n", i + 1);
		printf("Título: %s\n", lista[i].Titulo);
		printf("Autor: %s\n", lista[i].Autor);
		printf("Año: %d\n", lista[i].Ano);
		printf("------------------\n");
	}
}

void BuscarLibro(struct Libros *lista, int total) {
	int opcion;
	char texto[MAX_TITULO];
	int anio;
	int encontrado = 0;
	
	if (total == 0) {
		printf("No hay libros para buscar.\n");
		return;
	}
	
	printf("Buscar por:\n1. Título\n2. Autor\n3. Año\nElija una opción: ");
	if (scanf("%d", &opcion) != 1) {
		printf("Opción inválida.\n");
		int c; while ((c = getchar()) != '\n' && c != EOF) ;
		return;
	}
	getchar();
	
	if (opcion == 1) {
		printf("Ingrese el Título: ");
		if (fgets(texto, sizeof(texto), stdin) == NULL) return;
		texto[strcspn(texto, "\n")] = '\0';
		for (int i = 0; i < total; i++) {
			if (strcmp(lista[i].Titulo, texto) == 0) {
				printf("Título: %s\nAutor: %s\nAño: %d\n", lista[i].Titulo, lista[i].Autor, lista[i].Ano);
				encontrado = 1;
			}
		}
	} else if (opcion == 2) {
		printf("Ingrese el Autor: ");
		if (fgets(texto, sizeof(texto), stdin) == NULL) return;
		texto[strcspn(texto, "\n")] = '\0';
		for (int i = 0; i < total; i++) {
			if (strcmp(lista[i].Autor, texto) == 0) {
				printf("Título: %s\nAutor: %s\nAño: %d\n", lista[i].Titulo, lista[i].Autor, lista[i].Ano);
				encontrado = 1;
			}
		}
	} else if (opcion == 3) {
		printf("Ingrese el Año: ");
		if (scanf("%d", &anio) != 1) {
			printf("Año inválido.\n");
			int c; while ((c = getchar()) != '\n' && c != EOF) ;
			return;
		}
		for (int i = 0; i < total; i++) {
			if (lista[i].Ano == anio) {
				printf("Título: %s\nAutor: %s\nAño: %d\n", lista[i].Titulo, lista[i].Autor, lista[i].Ano);
				encontrado = 1;
			}
		}
	} else {
		printf("Opción inválida.\n");
		return;
	}
	
	if (!encontrado) {
		printf("No se encontró ningún libro con ese criterio.\n");
	}
}

void GuardarArchivo(struct Libros *lista, int total) {
	if (total == 0) {
		printf("No hay libros para guardar.\n");
		return;
	}
	
	FILE *archivo = fopen(ARCHIVO_LIBROS, "w");
	if (archivo == NULL) {
		printf("Error al abrir el archivo '%s'\n", ARCHIVO_LIBROS);
		return;
	}
	
	for (int i = 0; i < total; i++) {
		fprintf(archivo, "-----Libro-----\n");
		fprintf(archivo, "Titulo:%s\n", lista[i].Titulo);
		fprintf(archivo, "Autor:%s\n", lista[i].Autor);
		fprintf(archivo, "Año:%d\n", lista[i].Ano);
		fprintf(archivo, "-----Libro-----\n");
	}
	
	fclose(archivo);
	printf("Libros guardados correctamente en '%s'\n", ARCHIVO_LIBROS);
}
