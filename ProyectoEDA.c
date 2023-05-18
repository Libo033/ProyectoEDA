#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ObtenerRandomNum(int a, int b);
void imprimirVerde(char *a);
void imprimirAmarillo(char *a);
void lecturaArchivo();
char *palabraElegida();

int main(void)
{
  // La funcion time(NULL) devuelve la cant. de segundos que pasaron desde 01/01/1970 (%lld)
  // Funcion srand: https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm
  srand(time(NULL));
  system("color 0F");

  char *result = palabraElegida();
  printf("%s\n", result);
  printf("%lld\n", strlen(result));
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

void lecturaArchivo()
{
  FILE *archivo = NULL;
  char caracter;

  archivo = fopen("C:\\Users\\valen\\Desktop\\Code\\09-EDA\\Proyecto\\palabras.txt", "rt");

  if (archivo == NULL)
  {
    printf("\nError: No se pudo leer el archivo");
  }
  
  do
  {
    caracter = fgetc(archivo);
    printf("%c", caracter);
  } while (caracter != EOF);
}

char *palabraElegida()
{
  char *result = NULL;
  FILE *archivo = NULL;
  archivo = fopen("..\\palabras.txt", "rt");

  if (archivo == NULL)
  {
    printf("\nError: No se pudo leer el archivo");
    return result;
  }

  fseek(archivo, 0, SEEK_END);
  rewind(archivo);

  result = (char *)malloc(5);
  if (result == NULL)
  {
    printf("\nError: No se puedo asignar memoria");
    return result;
  }

  int posPalabra = ObtenerRandomNum(1,30);

  fseek(archivo, posPalabra*7-7,SEEK_SET);
  fread(result, 1, 5, archivo);
  result[5] = '\0';
  fclose(archivo);

  return result;
}