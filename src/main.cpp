#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128
#define HEIGHT 64

#define ROWS 8
#define COLUMNS 8
#define BLOCK 8

#define PLAYER_SQUARE 2

void draw_map();

struct player_t {
  int x;
  int y;
};

const int left_button = 4;
const int up_button = 18;
const int down_button = 19;
const int right_button = 23;

int velocity = 2;

int world_map[ROWS][COLUMNS] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    for(;;);
  }

  pinMode(left_button, INPUT_PULLUP);
  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
}

void loop() {
  display.clearDisplay();

  static player_t player = {8, 8};

  if (digitalRead(left_button) == LOW) player.x -= velocity;
  if (digitalRead(up_button) == LOW) player.y -= velocity;
  if (digitalRead(down_button) == LOW) player.y += velocity;
  if (digitalRead(right_button) == LOW) player.x += velocity;

  draw_map();

  display.fillRect(player.x, player.y, PLAYER_SQUARE, PLAYER_SQUARE, WHITE);

  display.display();

  delay(10);
}

void draw_map() {
  for (int row = 0; row < ROWS; row++){
    for (int column = 0; column < COLUMNS; column++) {

      int map_x = column * BLOCK;
      int map_y = row * BLOCK;

      switch (world_map[row][column]) {
        case 0:
          break;
        
        case 1:
          display.fillRect(map_x, map_y, BLOCK, BLOCK, WHITE);
          break;
      }
    }
  }
}
