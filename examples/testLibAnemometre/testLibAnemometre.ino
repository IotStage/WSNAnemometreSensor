#include <WSN.h>

Anemometre a;

void setup() {
  // put your setup code here, to run once:
  a.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  a.updateAnemometre();
}
