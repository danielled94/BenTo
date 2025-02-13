ImplementSingleton(FilesComponent);

bool FilesComponent::initInternal()
{
    useInternalMemory = GetBoolConfig("useSD");

    if (useInternalMemory) // use internal
    {
        NDBG("No SD Pin in config, using internal memory");
        if (SPIFFS.begin(true)) // Start the SPI Flash Files System
        {
            NDBG("SPIFFS initialized.");
            listDir("/", 0);
        }
        else
        {
            NDBG("Error initializing SPIFFS");
            return false;
        }
    }
    else
    {

        sdEnPin = GetIntConfig("sdEnPin");
        if (sdEnPin > 0)
        {
            sdEnVal = GetIntConfig("sdEnVal");
            pinMode(sdEnPin, OUTPUT);
            digitalWrite(sdEnPin, sdEnVal);
        }

        int sdSck = GetIntConfig("sdSCK");
        int sdMiso = GetIntConfig("sdMiso");
        int sdMosi = GetIntConfig("sdMosi");
        int sdCS = GetIntConfig("sdCS");

        int sdSpeed = GetIntConfig("sdSpeed");
        if (sdSpeed == 0)
            sdSpeed = 27000000;

        pinMode(sdSck, INPUT_PULLUP);
        pinMode(sdMiso, INPUT_PULLUP);
        pinMode(sdMosi, INPUT_PULLUP);
        pinMode(sdCS, INPUT_PULLUP);

        spiSD.begin((int8_t)sdSck, (int8_t)sdMiso, (int8_t)sdMosi, (int8_t)sdCS); // SCK,MISO,MOSI,ss

        if (SD.begin((uint8_t)sdCS, spiSD, (uint32_t)sdSpeed))
        {
            NDBG("SD Card initialized.");
            // listDir("/", 0);
        }
        else
        {
            NDBG("Error initializing SD Card");
            return false;
        }
    }

    return true;
}

File FilesComponent::openFile(String fileName, bool forWriting, bool deleteIfExists)
{

    if (forWriting && deleteIfExists)
        deleteFileIfExists(fileName);

    if (!fileName.startsWith("/"))
        fileName = "/" + fileName;

    File f;
    if (useInternalMemory)
        f = SPIFFS.open(fileName, forWriting ? "w" : "r"); // Open it
    else
        f = SD.open(fileName.c_str(), forWriting ? FILE_WRITE : FILE_READ);

    return f;
}

void FilesComponent::deleteFileIfExists(String path)
{

    if (!isInit)
        return;

    if (useInternalMemory)
    {
        if (SPIFFS.exists(path)) SPIFFS.remove(path);
    }
    else
    {

        if (SD.exists(path.c_str()))  SD.remove(path.c_str());
    }
}

String FilesComponent::listDir(const char *dirname, uint8_t levels)
{
    String result = "";

    File root;

    if (useInternalMemory)
        root = SPIFFS.open("/", "r");
    else
        root = SD.open(dirname);

    if (!root)
    {
        NDBG("Failed to open directory");
        return result;
    }

    if (!root.isDirectory())
    {
        NDBG("Not a directory");
        return result;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            NDBG("  DIR : " + String(file.name()));
            if (levels)
            {
                result += listDir(file.name(), levels - 1);
            }
        }
        else
        {
            NDBG("  FILE: " + String(file.name()));
            result += String(file.name()) + ",";
            NDBG("  SIZE: " + String(file.size()));
        }
        file = root.openNextFile();
    }

    return result;
}

bool FilesComponent::handleCommandInternal(const String &command, var *data, int numData)
{
    /*
        if (checkCommand(command, "delete", numData, 1))
        {
            deleteFileIfExists(data[0].stringValue());
            return true;
        }
        else if (checkCommand(command, "enable", numData, 1))
        {
            setSDEnabled(data[0].intValue() == 1);
            return true;
        }
        else if (checkCommand(command, "deleteFolder", numData, 0))
        {
            if (numData > 0)
            {
                DBG("Deleting folder " + data[0].stringValue());
    #ifdef FILES_USE_INTERNAL_MEMORY
                SPIFFS.rmdir(data[0].stringValue());
    #else
                SD.rmdir(data[0].stringValue());
    #endif
            }
            else
            {
                DBG("Deleting all files");
    #ifdef FILES_USE_INTERNAL_MEMORY
                SPIFFS.rmdir("/");
    #else
                SD.rmdir("/");
    #endif
            }

            return true;
        }
        else if (checkCommand(command, "list", numData, 0))
        {
            var data;
            data.type = 's';
            data.value.s = (char *)listDir("/", 0).c_str();

            sendEvent(FileEvent(FileEvent::FileList, data));
            return true;
        }
        */

    return false;
}