//Librerias
#include <Arduino.h>
#include <PID_v1.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
//#include <RotaryEncoder.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define DHTTYPE DHT11
//Pins & Variables
#define DHTPIN 2
#define Led 3
#define Soldador 9
#define Sonda A2
#define Pot A3
#define Store 4
#define Emerg 7
#define vIn A1
//RotaryEncoder encoder(A0, A3);
DHT dht(DHTPIN, DHTTYPE);
const int PWMMIN = 0;
const int PWMMAX = 255;
const int maxIntTemp = 50;
const int maxVolt = 250;
const int minVolt = -25;
int PWMOUT = 0;
bool emergencyStop = false;
float voltIn = 0;
float voltOut = 0;
int errCode = 0 ; 
/*
0 = OK
1 = Botón de emergencia
2 = baja tensión < 23.5 V
3 = Alta tension > 25 V
4 = Temperatura interna alta +50°
*/
float dhtInt = 0;
//Encoder 
static int pos = 0;
int newPos = 0;
int oldPos = 0;
//PID
double temp, set, out;
double Kp=1, Ki=0, Kd=0;
PID Pid1(&temp, &out, &set, Kp, Ki, Kd, DIRECT);
//Funciones
void EmergenciaCheck(){
    if (Emerg == HIGH)
    {
        Serial.println("Emergencia");
        errCode = 1;
        set = 0;
       lcd.clear();
        lcd.setCursor(0,1);lcd.print("Modo");
        lcd.setCursor(0,0);lcd.print("Emergencia");
        emergencyStop = true;
    }
        while (emergencyStop == true){
        set = 0;
        Pid1.Compute();    
        lcd.clear();
        delay(250);
        digitalWrite(Led, HIGH);
        delay(1000);
        digitalWrite(Led, LOW);
        lcd.setCursor(0,1);lcd.print("Modo  " + errCode);
        lcd.setCursor(0,0);lcd.print("Emergencia");
}
}
void lowVoltageCheck(){

    voltIn = analogRead(vIn);
    voltOut = map(voltIn, 0, 1023, 0, 25);
    if (voltOut <=  minVolt)
    {
        Serial.println("baja tensión");
        errCode = 2;
        emergencyStop = true;
        EmergenciaCheck();
    } 
}
void highVoltageCheck(){

    voltIn = analogRead(vIn);
    voltOut = map(voltIn, 0, 1023, 0, 25);
    if (voltOut >=  maxVolt)
    {
        Serial.println("alta tensión");
        errCode = 3;
        emergencyStop = true;
        EmergenciaCheck();
    }
    
}
void intTempCheck(){
        
     dhtInt = dht.readTemperature();
     Serial.println("Temp es: ");
     Serial.print(dhtInt);
     if (dhtInt > maxIntTemp){
        Serial.println("alta temperatura");
        
        errCode = 4;
        emergencyStop = true;
        EmergenciaCheck();
     }
}
void checkSystemStatus(){
      //      Serial.println("Checkeando...");
    EmergenciaCheck();
    lowVoltageCheck();
    highVoltageCheck();
    intTempCheck();
}
void store(){
            Serial.println("Stand By");
    set = 0;
    Pid1.Compute();
    lcd.clear();
    lcd.setCursor(5,1);lcd.print("Stand");
    lcd.setCursor(7,0);lcd.print("By");
    delay(1000);
    checkSystemStatus();
}
void off(){
            Serial.println("Off");
   lcd.clear();
    lcd.setCursor(6,1);lcd.print("OFF");
    
    delay(500);
    checkSystemStatus();
}
void lcdDefault(){
    lcd.clear();
    lcd.setCursor(0,1);lcd.print("PRESET T: ");  
    lcd.setCursor(0,0);lcd.print("T ACTUAL: "); 
}

void setup() {
    Serial.begin (9600);
    Serial.println("Iniciando....");
    pinMode(Led, OUTPUT);
    pinMode(Soldador, OUTPUT);
    pinMode(Sonda, INPUT);
    pinMode(Store, INPUT);
    pinMode(Emerg, INPUT);
    pinMode(vIn, INPUT);
    Serial.print(" pinmode listo...");
    Pid1.SetMode(AUTOMATIC);
    Serial.print(" PID listo....");
    lcd.backlight();
    lcd.init();
    lcd.clear();
    lcd.setCursor(0,1);lcd.print("Buan");
    lcd.setCursor(3,0);lcd.print("Industries"); 
    Serial.print(" LCD listo....");
    delay(1500);
    lcdDefault();
    dht.begin();
    Serial.print(" listo");
    digitalWrite(Led, HIGH);
    delay (500);
    digitalWrite(Led, LOW);
    digitalWrite(Led, HIGH);
    delay (500);
    digitalWrite(Led, LOW);
}

void loop() {
    checkSystemStatus();
    int InSonda = analogRead(Sonda);
    int InPot = analogRead(Pot);
  temp = map(InSonda, 0, 1023, 0, 500);
  //  temp = 25;
    set = map(InPot, 0, 1023, 0, 480);
   // encoder1();
    Pid1.Compute();
    delay(100); //solo depuracion
    Serial.print(out); //solo depuracion
    Serial.print(",");    
    Serial.print(set);//solo depuracion
    Serial.print(",");    
    Serial.println(PWMOUT);//solo depuracion
    PWMOUT = map(out, 0, 480, PWMMIN, PWMMAX);
    lcd.setCursor(10,1);lcd.print(set);
    lcd.setCursor(10,0);lcd.print(temp);
    analogWrite(Soldador, PWMOUT);
    lcdDefault();
    Pid1.Compute();
   while (Store == HIGH){
    store();
   }
   checkSystemStatus();
   while (set == 0){
    off();
   }
    checkSystemStatus();
}
