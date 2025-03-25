#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define ENA 46  
#define IN1 44  
#define IN2 45  

#define BTN_PIN A0  


int motorSpeed = 128;       
bool motorDirection = true;  


#define BTN_RIGHT 50   
#define BTN_UP 150      
#define BTN_DOWN 400     
#define BTN_LEFT 600     
#define BTN_SELECT 800   
#define BTN_NONE 1023    

void setup() {
    lcd.begin(16, 2);

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    updateLCD();
}

void loop() {

    int buttonValue = analogRead(BTN_PIN);


    if (buttonValue < BTN_RIGHT) {
        motorDirection = true;  
    } else if (buttonValue < BTN_UP) {
        motorSpeed = constrain(motorSpeed + 10, 0, 255);
    } else if (buttonValue < BTN_DOWN) {
        motorSpeed = constrain(motorSpeed - 10, 0, 255);
    } else if (buttonValue < BTN_LEFT) {
        motorDirection = false;
    }

    if (motorDirection) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    analogWrite(ENA, motorSpeed);


    updateLCD();
    delay(200);
}


void updateLCD() {
    lcd.clear(); 

    lcd.setCursor(0, 0);
    lcd.print("DUTY ");
    lcd.print(map(motorSpeed, 0, 255, 0, 100));
    lcd.print("%");


    lcd.setCursor(0, 1);
    lcd.print("DIR ");
    lcd.print(motorDirection ? "CW" : "CCW");
}
