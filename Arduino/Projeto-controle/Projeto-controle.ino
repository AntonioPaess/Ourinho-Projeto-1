#include <Keyboard.h>

// Definição dos pinos analógicos e digitais
#define pinX A2
#define pinY A4

#define pinBotA 3 
#define pinBotB 4
#define pinBotC 5
#define pinBotD 6
#define pinBotE 7

#define bot 2

// Variáveis para os ângulos X e Y
int anguloX;
int anguloY;

// Estados anteriores dos botões
int previousButtonStateB = HIGH;
int previousButtonStateC = HIGH;
int previousButtonStateD = HIGH;
int previousButtonStateE = HIGH;

void setup() {
  // Inicializa a comunicação serial e o teclado
  Serial.begin(9600);
  Keyboard.begin();

  // Configura os pinos analógicos e digitais como entrada com pull-up
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinBotA, INPUT_PULLUP);
  pinMode(pinBotB, INPUT_PULLUP);
  pinMode(pinBotC, INPUT_PULLUP);
  pinMode(pinBotD, INPUT_PULLUP);
  pinMode(pinBotE, INPUT_PULLUP);
  pinMode(bot, INPUT_PULLUP);
}

void loop() {
  // Lê os estados dos botões
  int buttonStateB = digitalRead(pinBotA);
  int buttonStateC = digitalRead(pinBotB);
  int buttonStateD = digitalRead(pinBotC);
  int buttonStateE = digitalRead(pinBotD);

  // Verifica o botão B (W)
  if (buttonStateB != previousButtonStateB) {
    if (buttonStateB == LOW) {
      Keyboard.press('w');
      Serial.println("Button B pressed, 'w' sent");
    } else {
      Keyboard.release('w');
      Serial.println("Button B released, 'w' stopped");
    }
    previousButtonStateB = buttonStateB;
  }

  // Verifica o botão C (D)
  if (buttonStateC != previousButtonStateC) {
    if (buttonStateC == LOW) {
      Keyboard.press('d');
      Serial.println("Button C pressed, 'd' sent");
    } else {
      Keyboard.release('d');
      Serial.println("Button C released, 'd' stopped");
    }
    previousButtonStateC = buttonStateC;
  }

  // Verifica o botão D (S)
  if (buttonStateD != previousButtonStateD) {
    if (buttonStateD == LOW) {
      Keyboard.press('s');
      Serial.println("Button D pressed, 's' sent");
    } else {
      Keyboard.release('s');
      Serial.println("Button D released, 's' stopped");
    }
    previousButtonStateD = buttonStateD;
  }

  // Verifica o botão E (A)
  if (buttonStateE != previousButtonStateE) {
    if (buttonStateE == LOW) {
      Keyboard.press('a');
      Serial.println("Button E pressed, 'a' sent");
    } else {
      Keyboard.release('a');
      Serial.println("Button E released, 'a' stopped");
    }
    previousButtonStateE = buttonStateE;
  }

  // Verifica o estado do botão 'bot' para ativar o joystick
  if (digitalRead(bot) == LOW) {
    // Lê os valores dos eixos X e Y do joystick
    anguloX = map(analogRead(pinX), 0, 1023, -127, 127);
    anguloY = map(analogRead(pinY), 0, 1023, -127, 127);

    // Controle das setas do teclado baseado nos valores dos eixos
    if (anguloX > 20) {  // Mover para a direita
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.release(KEY_LEFT_ARROW);
    } else if (anguloX < -20) {  // Mover para a esquerda
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.release(KEY_RIGHT_ARROW);
    } else {
      Keyboard.release(KEY_RIGHT_ARROW);
      Keyboard.release(KEY_LEFT_ARROW);
    }

    if (anguloY > 20) {  // Mover para baixo
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.release(KEY_UP_ARROW);
    } else if (anguloY < -20) {  // Mover para cima
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.release(KEY_DOWN_ARROW);
    } else {
      Keyboard.release(KEY_DOWN_ARROW);
      Keyboard.release(KEY_UP_ARROW);
    }
  }

  delay(100);  // Pequeno atraso para evitar muitas leituras seguidas
}
