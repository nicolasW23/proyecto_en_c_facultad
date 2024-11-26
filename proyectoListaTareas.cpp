#include "lista.h"

int main(){
	inicializarLista();
	menu();
	guardarEnArchivo(lista);
	return 0;
}

void menu(){
	int opcion = 0; 
	printf("\n\t\t\t\t\t***Programa De Lista De Tareas***\n");
	while (opcion != 7){
		printf("\n\t\tIngrese un numero para realizar una operacion:");
		printf("\n\t\t1-Ingresar Tarea");
		printf("\n\t\t2-Mostrar Tareas en la lista");
		printf("\n\t\t3-Mostrar Tareas ya almacenadas");
		printf("\n\t\t4-Borrar tarea de la lista");
		printf("\n\t\t5-eliminar tarea del programa");
		printf("\n\t\t6-Buscar en el archivo");
		printf("\n\t\t7-Finalizar el programa");
		printf("\n\n\t\tOpcion: ");
		scanf ("%d", &opcion);
		
		switch (opcion){
			case 1: { 
				insertarTarea();
				break;
			}
			case 2: { 
				mostrarDatos(lista);
				break;
			}
			case 3: { 
				leerDesdeElArchivo();
				break;
			}
			case 4:{
				eliminarPrimerTarea();
				break;
			}
			case 5:{
                eliminarTareaDeArchivo();
                break;  
            }
			case 6:{
				buscarEnArchivo();
				break;
			}
			case 7:{ 
                return;
                break;
			}default: {
				printf("Fin programa ...\n");
			} 
		}
 	}
}
