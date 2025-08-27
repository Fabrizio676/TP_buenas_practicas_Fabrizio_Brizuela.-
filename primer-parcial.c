/*
* primer-parcial.c
* Primer parcial - Gestión simple de libros
* Autor: Fabrizio Brizuela
* Fecha: 2025-08-27
*
* Descripción:
* Programa sencillo para cargar, mostrar, buscar y guardar libros.
* Versión: añadidos comentarios y documentación.
*/

#include <stdio.h>
#include <string.h>

/* Estructura que representa un libro */
struct Libros {
	char Titulo[100];
	char Autor[50];
	int Ano;
};

/* Arreglo global de libros (mantengo igual que el parcial) */
struct Libros lista[100];

/* Prototipos de funciones */
void CargarLibros(struct Libros *lista,int *total);
void MostrarLibros(struct Libros *lista,int total);
void BuscarLibro(struct Libros *lista,int total);
void GuardarArchivo(struct Libros *lista,int total);

/* main: muestra el menú y controla el flujo del programa */
int main(int argc, char *argv[]) {
	int total = 0;
	int opcion = 0;
	
	do {
		printf("-----MENU-----\n");
		printf("1.Cargar libros\n");
		printf("2.Mostrar libros en pantalla\n");
		printf("3.Buscar libros\n");
		printf("4.GuardarArchivo\n");
		printf("5.Salir del programa\n");
		printf("-----MENU-----\n");
		printf("¿Que opcion desea elegir?\n");
		scanf("%d", &opcion);
		getchar(); /* consumir '\n' */
		printf("\nEligio la opcion: %d\n", opcion);
		
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
		default:;
		}
	} while (opcion != 5);
	
	return 0;
}

/* CargarLibros: solicita datos de un libro y lo agrega a la lista */
void CargarLibros(struct Libros *lista,int *total){
	struct Libros m;
	
	printf("Ingrese el Titulo del libro:");
	fgets(m.Titulo,sizeof(m.Titulo),stdin);
	m.Titulo[strcspn(m.Titulo,"\n")]='\0';
	
	printf("Ingrese el nombre del Autor del libro:");
	fgets(m.Autor,sizeof(m.Autor),stdin);
	m.Autor[strcspn(m.Autor,"\n")]='\0';
	
	printf("Ingrese el Año del libro:");
	scanf("%d",&m.Ano);
	
	lista[*total]=m;
	(*total)++;
	printf("Sus datos fueron guardados...\n");
}
	
	/* MostrarLibros: imprime todos los libros cargados */
	void MostrarLibros(struct Libros *lista,int total){
		int i=0;
		if(total==0){
			printf("No hay libros cargados\n");
		}
		for(i=0;i<total;i++){
			printf("-----Libro-----\n");
			printf("Titulo:%s\n",lista[i].Titulo);
			printf("Autor:%s\n",lista[i].Autor);
			printf("Año:%d\n",lista[i].Ano);
			printf("-----Libro-----\n");
		}
	}
		
		/* BuscarLibro: permite buscar por título, autor o año */
		void BuscarLibro(struct Libros *lista, int total) {
			int opcion;
			char texto[100];
			int anio, encontrado = 0;
			
			printf("Buscar por:\n1. Titulo\n2. Autor\n3. Año\nElija una opción: ");
			scanf("%d", &opcion);
			getchar();
			
			if (opcion == 1) {
				printf("Ingrese el Titulo: ");
				fgets(texto, sizeof(texto), stdin);
				texto[strcspn(texto,"\n")] ='\0';
				for (int i = 0; i < total; i++) {
					if (strcmp(lista[i].Titulo, texto) == 0) {
						printf("Titulo: %s\nAutor: %s\nAño: %d\n", lista[i].Titulo, lista[i].Autor, lista[i].Ano);
						encontrado = 1;
					}
				}
			} else if (opcion == 2) {
				printf("Ingrese el Autor: ");
				fgets(texto, sizeof(texto), stdin);
				texto[strcspn(texto, "\n")] = '\0';
				for (int i = 0; i < total; i++) {
					if (strcmp(lista[i].Autor, texto) == 0) {
						printf("Titulo: %s\nAutor: %s\nAño: %d\n", lista[i].Titulo, lista[i].Autor, lista[i].Ano);
						encontrado = 1;
					}
				}
			} else if (opcion == 3) {
				printf("Ingrese el Año: ");
				scanf("%d", &anio);
				for (int i = 0; i < total; i++) {
					if (lista[i].Ano == anio) {
						printf("Titulo: %s\nAutor: %s\nAño: %d\n", lista[i].Titulo, lista[i].Autor, lista[i].Ano);
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
		
		/* GuardarArchivo: escribe la lista de libros en un archivo de texto */
		void GuardarArchivo(struct Libros *lista,int total){
			int i=0;
			FILE *archivo=fopen("LibrosGuardados.txt","w");
			if(archivo==NULL){
				printf("Error al abrir el archivo\n");
				return;
			}
			for(i=0;i<total;i++){
				fprintf(archivo,"-----Libro-----\n");
				fprintf(archivo,"Titulo:%s\n",lista[i].Titulo);
				fprintf(archivo,"Autor:%s\n",lista[i].Autor);
				fprintf(archivo,"Año:%d\n",lista[i].Ano);
				fprintf(archivo,"-----Libro-----\n");
			}
			fclose(archivo); /* Cierra el archivo correctamente */
			printf("Libros cargados Correctamente\n");
		}
			
