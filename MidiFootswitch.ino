#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 3
#define BUTTON_3_PIN 4
#define BUTTON_4_PIN 5
#define BUTTON_5_PIN 6
#define BUTTON_6_PIN 7
#define BUTTON_7_PIN 8
#define BUTTON_8_PIN 9
#define BUTTON_9_PIN 10
#define BUTTON_10_PIN 11
#define BUTTON_11_PIN 12
#define BUTTON_12_PIN 13

#define POT_1_PIN A0
#define POT_2_PIN A1
#define POT_3_PIN A2
#define POT_4_PIN A3
#define POT_5_PIN A4
#define POT_6_PIN A5

#define C_NOTE 60
#define Cdiez_NOTE 61
#define D_NOTE 62
#define Ddiez_NOTE 63
#define E_NOTE 64
#define F_NOTE 65
#define Fdiez_NOTE 66
#define G_NOTE 67
#define Gdiez_NOTE 68
#define A_NOTE 69
#define Adiez_NOTE 70
#define B_NOTE 71

class Button {
  public: boolean buttonOn = false; // buttonOn = true - с кнопки поступает сигнал нажатия
  public: boolean stateChange = false; // кнопка изменил своё состояние
  private: byte timeCounter; // счетчик времени, прошедшего с момента поступления сигнала об изменении состояния кнопки
  private: byte waitingTime; // timeCounter = waitingTime - кнопка считается изменившей своё состояние
  private: byte pin; // номер пина кнопки

  public: Button(byte pinPar, byte waitingTimePar); // объявление конструктора кнопки
  public: void scanState (); // объявление метода сканирования состояния кнопки
};

Button::Button (byte pinPar, byte waitingTimePar) { // конструктор кнопки
  pin = pinPar;
  waitingTime = waitingTimePar;
  pinMode(pin, INPUT_PULLUP);
}

void Button::scanState () { // метод сканирования состояния кнопки
  if (buttonOn != digitalRead(pin)) { // если сигнал на пине кнопки изменился, сбрасываем timeCounter на 0
    timeCounter = 0;
  } else {
    timeCounter++; 
    if (timeCounter >= waitingTime) {
      buttonOn = ! buttonOn;
      timeCounter = 0;
    }
  }
}

byte waitingTime = 5;

Button but1(BUTTON_1_PIN, waitingTime);
Button but2(BUTTON_2_PIN, waitingTime);
Button but3(BUTTON_3_PIN, waitingTime);
Button but4(BUTTON_4_PIN, waitingTime);
Button but5(BUTTON_5_PIN, waitingTime);
Button but6(BUTTON_6_PIN, waitingTime);
Button but7(BUTTON_7_PIN, waitingTime);
Button but8(BUTTON_8_PIN, waitingTime);
Button but9(BUTTON_9_PIN, waitingTime);
Button but10(BUTTON_10_PIN, waitingTime);
Button but11(BUTTON_11_PIN, waitingTime);
Button but12(BUTTON_12_PIN, waitingTime);
Button button[12] = {but1, but2, but3, but4, but5, but6, but7, but8, but9, but10, but11, but12};

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (byte i = 0; i < 12; i++) { // поочередная проверка состояния кропок с отправкой соответствующего сообщения
    button[i].scanState();
    if (button[i].buttonOn == true && button[i].stateChange == false) {
      button[i].stateChange = true;
      //Serial.println("Button is ON");
      switch (i) {
        case 0:
        noteOn(C_NOTE);
        break;
        case 1:
        noteOn(Cdiez_NOTE);
        break;
        case 2:
        noteOn(D_NOTE);
        break;
        case 3:
        noteOn(Ddiez_NOTE);
        break;
        case 4:
        noteOn(E_NOTE);
        break;
        case 5:
        noteOn(F_NOTE);
        break;
        case 6:
        noteOn(Fdiez_NOTE);
        break;
        case 7:
        noteOn(G_NOTE);
        break;
        case 8:
        noteOn(Gdiez_NOTE);
        break;
        case 9:
        noteOn(A_NOTE);
        break;
        case 10:
        noteOn(Adiez_NOTE);
        break;
        case 11:
        noteOn(B_NOTE);
        break;
      }
    }
    else if (button[i].buttonOn == false && button[i].stateChange == true) {
      button[i].stateChange = false;
      //Serial.println("Button is OFF");
      switch (i) {
        case 0:
        noteOff(C_NOTE);
        break;
        case 1:
        noteOff(Cdiez_NOTE);
        break;
        case 2:
        noteOff(D_NOTE);
        break;
        case 3:
        noteOff(Ddiez_NOTE);
        break;
        case 4:
        noteOff(E_NOTE);
        break;
        case 5:
        noteOff(F_NOTE);
        break;
        case 6:
        noteOff(Fdiez_NOTE);
        break;
        case 7:
        noteOff(G_NOTE);
        break;
        case 8:
        noteOff(Gdiez_NOTE);
        break;
        case 9:
        noteOff(A_NOTE);
        break;
        case 10:
        noteOff(Adiez_NOTE);
        break;
        case 11:
        noteOff(B_NOTE);
        break;
      }
    }
  }
  
  // код для обработки потенциометров
  
  delay(2); 
}

void noteOn (int pitch) {
  Serial.write(0x90);
  Serial.write(pitch);
  Serial.write(0x7F);
}

void noteOff (int pitch) {
  Serial.write(0x80);
  Serial.write(pitch);
  Serial.write(0x7F);
}
