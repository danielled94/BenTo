
#include "src/MainManager.h"
MainManager main("1.2.3");

void setup()
{
  delay(50); //
  main.init();
}

void loop()
{
  main.update();
}
