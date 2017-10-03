#define LED 2
#define LED_RED 15
#define LED_GREEN 12
#define LED_BLUE 13
#define BUTTON 4

bool toggle = true;
float fade = 0;

int fade_time = 3000;
int fade_clock = 50;
void setup() {
  Serial.begin(9600); //กำหนด baud rate เสมอ
  pinMode(LED, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  unsigned long elapsed = 0;
  int v = analogRead(A0);
  int btn = digitalRead(BUTTON);
  int current = millis();
  int COLOR = LED_RED;
  Serial.print("A0 = ");
  Serial.print(v * 100 / 1024);
  Serial.println("%");

  Serial.print("BTN = ");
  Serial.println(btn);
  if (btn == 0) {
    if (COLOR == LED_GREEN) {
      COLOR = LED_RED;
    } else {
      COLOR = LED_RED;
    }
  }
  
  // v * 100 / 1023 > 50
  if (current - elapsed > fade_clock) {
    if (toggle) {
      fade += fade_clock / (fade_time / 1023);
      if (fade >= 1023) {
        fade = 1023;
        toggle = false;
      }
    } else {
      fade -= fade_clock / (fade_time / 1023);
      if (fade <= 0) {
        fade = 0;
        toggle = true;
      }
    }
    analogWrite(COLOR, fade);
    elapsed = millis();
  }
}


