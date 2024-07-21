#include "LedControl.h"
#include <SPI.h>
#include <MFRC522.h>
#include <RFID.h>


#define DIN 3
#define CS 2
#define CLK 5
#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 

// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;

LedControl lc = LedControl(DIN, CLK, CS, 1);
unsigned char A[] = {0b00000000,
  0b00111100,
  0b01100110,
  0b01100110,
  0b01111110,
  0b01100110,
  0b01100110,
  0b01100110};
unsigned char B[] = {0b00000000,
  0b01111100,
  0b01100110,
  0b01100110,
  0b01111100,
  0b01100110,
  0b01100110,
  0b01111100};
unsigned char C[] = {0b00000000,
  0b00111100,
  0b01100110,
  0b01100000,
  0b01100000,
  0b01100000,
  0b01100110,
  0b00111100};
unsigned char D[] = {0b00000000,
  0b01111100,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01111100};
unsigned char E[] = {0b00000000,
  0b01111110,
  0b01100000,
  0b01100000,
  0b01111100,
  0b01100000,
  0b01100000,
  0b01111110};
unsigned char F[] = {0b00000000,
  0b01111110,
  0b01100000,
  0b01100000,
  0b01111100,
  0b01100000,
  0b01100000,
  0b01100000};
unsigned char G[] = {0b00000000,
  0b00111100,
  0b01100110,
  0b01100000,
  0b01100000,
  0b01101110,
  0b01100110,
  0b00111100};
unsigned char H[] = {0b00000000,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01111110,
  0b01100110,
  0b01100110,
  0b01100110
};
unsigned char I[] = {0b00000000,
  0b00111100,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00111100
};
unsigned char J[] = {0b00000000,
  0b00011110,
  0b00001100,
  0b00001100,
  0b00001100,
  0b01101100,
  0b01101100,
  0b00111000};
unsigned char K[] = {0b00000000,
  0b01100110,
  0b01101100,
  0b01111000,
  0b01110000,
  0b01111000,
  0b01101100,
  0b01100110};
unsigned char L[] = {0b00000000,
  0b01100000,
  0b01100000,
  0b01100000,
  0b01100000,
  0b01100000,
  0b01100000,
  0b01111110};
unsigned char M[] = {0b00000000,
  0b01100011,
  0b01110111,
  0b01111111,
  0b01101011,
  0b01100011,
  0b01100011,
  0b01100011};
unsigned char N[] = {0b00000000,
  0b01100011,
  0b01110011,
  0b01111011,
  0b01101111,
  0b01100111,
  0b01100011,
  0b01100011
};
unsigned char O[] = {0b00000000,
  0b00111100,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b00111100};
unsigned char P[] = {0b00000000,
  0b01111100,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01111100,
  0b01100000,
  0b01100000};
unsigned char Q[] = {0b00000000,
  0b00111100,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01101110,
  0b00111100,
  0b00000110};
unsigned char R[] = {0b00000000,
  0b01111100,
  0b01100110,
  0b01100110,
  0b01111100,
  0b01111000,
  0b01101100,
  0b01100110};
unsigned char S[] = {0b00000000,
  0b00111100,
  0b01100110,
  0b01100000,
  0b00111100,
  0b00000110,
  0b01100110,
  0b00111100};
unsigned char T[] = {0b00000000,
  0b01111110,
  0b01011010,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000};
unsigned char U[] = {0b00000000,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b00111110
};
unsigned char V[] = {0b00000000,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b00111100,
  0b00011000};
unsigned char W[] = {0b00000000,
  0b01100011,
  0b01100011,
  0b01100011,
  0b01101011,
  0b01111111,
  0b01110111,
  0b01100011};
unsigned char X[] = {0b00000000,
  0b01100011,
  0b01100011,
  0b00110110,
  0b00011100,
  0b00110110,
  0b01100011,
  0b01100011};
unsigned char Y[] = {0b00000000,
  0b01100110,
  0b01100110,
  0b01100110,
  0b00111100,
  0b00011000,
  0b00011000,
  0b00011000};
unsigned char Z[] = {0b00000000,
  0b01111110,
  0b00000110,
  0b00001100,
  0b00011000,
  0b00110000,
  0b01100000,
  0b01111110};

void setup() {
    Serial.begin(9600);
    SPI.begin(); 
    rfid.init();
    lc.shutdown(0, false);
    lc.setIntensity(0, 0);
    lc.clearDisplay(0);
}

void loop() {
    printWord();
    if (rfid.isCard()) {
        if (rfid.readCardSerial()) {
            if (rfid.serNum[0] != serNum0
                && rfid.serNum[1] != serNum1
                && rfid.serNum[2] != serNum2
                && rfid.serNum[3] != serNum3
                && rfid.serNum[4] != serNum4
            ) {
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("Card found");
                serNum0 = rfid.serNum[0];
                serNum1 = rfid.serNum[1];
                serNum2 = rfid.serNum[2];
                serNum3 = rfid.serNum[3];
                serNum4 = rfid.serNum[4];
               
                //Serial.println(" ");
                Serial.println("Cardnumber:");
                Serial.print("Dec: ");
		Serial.print(rfid.serNum[0],DEC);
                Serial.print(", ");
		Serial.print(rfid.serNum[1],DEC);
                Serial.print(", ");
		Serial.print(rfid.serNum[2],DEC);
                Serial.print(", ");
		Serial.print(rfid.serNum[3],DEC);
                Serial.print(", ");
		Serial.print(rfid.serNum[4],DEC);
                Serial.println(" ");
                        
                Serial.print("Hex: ");
		Serial.print(rfid.serNum[0],HEX);
                Serial.print(", ");
		Serial.print(rfid.serNum[1],HEX);
                Serial.print(", ");
		Serial.print(rfid.serNum[2],HEX);
                Serial.print(", ");
		Serial.print(rfid.serNum[3],HEX);
                Serial.print(", ");
		Serial.print(rfid.serNum[4],HEX);
                Serial.println(" ");
             } else {
               /* If we have the same ID, just write a dot. */
               Serial.print(".");
             }
          }
    }
    
    rfid.halt();
}

void printWord(){
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, A[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, B[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, C[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, D[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, E[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, F[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, G[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, H[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, I[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, J[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, K[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, L[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, M[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, N[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, O[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, P[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, Q[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, R[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, S[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, T[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, U[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, V[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, W[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, X[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, Y[row]);
    }
    delay(1000);
    for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, Z[row]);
    }
    delay(1000);
}