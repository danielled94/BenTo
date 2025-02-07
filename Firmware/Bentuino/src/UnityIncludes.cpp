
#include "UnityIncludes.h"

//SD shit
#include "../lib/SD/src/SD.cpp" //really weird
#include "../lib/SD/src/sd_diskio.cpp" //really weird

// Firmware

#include "Component/ComponentEvent.cpp"
#include "Component/Component.cpp"

#include "Component/components/settings/SettingsComponent.cpp"
#include "Component/components/wifi/WifiComponent.cpp"
#include "Component/components/battery/BatteryComponent.cpp"
#include "Component/components/communication/CommunicationComponent.cpp"
#include "Component/components/communication/osc/OSCComponent.cpp"
#include "Component/components/communication/serial/SerialComponent.cpp"
#include "Component/components/server/WebServerComponent.cpp"

#include "Component/components/sequence/SequenceComponent.cpp"
#include "Component/components/files/FilesComponent.cpp"

#include "Component/components/ledstrip/Layer/LedStripLayer.cpp"
#include "Component/components/ledstrip/Layer/layers/stream/LedStripStreamLayer.cpp"
#include "Component/components/ledstrip/Layer/layers/bake/LedStripBakeLayer.cpp"
#include "Component/components/ledstrip/Layer/layers/script/LedStripScriptLayer.cpp"
#include "Component/components/ledstrip/Layer/layers/system/LedStripSystemLayer.cpp"

#include "RootComponent.cpp"