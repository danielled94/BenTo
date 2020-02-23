#pragma once

#include "../../common/Common.h"
#include "LedHelpers.h"

class RGBLedsEvent
{
public:
    enum Type { ASK_FOCUS };
    RGBLedsEvent(Type type) : type(type) {}
    Type type;
};

class RGBLedsManager : public Component, public EventBroadcaster<RGBLedsEvent> {
public:
    RGBLedsManager();

    CRGB leds[LED_COUNT];
    float globalBrightness;

    void init();
    void update();


    void setBrightness(float value, bool save = false);
    bool handleCommand(String command, var * data, int numData) override;

    //Helpers
    void clear();
    void fillAll(CRGB c);
    void fillRange(CRGB c, float start, float end, bool clear = true);
    void point(CRGB c, float pos, float radius, bool clear = true);

    void setLed(int index, CRGB c);
        
private:
    Preferences prefs;
};
    
