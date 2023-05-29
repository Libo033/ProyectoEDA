#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int ObtenerRandomNum(int a, int b);
int seEncuentraEn(char letra, char *palabra);
int compararPalabras(char *random, char *usuario);

void imprimirVerde(char a);
void imprimirAmarillo(char a);
void toUpper(char *a);

char *ingresarPalabra();
char *palabraRandom();

int main(void)
{
  // La funcion time(NULL) devuelve la cant. de segundos que pasaron desde 01/01/1970 (%lld)
  // Funcion srand: https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm
  srand(time(NULL));

  // Variables y punteros WORDLE
  short menu = 1, intentos = 0, finalJuego = 0, seguirJugando = 0;
  char *result = NULL, *palabraIngresada = NULL;

  do
  {
    system("cls");
    printf("Bienvenido\n0-Salir.\n1-Jugar al WORDLE.\n2-Jugar al AHORCADO\n3-Ver puntajes\nIngresar: ");
    scanf("%hd", &menu);

    switch (menu)
    {
    case 1:
      while (seguirJugando == 0)
      {
        system("cls");

        intentos = 0, finalJuego = 0, seguirJugando = 0;
        result = palabraRandom();

        printf("WORDLE\nTienes 5 intentos para descubrir la palabra de 5 letras.\nIngresar palabra\n");
        printf("%s\n", result);

        while (intentos < 5 && finalJuego == 0)
        {
          palabraIngresada = ingresarPalabra();
          printf("            ");
          finalJuego = compararPalabras(result, palabraIngresada);
          printf("\n");

          intentos++;
          free(palabraIngresada);
        }

        if (finalJuego == 1)
        {
          printf("\nFelicidades Ganaste!!!\nIngresa 0 si quieres seguir jugando o 1 para salir\n");
          scanf("%hd", &seguirJugando);
        }
        else
        {
          printf("Perdiste :(\nLa palabra era %s", result);
          seguirJugando = 1;
        }

        free(result);
      }

      printf("\n");
      system("pause");
      break;
    case 2:
      system("cls");

      printf("AHORCADO\n");

      system("pause");
      break;
    case 3:
      system("cls");

      printf("Puntaje\n");

      system("pause");
      break;
    default:
      break;
    }
  } while (menu != 0);

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

int compararPalabras(char *random, char *usuario) // Que devuelva la palabra con cada color.
{
  short i;

  if (strcmp(random, usuario) == 0) // CORRECTO
  {
    for (i = 0; i < (short)strlen(usuario); i++)
      imprimirVerde(usuario[i]);

    return 1;
  }
  else
  {
    for (i = 0; i < (short)strlen(usuario); i++) // INCORRECTO - COMPARA POR LETRAS
    {
      if (usuario[i] == random[i])
      {
        imprimirVerde(usuario[i]);
      }
      else if (seEncuentraEn(usuario[i], random) == 0)
      {
        imprimirAmarillo(usuario[i]);
      }
      else
      {
        printf("%c", usuario[i]);
      }
    }
    return 0;
  }
}

int seEncuentraEn(char letra, char *palabra)
{
  for (short i = 0; i < (short)strlen(palabra); i++)
  {
    if (palabra[i] == letra)
      return 0;
  }

  return 1;
}

void imprimirVerde(char a) // https://elpuig.xeill.net/Members/vcarceler/articulos/escape-ansi
{
  char *verde = "\033[0;40;1;32m";
  char *normal = "\033[0m";

  printf("%s%c%s", verde, a, normal);
}

void imprimirAmarillo(char a)
{
  char *amarillo = "\033[0;40;1;33m";
  char *normal = "\033[0m";

  printf("%s%c%s", amarillo, a, normal);
}

void toUpper(char *a)
{
  int len = strlen(a);

  for (short i = 0; i < len; i++)
    a[i] = toupper(a[i]);
}

char *palabraRandom()
{
  // Se crean el puntero result que es el que retorna el valor final.
  // y el puntero FILE que abrira el archivo palabras.txt
  char *result = NULL;
  FILE *archivo = NULL;
  archivo = fopen("..\\palabras.txt", "rt");

  if (archivo == NULL) // Controla el error
  {
    printf("\nError: No se pudo leer el archivo");
    return result;
  }

  result = (char *)malloc(5 * sizeof(char)); // Se establece el tamaño del string que se devuelve
  if (result == NULL)                        // Controla el error
  {
    printf("\nError: No se puedo asignar memoria");
    return result;
  }

  int posPalabra = ObtenerRandomNum(1, 127);

  // Se establece la posicion al inicio de la palabra con el num random y se lee 5 caracteres
  fseek(archivo, posPalabra * 7 - 7, SEEK_SET);
  fread(result, 1, 5, archivo);
  result[5] = '\0'; // Final
  fclose(archivo);  // Se cierra el archivo.

  toUpper(result);

  return result;
}

char *ingresarPalabra()
{
  char *result = NULL;
  result = (char *)malloc(5 * sizeof(char)); // Se establece el tamaño del string que se devuelve

  if (result == NULL)
  {
    printf("\nError: No se puedo asignar memoria");
    return result;
  }

  scanf("%5s", result);

  toUpper(result);

  return result;
}
