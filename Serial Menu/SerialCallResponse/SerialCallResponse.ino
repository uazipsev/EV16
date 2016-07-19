/*

Menu testing

 */

 void MenuePrint(char MenuLocation);
 void MenuControl();
 void ClearScreen();

bool VerboseEn = 1;
char inByte = 0;
char MenuMode = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    if(VerboseEn){
      Serial.write(inByte);
    }
    MenuControl();
  }
}

void MenuControl(){
  if(MenuMode ==  0){
    if(inByte == '0'){
        MenuePrint(0);
    }
    if(inByte == 'B'){
        MenuMode = 0;
        MenuePrint(0);
    }
    if(inByte == '1'){
        MenuMode = 1;
        MenuePrint(1);
    }
    if(inByte == '2'){
        MenuMode = 2;
        MenuePrint(2);
    }
    if(inByte == '3'){
        MenuMode = 3;
        MenuePrint(3);
    }
    if(inByte == '4'){
        MenuMode = 5;
        MenuePrint(5);
    }
    if(inByte == '5'){
        MenuMode = 6;
        MenuePrint(6);
    }
    else{
      MenuePrint(255);
      MenuePrint(0);
    }
  }
  if(MenuMode ==  1){
    if(inByte == 'B'){
        MenuMode = 0;
        MenuePrint(0);
    }
    else {
      MenuePrint(255);
      MenuePrint(1);
    }
  }
  if(MenuMode ==  2){
    if(inByte == 'B'){
        MenuMode = 0;
        MenuePrint(0);
    }
    else {
      MenuePrint(255);
      MenuePrint(2);
    }
  }
  if(MenuMode ==  3){
    if(inByte == 'B'){
        MenuMode = 0;
        MenuePrint(0);
    }
    if(inByte == '1'){
        MenuMode = 1;
        MenuePrint(4);
    }
    else{
      MenuePrint(255);
      MenuePrint(3);
    }
  }
  if(MenuMode ==  4){
    if(inByte == 'B'){
        MenuMode = 0;
        MenuePrint(0);
    }
//    if(inByte == '1'){
//        MenuMode = 1;
//        MenuePrint(4);
//    }
    else{
      MenuePrint(255);
      MenuePrint(4);
    }
  }
  if(MenuMode ==  5){
    if(inByte == 'B'){
        MenuMode = 0;
        MenuePrint(0);
    }
//    if(inByte == '1'){
//        MenuMode = 1;
//        MenuePrint(4);
//    }
    else {
      MenuePrint(255);
      MenuePrint(5);
    }
  }
}

void MenuePrint(char MenuLocation){
  switch (MenuLocation){
    case 0: 
      Serial.println("|-----Main Menu------|");
      Serial.println("1) Throttle Menu");
      Serial.println("2) Brake Menu");
      Serial.println("3) Settings Menu");
      Serial.println("4) Battery Info");
      Serial.println("5) ComBus Info");
      break;
   case 1:
      Serial.println("|---Throttle Menu----|");
      break;
   case 2:
      Serial.println("|-----Brake Menu-----|");
      break;   
   case 3:
      Serial.println("|---Settings Menu----|");
      Serial.println("1) Verbose ");
      Serial.println("2) Reset Value ");
      break;
   case 4:
      Serial.println("Verbose Toggled");
      if(VerboseEn){
        VerboseEn = 0;
      }
      else VerboseEn = 1;
      ClearScreen();
      break;
   case 5:
      Serial.println("|---Batery Info---|");
      break;
   case 6:
      Serial.println("|---ComBus Info---|");
      break;
   case 255:
      Serial.println("******NO Match*****");
      break;
  }
}

void ClearScreen()
{
  Serial.println("\033[2J");
}

