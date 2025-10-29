#include <TM1637Display.h>

// --- DISPLAY DE LED ---
#define CLK 8
#define DIO 11
// ------

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#define CHOICE_OFF      0
#define CHOICE_NONE     0
#define CHOICE_RED      (1 << 0)
#define CHOICE_GREEN    (1 << 1)
#define CHOICE_BLUE     (1 << 2)
#define CHOICE_YELLOW   (1 << 3)

#define LED_RED     10
#define LED_GREEN   3
#define LED_BLUE    13
#define LED_YELLOW  5

#define BUTTON_RED    9
#define BUTTON_GREEN  2
#define BUTTON_BLUE   12
#define BUTTON_YELLOW 6

#define BUZZER1   4
#define BUZZER2   7

#define ROUNDS_TO_WIN      13
#define ENTRY_TIME_LIMIT   3000

#define MODE_MEMORY 0
#define MODE_BATTLE 1
#define MODE_BEEGEES 2

byte gameMode = MODE_MEMORY;
byte gameBoard[32];
byte gameRound = 0;

TM1637Display display(CLK, DIO);

const uint8_t SEG_GOOD_ARRAY[] = {
  SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // G
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // O
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // O
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G          // D
};

const uint8_t SEG_BYE_ARRAY[] = {
  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // B
  SEG_B | SEG_C | SEG_D | SEG_F | SEG_G, // y
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G  // E
};

const uint8_t SEG_HI_ARRAY[] = {
  0x00,                                  // espaço (1º dígito apagado)
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // H (2º dígito)
  SEG_E | SEG_F,                         // i (3º dígito)
  0x00                                   // espaço (4º dígito apagado)
};

int melody[] = {
  NOTE_G4, NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_G4, 0, 0, 0,
  NOTE_E4, 0, NOTE_D4, NOTE_E4, NOTE_G4, 0,
  NOTE_D4, NOTE_E4, 0, NOTE_G4, 0, 0,
  NOTE_D4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_A4, 0, NOTE_C5, 0
};

int noteDuration = 115;
int LEDnumber = 0;

void setup()
{
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  
  display.setBrightness(4); 
  display.clear();
  display.showNumberDec(gameRound);

  gameMode = MODE_MEMORY;

  // Os checks para o modo Bee Gees e Battle agora estão no loop principal
  // para serem verificados APÓS o modo de atração.
  // Estes foram removidos do setup.
  
  // play_winner() também é removido daqui, pois deve vir depois do "HI" e da seleção de modo.
}

void loop()
{
  attractMode(); // O loop irá chamar o attractMode até um botão ser pressionado

  // **** AQUI é onde a magia acontece: o jogador pressionou um botão e saiu do attractMode ****
  display.setSegments(SEG_HI_ARRAY); // Mostra "HI"
  delay(1500); // Exibe "HI" por 1.5 segundos
  display.clear(); // Limpa o display
  // Certifique-se de que o botão foi liberado para evitar que o próximo checkButton o detecte novamente
  while(checkButton() != CHOICE_NONE); 
  delay(50); // Pequeno atraso para estabilizar

  // Agora, após "HI", verificamos se o jogador quer iniciar o modo Bee Gees ou Battle
  byte initialChoice = checkButton(); // Pega o último botão pressionado para sair do attractMode

  if (initialChoice == CHOICE_YELLOW) {
      play_beegees();
  } else if (initialChoice == CHOICE_GREEN) {
      gameMode = MODE_BATTLE; 
      setLEDs(CHOICE_GREEN);
      toner(CHOICE_GREEN, 150);
      setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW);
      // O jogador deve liberar o botão para o battle mode iniciar limpo
      while(checkButton() != CHOICE_NONE);
  } else {
      // Se nenhum modo especial foi selecionado, assume MODE_MEMORY (já é o default)
      // ou se o botão para sair do attractMode não era Verde ou Amarelo
      gameMode = MODE_MEMORY;
  }

  // Agora que o modo foi definido e "HI" foi mostrado, podemos chamar play_winner
  // ou a sequência de início do jogo.
  play_winner(); // Toca a melodia de "vitória" como som de início do jogo

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);
  delay(1000);
  setLEDs(CHOICE_OFF);
  delay(250);

  if (gameMode == MODE_MEMORY)
  {
    if (play_memory() == true)
      play_winner_sequence();
    else
      play_loser_sequence();
  }

  if (gameMode == MODE_BATTLE)
  {
    play_battle();
    play_loser_sequence();
  }
}

boolean play_memory(void)
{
  randomSeed(millis());
  gameRound = 0;
  display.showNumberDec(gameRound);

  while (gameRound < ROUNDS_TO_WIN)
  {
    add_to_moves();
    playMoves();

    for (byte currentMove = 0; currentMove <= gameRound; currentMove++)
    {
      byte choice = wait_for_button();
      if (choice == 0) return false;
      if (choice != gameBoard[currentMove]) return false;
    }

    gameRound++; // ✅ agora só aumenta após acerto
    showGoodAndScore();
    delay(1000);
  }

  return true;
}

boolean play_battle(void)
{
  gameRound = 0;
  display.showNumberDec(gameRound);

  while (1)
  {
    byte newButton = wait_for_button();
    gameBoard[gameRound++] = newButton;
    display.showNumberDec(gameRound);

    for (byte currentMove = 0; currentMove < gameRound; currentMove++)
    {
      byte choice = wait_for_button();
      if (choice == 0) return false;
      if (choice != gameBoard[currentMove]) return false;
    }

    showGoodAndScore();
    delay(100);
  }

  return true;
}

void playMoves(void)
{
  for (byte currentMove = 0; currentMove <= gameRound; currentMove++)
  {
    toner(gameBoard[currentMove], 150);
    delay(150);
  }
}

void add_to_moves(void)
{
  byte newButton = random(0, 4);
  if (newButton == 0) newButton = CHOICE_RED;
  else if (newButton == 1) newButton = CHOICE_GREEN;
  else if (newButton == 2) newButton = CHOICE_BLUE;
  else if (newButton == 3) newButton = CHOICE_YELLOW;

  gameBoard[gameRound] = newButton; // ✅ não incrementa aqui
}

void setLEDs(byte leds)
{
  digitalWrite(LED_RED, (leds & CHOICE_RED) ? HIGH : LOW);
  digitalWrite(LED_GREEN, (leds & CHOICE_GREEN) ? HIGH : LOW);
  digitalWrite(LED_BLUE, (leds & CHOICE_BLUE) ? HIGH : LOW);
  digitalWrite(LED_YELLOW, (leds & CHOICE_YELLOW) ? HIGH : LOW);
}

byte wait_for_button(void)
{
  long startTime = millis();
  while ((millis() - startTime) < ENTRY_TIME_LIMIT)
  {
    byte button = checkButton();
    if (button != CHOICE_NONE)
    {
      toner(button, 150);
      while (checkButton() != CHOICE_NONE);
      delay(10);
      return button;
    }
  }
  return CHOICE_NONE;
}

byte checkButton(void)
{
  if (digitalRead(BUTTON_RED) == 0) return CHOICE_RED;
  else if (digitalRead(BUTTON_GREEN) == 0) return CHOICE_GREEN;
  else if (digitalRead(BUTTON_BLUE) == 0) return CHOICE_BLUE;
  else if (digitalRead(BUTTON_YELLOW) == 0) return CHOICE_YELLOW;
  return CHOICE_NONE;
}

void toner(byte which, int buzz_length_ms)
{
  setLEDs(which);
  switch(which)
  {
    case CHOICE_RED:    buzz_sound(buzz_length_ms, 1136); break;
    case CHOICE_GREEN:  buzz_sound(buzz_length_ms, 568); break;
    case CHOICE_BLUE:   buzz_sound(buzz_length_ms, 851); break;
    case CHOICE_YELLOW: buzz_sound(buzz_length_ms, 638); break;
  }
  setLEDs(CHOICE_OFF);
}

void buzz_sound(int buzz_length_ms, int buzz_delay_us)
{
  long buzz_length_us = buzz_length_ms * (long)1000;
  while (buzz_length_us > (buzz_delay_us * 2))
  {
    buzz_length_us -= buzz_delay_us * 2;
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}

void play_winner(void)
{
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
}

void winner_sound(void)
{
  for (byte x = 250; x > 70; x--)
  {
    for (byte y = 0; y < 3; y++)
    {
      digitalWrite(BUZZER2, HIGH);
      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x);
      digitalWrite(BUZZER2, LOW);
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);
    }
  }
}

void play_loser(void)
{
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
}

void attractMode(void)
{
  display.clear();
  uint8_t segments_for_attract[] = {
    0b00000000,
    SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G
  };
  
  int delayDuration = 25; // ✅ reduzido de 70 → 25 para fluidez
  while(1)
  {
    setLEDs(CHOICE_RED);
    display.setSegments(&segments_for_attract[1], 1, 0);
    delay(delayDuration);
    if (checkButton() != CHOICE_NONE) { display.clear(); return; } // SAÍDA: botão pressionado

    setLEDs(CHOICE_BLUE);
    display.setSegments(&segments_for_attract[2], 1, 1);
    delay(delayDuration);
    if (checkButton() != CHOICE_NONE) { display.clear(); return; } // SAÍDA: botão pressionado

    setLEDs(CHOICE_GREEN);
    display.setSegments(&segments_for_attract[3], 1, 2);
    delay(delayDuration);
    if (checkButton() != CHOICE_NONE) { display.clear(); return; } // SAÍDA: botão pressionado

    setLEDs(CHOICE_YELLOW);
    display.setSegments(&segments_for_attract[4], 1, 3);
    delay(delayDuration);
    if (checkButton() != CHOICE_NONE) { display.clear(); return; } // SAÍDA: botão pressionado
    setLEDs(CHOICE_OFF);

    for (int i = 0; i < 7; i++) {
      uint8_t data[] = {segments_for_attract[i+1], segments_for_attract[(i+2)%7+1], segments_for_attract[(i+3)%7+1], segments_for_attract[(i+4)%7+1]};
      display.setSegments(data);
      delay(delayDuration);
      if (checkButton() != CHOICE_NONE) {
        display.clear();
        return; // SAÍDA: botão pressionado
      }
    }
  }
}

void play_beegees()
{
  setLEDs(CHOICE_YELLOW);
  toner(CHOICE_YELLOW, 150);
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE);
  while(checkButton() != CHOICE_NONE);
  setLEDs(CHOICE_NONE);
  delay(1000);
  digitalWrite(BUZZER1, LOW);

  while(checkButton() == CHOICE_NONE)
  {
    for (int thisNote = 0; thisNote < 32; thisNote++) {
      changeLED();
      tone(BUZZER2, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZER2);
    }
  }
  display.clear();
}

void changeLED(void)
{
  setLEDs(1 << LEDnumber);
  LEDnumber++;
  if(LEDnumber > 3) LEDnumber = 0;
}

void showGoodAndScore() {
  display.clear();
  display.setSegments(SEG_GOOD_ARRAY);
  delay(1000);
  display.showNumberDec(gameRound);
  delay(500);
}

void play_loser_sequence() {
  play_loser();
  for (int i = 0; i < 3; i++) {
    display.showNumberDec(gameRound);
    delay(200);
    display.clear();
    delay(200);
  }
  uint8_t tempBye[] = {SEG_BYE_ARRAY[0], SEG_BYE_ARRAY[1], SEG_BYE_ARRAY[2], 0b00000000};
  display.setSegments(tempBye);
  delay(1500);
  display.clear();
}

void play_winner_sequence() {
  play_winner();
  for (int i = 0; i < 3; i++) {
    display.showNumberDec(gameRound);
    delay(200);
    display.clear();
    delay(200);
  }
  crazyDisplayEffect();
  display.clear();
}

void crazyDisplayEffect() {
  uint8_t fullSegments[] = {0b11111111, 0b11111111, 0b11111111, 0b11111111};
  uint8_t emptySegments[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000};
  for(int k=0; k<5; k++) {
    display.setSegments(fullSegments);
    delay(100);
    display.setSegments(emptySegments);
    delay(100);
  }
  uint8_t segments_list[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G};
  for(int k=0; k<2; k++) {
    for(int i=0; i<7; i++) {
      uint8_t singleSeg = segments_list[i];
      uint8_t data[] = {singleSeg, singleSeg, singleSeg, singleSeg};
      display.setSegments(data);
      delay(70);
    }
  }
  for(int i=0; i<30; i++) {
    uint8_t currentSegments[4];
    for(int j=0; j<4; j++) {
      currentSegments[j] = random(0, 256);
    }
    display.setSegments(currentSegments);
    delay(50);
  }
}