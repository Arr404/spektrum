

#include <LiquidCrystal.h>

int sensorValue = 0;
int buttonPIN = 6;
int priorstate=0;
int now=0;
int scrolLeft = 0;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
String nilai[4] = {"", "", "", ""};
const uint8_t analog_pins[4] = {A1, A2, A3, A4};
int state[4] = {0,0,0,0};
String jawab[4] = {
  "1000011101101101",
  "1011010000000000",
  "1001111110011001",
  "110100000111010"};

void setup()
{
  Serial.begin(9600);
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
  pinMode(buttonPIN, INPUT);
  
  // Print a message to the LCD.
  lcd_1.print("Rahasia negara : ");
}

void loop()
{
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting
  // begins with 0):

  lcd_1.setCursor(0, 1);
  getPotensio();
  lcd_1.print(ledNilai());
  getButton();
  
  delay(10); // Wait for 1000 millisecond(s)
}

String encrypt(int a){
  int b = a+1;
  b = b*12093293;
  String hasil = String(b,BIN);
  return hasil;
}

String ledNilai(){
 
 return (nilai[0])+" "+(nilai[1])+" "+(nilai[2])+" "+(nilai[3]);
}

void checked(bool howSwitch){
  if(howSwitch){
    setRow(1);
    if(encrypt(analogRead(A0)) == jawab[now]){
    state[now] = 1023;
    now+=1;
    for (int positionCounter = 0; positionCounter < 1; positionCounter++) {
      // scroll one position left:
      lcd_1.scrollDisplayLeft();
      // wait a bit:
      delay(150);
    }
   }else{
    setRow(0);
   }
    lightLed();
  }
}
void getButton(){
  int stater;
  stater = digitalRead(buttonPIN);
  if( stater != priorstate ){
    Serial.println(stater);
    priorstate = stater;
    
    checked(stater);
  }
  
}
void setRow(bool what){
  lcd_1.setCursor(0, 0);
  if(what){
    lcd_1.print("Wah bener bangedd :)");
  }else{
    lcd_1.print("Yah salah aowwkwowkokwko :(");
  }
  
}
void getPotensio(){
  sensorValue = analogRead(A0);
  String hasil = "";
  if(sensorValue < 10){
    hasil = "000"+String(sensorValue);
  }else if(sensorValue < 100){
    hasil = "00"+String(sensorValue);
  }else if(sensorValue < 1000){
    hasil = "0"+String(sensorValue);
  }else{
    hasil += String(sensorValue);
  }
  
  nilai[now] = hasil;
}


void lightLed(){
  
  for(int i = 0 ;i<4;i++){
    analogWrite(analog_pins[i],state[i]);
  }
}
