#define WHITE_LED 3
#define RED_LED 5
#define BUTTON 10
#define ARRAY_LEN(x)  (sizeof(x) / sizeof((x)[0]))

int whiteState[] = { LOW, HIGH, LOW, HIGH };
int redState[] = { LOW, LOW, HIGH, HIGH };

int i = 0;

void setup() {
  pinMode(WHITE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    i = (i + 1) % ARRAY_LEN(whiteState);
    digitalWrite(WHITE_LED, whiteState[i]);
    digitalWrite(RED_LED, redState[i]);
  }
}