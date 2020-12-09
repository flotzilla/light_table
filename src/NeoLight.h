#ifndef NEOLIGHT_H
#define NEOLIGHT_H

#include <Adafruit_NeoPixel.h>

class NeoLight : public Adafruit_NeoPixel
{
#define MODE_LIGHT 0
#define MODE_ANIMATION 1

#define LIGHNT_MODE_0 0   // WHITE
#define LIGHNT_MODE_1 1   // GREEN
#define LIGHNT_MODE_2 2   // BLUE
#define LIGHNT_MODE_3 3   // RED
#define LIGHNT_MODE_4 4   // YELLOW
#define LIGHNT_MODE_5 5   // LIGHT_BLUE
#define LIGHNT_MODE_6 6   // PURPLE
#define LIGHNT_MODE_7 7   // LIGHT_BLUE
#define LIGHNT_MODE_8 8   // LIGHT_BLUE
#define LIGHNT_MODE_9 9   // LIGHT_BLUE
#define LIGHNT_MODE_10 10 // LIGHT_BLUE
#define LIGHNT_MODE_11_CUSTOM 11 // LIGHT_BLUE

#define MAX_LIGHT_MODE LIGHNT_MODE_11_CUSTOM
#define MIN_LIGHT_MODE LIGHNT_MODE_0

#define ANIMATION_MODE_0 0 // RAINBOW
#define ANIMATION_MODE_1 1 // CHASE
#define ANIMATION_MODE_2 2 // LAVA
#define ANIMATION_MODE_3 3 // SCANNER

#define MAX_ANIMATION_MODE ANIMATION_MODE_3
#define MIN_ANIMATION_MODE ANIMATION_MODE_0

    const uint8_t
        ANIMATION_CHASE_DELAY = 70,
        ANIMATION_SCANNER_DELAY = 10,
        ANIMATION_LAVA_DELAY = 50;

    bool
        shouldAnimationStop = false,
        shouldBeTurnedOff = false;

    uint8_t
        current_mode = MODE_LIGHT,
        currentLightMode = LIGHNT_MODE_0,
        currentAnimationMode = ANIMATION_MODE_0,
        light_intensity;

public:
    NeoLight(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)());

    uint32_t Wheel(byte WheelPos);
    uint32_t customColor; 

    void (*OnComplete)();

    void setIntensity(uint8_t val);
    void Update();
    void Increment();
    void Reverse();
    void ColorSet(uint32_t color);
    void calculateColor();
    void turnOn();
    void turnOff();
    void changeMode();
    void changeAnimationMode();

    // animations
    void animationRainbow();
    void animationChase();
    void animationLava();
    void animationScanner();

    void setCustomColor(uint8_t r, uint8_t g, uint8_t b);

    int getCurrentLightMode();
};

#endif