#pragma once

#include <Preferences.h>

DeclareComponentSingleton(Settings, "settings", )

#ifdef ESP32
    Preferences prefs;
#endif

StaticJsonDocument<4096> settings;

bool initInternal() override;
bool saveSettings();

void setConfig(const String &comp, const String &name, var val, bool save);

EndDeclareComponent