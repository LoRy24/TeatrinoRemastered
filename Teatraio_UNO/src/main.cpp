//
// Teatraio v1.0.0
// By i non fantastici 4
//

/*
 * Librerie
 */

#pragma region Libs

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include <Stepper.h>
#include <SoftwareSerial.h>

#pragma endregion

/*
 * Definizioni
 */

#pragma region Definizioni

// Versione
#define VERSION                     "v1.0.0/DEV.1"

// Pulsanti gestione (PINs)
#define CHANGE_MENU_BUTTON          2
#define DECREASE_BUTTON             3
#define INCREASE_BUTTON             4

// Indirizzi I2C
#define LCD_I2C_ADDRESS             0x27
#define LCD_COLS                    16
#define LCD_ROWS                    2

// Mega Serial
#define MEGA_SERIAL_RECEIVE         5
#define MEGA_SERIAL_TRANSMIT        6

// Stepper
#define STEPPER_STEPS               2048
#define STEPPER_PIN_1               8
#define STEPPER_PIN_2               10
#define STEPPER_PIN_3               9
#define STEPPER_PIN_4               11

#pragma endregion

/*
 * Testate funzioni
 */

#pragma region Testate Funzioni

void updateButtonsStates();
bool pressed(const int* buttonStates);
char* convertMenuIdToString(int id);
void printSerialMenuChange();
void updateMenuName();
void increaseMenuAction();
void decreaseMenuAction();

#pragma endregion

/*
 * Registri globali
 */

#pragma region Globali

// Stati pulsanti {LAST, CURRENT}
int CHANGE_MENU_BUTTON_STATES[2]    = {0, 0};
int DECREASE_BUTTON_STATES[3]       = {0, 0};
int INCREASE_BUTTON_STATES[4]       = {0, 0};

// Menu selezionato
int menu = 0;
int menusAmount = 2;

// Profilo luci attuale
int lightsProfile = 1;
int lightsProfilesAmount = 5;

// Display LCD
LiquidCrystal_I2C lcdDisplayI2C(LCD_I2C_ADDRESS, LCD_COLS, LCD_ROWS);

// Motore stepper palco
Stepper stepper(STEPPER_STEPS, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);

// Seriale X Arduino Mega
SoftwareSerial MegaSerial(MEGA_SERIAL_RECEIVE, MEGA_SERIAL_TRANSMIT);

#pragma endregion

/*
 * Runtime Arduino
 */

#pragma region Runtime Arduino

/**
 * Funzione principale di avvio
 */
void setup() {
    // Setup seriale
    Serial.begin(9600);

    // Init seriale Mega
    MegaSerial.begin(9600);
    MegaSerial.print(0);

    // Messaggio avvio seriale
    Serial.println("-------------------------------------------------");
    Serial.println("");
    Serial.println("Teatraio " VERSION);
    Serial.println("By Lorenzo, Martina, Leonardo, Stefania");
    Serial.println("");

    // Setup pulsanti management
    pinMode(CHANGE_MENU_BUTTON, INPUT);
    pinMode(DECREASE_BUTTON, INPUT);
    pinMode(INCREASE_BUTTON, INPUT);

    // Notifica setup pulsanti

    Serial.println("-------------------------------------------------");
    Serial.println("");
    Serial.println("Pin di input impostati!");
    Serial.println("");

    // Init LCD
    lcdDisplayI2C.init();
    lcdDisplayI2C.setCursor(0, 0);
    lcdDisplayI2C.setBacklight(HIGH);
    lcdDisplayI2C.printstr("Teatraio Admin");
    lcdDisplayI2C.setCursor(0, 1);
    lcdDisplayI2C.printstr("Luci #");
    lcdDisplayI2C.print(lightsProfile);
    lcdDisplayI2C.setCursor(0, 1);

    // Notifica setup display

    Serial.println("-------------------------------------------------");
    Serial.println("");
    Serial.println("Display LCD I2C Configurato!");
    Serial.println("");

    Serial.print("Indirizzo: ");
    Serial.print(LCD_I2C_ADDRESS);
    Serial.print("\n\r");

    Serial.print("Righe: ");
    Serial.print(LCD_ROWS);
    Serial.print("\n\r");

    Serial.print("Colonne: ");
    Serial.print(LCD_COLS);
    Serial.print("\n\r");

    Serial.println("");

    // Setup Stepper
    stepper.setSpeed(10);

    // Notifica setup stepper

    Serial.println("-------------------------------------------------");
    Serial.println("");
    Serial.println("Setup stepper completato!");
    Serial.println("");
    Serial.println("-------------------------------------------------");
}

/**
 * Funzione di loop
 */
void loop() {
    // Aggiorna i pulsanti
    updateButtonsStates();

    // Esegui in base al menu
    if (pressed(CHANGE_MENU_BUTTON_STATES)) {
        menu = (menu + 1) % menusAmount;
        printSerialMenuChange();
        updateMenuName();
    }
    else if (pressed(DECREASE_BUTTON_STATES)) {
        Serial.println("[-] Decrease");
        decreaseMenuAction();
    }
    else if (pressed(INCREASE_BUTTON_STATES)) {
        Serial.println("[+] Increase");
        increaseMenuAction();
    }

    // Delay del loop (1k esecuzioni al secondo)
    delay(1);
}

#pragma endregion

/*
 * Funzioni
 */

#pragma region Functions

void updateButtonsStates() {
    // Pulsante change menu
    CHANGE_MENU_BUTTON_STATES[0] = CHANGE_MENU_BUTTON_STATES[1];
    CHANGE_MENU_BUTTON_STATES[1] = digitalRead(CHANGE_MENU_BUTTON);

    // Pulsante diminuisci
    DECREASE_BUTTON_STATES[0] = DECREASE_BUTTON_STATES[1];
    DECREASE_BUTTON_STATES[1] = digitalRead(DECREASE_BUTTON);

    // Pulsante aumenta
    INCREASE_BUTTON_STATES[0] = INCREASE_BUTTON_STATES[1];
    INCREASE_BUTTON_STATES[1] = digitalRead(INCREASE_BUTTON);
}

bool pressed(const int* buttonStates) {
    if (buttonStates[0] == 0 && buttonStates[1] == 1) {
        return true;
    }

    return false;
}

void printSerialMenuChange() {
    Serial.print("Change menu state to ");

    // Stato menu
    Serial.print(
        menu == 0 ? "'Profilo Luci'" :
        "'Rotazione Palco'"
    );

    Serial.print("\n\r");
}

void updateMenuName() {
    // Pulisci la seconda riga
    lcdDisplayI2C.setCursor(0, 1);
    lcdDisplayI2C.printstr("                ");
    lcdDisplayI2C.setCursor(0, 1);

    if (menu == 0) {
        lcdDisplayI2C.printstr("Luci #");
        lcdDisplayI2C.print(lightsProfile);
    }
    else if (menu == 1) {
        lcdDisplayI2C.printstr("Rotazione Palco");
    }

    Serial.println("[!] LCD Updated");
}

void increaseMenuAction() {
    if (menu == 0 && lightsProfile < lightsProfilesAmount) {
        lightsProfile++;
        MegaSerial.print(lightsProfile - 1);
        updateMenuName();
    }
    else if (menu == 1) {
        while (digitalRead(INCREASE_BUTTON) == HIGH) {
            stepper.step(-128);
        }
    }
}

void decreaseMenuAction() {
    if (menu == 0 && lightsProfile > 1) {
        lightsProfile--;
        MegaSerial.print(lightsProfile - 1);
        updateMenuName();
    }
    else if (menu == 1) {
        while (digitalRead(DECREASE_BUTTON) == HIGH) {
            stepper.step(128);
        }
    }
}

#pragma endregion
