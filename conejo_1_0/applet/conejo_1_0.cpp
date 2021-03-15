/* conejo-1.0 */
#include <Stepper.h>

#define motorSteps 200
#define motorPin1 8
#define motorPin2 9
#define vibrator 6
#define ledR 3
#define ledG 5
#define ldrPin 1
#define piezoPin 0
#define LDR_UMBRAL 100
#define PIEZO_UMBRAL 20
#define STEPPER_FAST 100
#define STEPPER_MEDIUM 90 
#define STEPPER_LOW 20
#define BLINK_TIME 150

#include "WProgram.h"
void setup();
void loop();
void encoge( int vel );
void estira( int vel );
void vibraBrazo( int n);
void vibrarON();
void vibrarOFF();
int checkLDR();
int checkPIEZO();
void fadeR (int vel, int dur);
void blinkR(int howManyTimes);
void blinkG(int howManyTimes);
void onR();
void offR();
void onG();
void offG();
Stepper myStepper(motorSteps, motorPin1, motorPin2);
int ldr = 0;
int piezo = 0;
int fade=0;  //valor del fade led loop principal
int subida=1;  //lo mismo

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed( STEPPER_MEDIUM );
  pinMode( ledR, OUTPUT );
  pinMode( ledG, OUTPUT );
  pinMode( vibrator, OUTPUT );
  Serial.print("LDR = ");
  Serial.println( ldr, DEC );
  Serial.print("PIEZO = ");
  Serial.println( piezo, DEC );
  Serial.println( "Ready!" );
}

void loop() {
  Serial.print("PIEZO = ");
  Serial.println( piezo, DEC );
  if(subida==1){
    fade++;
    analogWrite(ledR,fade);
    offG();
    if (fade==250){
      subida=0;
      }
    } else {
      fade--;
      analogWrite(ledG,fade);
      offR();
      if (fade==0){
        subida=1;
        }
   }
  
  if( checkLDR() ) {
    Serial.print("LDR = ");
    Serial.println( ldr, DEC );
     myStepper.step( 200 );
     blinkR(2);
     onG();
     myStepper.step( -400 );
     blinkR( 4 );
     myStepper.step( 400 );
     offG();
     onR();
     myStepper.step( -200 );     
     blinkR( 1 );
     blinkG( 1 );
     blinkR( 1 );
     blinkG( 1 );
     blinkR( 1 );
     blinkG( 1 );
     blinkR( 1 );
     blinkG( 1 );
     blinkR( 1 );
     blinkG( 1 );
     blinkR( 1 );
     blinkG( 1 );
  }
  if( checkPIEZO() ) {
    Serial.print("PIEZO = ");
    Serial.println( piezo, DEC );
    onR();
    vibrarON();
    blinkR( 12 );
    vibrarOFF();
    blinkR( 1 );
    blinkG( 1 );
    blinkR( 1 );
    blinkG( 1 );
    
  }
}

void encoge( int vel ) {
  myStepper.setSpeed( vel );
  myStepper.step( -200 );
}

void estira( int vel ) {
  myStepper.setSpeed( vel );
  myStepper.step( 200 );
  
}

void vibraBrazo( int n) {
  myStepper.setSpeed( STEPPER_FAST );
  for( int i = 0; i < n; i++ ) {
    myStepper.step( 50 );
    myStepper.step( -50 ); 
  }
  
}

void vibrarON() {
  digitalWrite( vibrator, HIGH );
}

void vibrarOFF() {
  digitalWrite( vibrator, LOW );
}

int checkLDR(){
  ldr = analogRead( ldrPin );
  
  if ( ldr < LDR_UMBRAL ){
    return 1;
  } else {
    return 0;
  }   
}  

int checkPIEZO(){
  piezo = analogRead( piezoPin );
    
  if ( piezo > PIEZO_UMBRAL ){
    return 1;
    }
  else {
    return 0;
  }   
}  


void fadeR (int vel, int dur) {   
  unsigned long t0 = millis();
  
  while( (millis() - t0) < dur) {
    for(int i=0; i<255; i++) {
      analogWrite(ledR, i);
      delay(vel);
      }
    for(int i=255; i>=0; i--) {
      analogWrite(ledR, i);
      delay(vel);
      }
  }
}

void blinkR(int howManyTimes) {
  int i;
  for (i=0; i< howManyTimes; i++) {
    digitalWrite(ledR, HIGH);
    delay( BLINK_TIME );
    digitalWrite(ledR, LOW);
    delay( BLINK_TIME );
  }
}

void blinkG(int howManyTimes) {
  int i;
  for (i=0; i< howManyTimes; i++) {
    digitalWrite(ledG, HIGH);
    delay( BLINK_TIME );
    digitalWrite(ledG, LOW);
    delay( BLINK_TIME );
  }
}

void onR() {
  digitalWrite(ledR, HIGH); 
}

void offR() {
  digitalWrite(ledR, LOW); 
}

void onG() {
  digitalWrite(ledG, HIGH); 
}

void offG() {
  digitalWrite(ledR, LOW); 
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

