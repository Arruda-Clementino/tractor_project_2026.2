// ---------------------------------------------------------------
// Main.cpp - Trator: movimento + sensores + envio de JSON ao ESP32
// Tudo roda sem parar, sem delay no loop().
// ---------------------------------------------------------------
#include <Arduino.h>

#include "../lib/Motion.h"          // movimento (MyRobot_IFPB)
#include "../lib/SensorsDriver.h"   // GPS + DHT22 + BMP280 + RFID
#include "../lib/JsonSerial.h"      // monta o JSON (ArduinoJson v7) e envia pela Serial3 ao ESP32

// Telemetria enviada de forma contínua neste intervalo (mesmo do mega_sender)
static const uint32_t TELEMETRY_INTERVAL_MS = 2000;

// Buzzer: bip curto quando uma tag RFID nova é lida (buzzer ativo no pino 48)
static const uint8_t  TAG_BUZZER_PIN    = 48;
static const uint32_t TAG_BEEP_MS       = 80;

static uint32_t lastTelemetryMs = 0;
static bool     envioImediato   = false;   // true = tag nova lida, força envio imediato do JSON
static bool     beepLigado      = false;
static uint32_t beepInicioMs    = 0;

// Liga o buzzer (não bloqueia)
static void Beep_Start() {
  digitalWrite(TAG_BUZZER_PIN, HIGH);
  beepLigado   = true;
  beepInicioMs = millis();
}

// Desliga o buzzer quando o tempo do bip acabou. Chamar todo ciclo.
static void Beep_Update() {
  if (beepLigado && millis() - beepInicioMs >= TAG_BEEP_MS) {
    digitalWrite(TAG_BUZZER_PIN, LOW);
    beepLigado = false;
  }
}

void setup() {
  Motion_Init();          // I2C, Serial (USB), motores, PWM, encoders, Timer3
  SensorsDriver_Init();   // GPS, DHT22, BMP280, RFID
  JsonSerial_Init();      // Serial3 (115200) -> ESP32

  pinMode(TAG_BUZZER_PIN, OUTPUT);
  digitalWrite(TAG_BUZZER_PIN, LOW);

  lastTelemetryMs = millis();
}

void loop() {
  // 1. MOVER: roda o PID quando o Timer3 sinaliza (50 ms)
  Motion_Loop();

  // 2. LER SENSORES: GPS todo ciclo, RFID a cada 100 ms, DHT/BMP no próprio intervalo
  if (SensorsDriver_Update()) {
    envioImediato = true;    // tag RFID nova: envia o JSON atualizado imediatamente
    Beep_Start();            // bip curto de confirmação
  }
  Beep_Update();

  // 3. ENVIAR JSON UNIFICADO (dht + bmp + gps + rfid)
  uint32_t now = millis();
  if (envioImediato || (now - lastTelemetryMs >= TELEMETRY_INTERVAL_MS)) {
    if (JsonSerial_SendTelemetry(SensorsDriver_Get())) {
      lastTelemetryMs = now;
      envioImediato   = false;
    }
  }

  // 4. Despeja a fila na Serial3 (sem bloquear) e lê o status do ESP32
  JsonSerial_Loop();
}