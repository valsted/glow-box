#define PIN_COUNT 10

int pins[] = { 5, 6, 7, 8, 10, 11, A0, A1, A2, A3 };

void setup() {
    for (int i = 0; i < PIN_COUNT; i++)
    {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH); // OFF
    }
}

void loop() {
    for (int i = 0; i < PIN_COUNT; i++)
    {
        digitalWrite(pins[i], LOW); // ON
        delay(500);
    }
    for (int i = PIN_COUNT - 1; i >= 0; i--)
    {
        digitalWrite(pins[i], HIGH); // OFF
        delay(500);
    }
}