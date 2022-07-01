#include <string.h>

int main ()
{
  char str[] = "This is a sample string";
  char * pch;
  printf ("Looking for the 's' character in \"%s\"...\n",str);
  pch=strchr(str,'s');
  while (pch!=NULL)
  {
    printf ("found at %d\n",pch-str+1);
    pch=strchr(pch+1,'s');
  }
  return 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  main();
}

void loop() {
  // put your main code here, to run repeatedly:

}
