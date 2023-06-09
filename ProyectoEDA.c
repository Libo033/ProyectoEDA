#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <Windows.h>

int ObtenerRandomNum(int a, int b);                    // WORDLE
int seEncuentraEn(char letra, char *palabra);          // WORDLE
int compararPalabras(char *random, char *usuario);     // WORDLE
int contarGuiones(char *palPantalla);                  // AHORCADO
int DescubrirPalabra(char *result, char *palPantalla); // AHORCADO
int cantidadDePuntajes();                              // PUNTAJE

void imprimirVerde(char a);                        // WORDLE
void imprimirAmarillo(char a);                     // WORDLE
void toUpper(char *a);                             // WORDLE
void unir(char *palIncompleta, char *palPantalla); // AHORCADO
void mostrarHorca(int nro);                        // AHORCADO
void llenarConGuiones(char *palPantalla);          // AHORCADO
void guardarPuntaje(char *nombre, int puntaje);    // PUNTAJE

char *ingresarPalabra();                          // WORDLE
char *palabraRandom();                            // WORDLE
char ingresarLetra();                             // AHORCADO
char *DescubrirLetras(char *palabra, char letra); // AHORCADO
char *IngresarNombre();                           // PUNTAJE

struct puntajeJugador *obtenerPuntajes(int jugadores);

struct puntajeJugador
{
  char *nombre;
  int puntaje;
};

int main(void)
{
  srand(time(NULL)); // La funcion time(NULL) devuelve la cant. de segundos que pasaron desde 01/01/1970 (%lld)
  SetConsoleTitle("Wordle & Ahorcado");

  short menu = 1, intentos = 0, finalJuego = 0, seguirJugando = 0, puntajePartida = 0, puntajeTotal = 0, cargarPuntaje = 1;
  char *result = NULL, *palabraIngresada = NULL, *jugador = NULL, *palPantalla = NULL, *palIncompleta = NULL;
  char letraIngresada;

  if (result != NULL || palabraIngresada != NULL || palPantalla != NULL || palIncompleta != NULL)
  {
    printf("Error en el puntero");
  }

  do
  {
    system("cls");
    printf("Bienvenido\n0-Salir.\n1-Jugar al WORDLE.\n2-Jugar al AHORCADO\n3-Ver puntajes\nIngresar: ");
    scanf(" %hd", &menu);

    switch (menu)
    {
    case 1:
      seguirJugando = 0, puntajeTotal = 0, cargarPuntaje = 1;

      while (seguirJugando == 0)
      {
        system("cls");

        intentos = 0, finalJuego = 0, seguirJugando = 0, puntajePartida = 5;
        result = palabraRandom();

        printf("WORDLE\nTienes 5 intentos para descubrir la palabra de 5 letras.\nIngresar palabra\n");

        while (intentos < 5 && finalJuego == 0)
        {
          palabraIngresada = ingresarPalabra();
          printf("            ");
          finalJuego = compararPalabras(result, palabraIngresada); // Chequea si el jugador acerto la pal.
          printf("\n");

          if (finalJuego != 1) // Si el jugador no descubrio la pal. se le resta un punto
            puntajePartida--;

          intentos++;
          free(palabraIngresada);
        }

        puntajeTotal = puntajeTotal + puntajePartida;

        if (finalJuego == 1)
        {
          printf("Puntaje: %d\n", puntajeTotal);
          printf("\nFelicidades Ganaste!!!\nIngresa 0 si quieres seguir jugando o 1 para salir\n");
          scanf(" %hd", &seguirJugando); // El jugador elige seguir jugando o salir.
        }
        else
        { // El jugador sale si o si. Porque perdio.
          printf("Puntaje: %d\n", puntajeTotal);
          printf("Perdiste :(\nLa palabra era %s", result);
          seguirJugando = 1;
        }

        free(result);
        fflush(stdin);
      }

      if (puntajeTotal > 0) // Si el jugador obtuvo puntaje
      {                     // Elige si quiere que se guarde o no
        printf("\nDeseas agregar tu puntaje? 0-SI  1-NO\n");
        scanf(" %hd", &cargarPuntaje);
      }

      if (cargarPuntaje == 0)
      {
        system("cls");
        printf("Tu puntaje fue de %d\nIngresa tu nombre(MAX 15): ", puntajeTotal);
        jugador = (char *)malloc(15 * sizeof(char));
        jugador = IngresarNombre();
        guardarPuntaje(jugador, puntajeTotal);
      }

      free(jugador);
      printf("\n");
      system("pause");
      break;
    case 2:
      seguirJugando = 0, puntajeTotal = 0, cargarPuntaje = 1;

      while (seguirJugando == 0)
      {
        system("cls");

        intentos = 0, finalJuego = 0, puntajePartida = 6;
        int contGuiones = 5, nro = 0, contGuionesAct = 0;

        palPantalla = (char *)malloc(5 * sizeof(char));

        llenarConGuiones(palPantalla);
        result = palabraRandom(); // Obtiene palabra a descubrir

        printf("AHORCADO\nTienes 6 intentos para descubrir la palabra de 5 letras\n");
        mostrarHorca(0);
        
        while (intentos < 6 && finalJuego == 0)
        {
          printf("Ingresar letra: ");
          letraIngresada = ingresarLetra(); // Ingresa la letra
          palIncompleta = DescubrirLetras(result, letraIngresada);
          unir(palIncompleta, palPantalla);
          contGuionesAct = contarGuiones(palPantalla);

          if (contGuionesAct < contGuiones)
          { // acerto una letra
            contGuiones--;
          }
          else
          { // pierde una vida
            nro++;
            intentos++;
            puntajePartida--;
          }

          mostrarHorca(nro);
          printf("  %s\n", palPantalla);                      // Imprime la pal. con las letras descubiertas que ingreso el jugador.
          finalJuego = DescubrirPalabra(result, palPantalla); // Chequea si el jugador descubrio la pal.
          printf("\n");
        }

        puntajeTotal = puntajeTotal + puntajePartida;

        if (finalJuego == 1)
        {
          printf("Puntaje: %d\n", puntajeTotal);
          printf("\nFelicidades Ganaste!!!\nIngresa 0 si quieres seguir jugando o 1 para salir\n");
          scanf(" %hd", &seguirJugando); // El jugador elige seguir jugando o salir.
        }
        else
        {
          printf("Puntaje: %d\n", puntajeTotal);
          printf("Perdiste :(\nLa palabra era %s", result);
          seguirJugando = 1;
        }

        free(result);
        free(palPantalla);
        free(palIncompleta);
      }

      if (puntajeTotal > 0) // Si el jugador obtuvo puntaje
      {                     // Elige si quiere que se guarde o no
        printf("\nDeseas agregar tu puntaje? 0-SI  1-NO\n");
        fflush(stdin);
        scanf(" %hd", &cargarPuntaje);
      }

      if (cargarPuntaje == 0)
      {
        system("cls");
        printf("Tu puntaje fue de %d\nIngresa tu nombre(MAX 15): ", puntajeTotal);
        jugador = (char *)malloc(15 * sizeof(char));
        jugador = IngresarNombre();
        guardarPuntaje(jugador, puntajeTotal);
      }

      free(jugador);
      printf("\n");
      system("pause");
      break;
    case 3:
      system("cls");
      int pGuardados = cantidadDePuntajes();

      if (pGuardados == -1)
        return 1;

      struct puntajeJugador *todos = obtenerPuntajes(pGuardados);

      printf("Puntajes\n----------\n");

      for (int i = 0; i < pGuardados; i++)
      {
        printf("Posicion: %d\nNombre: %s\nPuntaje: %d\n----------\n", (i+1), todos[i].nombre, todos[i].puntaje);
      }

      printf("\n");
      system("pause");

      for (int j = 0; j < pGuardados; j++)
      {
        free(todos[j].nombre);
      }

      break;
    default:
      break;
    }
    fflush(stdin);
  } while (menu != 0);

  return 0;
}

int ObtenerRandomNum(int a, int b)
{
  // Se obtiene el num random a partir de la funcion rand() y a ese numero random se le aplica el modulo
  // de (b - a + 1) + a. Que son los numeros max y min. Por ende el num siempre estara entra esos rangos.
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
  for (short i = 0; i < (short)strlen(a); i++)
    a[i] = toupper(a[i]);
}

char *palabraRandom()
{
  char *result = NULL; // Se crean el puntero result que es el que retorna el valor final.
  FILE *archivo = NULL; // Y el puntero FILE que abrira el archivo palabras.txt
  archivo = fopen("..\\palabras.txt", "rt");

  if (archivo == NULL) // Controla el error
  {
    printf("\nError: No se pudo leer el archivo\n");
    return result;
  }

  result = (char *)malloc(5 * sizeof(char)); // Se establece el tama�o del string que se devuelve
  if (result == NULL)                        // Controla el error
  {
    printf("\nError: No se puedo asignar memoria\n");
    return result;
  }

  int posPalabra = ObtenerRandomNum(1, 126);

  fseek(archivo, posPalabra * 7 - 7, SEEK_SET);  // Se establece la posicion al inicio de la palabra con el num random 
  fread(result, 1, 5, archivo);  // y se lee 5 caracteres
  result[5] = '\0'; // Final
  fclose(archivo);  // Se cierra el archivo.
  toUpper(result);

  return result;
}

char *ingresarPalabra()
{
  char *result = NULL;
  result = (char *)malloc(5 * sizeof(char)); // Se establece el tama�o del string que se devuelve

  if (result == NULL)
  {
    printf("\nError: No se puedo asignar memoria");
    return result;
  }

  scanf(" %[^\n]", result); // Soluciona que si ponen palabras con espacio no haga cualquier cosa.

  if (strlen(result) > 5) // Si la palabra ingresada es mayor a 5
  {
    char *strRecortado = (char *)malloc(6 * sizeof(char));

    if (strRecortado == NULL)
    {
      printf("\nError: No se puedo asignar memoria");
      return strRecortado;
    }
    memset(strRecortado, '\0', 6 * sizeof(char)); // Se coloca \0 para que no hay caracteres basura
    strncpy(strRecortado, result, 5);             // Se recorta
    toUpper(strRecortado);
    free(result);

    return strRecortado; // Y se envia
  }

  toUpper(result);

  return result;
}

char ingresarLetra()
{
  char letra;
  scanf(" %c", &letra);
  letra = toupper(letra);
  return letra;
}

char *DescubrirLetras(char *palabra, char letra)
{
  char *palADescubrir = NULL;
  palADescubrir = (char *)malloc(5 * sizeof(char));

  if (palADescubrir == NULL)
  {
    printf("\nError: No se puedo asignar memoria");
    return palADescubrir;
  }

  for (short i = 0; i < 5; i++)
  {
    if (palabra[i] == letra)
    {
      palADescubrir[i] = letra;
    }
    else
    {
      palADescubrir[i] = '_';
    }
  }
  palADescubrir[5] = '\0';

  return palADescubrir;
}

int DescubrirPalabra(char *result, char *palPantalla)
{
  if (strcmp(result, palPantalla) == 0)
    return 1;
  else
    return 0;
}

void unir(char *palIncompleta, char *palPantalla)
{
  for (short i = 0; i < 5; i++)
  {
    if (palIncompleta[i] != '_')
      palPantalla[i] = palIncompleta[i];
  }
}

void mostrarHorca(int nro)
{
  switch (nro)
  {
  case 0:
    printf("    +---+\n");
    printf("    |   |\n");
    printf("        |\n");
    printf("        |\n");
    printf("        |\n");
    printf("        |\n");
    printf("  =======\n");
    break;
  case 1:
    printf("    +---+\n");
    printf("    |   |\n");
    printf("    O   |\n");
    printf("        |\n");
    printf("        |\n");
    printf("        |\n");
    printf("  =======\n");
    break;
  case 2:
    printf("    +---+\n");
    printf("    |   |\n");
    printf("    O   |\n");
    printf("    |   |\n");
    printf("        |\n");
    printf("        |\n");
    printf("  =======\n");
    break;
  case 3:
    printf("    +---+\n");
    printf("    |   |\n");
    printf("    O   |\n");
    printf("   /|   |\n");
    printf("        |\n");
    printf("        |\n");
    printf("  =======\n");
    break;
  case 4:
    printf("    +---+\n");
    printf("    |   |\n");
    printf("    O   |\n");
    printf("   /|\\  |\n");
    printf("        |\n");
    printf("        |\n");
    printf("  =======\n");
    break;
  case 5:
    printf("    +---+\n");
    printf("    |   |\n");
    printf("    O   |\n");
    printf("   /|\\  |\n");
    printf("   /    |\n");
    printf("        |\n");
    printf("  =======\n");
    break;
  case 6:
    printf("    +---+\n");
    printf("    |   |\n");
    printf("    O   |\n");
    printf("   /|\\  |\n");
    printf("   / \\  |\n");
    printf("        |\n");
    printf("  =======\n");
    break;
  }
}

int contarGuiones(char *palPantalla)
{
  int cont = 0;

  for (short i = 0; i < 5; i++)
  {
    if (palPantalla[i] == '_')
      cont++;
  }
  return cont;
}

void llenarConGuiones(char *palPantalla)
{
  for (short i = 0; i < 5; i++)
  {
    palPantalla[i] = '_';
  }
  palPantalla[5] = '\0';
}

char *IngresarNombre()
{
  char *result = NULL;
  result = (char *)malloc(15 * sizeof(char));

  if (result == NULL)
  {
    printf("\nError: No se puedo asignar memoria");
    return result;
  }
  scanf(" %[^\n]", result);

  return result;
}

void guardarPuntaje(char *nombre, int puntaje)
{
  FILE *archivo = NULL;
  archivo = fopen("..\\puntaje.txt", "at"); // El modo de accesto 'at' abre el archivo para añadir datos al final
  char carga[30];
  short i = 0;

  sprintf(carga, "%s=%d\n", nombre, puntaje);

  if (archivo == NULL) // Controla el error
  {
    printf("\nError: No se pudo leer el archivo\n");
    return;
  }

  while (carga[i] != 0)
  {
    fputc(carga[i], archivo);
    i++;
  }

  fclose(archivo);
}

int cantidadDePuntajes()
{
  int cantidad = 0;
  FILE *archivo = NULL;
  archivo = fopen("..\\puntaje.txt", "rt");
  char caracter;

  if (archivo == NULL) // Controla el error
  {
    printf("\nError: No se pudo leer el archivo\n");
    return -1;
  }

  do
  {
    caracter = fgetc(archivo);
    if (caracter == '\n')
    {
      cantidad++;
    }
  } while (caracter != EOF);

  return cantidad;
}

struct puntajeJugador *obtenerPuntajes(int jugadores)
{
  FILE *archivo = fopen("..\\puntaje.txt", "r");
  struct puntajeJugador *puntajes = malloc(jugadores * sizeof(struct puntajeJugador));
  struct puntajeJugador aux;

  if (archivo == NULL)
  {
    printf("No se pudo abrir el archivo.\n");
    return NULL;
  }

  if (puntajes == NULL)
  {
    printf("Error de memoria.\n");
    fclose(archivo);
    return NULL;
  }

  for (int i = 0; i < jugadores; i++)
  {
    char linea[50];
    fgets(linea, sizeof(linea), archivo);  // Traigo la linea del archivo.

    char *nombre = strtok(linea, "=");      // Corto la linea desde 0 hasta que encuentre '='
    char *puntajeStr = strtok(NULL, "\n");  // NULL(misma linea) hasta \n (fin de linea).

    if (nombre != NULL && puntajeStr != NULL)
    {
      puntajes[i].nombre = malloc(strlen(nombre) + 1);
      strcpy(puntajes[i].nombre, nombre);
      sscanf(puntajeStr, "%d", &puntajes[i].puntaje);
    }
  }
  fclose(archivo);

  for (int i = 0; i < jugadores-1; i++)  // Ordenamiento. Para devolver funcion ya ordenada.
  {
    for (int j = i + 1; j < jugadores; j++)
    {
      if (puntajes[i].puntaje < puntajes[j].puntaje)
      {
        aux = puntajes[i];
        puntajes[i] = puntajes[j];
        puntajes[j] = aux;
      }
    }
  }

  return puntajes;
}