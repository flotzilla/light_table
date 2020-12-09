#include "NeoLight.h"

using namespace std;

NeoLight::NeoLight(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)()) : Adafruit_NeoPixel(pixels, pin, type)
{
    OnComplete = callback;
    current_mode = MODE_LIGHT;
    currentAnimationMode = MIN_ANIMATION_MODE;
}

void NeoLight::Update()
{

    if (current_mode == MODE_LIGHT)
    {
        // do nothing, color will be changed in changeMode()
    }
    else if (current_mode == MODE_ANIMATION)
    {
        changeAnimationMode();
    }
}

void NeoLight::changeMode()
{
    shouldAnimationStop = true;

    if (current_mode == MODE_LIGHT)
    {
        Serial.println("switching to animation mode");
        current_mode = MODE_ANIMATION;
    }
    else
    {
        Serial.println("switching to light mode");
        current_mode = MODE_LIGHT;
        calculateColor();
    }
}

void NeoLight::changeAnimationMode()
{
    shouldAnimationStop = false;

    switch (currentAnimationMode)
    {
    case ANIMATION_MODE_0:
        animationRainbow();
        break;
    case ANIMATION_MODE_1:
        animationChase();
        break;
    case ANIMATION_MODE_2:
        animationLava();
        break;
    case ANIMATION_MODE_3:
        animationScanner();
        break;

    default:
        break;
    }
}

void NeoLight::Increment()
{

    shouldAnimationStop = true;

    if (current_mode == MODE_LIGHT)
    {
        if (currentLightMode + 1 > MAX_LIGHT_MODE)
        {
            currentLightMode = MIN_LIGHT_MODE;
        }
        else
        {
            ++currentLightMode;
        }
        calculateColor();
    }
    else if (current_mode == MODE_ANIMATION)
    {
        if (currentAnimationMode + 1 > MAX_ANIMATION_MODE)
        {
            currentAnimationMode = MIN_ANIMATION_MODE;
        }
        else
        {
            ++currentAnimationMode;
        }
    }
}

void NeoLight::Reverse()
{

    shouldAnimationStop = true;

    if (current_mode == MODE_LIGHT)
    {
        if (currentLightMode - 1 < MIN_LIGHT_MODE)
        {
            currentLightMode = MAX_LIGHT_MODE;
        }
        else
        {
            --currentLightMode;
        }
        calculateColor();
    }
    else if (current_mode == MODE_ANIMATION)
    {
        if (currentAnimationMode - 1 < MIN_ANIMATION_MODE)
        {
            currentAnimationMode = MAX_ANIMATION_MODE;
        }
        else
        {
            --currentAnimationMode;
        }
    }
}

void NeoLight::ColorSet(uint32_t color)
{

    for (unsigned int i = 0; i < numPixels(); i++)
    {
        setPixelColor(i, color);
    }

    show();
}

void NeoLight::setIntensity(uint8_t val)
{
    setBrightness(val);
    show();
}

void NeoLight::calculateColor()
{
    switch (currentLightMode)
    {
    case LIGHNT_MODE_0:
        ColorSet(Color(255, 255, 255));
        break;
    case LIGHNT_MODE_1:
        ColorSet(Color(3, 255, 20));
        break;
    case LIGHNT_MODE_2:
        ColorSet(Color(0, 74, 236));
        break;
    case LIGHNT_MODE_3:
        ColorSet(Color(236, 0, 24));
        break;
    case LIGHNT_MODE_4:
        ColorSet(Color(255, 255, 0));
        break;
    case LIGHNT_MODE_5:
        ColorSet(Color(51, 103, 255));
        break;
    case LIGHNT_MODE_6:
        ColorSet(Color(127, 0, 255));
        break;
    case LIGHNT_MODE_7:
        ColorSet(Color(0, 204, 204));
        break;
    case LIGHNT_MODE_8:
        ColorSet(Color(153, 204, 255));
        break;
    case LIGHNT_MODE_9:
        ColorSet(Color(102, 102, 255));
        break;
    case LIGHNT_MODE_10:
        ColorSet(Color(255, 51, 153));
        break;
     case LIGHNT_MODE_11_CUSTOM:
        ColorSet(customColor);
        break;
    }
}

void NeoLight::setCustomColor(uint8_t r, uint8_t g, uint8_t b)
{
    if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0){
        return;
    }

    if (currentLightMode == LIGHNT_MODE_11_CUSTOM && current_mode == MODE_LIGHT){
        customColor = Color(r, g, b);
        ColorSet(customColor);
        show();
    }
}

uint32_t NeoLight::Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

void NeoLight::animationChase()
{
    if (shouldAnimationStop)
        return;

    for (uint8_t j = 0; j < 256; j++)
    { // cycle all 256 colors in the wheel
        for (uint8_t q = 0; q < 3; q++)
        {
            for (uint8_t i = 0; i < numPixels(); i = i + 3)
            {
                setPixelColor(i + q, Wheel((i + j) % 255)); //turn every third pixel on

                if (OnComplete != NULL)
                    OnComplete();
                if (shouldAnimationStop || shouldBeTurnedOff)
                    return;
            }

            show();

            delay(ANIMATION_CHASE_DELAY);

            for (uint8_t i = 0; i < numPixels(); i = i + 3)
            {
                setPixelColor(i + q, 0); //turn every third pixel off
            }
        }
    }
}

void NeoLight::animationRainbow()
{
    if (shouldAnimationStop)
        return;

    uint16_t i, j;

    for (j = 0; j < 256; j++)
    {
        for (i = 0; i < numPixels(); i++)
        {
            setPixelColor(i, Wheel((i + j) & 255));

            show();

            if (OnComplete != NULL)
                OnComplete();
            if (shouldAnimationStop || shouldBeTurnedOff)
                return;
        }
    }
}

void NeoLight::animationScanner()
{
    uint8_t i, j;

    for (j = 0; j < 256; j = j + 10)
    {

        // going up
        for (i = 0; i < numPixels(); i++)
        {
            setPixelColor(i, Wheel(j));
            if (i != 0)
            {
                setPixelColor(i - 1, Color(0, 0, 0));
            }

            show();
            delay(ANIMATION_SCANNER_DELAY);

            if (OnComplete != NULL)
                OnComplete();
            if (shouldAnimationStop || shouldBeTurnedOff)
                return;
        }
        setPixelColor(numPixels() - 1, Color(0, 0, 0));

        // and down
        for (i = numPixels() - 1; i > 0; i--)
        {
            setPixelColor(i, Wheel(j));
            if (i != numPixels() - 1)
            {
                setPixelColor(i + 1, Color(0, 0, 0));
            }

            show();

            delay(ANIMATION_SCANNER_DELAY);

            if (OnComplete != NULL)
                OnComplete();
            if (shouldAnimationStop || shouldBeTurnedOff)
                return;
        }
    }
}

void NeoLight::animationLava()
{
    uint8_t l, r, j; // l for left, r for right

    for (j = 0; j < 256; j = j + 20)
    {
        for (l = r = numPixels() / 2;
             l > 1 || r < numPixels() - 1;
             l--, r++)
        {
            setPixelColor(l, Wheel(j));
            setPixelColor(r, Wheel(j));

            show();

            delay(ANIMATION_LAVA_DELAY);

            if (OnComplete != NULL)
                OnComplete();
            if (shouldAnimationStop || shouldBeTurnedOff)
                return;
        }
        setPixelColor(0, Wheel(j));
        setPixelColor(numPixels() - 1, Wheel(j));
    }
}

void NeoLight::turnOn()
{
    shouldBeTurnedOff = false;

    setBrightness(100);

    if (current_mode == MODE_LIGHT)
    {
        calculateColor();
    }
}

void NeoLight::turnOff()
{
    shouldBeTurnedOff = true;
    setBrightness(0);
    show();
}

int NeoLight::getCurrentLightMode(){
    return currentLightMode;
}
