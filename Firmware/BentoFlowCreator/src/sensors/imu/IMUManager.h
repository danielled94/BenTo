#include "../../common/Common.h"

#include <Wire.h>
#include "Adafruit_BNO055/Adafruit_BNO055.h"

#define TRAIL_MAX 20
#define IMU_READ_ASYNC
#define NATIVE_STACK_SIZE (32 * 1024)

class IMUEvent
{
public:
    enum Type { OrientationUpdate, AccelUpdate, GyroUpdate, LinearAccelUpdate, Gravity, ThrowState, CalibrationStatus, ActivityUpdate, Debug, ProjectedAngleUpdate, TYPES_MAX };
    static const String eventNames[TYPES_MAX];

    IMUEvent(Type t, float * data = nullptr, int numData = 0) : type(t), data(data), numData(numData) {}
    Type type;
    float * data;
    int intData;
    int numData;
};


class IMUManager : public Component, public EventBroadcaster<IMUEvent> {
public:
    IMUManager();
    ~IMUManager();

    static IMUManager * instance;

#ifdef HAS_IMU
    Adafruit_BNO055 bno;
#endif

    long tstart;
    long tend;

    bool isConnected;
    bool isEnabled;
    int sendLevel; //-1 = noSend / 0 = throws / 1 = +orientation / 2 = + other stuff
    
    long orientationSendTime;
    long timeSinceOrientationLastSent;

    float calibration[4];
    
    float orientation[3];
    float accel[3];
    float gyro[3];
    float linearAccel[3];
    float gravity[3];
    
    int throwState; //0 = none, 1 = flat, 2 = single, 3 = double+, 4 = flat-front, 5 = loftie
    float activity;
    float prevActivity;
    float debug[4];

    //IMU Compute
    float flatThresholds[2];
    float accelThresholds[3];
    float diffThreshold;
    float semiFlatThreshold;
    float loftieThreshold;
    float singleThreshold;

    // Projected Angle
    float angleOffset;
    float projectedAngle;
    float xOnCalibration;
    
#ifdef IMU_READ_ASYNC
    bool hasNewData;
    bool imuLock;
    bool shouldStopRead;
    static void readIMUStatic(void *);
#endif
    
    void init();
    void update();
    
    void readIMU();

    void sendCalibrationStatus();
    void computeThrow();
    void computeActivity();
    void computeProjectedAngle();

    void setEnabled(bool value);
    void setProjectAngleOffset(float yaw, float angle);
    
    void shutdown();

    bool handleCommand(String command, var * data, int numData) override;

    #ifdef USE_PREFERENCES
    Preferences prefs;
    #endif
};
