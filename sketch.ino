#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración de pines
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configuración del joystick
const int joyYPin = 35;  // Pin analógico del joystick para el eje Y

int textPosition = 0;  // Posición actual del texto
const int textHeight = 8;  // Altura de una línea de texto (ajustada a 8)
const int screenLines = SCREEN_HEIGHT / textHeight;  // Número de líneas visibles en la pantalla

// Texto largo para mostrar
const char* longText[] = {
  "Esta es la primera linea de texto.",
  "Esta es la segunda linea de texto.",
  "Esta es la tercera linea de texto.",
  "Esta es la cuarta linea de texto.",
  "Esta es la quinta linea de texto.",
  "Esta es la sexta linea de texto.",
  "Esta es la septima linea de texto.",
  "Esta es la octava linea de texto.",
  "Esta es la novena linea de texto.",
  "Esta es la decima linea de texto.",
  "Esta es la undecima linea de texto.",
  "Esta es la duodecima linea de texto."
};
const int totalLines = sizeof(longText) / sizeof(longText[0]);

void setup() {
  Serial.begin(115200);
  
  // Inicializar el display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  // Configuración inicial
  display.display();
}

void loop() {
  // Leer valor del joystick
  int joyYValue = analogRead(joyYPin);
  int threshold = 500; // Umbral para detección de movimiento
  
  // Desplazar texto en función del valor del joystick
  if (joyYValue < 1024 - threshold && textPosition < totalLines - screenLines) {
    textPosition++;
    delay(200); // Retraso para evitar movimientos demasiado rápidos
  }
  if (joyYValue > threshold && textPosition > 0) {
    textPosition--;
    delay(200); // Retraso para evitar movimientos demasiado rápidos
  }

  // Limpiar pantalla y mostrar texto
  display.clearDisplay();

  for (int i = 0; i < screenLines; i++) {
    if (textPosition + i < totalLines) {
      display.setCursor(0, i * textHeight);
      display.print(longText[textPosition + i]);
    }
  }

  display.display();
}
