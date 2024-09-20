// Juan Daniel Vanegas Mayorquin - 20222020077
// Ejercicio Binary Search

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

struct Persona{
 	int cedula;
	char nombre[15];
	char apellido[15];
};

int contarRegistros();
void leerArchivo(Persona *datos, int n);
void quickSort(Persona *datos, int inicio, int fin);
int particion(Persona *datos, int inicio, int fin);
void organizarPersonas(Persona *datos, int n);
int busquedaBinaria(Persona *datos, int n, int cedulaBuscar);

int main() {
    Persona *datos;
    int n;
    int cedulaBuscar;

    n = contarRegistros();
    if(n <= 0){
        printf("No hay registros en la base de datos o hubo un error al leer el archivo.");
        return 1;
    }

    datos = new Persona[n];

    leerArchivo(datos, n);

    printf("Ingrese la cedula de la persona que desea buscar: ");
    scanf("%i", &cedulaBuscar);

    organizarPersonas(datos, n);

    int indice = busquedaBinaria(datos, n, cedulaBuscar);

    if(indice != -1){
        printf("Persona encontrada: Cedula: %i, Nombre: %s, Apellido: %s\n", datos[indice].cedula, datos[indice].nombre, datos[indice].apellido); 
    } else {
        printf("No se logró encontrar la persona con la cedula indicada.\n");
    }

    delete[] datos;

    return 0;
}

int contarRegistros(){
    FILE *archivo;
    int contador = 0;
    int cedula;
    char nombre[15], apellido[15];

    archivo = fopen("Personas.txt", "r");

    if(archivo == NULL){
        return -1;
    }

    while(fscanf(archivo, "%d %s %s", &cedula, nombre, apellido) != EOF){
        contador ++;
    } 

    fclose(archivo);
    return contador;
}

void leerArchivo(Persona *datos, int n){
    FILE *archivo;
    archivo = fopen("Personas.txt", "r");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        if(fscanf(archivo, "%d %s %s", &datos[i].cedula, datos[i].nombre, datos[i].apellido) != 3){
            printf("Error al leer los datos en la linea %d.\n", i+1);
            break;
        }
    }

    fclose(archivo); 
}

void organizarPersonas(Persona *datos, int n){
    quickSort(datos, 0, n - 1);
}

void quickSort(Persona *datos, int inicio, int fin){
    if(inicio < fin){
        int indiceParticion = particion(datos, inicio, fin);
        quickSort(datos, inicio, indiceParticion - 1);
        quickSort(datos, indiceParticion + 1, fin);
    }
}

int particion(Persona *datos, int inicio, int fin){
    int pivote = datos[fin].cedula;
    int i = inicio - 1;

    for(int j = inicio; j < fin; j++){
        if(datos[j].cedula < pivote){
            i++;
            Persona temporal = datos[i];
            datos[i] = datos[j];
            datos[j] = temporal;
        }
    }
    Persona temporal = datos[i + 1];
    datos[i + 1] = datos[fin];
    datos[fin] = temporal;

    return i + 1;
}

int busquedaBinaria(Persona *datos, int n, int cedulaBuscar){
    int inicio = 0; 
    int fin = n - 1;

    while(inicio <= fin){
        int medio = (inicio + fin) / 2;
        if(datos[medio].cedula == cedulaBuscar){
            return medio;
        }
        if(datos[medio].cedula < cedulaBuscar){
            inicio = medio+1;
        } else {
            fin = medio - 1;
        }
    }
    return -1;
}