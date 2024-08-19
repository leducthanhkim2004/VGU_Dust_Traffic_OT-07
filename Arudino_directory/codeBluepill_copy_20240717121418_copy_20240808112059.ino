#include <Wire.h>
#include <BME280I2C.h>
#include <RtcDS1307.h>

// Operational variables
RtcDS1307<TwoWire> Rtc(Wire);
BME280I2C bme;
unsigned long last = 0;
String data;
unsigned char pms[32] = {
  0,
};

// Setting variables
int update_interval = 10;  // in seconds

void setup() {
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, LOW);
  Serial.begin(115200);
  while (!Serial) {}  // Wait for Serial

  //================ PMS7003 ===============
  Serial3.begin(9600);

  //================ BME280 ===============
  Wire.begin();  // Initialize I2C communication
  while (!bme.begin()) {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  //================ DS1307 ===============
  Rtc.Begin();

  // Comment this out after setting the RTC once
  // Uncomment to set the time once
  //RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  //Rtc.SetDateTime(compiled); // Set clock time as system time

  Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low);

  digitalWrite(PC13, HIGH);
}

void loop() {
  //================ PMS7003 ===============
  if (Serial3.available() >= 32) {
    // Find the start of a new frame
    while (Serial3.available() > 0 && Serial3.peek() != 0x42) {
      Serial3.read();  // Discard bytes until we find the start byte (0x42)
    }

    if (Serial3.available() >= 32) {
      for (int j = 0; j < 32; j++) {
        pms[j] = Serial3.read();
      }
    }
  }

  //================ BME280 ===============
  float temp(NAN), hum(NAN), pres(NAN);
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);
  bme.read(pres, temp, hum, tempUnit, presUnit);

  //================ DS1307 ===============
  RtcDateTime now = Rtc.GetDateTime();
  unsigned long current = now.Epoch32Time();

  // Convert RtcDateTime to human-readable format
  char dateString[20];
  snprintf(dateString, sizeof(dateString), "%04u-%02u-%02u %02u:%02u:%02u",
           now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second());

  if ((current - last) >= update_interval && current != 0) {
    data = String(dateString) + ',' + String(temp) + ',' + String(hum) + ',' + String(pres);
    if (pms[0] == 66 && pms[1] == 77) {
      data += ',' + String(pms[11]) + ',' + String(pms[13]) + ',' + String(pms[15]);
    } else {
      data += "0,0,0";
    }

    Serial.println(data);
    digitalWrite(PC13, LOW);
    delay(100);  // Small delay to ensure visibility of the LED toggle
    digitalWrite(PC13, HIGH);
    last = current;
  }
}
