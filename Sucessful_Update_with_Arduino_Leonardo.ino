#include "Keyboard.h"

void setup()
{
  Keyboard.begin();
  delay(500);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_ESC);
  Keyboard.releaseAll();
  delay(300);

  Keyboard.print("");
  delay(1000);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(500);

  Keyboard.print("ubuntu");
  delay(500);

  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(2000);

  Keyboard.print("sudo apt-get update");
  Keyboard.press(KEY_RETURN);
   Keyboard.releaseAll();
  delay(500);
  Keyboard.print("toor");
  Keyboard.press(KEY_RETURN);

  


  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(500);

  Keyboard.end();
}
void loop()
{
  
}
