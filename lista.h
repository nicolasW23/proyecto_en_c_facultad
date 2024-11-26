#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <windows.h>

/*** Lista de tareas ***/
typedef char tString[25];
typedef struct{
	int idTarea;
	tString descripcionTarea;
}tDato;

typedef struct nodo{
	tDato dato;
	struct nodo *siguiente;
}tLista;

FILE *archivo;
tLista *lista;
tDato dato;

//prototipos
void inicializarLista();
bool listaVacia(tLista *);
void insertarTarea();
void insertarDatos(tDato);
void insertarPrimerTarea(tDato);
void insertarTareaAdelante(tDato);
void eliminarPrimerTarea();
void eliminarTareaDeArchivo();
void leerDesdeElArchivo();
void mostrarDatos(tLista *);
void menu();
void guardarEnArchivo(tLista *);
void leerDesdeArchivo();
void buscarEnArchivo();

void inicializarLista(){
	lista = NULL;
}
 
bool listaVacia(tLista *pLista){
	return(pLista == NULL);
} 

void insertarTarea(){
	system("cls");
	char opcion = 's';
	
 	while(opcion != 'n' && opcion !='N'){
	 	printf("\n\t\tIngrese el id de la tarea: ");
		scanf("%d", &dato.idTarea);
			  
		printf("\n\t\tDescripcion de la tarea: ");
		fflush(stdin);
		fgets(dato.descripcionTarea, sizeof(dato.descripcionTarea), stdin); // Leer la descripción completa
        dato.descripcionTarea[strcspn(dato.descripcionTarea, "\n")] = '\0'; // Eliminar el salto de línea
        
		insertarDatos(dato);
 		
		printf("\n\n\t\tDesea ingresar otra tarea? s-si n-no: ");
		fflush(stdin);
		scanf("%c", &opcion);
	}
	
	system("cls");
}


void insertarDatos(tDato pDato) {
	if(listaVacia(lista)){
		insertarPrimerTarea(pDato);
	}else{
		insertarTareaAdelante(pDato);
	}
}

void insertarPrimerTarea(tDato pDato){
	tLista * nuevoNodo;
	nuevoNodo= (tLista *) malloc(sizeof(tLista));
	nuevoNodo->dato= pDato;
	nuevoNodo->siguiente = NULL;
	lista= nuevoNodo;	
	printf("\n\t\tTarea almacenada en la lista (para guardar en el archivo debe finaliazar el programa)\n");	
}

void insertarTareaAdelante(tDato pDato){
	tLista * nuevoNodo;
	nuevoNodo= (tLista *) malloc(sizeof(tLista));
	nuevoNodo->dato= pDato;
	nuevoNodo->siguiente = lista;
	lista= nuevoNodo;	
	printf("\n\t\tTarea almacenada en la lista (para guardar en el archivo debe finaliazar el programa)\n");	
}

void eliminarPrimerTarea(){
	system("cls");
	if(listaVacia(lista)){
		printf("\n\t\tNo hay Tareas para quitar de la lista!\n");
	}
	else{
		tLista *nodoSup = lista;
		lista = lista->siguiente;
		printf("\n\t\tTarea eliminada: %s\n", nodoSup->dato.descripcionTarea);
		free(nodoSup);
		nodoSup = NULL; 
	}
	menu();
}

void eliminarTareaDeArchivo(){
	int idAEliminar;
	tLista *listaTemp = NULL;
	tDato datoTemp;
	
	archivo = fopen("lista.dat", "r");
	if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura.\n");
        return;
    }
    
    // Cargar los datos del archivo a la lista enlazada temporal
    while (fread(&datoTemp, sizeof(tDato), 1, archivo) == 1) {
		tLista *nuevoNodo;
		nuevoNodo = (tLista *) malloc(sizeof(tLista));
		nuevoNodo->dato = datoTemp;
		nuevoNodo->siguiente = listaTemp;
		listaTemp = nuevoNodo;
	}
	fclose(archivo);
	
	system("cls");
	// Solicitar al usuario el ID de la tarea a eliminar
    printf("\n\t\tIngrese el ID de la tarea a eliminar: ");
    scanf("%d", &idAEliminar);
    
    // Crear una nueva lista sin el elemento a eliminar
	tLista *actual = listaTemp, *anterior = NULL;
	while(actual != NULL){
		if(actual->dato.idTarea == idAEliminar){
			if(anterior == NULL){
			  listaTemp = actual->siguiente; // Eliminar el primer nodo
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            printf("\n\t\tTarea con ID %d eliminada.\n", idAEliminar);
            break;
		}
		anterior = actual;
		actual = actual->siguiente;
	}
	
	//Abrir en modo escritura y sobrescribir el archivo con los datos restantes
	archivo = fopen("lista.dat", "w");
	if(archivo == NULL){
		printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    
    tLista *temp = listaTemp;
    while(temp != NULL){
    	fwrite(&temp->dato, sizeof(tDato), 1, archivo);
    	temp = temp->siguiente;
	}
	fclose(archivo);
	
	// Liberar memoria
	while(listaTemp != NULL){
		tLista*nodoEliminar = listaTemp;
		listaTemp = listaTemp->siguiente;
		free(nodoEliminar);
	}
}

//solo de la pila
void mostrarDatos(tLista *pLista) {
    tLista *listaAux = pLista;
    system("cls");
    char opcion = 'n';
    
    printf("\n\t\t*** Lista de Tareas ***");
	printf("\n\t\tID \tDescripcion\n");
	while(opcion != 's' && opcion !='S'){
	    while (listaAux != NULL) {
	        printf("\t\t%d \t%s\n", 
	               listaAux->dato.idTarea, 
	               listaAux->dato.descripcionTarea);
	        listaAux = listaAux->siguiente;
	    }
	    
	    printf("\n\t\tSalir? s-si n-no: ");
		fflush(stdin);
		scanf("\t\t%c", &opcion);
	}
	system("cls");
}


void guardarEnArchivo(tLista *pLista){
	archivo = fopen("lista.dat", "a+");//sobrescribe los datos
	
	if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar datos.\n");
        return;//termina el programa
    }
	
	tLista *temp = pLista;
	while(temp != NULL){
		fwrite(&temp->dato, sizeof(tDato), 1, archivo);
		temp = temp->siguiente;
	}
	
	fclose(archivo);
	printf("\n\t\tDatos guardados en el archivo correctamente.\n");
}
 
 

void buscarEnArchivo(){
	int pIdBusc;
	char opcion = 'n';
	int encontrado = 0;
	system("cls");
	
    archivo = fopen("lista.dat", "r");
    if (archivo == NULL) {
        printf("\n\t\tError al abrir el archivo.\n");
        return;
    }
	
	printf("\n\t\tIngrese el ID de la tarea a buscar: ");
	scanf("%d", &pIdBusc);
	
	while(opcion != 's' && opcion !='S'){
		while (fread(&dato, sizeof(tDato), 1, archivo) == 1) {
	        if (dato.idTarea == pIdBusc) {
	            printf("\n\t\tElemento encontrado:");
	            printf("\n\t\tID: %d \tDescripcion: %s\n", dato.idTarea, dato.descripcionTarea);
	            encontrado = 1; // Marcar que se encontró
	            break;
	        }
    	}
    	
	    if (!encontrado) {
	        printf("\n\t\tElemento no encontrado.\n");
	    }
	    
	    printf("\n\t\tPulse s para salir: ");
		fflush(stdin);
		scanf("\t\t%c", &opcion);
	}
	
    fclose(archivo);
	system("cls");
	menu();
}

void leerDesdeElArchivo(){
	archivo = fopen("lista.dat", "r");
	system("cls");
	char opcion = 'n';

	if (archivo == NULL) {
        printf("Error al abrir el archivo para leer datos.\n");
    }
    
    printf("\n\t\t\t\t\t***Tareas Almacenadas***\n");	
	printf("\n\t\tID \tDescripcion\n");
	while(opcion != 's' && opcion !='S'){
	    while(fread(&dato,sizeof(tDato),1,archivo) == 1){
	    	printf("\n\t\t%d \t%s\n", dato.idTarea, dato.descripcionTarea);
		}
	
		printf("\n\t\tSalir? s-si n-no: ");
		fflush(stdin);
		scanf("%c", &opcion);
	}
	
	system("cls");
    fclose(archivo);
}

 
