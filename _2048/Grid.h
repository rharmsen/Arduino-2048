#include <Arduino.h>
#include <TrueRandom.h>

#define GridSize 4

#define LoopOverTiles; for (char x = 0; x < GridSize; x++) { for (char y = 0; y < GridSize; y++) {
#define LoopEnd; } }


// Display Settings
//Pin connected to latch pin (ST_CP) of 74HC595 //ARDUINO = 8
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595 //ARDUINO = 11
const int clockPin = 13;
////Pin connected to Data in (DS) of 74HC595 //ARDUINO = 12
const int dataPin = 12;



// Conversion for the segments of the displays
const byte convert[8] = {
  //ABCDEFG.
  0b00010000, //D G
  0b00001000, //E C
  0b00000100, //F .
  0b10000000, //A B
  0b01000000, //B Aa
  0b00000001, //. F
  0b00100000, //C Ea
  0b00000010  //G D
};

// number to segments
const byte numbers[17] = {
  0b11111100, // 0
  0b01100000, // 1
  0b11011010, // 2
  0b11110010, // 3
  0b01100110, // 4
  0b10110110, // 5
  0b10111110, // 6
  0b11100000, // 7
  0b11111110, // 8
  0b11100110, // 9
  0b11101110, // A
  0b00111110, // B
  0b10011100, // C
  0b01111010, // D
  0b10011110, // E
  0b10001110, // F
  0b00000000  // Blank
};

const int mappingArray[16] = { 12,8,13,9,14,10,15,11,7,3,6,2,5,1,4,0};


    const byte A = 0b10000000;
    const byte B = 0b01000000;
    const byte C = 0b00100000;
    const byte D = 0b00010000;
    const byte E = 0b00001000;
    const byte F = 0b00000100;
    const byte G = 0b00000010;
    const byte H = 0b00000001;


class Grid {
public:

  Tile cells[GridSize][GridSize];

  Grid() {

    // Board Settings
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    empty();
  }

  void empty() {
    LoopOverTiles;
    Tile tile(x,y);
    cells[x][y] = tile;
    LoopEnd;



  }

  /** Return the position of a random available cell */
  Position randomAvailableCell() {
    int emptyTile = TrueRandom.random(availableCells());
    Position result;
    LoopOverTiles;
    if (cells[x][y].isEmpty()) {
      if (emptyTile == 0) {
        result.x = x;
        result.y = y;
      }
      emptyTile--;
    }
    LoopEnd;
    return result;
  }

  int availableCells() {
    int count = 0;
    LoopOverTiles;
    if (cells[x][y].isEmpty()) {
      count++;
    }
    LoopEnd;

    return count;
  }

  void prepareTiles() {
    LoopOverTiles;
    cells[x][y].resetMerged();
    cells[x][y].x = x;
    cells[x][y].y = y;
    cells[x][y].savePosition();
    LoopEnd;
  }

  bool isEmptyCell(int x, int y) {
    return (cells[x][y].value == 0);
  }

  bool isEmptyCell(Position pos) {
    return isEmptyCell(pos.x,pos.y);
  }

  void moveTile(Tile tile, Position pos) {
    Tile newtile(tile.x,tile.y);

    cells[tile.x][tile.y] = newtile;
    tile.fromPosition(pos);
    cells[pos.x][pos.y] = tile;
  }

  bool setValue(Position pos, int value) {
    cells[pos.x][pos.y].value = value;
  }

  bool setValue(Tile tile) {
    cells[tile.x][tile.y] = tile;
  }


  bool insertTile(Tile tile) {
    setValue(tile);
  }

  bool removeTile(Tile tile) {
    cells[tile.x][tile.y].value = 0;
  }

  Tile getTile(Position pos) {
    if (withinBounds(pos)) {
      return cells[pos.x][pos.y];
    }
    else {
      return Tile(-1,-1);
    }
  }

  Tile getTile(int x, int y) {
    Position pos(x,y);
    return getTile(pos);
  }

  /** Return if there are available cells */
  bool cellsAvailable() {
    return (availableCells() > 0);
  }

  void print() {
    for (char y = 0; y < GridSize; y++) {
      for (char x = 0; x < GridSize; x++) {
        if (cells[x][y].value != 0) {
          Serial.print(cells[x][y].value);
        }
        else {
          Serial.print(" ");
        }
        Serial.print("\t");
      }
      Serial.println("");
    }
    Serial.println("");
  }

  int* getNumbers() {
    int result[16] ={
      1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16    };

    return result;
  }

  bool withinBounds(Position pos) {
    return (pos.x >=0 && pos.y >=0 && pos.x < GridSize && pos.y < GridSize);
  }

  bool cellAvailable(Position pos) {
    return (cells[pos.x][pos.y].value==0);
  }


  byte convNumb (byte input, boolean prevzero) {

    if (input==0 && prevzero) {
      return numbers[16];
    }
    else{
      return numbers[input];
    }
  }
  
  void create2048() {
    int ar[16][4];
    
    // Empty
    for (int i = 0; i < 16; i++) {
      ar[i][0] = 0; 
      ar[i][1] = 0; 
      ar[i][2] = 0; 
      ar[i][3] = 0; 
    }
    
    // Horizontal Lines
    byte hor_bottom = G | D | E | C;
    byte hor_top = A | G | B | F;
    byte hor_top_middle = D;
    byte hor_top_bottom = A;
    for (int i= 0; i < 4; i++) {
      ar[0][i] = hor_top; // Top of 2
      ar[1][i] = hor_top; // Top of 0
      ar[3][i] = hor_top; // Top of 8
      
      ar[4][i] = hor_top_middle; // Middle of 2
      ar[6][i] = hor_top_middle; // Middle of 4
      ar[7][i] = hor_top_middle; // Middle of 8 
      
      ar[8][i] = hor_top_bottom; // Middle of 2
      ar[10][i] = hor_top_bottom; // Middle of 4
      ar[11][i] = hor_top_bottom; // Middle of 8
      
      ar[12][i] = hor_bottom; // Bottom of 2
      ar[13][i] = hor_bottom; // Bottom of 0
      ar[15][i] = hor_bottom; // Bottom of 8      
    }
    
    byte verticalLeft = 0b11111110; // B | C | F | E;
    byte verticalRight = 0b11111110; // B | C | F | E;
    
    // 2 vertical
    ar[0][0] |= verticalRight;
    ar[4][0] |= verticalRight;
    ar[8][3] |= verticalLeft;
    ar[12][3] |= verticalLeft;
    
    // 0-top vertical
    ar[1][0] |= verticalRight;
    ar[1][3] |= verticalLeft;
    ar[5][0] |= verticalRight;
    ar[5][3] |= verticalLeft;
    // 0-bottom vertical
    ar[9][0] |= verticalRight;
    ar[9][3] |= verticalLeft;
    ar[13][0] |= verticalRight;
    ar[13][3] |= verticalLeft;
    
    // 4-top vertical
    ar[2][0] |= verticalRight;
    ar[2][3] |= verticalLeft;
    ar[6][0] |= verticalRight;
    ar[6][3] |= verticalLeft;
    
    // 4-bottom vertical
    ar[10][0] |= verticalRight;
    ar[14][0] |= verticalRight;
    
    
    
    // 8-top vertical
    ar[3][0] |= verticalRight;
    ar[3][3] |= verticalLeft;
    ar[7][0] |= verticalRight;
    ar[7][3] |= verticalLeft;
    // 8-bottom vertical
    ar[11][0] |= verticalRight;
    ar[11][3] |= verticalLeft;
    ar[15][0] |= verticalRight;
    ar[15][3] |= verticalLeft;
    
    
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
         invidValues[i][j] = ar[mappingArray[i]][j];
      }
    }
  }
  
  void createLeftArrow() {
     int temp,num;
    int values[16] = {1234,5678,9012,3456,1234,5678,9012,3456,1234,5678,9012,3456,1234,5678,9012,3456};
    boolean prevzero = true;
    int mapArray[16] = { 12,8,13,9,14,10,15,11,7,3,6,2,5,1,4,0};

    int ar[16][4];
    
    for (int i = 0; i < 16; i++) {
      ar[i][0] = 0; 
      ar[i][1] = 0; 
      ar[i][2] = 0; 
      ar[i][3] = 0; 
    }
    
    const byte A = 0b10000000;
    const byte B = 0b01000000;
    const byte C = 0b00100000;
    const byte D = 0b00010000;
    const byte E = 0b00001000;
    const byte F = 0b00000100;
    const byte G = 0b00000010;
    const byte H = 0b00000001;
    
    // Horizontal Bar
    for (int i = 4; i <= 7; i++) {
      ar[i][0] = D;
      ar[i][1] = D;
      ar[i][2] = D;
      ar[i][3] = D;
    }
    
    for (int i = 8; i <= 11; i++) {
      ar[i][0] = A;
      ar[i][1] = A;
      ar[i][2] = A;
      ar[i][3] = A;
    }

    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
         invidValues[i][j] = ar[mapArray[i]][j];
      }
    }
  }
  
  /**
   * Calculate the values for each digit of the screen (so 4 digit's per display).
   * Only calculate after an update to the grid, not every display iteration of the screen, this would be useless overcalcution.
   */

  byte invidValues[16][4];

  void calculateInvidValues() {
    int temp,num;

    boolean prevzero = true;
    int values[16];

    Tile tile;
    int  count = 0;
    for (char y = 0; y < GridSize; y++) {
      for (char x = 0; x < GridSize; x++) {
        values[count++] = cells[x][y].value;
      }
    }
    
    // This is the correct order of the "Display" Tiles
    // This is the order of the display tiles: (input is at tile #1 and data is shifted until tile 16).
    /*  1  3  5  7
     *  2  4  6  8
     * 15 13 11  9
     * 16 14 12 10
     */
    int mapArray[16] = { 12,8,13,9,14,10,15,11,7,3,6,2,5,1,4,0};


    for (int i = 0; i < 16; i++) {
      temp = values[mapArray[i]];
      prevzero = true;
      num = convNumb (temp/1000,prevzero);
      invidValues[i][3] = num;
      prevzero = prevzero && (num==numbers[16]);

      num = convNumb ((temp % 1000)/100,prevzero);
      invidValues[i][2] = num;
      prevzero = prevzero && (num==numbers[16]);

      num = convNumb ((temp % 100)/10,prevzero);
      invidValues[i][1] = num;
      prevzero = prevzero && (num==numbers[16]);

      num = convNumb ((temp % 10),prevzero);
      invidValues[i][0] = num;
    }

  }

  /**
   * Function to write a data bit on the data bus
   * Not using the arduino "digitalWrite" because this uses to much overhead and causes a flickering on the displays.
   */
  void writeBit(int signal) {

    PORTB &= ~_BV(5); // Clockpin Low
    if (signal) {
      // turn “On”
      PORTB &= ~_BV(4); // Datapin low
      //Serial.print(0);
    }
    else {
      // turn “Off”
      PORTB |= _BV(4); // Datapin High
      // Serial.print(1);
    }
    PORTB |= _BV(5); // Clockpin High
  }

  /**
   * The actual funcion that displays the board on the segment displays.
   *
   */
  void displayBoard() {

    byte value,converted;
    int count = 0;
    int enable[8];

    //Serial.println("DisplayBoard -------------------------------");
    for (int j = 0; j < 4; j++) {
      digitalWrite(latchPin, LOW);
      //Serial.print("1 cell: ");
      for (int i = 0; i < 16; i++) {
        value = invidValues[i][j];

        count++;

        // Enable individual leds
        for (int k=0; k <=7 ; k++)
        {
          writeBit(value & convert[k]);
        }

        // Enable/Disable Digits
        if (count==2) {

          for (int x = 0; x < 8; x++) {

            if ((x==j || x == (j+4))) {
              writeBit(1);
            }
            else {
              writeBit(0);
            }

          }
          count = 0;
        }
      }
      digitalWrite(latchPin, HIGH);
    }


  }



};














