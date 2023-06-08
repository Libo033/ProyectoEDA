#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main(void)
{
  time_t today = time(NULL);
  struct tm *tm = localtime(&today);

  printf("%02d/%02d/%d", tm->tm_mday, tm->tm_mon, (tm->tm_year + 1900));

  return 0;
}
