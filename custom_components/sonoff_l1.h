// credit to https://gist.github.com/emorydunn/db410db8bf68c8a335f3362d69624aaa for the script below

#include "esphome.h"

class SonoffL1 : public Component, public LightOutput {

  #define SONOFF_L1_MODE_COLORFUL           1  // [Color key] Colorful (static color)
  #define SONOFF_L1_MODE_COLORFUL_GRADIENT  2  // [SMOOTH] Colorful Gradient
  #define SONOFF_L1_MODE_COLORFUL_BREATH    3  // [FADE] Colorful Breath
  #define SONOFF_L1_MODE_DIY_GRADIENT       4  // DIY Gradient (fade in and out) [Speed 1- 100, color]
  #define SONOFF_L1_MODE_DIY_PULSE          5  // DIY Pulse  (faster fade in and out) [Speed 1- 100, color]
  #define SONOFF_L1_MODE_DIY_BREATH         6  // DIY Breath (toggle on/off) [Speed 1- 100, color]
  #define SONOFF_L1_MODE_DIY_STROBE         7  // DIY Strobe (faster toggle on/off) [Speed 1- 100, color]
  #define SONOFF_L1_MODE_RGB_GRADIENT       8  // RGB Gradient
  #define SONOFF_L1_MODE_RGB_PULSE          9  // [STROBE] RGB Pulse
  #define SONOFF_L1_MODE_RGB_BREATH        10  // RGB Breath
  #define SONOFF_L1_MODE_RGB_STROBE        11  // [FLASH] RGB strobe
  #define SONOFF_L1_MODE_SYNC_TO_MUSIC     12  // Sync to music [Speed 1- 100, sensitivity 1 - 10]

 public:

  int mode = SONOFF_L1_MODE_COLORFUL;

  void setup() override {
    // nothing to do here
    Serial.begin(19200);
  }
  LightTraits get_traits() override {
    // return the traits this light supports
    auto traits = LightTraits();
    traits.set_supported_color_modes({ColorMode::RGB, ColorMode::BRIGHTNESS});
    return traits;
  }

  void write_state(LightState *state) override {
    // This will be called by the light to get a new state to be written.
    float red, green, blue;
    // use any of the provided current_values methods
    state->current_values_as_rgb(&red, &green, &blue);


    // Convert to 0-255
    int redValue, greenValue, blueValue;
    redValue = floor(red * 255);
    greenValue = floor(green * 255);
    blueValue = floor(blue * 255);

    bool ledState;
    state->current_values_as_binary(&ledState);

    float brightnessPercent;
    state->current_values_as_brightness(&brightnessPercent);

    // Convert to 0-100
    int brightness = floor(brightnessPercent * 100);

    char buffer[140];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"switch\":\"%s\",\"light_type\":1,\"colorR\":%d,\"colorG\":%d,\"colorB\":%d,\"bright\":%d,\"mode\":%d"),
    millis(), millis()%1000,
    ledState ? "on" : "off",
    redValue, greenValue, blueValue,
    brightness,
    SONOFF_L1_MODE_COLORFUL);

    Serial.print(buffer);
    Serial.write(0x1B);
    Serial.flush();

  }

  // SONOFF_L1_MODE_COLORFUL_GRADIENT
  void setModeGradient() {
    char buffer[140];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis()%1000,
    SONOFF_L1_MODE_COLORFUL_GRADIENT
    );

    Serial.print(buffer);
    Serial.write(0x1B);
    Serial.flush();
  }

  // SONOFF_L1_MODE_COLORFUL_BREATH
  void setModeBreath() {
    char buffer[140];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis()%1000,
    SONOFF_L1_MODE_COLORFUL_BREATH
    );

    Serial.print(buffer);
    Serial.write(0x1B);
    Serial.flush();
  }

  // SONOFF_L1_MODE_RGB_GRADIENT
  void setModeRGBGradient() {
    char buffer[140];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis()%1000,
    SONOFF_L1_MODE_RGB_GRADIENT
    );

    Serial.print(buffer);
    Serial.write(0x1B);
    Serial.flush();
  }

  // SONOFF_L1_MODE_RGB_PULSE
  void setModeRGBPulse() {
    char buffer[140];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis()%1000,
    SONOFF_L1_MODE_RGB_PULSE
    );

    Serial.print(buffer);
    Serial.write(0x1B);
    Serial.flush();
  }

  // SONOFF_L1_MODE_RGB_BREATH
  void setModeRGBBreath() {
    char buffer[140];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis()%1000,
    SONOFF_L1_MODE_RGB_BREATH
    );

    Serial.print(buffer);
    Serial.write(0x1B);
    Serial.flush();
  }

  // SONOFF_L1_MODE_RGB_STROBE
  void setModeRGBStrobe() {
    char buffer[140];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis()%1000,
    SONOFF_L1_MODE_RGB_STROBE
    );

    Serial.print(buffer);
    Serial.write(0x1B);
    Serial.flush();
  }

  // SONOFF_L1_MODE_SYNC_TO_MUSIC
  void setModeSync(int sensitive = 10, int speed = 50) {
    char buffer[140];
    snprintf_P(buffer, sizeof(buffer), PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d,\"sensitive\":%d,\"speed\":%d"),
    millis(), millis()%1000,
    SONOFF_L1_MODE_SYNC_TO_MUSIC,
    sensitive,
    speed
    );

    Serial.print(buffer);
    Serial.write(0x1B);
    Serial.flush();
  }


};
