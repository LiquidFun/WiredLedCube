/*
GPIO Pins:
10, 11, 12 vertical (10 bottom, 12 top)
0 to 8 horizontal

Horizontal pattern:

0 1 2
5 4 3
6 7 8

As viewed from the top. 6 7 8 is the side closer to the USB port

*/

int L = LOW;
int H = HIGH;

// the setup function runs once when you press reset or power the board
void setup() {
  for (int i = 0; i <= 12; i++) {
    pinMode(i, OUTPUT);
  }
}

void layers(int bottom=L, int middle=L, int top=L) {
  digitalWrite(10, bottom);
  digitalWrite(11, middle);
  digitalWrite(12, top);
}

void cols(int c0=H, int c1=H, int c2=H, int c3=H, int c4=H, int c5=H, int c6=H, int c7=H, int c8=H) {
  digitalWrite(0, c0);
  digitalWrite(1, c1);
  digitalWrite(2, c2);
  digitalWrite(3, c3);
  digitalWrite(4, c4);
  digitalWrite(5, c5);
  digitalWrite(6, c6);
  digitalWrite(7, c7);
  digitalWrite(8, c8);
}

//                            0  1  2  3  4  5  6  7  8
int roundHorizontalCycle[] = {1, 2, 3, 8, 4, 0, 5, 6, 7};

int cycleRoundHorizontal(int c) {
  return roundHorizontalCycle[c];
}

void patternCycle() {
  layers(H, H, H);
  int curr = 0;
  int curr2 = 8;
  int del = 30;
  do {
    layers(curr%2==0?H:L, curr2%3==0?H:L, curr%2==0?L:H);
    cols();
    digitalWrite(curr, L);
    digitalWrite(curr2, L);
    curr = cycleRoundHorizontal(curr);
    curr2 = cycleRoundHorizontal(curr2);
    delay(79);
  } while(curr != 0);
  
}

// the loop function runs over and over again forever
void loop() {
  patternCycle();
}
