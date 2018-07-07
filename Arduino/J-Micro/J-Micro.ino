#define KEY_H0 6
#define KEY_H1 7
#define KEY_H2 8
#define KEY_H3 9

#define KEY_V0 10
#define KEY_V1 11
#define KEY_V2 12
#define KEY_V3 13

#define JOY_X A2
#define JOY_Y A1
#define JOY_SW A0

//Array Of Pins Giving Supply To Key Matrix
uint8_t KEY_H_OUT[] = {KEY_H0,KEY_H1,KEY_H2,KEY_H3};

//Array Of Pins Reading State Of Key Matrix
uint8_t KEY_V_IN[] = {KEY_V0,KEY_V1,KEY_V2,KEY_V3};

//Array Of Key Map
char KEY_MAP[][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};

bool KEY_PRESSED_NOW = false;
bool KEY_PRESSED_PREV = false;
bool JOY_PRESSED_NOW = false;
bool JOY_PRESSED_PREV = false;
bool JOY_SCR = false;

int16_t MOUSE_X = 0;
int16_t MOUSE_Y = 0;
int16_t MOUSE_WH = 0;

void setup() {
  Serial.begin(9600);

  //Pin Config For KeyPad Matrix
  for (int i = 0; i<4; i++) {
    pinMode(KEY_H_OUT[i], OUTPUT);
    digitalWrite(KEY_H_OUT[i], HIGH);
  }
  for (int i = 0; i<4; i++) {
    pinMode(KEY_V_IN[i], INPUT_PULLUP);
  }

  //Pin Config For JoyStick
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_SW, INPUT_PULLUP);  
}

void loop() {  
  // put your main code here, to run repeatedly:
  for (int i = 0; i<4; i++) {
    for (int j = 0; j<4; j++) {
       digitalWrite(KEY_H_OUT[j], HIGH);
    }
    digitalWrite(KEY_H_OUT[i], LOW);
    for (int j = 0; j<4; j++) {
      if (!digitalRead(KEY_V_IN[j])) {
        KEY_PRESSED_NOW = true;
        if (!KEY_PRESSED_PREV) {
          Serial.println(KEY_MAP[i][j]);
        }
      }
    }
  }
  KEY_PRESSED_PREV = KEY_PRESSED_NOW;
  KEY_PRESSED_NOW = false;

  JOY_PRESSED_NOW = !digitalRead(JOY_SW);
  if (!JOY_PRESSED_PREV) {
    if (JOY_PRESSED_NOW) {
      JOY_SCR = !JOY_SCR;
    }
  }
  JOY_PRESSED_PREV = JOY_PRESSED_NOW;

  if (JOY_SCR) {
    MOUSE_X = 0;
    MOUSE_Y = 0;
    MOUSE_WH = analogRead(JOY_Y)-512;
  }
  else {
    MOUSE_X = analogRead(JOY_X)-512;
    MOUSE_Y = analogRead(JOY_Y)-512;
    MOUSE_WH = 0;    
  }
  if (!(MOUSE_X<10 && MOUSE_X>-10 && MOUSE_Y<10 && MOUSE_Y>-10 && MOUSE_WH<10 && MOUSE_WH>-10)) {
    Serial.print("X : ");
    Serial.print(MOUSE_X);
    Serial.print(", ");
    Serial.print("Y : ");
    Serial.print(MOUSE_Y);
    Serial.print(", ");
    Serial.print("WH : ");
    Serial.println(MOUSE_WH); 
  }
}
