#include <Keyboard.h>

int column_1 = 27;
int column_2 = 26;
int column_3 = 22;
int columns[3] = {column_1, column_2, column_3};

int row_1 = 21;
int row_2 = 20;
int row_3 = 19;
int row_4 = 18;
int rows[4] = {row_1, row_2, row_3, row_4};

bool inputs[12];
bool pressed[12];

/*
  #Numpad index#
  +----+---+---+
  |  9 | 8 | 1 |
  +----+---+---+
  | 10 | 7 | 2 |
  +----+---+---+
  | 11 | 6 | 3 |
  +----+---+---+
  | 12 | 5 | 4 |
  +----+---+---+
*/
uint8_t keymap[12] = {
  KEY_KP_7,
  KEY_KP_8,
  KEY_KP_9,
  KEY_NUM_LOCK,
  KEY_KP_0,
  KEY_KP_6,
  KEY_KP_5,
  KEY_KP_4,
  KEY_KP_1,
  KEY_KP_2,
  KEY_KP_3,
  KEY_KP_DOT
};


void setup() {
  // Serial.begin(9600);

  setup_columns();
  setup_rows();
}

void loop() {
  reset_inputs();
  read_inputs();
  handle_keypress();
  // print_inputs();

  delay(10);
}



void setup_columns() {
  for (int i = 0; i < 3; i++) {
    pinMode(columns[i], OUTPUT);
    change_column(0);
  }
}

void setup_rows() {
  for (int i = 0; i < 4; i++) {
    pinMode(rows[i], INPUT_PULLDOWN);
  }
}

void reset_inputs() {
  for (int i = 0; i < 12; i++) {
    inputs[i] = false;
  }
}

void read_inputs() {
  for (int c = 0; c < 3; c++) {
    change_column(c);
  for (int r = 0; r < 4; r++) {
      inputs[(c * 4) + r] = digitalRead(rows[r]);
    }
  }
}

void change_column(int column_num) {
  for (int i = 0; i < 3; i++) {
    if (i == column_num) {
      digitalWrite(columns[i], HIGH);
    } else {
      digitalWrite(columns[i], LOW);
    }
  }
}

void handle_keypress() {
  for (int i = 0; i < 12; i++) {
    if (inputs[i] && keymap[i] != 0) {
      Keyboard.press(keymap[i]);
      pressed[i] = true;
    } else if (pressed[i]) {
      Keyboard.release(keymap[i]);
      pressed[i] = false;
    }
  }
}

void print_inputs() {
  String result = "[ ";
  for(int i = 0; i < 12; i++) {
    result += String(inputs[i]);
    if (i != 11) {
      result += ", ";
    }
  }
  result += " ]";
  Serial.println(result);
}
