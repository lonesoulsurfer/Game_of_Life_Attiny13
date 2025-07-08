/*

  @file ATtiny13A_Game_of_Life_16x16.ino

  Memo:
  Arduino IDE 1.8.2 + https://mcudude.github.io/MicroCore/package_MCUdude_MicroCore_index.json

  @brief Game of Life
  References:
  https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

  @author Kei Takagi
  @date 2017.5.5

  Copyright (c) 2017 Kei Takagi
  Released under the MIT license
  http://opensource.org/licenses/mit-license.php

*/

#define Max7219PinCLK  PB2
#define Max7219PinCS   PB1
#define Max7219PinDIN  PB0

#define HIGHT  16
#define WIDTH  16
#define Max7219_HIGHT   8
#define Max7219_WIDTH   8

#define GEBERATIONS 1000
#define SPEED       100
#define STARTY      1

byte Generations = 21;
word cellCount = 0;

word DotArea[HIGHT + 2] = {
  // Hertz oscillator
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0010000000000000,
  0b1010000000000000,
  0b0110000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000
};

void setup() {
  // Setup MAX7219
  DDRB = 1 << Max7219PinCLK | 1 << Max7219PinCS | 1 << Max7219PinDIN;
  Write_Max7219(0x09, 0x00, 0x00, 0x00, 0x00); // using an led matrix (not digits)
  Write_Max7219(0x0A, 0x07, 0x07, 0x07, 0x07); // Brightness 0x00-0x0F 0x01=dark .... 0x0F=bright
  Write_Max7219(0x0B, 0x07, 0x07, 0x07, 0x07); // Scan limit = 7
  Write_Max7219(0x0C, 0x01, 0x01, 0x01, 0x01); // Normal operation mode
  Write_Max7219(0x0F, 0x00, 0x00, 0x00, 0x00); // Disable display test
}

void loop() {
  byte i, j, c, d, ans;
  word calcArea[3];

  if (Generations == 0) {
    DotArea[0] = 0x0000;
    DotArea[HIGHT + 1] = 0x0000;

    for (i = 0; i < HIGHT; i++) {
      DotArea[i + 1] = 0x0000;
      for (j = 0; j < WIDTH; j++) {
        if (analogRead(PB3) % 2 == 0)DotArea[i + 1] |= (0x0001 << j);
      }
    }
    Generations = GEBERATIONS;
  }
  Generations--;

  for (i = 0; i < Max7219_HIGHT; i++) {
    //Display
    Write_Max7219(i + 1,
                  DotArea[i + STARTY] >> 8 ,

                  DotArea[i + STARTY],
                  DotArea[i + Max7219_HIGHT + STARTY] >> 8 ,
                  DotArea[i + Max7219_HIGHT + STARTY]);
  }
  delay(SPEED);

  DotArea[HIGHT + 1] = DotArea[1];
  DotArea[0]  = DotArea[HIGHT];

  calcArea[0] = DotArea[0];
  calcArea[1] = DotArea[1];
  calcArea[2] = DotArea[2];

  //GAME OF LIFE
  cellCount = 0;
  for (i = 1; i < (HIGHT + 1); i++) {
    DotArea[i] = 0x0000;
    for (j = 0; j < WIDTH; j++) {
      c = j - 1 < 0 ? WIDTH - 1 : j - 1;
      d = j + 1 >= WIDTH ? 0 : j + 1;
      ans = ((calcArea[0] >> c) & 0x0001)
            + ((calcArea[0] >> j) & 0x0001)
            + ((calcArea[0] >> d) & 0x0001)
            + ((calcArea[1] >> c) & 0x0001)
            + ((calcArea[1] >> d) & 0x0001)
            + ((calcArea[2] >> c) & 0x0001)
            + ((calcArea[2] >> j) & 0x0001)
            + ((calcArea[2] >> d) & 0x0001);
      if ( (calcArea[1] >> j) & 0x0001) {
        if (ans == 2) {
          DotArea[i] |= 0x0001 << j;
          cellCount++;
        }
      }
      if (ans == 3) {
        DotArea[i] |= 0x0001 << j;
        cellCount++;
      }
    }
    calcArea[0] = calcArea[1];
    calcArea[1] = calcArea[2];
    calcArea[2] = DotArea[i + 2];
  }
  if (cellCount < 5 & Generations > 5)Generations = 5;
}

void Write_Max7219(byte address, short in_01, short in_02 , short in_03, short in_04)
{
  PORTB = 0x00;
  shiftOut( Max7219PinDIN, Max7219PinCLK, MSBFIRST, address );
  shiftOut( Max7219PinDIN, Max7219PinCLK, MSBFIRST, in_01 );
  shiftOut( Max7219PinDIN, Max7219PinCLK, MSBFIRST, address );
  shiftOut( Max7219PinDIN, Max7219PinCLK, MSBFIRST, in_02 );
  shiftOut( Max7219PinDIN, Max7219PinCLK, MSBFIRST, address );
  shiftOut( Max7219PinDIN, Max7219PinCLK, MSBFIRST, in_03 );
  shiftOut( Max7219PinDIN, Max7219PinCLK, MSBFIRST, address );
  shiftOut( Max7219PinDIN, Max7219PinCLK, MSBFIRST, in_04 );
  PORTB =  1 << Max7219PinCS;
}
