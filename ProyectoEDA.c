#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ObtenerRandomNum(int a, int b);
void imprimirVerde(char *a);
void imprimirAmarillo(char *a);
char *palabraElegida();

int main(void)
{
  // La funcion time(NULL) devuelve la cant. de segundos que pasaron desde 01/01/1970 (%lld)
  // Funcion srand: https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm
  srand(time(NULL));
  system("color 0F");

  
  char *result = palabraElegida();
  printf("%s\n", result);
  free(result);
  
  return 0;
}

int ObtenerRandomNum(int a, int b)
{
  // Se obtiene el num random a partir de la funcion rand() y hace numero random
  // se le aplica el modulo de (b - a + 1) + a. Que son los numeros max y min. Por ende el num
  // siempre estara entra esos rangos.
  // Ver https://www.omnicalculator.com/math/modulo. Ingresar en el dividendo un num random y en el divisor
  // el num resultado de (b - a + 1) y ves como siempre se obtiene un num entre los valores indicados.
  return rand() % (b - a + 1) + a;
}

void imprimirVerde(char *a) // https://elpuig.xeill.net/Members/vcarceler/articulos/escape-ansi
{
  char *verde = "\033[0;40;1;32m";
  char *normal = "\033[0m";

  printf("%s%s%s", verde, a, normal);
}

void imprimirAmarillo(char *a) // https://elpuig.xeill.net/Members/vcarceler/articulos/escape-ansi
{
  char *amarillo = "\033[0;40;1;33m";
  char *normal = "\033[0m";

  printf("%s%s%s", amarillo, a, normal);
}

char *palabraElegida()
{
  // Se crean el puntero result que es el que retorna el valor final.
  // y el puntero FILE que abrira el archivo palabras.txt
  char *result = NULL;
  FILE *archivo = NULL;
  archivo = fopen("..\\palabras.txt", "rt");

  if (archivo == NULL)  // Controla el error
  {
    printf("\nError: No se pudo leer el archivo");
    return result;
  }

  result = (char *)malloc(5);  //Se establece el tamaño del string que se devuelve
  if (result == NULL)   // Controla el error
  {
    printf("\nError: No se puedo asignar memoria");
    return result;
  }

  // Se recibe el num. random para encontrar la palabra random
  int posPalabra = ObtenerRandomNum(1,30);

  // Se establece la posicion al inicio de la palabra con el num random
  // y se lee 5 caracteres
  fseek(archivo, posPalabra*7-7,SEEK_SET);
  fread(result, 1, 5, archivo);
  result[5] = '\0';  // Final
  fclose(archivo);  // Se cierra el archivo.

  return result;
}