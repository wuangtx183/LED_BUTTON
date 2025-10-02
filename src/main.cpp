#include <Arduino.h>
#include <OneButton.h>

// GPIO cho LED ngoài và nút nhấn
#define LED2  26      // LED ngoài (bạn có thể đổi sang GPIO khác)
#define BUTTON  25    // Nút nhấn ngoài

// LED tích hợp sẵn trên board (thường là GPIO 2 hoặc GPIO 13 tùy devkit)
#define LED1  13     

OneButton button(BUTTON, true);

// Biến điều khiển
int currentLED = LED1;    // Mặc định điều khiển LED1
bool ledState = false;
bool isBlinking = false;
unsigned long lastBlink = 0;

void toggleLED() {
  if (isBlinking) return;  // Nếu đang nhấp nháy thì bỏ qua
  ledState = !ledState;
  digitalWrite(currentLED, ledState);
  Serial.printf("Single click -> Toggle LED%d: %s\n",
                (currentLED == LED1 ? 1 : 2), ledState ? "ON" : "OFF");
}

void switchLED() {
  if (isBlinking) return;
  currentLED = (currentLED == LED1) ? LED2 : LED1;
  Serial.printf("Double click -> Switched to LED%d\n",
                (currentLED == LED1 ? 1 : 2));
}

void startBlink() {
  isBlinking = true;
  Serial.printf("Hold -> Blinking LED%d\n",
                (currentLED == LED1 ? 1 : 2));
}

void stopBlink() {
  isBlinking = false;
  digitalWrite(currentLED, LOW);
  ledState = false;
  Serial.printf("Release -> Stop blinking LED%d\n",
                (currentLED == LED1 ? 1 : 2));
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Gán sự kiện cho nút nhấn
  button.attachClick(toggleLED);
  button.attachDoubleClick(switchLED);
  button.attachLongPressStart(startBlink);
  button.attachLongPressStop(stopBlink);

  Serial.println("=== LED Control with OneButton ===");
}

void loop() {
  button.tick();

  // Nếu đang nhấp nháy
  if (isBlinking) {
    unsigned long now = millis();
    if (now - lastBlink >= 200) {
      lastBlink = now;
      ledState = !ledState;
      digitalWrite(currentLED, ledState);
    }
  }
}
