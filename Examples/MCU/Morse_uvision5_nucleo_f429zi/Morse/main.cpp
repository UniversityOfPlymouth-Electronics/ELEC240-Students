#include "mbed.h"
#define speed 100

DigitalOut myled(LED1);

void flashLED (char dNdString[]);

// Dot  = 1 element
// Dash = 3 elements
// Inter-symbol (dot/dash) spacing = 1 element
// Inter-character spacing         = 3 elements
// Inter-word spacing              = 7 elements

// Define dots and dashes         // String index to Character
char* MorseCode[] =     {".-",      //  0 = A ('A' = ASCII code 65; 'a' = ASCII code 97)
                         "-...",    //  1 = B
                         "-.-.",    //  2 = C
                         "-..",     //  3 = D
                         ".",       //  4 = E
                         "..-.",    //  5 = F
                         "--.",     //  6 = G
                         "....",    //  7 = H
                         "..",      //  8 = I
                         ".---",    //  9 = J
                         "-.-",     // 10 = K
                         ".-..",    // 11 = L
                         "--",      // 12 = M
                         "-.",      // 13 = N
                         "---",     // 14 = O
                         ".--.",    // 15 = P
                         "--.-",    // 16 = Q
                         ".-.",     // 17 = R
                         "...",     // 18 = S
                         "-",       // 19 = T
                         "..-",     // 20 = U
                         "...-",    // 21 = V
                         ".--",     // 22 = W
                         "-..-",    // 23 = X
                         "-.--",    // 24 = Y
                         "--..",    // 25 = Z
                         "-----",   // 26 = 0 (ASCII code 48)
                         ".----",   // 27 = 1
                         "..---",   // 28 = 2
                         "...--",   // 29 = 3
                         "....-",   // 30 = 4
                         ".....",   // 31 = 5
                         "-....",   // 32 = 6
                         "--...",   // 33 = 7
                         "---..",   // 33 = 8
                         "----.",   // 34 = 9
                         "--..--",  // 36 = , (ASCII code 44)
                         ".-.-.-"   // 37 = . (ASCII code 46)
                        };


void dot (void)
{
    myled = 1; // LED is ON
    wait_ms(speed); // 200 ms
    myled = 0; // LED is OFF
    wait_ms(speed); // 200ms sec
}

void dash (void)
{
    myled = 1; // LED is ON
    wait_ms(speed*3); // 200 ms
    myled = 0; // LED is OFF
    wait_ms(speed); // 200ms sec
}

void CharErr(void)                      // FLASH LED QUICKLY
{
    while(1) {
        myled = 1; // LED is ON
        wait_ms(50); // 200 ms
        myled = 0; // LED is OFF
        wait_ms(50); // 200ms sec
    }
}

void flashLED (char Morse[])
{

    for (int i = 0; Morse[i] != '\0'; i++) {
        if (Morse[i] == '.')            // It's a dot
            dot();
        else if (Morse[i] == '-')       // It's a dash
            dash();
        else
            CharErr();               // Unexpected character
    }
}

void Transmit (char txt[])
{
    char TxChar;

    for (int i = 0; txt[i] != '\0'; i++) {
        TxChar = txt[i];
        if (TxChar >= 'a' && TxChar <= 'z')
            TxChar = TxChar - 32;                                           // convert to CAPITAL

        if (TxChar >= 'A' && TxChar <= 'Z')
            flashLED(MorseCode[TxChar - 'A']);
        else if (TxChar >= '0' && TxChar <= '9')
            flashLED(MorseCode[TxChar - '0' + 26]);
        else if (TxChar == ',')
            flashLED(MorseCode[36]);
        else if (TxChar == '.')
            flashLED(MorseCode[37]);
        else if (TxChar == ' ')
            wait_ms(6*speed);     // Inter-word delay = 7 x dot delays; we already have one after last symbol
        else
            CharErr();              // Unexpected character

        wait_ms(3*speed);   // Inter-character delay = 3 x dot delays; we already have one after last symbol
    }
    wait_ms(7*speed);       // Inter-word delay = 7 x dot delays; we already have one after last symbol
}

int main()
{
    while(1) {
        Transmit("Hello World");
    }
}
