#include "bno055.h"
#include <math.h>
#include "Function.h"
#include <stdio.h>
#include "mcc_generated_files/i2c1.h"

#define PI 3.1425

#define SLAVE_I2C_GENERIC_RETRY_MAX 2

// Pin definitions
char intPin = 8;  // These can be changed, 2 and 3 are the Arduinos ext int pins
char myLed = 13;

int accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
int gyroCount[3];   // Stores the 16-bit signed gyro sensor output
int magCount[3];    // Stores the 16-bit signed magnetometer sensor output
int quatCount[4];   // Stores the 16-bit signed quaternion output
int EulCount[3];    // Stores the 16-bit signed Euler angle output
int LIACount[3];    // Stores the 16-bit signed linear acceleration output
int GRVCount[3];    // Stores the 16-bit signed gravity vector output
float gyroBias[3] = {0, 0, 0}, accelBias[3] = {0, 0, 0}, magBias[3] = {0, 0, 0};  // Bias corrections for gyro, accelerometer, and magnetometer
int tempGCount, tempMCount;      // temperature raw count output of mag and gyro
float   Gtemperature, Mtemperature;  // Stores the BNO055 gyro and mag internal chip temperatures in degrees Celsius

// global constants for 9 DoF fusion and AHRS (Attitude and Heading Reference System)
float GyroMeasError = PI * (40.0f / 180.0f);   // gyroscope measurement error in rads/s (start at 40 deg/s)
float GyroMeasDrift = PI * (0.0f  / 180.0f);   // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
// There is a tradeoff in the beta parameter between accuracy and response speed.
// In the original Madgwick study, beta of 0.041 (corresponding to GyroMeasError of 2.7 degrees/s) was found to give optimal accuracy.
// However, with this value, the LSM9SD0 response time is about 10 seconds to a stable initial quaternion.
// Subsequent changes also require a longish lag time to a stable output, not fast enough for a quadcopter or robot car!
// By increasing beta (GyroMeasError) by about a factor of fifteen, the response time constant is reduced to ~2 sec
// I haven't noticed any reduction in solution accuracy. This is essentially the I coefficient in a PID control sense; 
// the bigger the feedback coefficient, the faster the solution converges, usually at the expense of accuracy. 
// In any case, this is the free parameter in the Madgwick filtering and fusion scheme.

#define Kp 2.0f * 5.0f // these are the free parameters in the Mahony filter and fusion scheme, Kp for proportional feedback, Ki for integral
#define Ki 0.0f
float beta = 0;   // compute beta
float zeta = 0;
long delt_t = 0, count = 0, sumCount = 0;  // used to control display output rate
float pitch, yaw, roll;
float Pitch, Yaw, Roll;
float LIAx, LIAy, LIAz, GRVx, GRVy, GRVz;
float deltat = 0.0f, sum = 0.0f;          // integration interval for both filter schemes
long lastUpdate = 0, firstUpdate = 0; // used to calculate integration interval
long Now = 0;                         // used to calculate integration interval

float ax, ay, az, gx, gy, gz, mx, my, mz; // variables to hold latest sensor data values 
float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
float quat[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
float eInt[3] = {0.0f, 0.0f, 0.0f};       // vector to hold integral error for Mahony method

void Setup()
{
    
    beta = sqrt(3.0 / 4.0) * GyroMeasError;   // compute beta
    zeta = sqrt(3.0 / 4.0) * GyroMeasDrift;   // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value
//  Wire.begin();
//  TWBR = 12;  // 400 kbit/sec I2C speed for Pro Mini
  // Setup for Master mode, pins 16/17, external pullups, 400kHz for Teensy 3.1
  //Wire.begin(I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);

  
  // Read the WHO_AM_I register, this is a good test of communication
  printf("BNO055 9-axis motion sensor.../n");
  Delay(200);
  char c = readByte(BNO055_ADDRESS, BNO055_CHIP_ID);  // Read WHO_AM_I register for BNO055
  Delay(200);
  printf("BNO055 Address = 0x%s/n",BNO055_ADDRESS);
  Delay(200);
  printf("BNO055 WHO_AM_I = 0x%s/n", BNO055_CHIP_ID);
  Delay(200);
  printf("BNO055 - I AM %s  - I should be 0xA0/n",c); 
  Delay(200);
  

    // Read the WHO_AM_I register of the accelerometer, this is a good test of communication
  char d = readByte(BNO055_ADDRESS, BNO055_ACC_ID);  // Read WHO_AM_I register for accelerometer
  printf("BNO055 ACC I AM %c I should be 0xFB/n",d);
    Delay(200);
  // Read the WHO_AM_I register of the magnetometer, this is a good test of communication
  char e = readByte(BNO055_ADDRESS, BNO055_MAG_ID);  // Read WHO_AM_I register for magnetometer
  printf("BNO055 MAG I AM %c I should be 0x32/n",e);  
    Delay(200);
  // Read the WHO_AM_I register of the gyroscope, this is a good test of communication
  char f = readByte(BNO055_ADDRESS, BNO055_GYRO_ID);  // Read WHO_AM_I register for LIS3MDL
  printf("BNO055 GYRO I AM %c  I should be 0x0F/n",f); 
  Delay(200);
  if (c == 0xA0) // BNO055 WHO_AM_I should always be 0xA0
  {  
    printf("BNO055 is online...");
      Delay(200);
    // Check software revision ID
    char swlsb = readByte(BNO055_ADDRESS, BNO055_SW_REV_ID_LSB);
    Delay(10);
    char swmsb = readByte(BNO055_ADDRESS, BNO055_SW_REV_ID_MSB);
    Delay(200);
    printf("BNO055 SW Revision ID: %c.%c/n",swmsb,swlsb);  
    printf("Should be 03.04/n");
      Delay(200);
    // Check bootloader version
    char blid = readByte(BNO055_ADDRESS, BNO055_BL_REV_ID);
    printf("BNO055 bootloader Version: %c", blid);
    
    // Check self-test results
    char selftest = readByte(BNO055_ADDRESS, BNO055_ST_RESULT);
    
    if(selftest & 0x01) {
      printf("accelerometer passed self test/n"); 
    } else {
      printf("accelerometer failed self test"); 
    }
    if(selftest & 0x02) {
      printf("magnetometer passed self test/n"); 
    } else {
      printf("magnetometer failed self test"); 
    }  
    if(selftest & 0x04) {
      printf("gyroscope passed self test/n"); 
    } else {
      printf("gyroscope failed self test"); 
    }      
    if(selftest & 0x08) {
      printf("MCU passed self test/n"); 
    } else {
      printf("MCU failed self test"); 
    }
      
    Delay(1000);
 
  accelgyroCalBNO055(accelBias, gyroBias);
  
  printf("Average accelerometer bias (mg) = %f", accelBias);
  printf("Average gyro bias (dps) = %f",gyroBias);

  Delay(1000); 
  
  magCalBNO055(magBias);
  
  printf("Average magnetometer bias (mG) = %f", magBias);
  
  Delay(1000); 
  
  // Check calibration status of the sensors
  char calstat = readByte(BNO055_ADDRESS, BNO055_CALIB_STAT);
  printf("Not calibrated = 0, fully calibrated = 3");
  printf("System calibration status = %c", (0xC0 & calstat) >> 6);
  printf("Gyro   calibration status = %c", (0x30 & calstat) >> 4);
  printf("Accel  calibration status = %c", (0x0C & calstat) >> 2);
  printf("Mag    calibration status = %c", (0x03 & calstat) >> 0);
  
  initBNO055(); // Initialize the BNO055
  printf("BNO055 initialized for sensor mode...."); // Initialize BNO055 for sensor read 
 
  }
  else
  {
    printf("Could not connect to BNO055: 0x%c",c);
    while(1) ; // Loop forever if communication doesn't happen
  }
}

void loop()
{  
    readAccelData(accelCount);  // Read the x/y/z adc values
    // Now we'll calculate the accleration value into actual mg's
    ax = (float)accelCount[0]; // - accelBias[0];  // subtract off calculated accel bias
    ay = (float)accelCount[1]; // - accelBias[1];
    az = (float)accelCount[2]; // - accelBias[2]; 

    readGyroData(gyroCount);  // Read the x/y/z adc values
    // Calculate the gyro value into actual degrees per second
    gx = (float)gyroCount[0]/16.; // - gyroBias[0];  // subtract off calculated gyro bias
    gy = (float)gyroCount[1]/16.; // - gyroBias[1];  
    gz = (float)gyroCount[2]/16.; // - gyroBias[2];   

    readMagData(magCount);  // Read the x/y/z adc values   
    // Calculate the magnetometer values in milliGauss
    mx = (float)magCount[0]/1.6; // - magBias[0];  // get actual magnetometer value in mGauss 
    my = (float)magCount[1]/1.6; // - magBias[1];  
    mz = (float)magCount[2]/1.6; // - magBias[2];   
    
    readQuatData(quatCount);  // Read the x/y/z adc values   
    // Calculate the quaternion values  
    quat[0] = (float)(quatCount[0])/16384.;    
    quat[1] = (float)(quatCount[1])/16384.;  
    quat[2] = (float)(quatCount[2])/16384.;   
    quat[3] = (float)(quatCount[3])/16384.;   
    
    readEulData(EulCount);  // Read the x/y/z adc values   
    // Calculate the Euler angles values in degrees
    Yaw = (float)EulCount[0]/16.;  
    Roll = (float)EulCount[1]/16.;  
    Pitch = (float)EulCount[2]/16.;   
 
    readLIAData(LIACount);  // Read the x/y/z adc values   
    // Calculate the linear acceleration (sans gravity) values in mg
    LIAx = (float)LIACount[0];  
    LIAy = (float)LIACount[1];  
    LIAz = (float)LIACount[2];   

    readGRVData(GRVCount);  // Read the x/y/z adc values   
    // Calculate the linear acceleration (sans gravity) values in mg
    GRVx = (float)GRVCount[0];  
    GRVy = (float)GRVCount[1];  
    GRVz = (float)GRVCount[2];   
    
  
  //Now = micros();
  deltat = ((Now - lastUpdate)/1000000.0); // set integration time by time elapsed since last filter update
  lastUpdate = Now;
  
  sum += deltat; // sum for averaging filter update rate
  sumCount++;
  
  // Sensors x, y, and z-axes  for the three sensor: accel, gyro, and magnetometer are all aligned, so
  // no allowance for any orientation mismatch in feeding the output to the quaternion filter is required.
  // For the BNO055, the sensor forward is along the x-axis just like
  // in the LSM9DS0 and MPU9250 sensors. This rotation can be modified to allow any convenient orientation convention.
  // This is ok by aircraft orientation standards!  
  // Pass gyro rate as rad/s
 // MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  mx,  my,  mz);
//  MahonyQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f, mx, my, mz);
    
    // Serial print and/or display at 0.5 s rate independent of data rates
    //delt_t = millis() - count;
    if (1) { // update LCD once per half-second independent of read rate

           // check BNO-055 error status at 2 Hz rate
        char sysstat = readByte(BNO055_ADDRESS, BNO055_SYS_STATUS); // check system status
        Delay(50);
        printf("System Status = 0x5c\n",sysstat);
        if(sysstat == 0x05){
            printf("Sensor fusion algorithm running\n");
        }
        if(sysstat == 0x06) {
            printf("Sensor fusion not algorithm running");
        }

        if(sysstat == 0x01) {
            char syserr = readByte(BNO055_ADDRESS, BNO055_SYS_ERR);
            if(syserr == 0x01) printf("Peripheral initialization error");
            if(syserr == 0x02) printf("System initialization error");
            if(syserr == 0x03) printf("Self test result failed");
            if(syserr == 0x04) printf("Register map value out of range");
            if(syserr == 0x05) printf("Register map address out of range");
            if(syserr == 0x06) printf("Register map write error");
            if(syserr == 0x07) printf("BNO low power mode no available for selected operation mode");
            if(syserr == 0x08) printf("Accelerometer power mode not available");
            if(syserr == 0x09) printf("Fusion algorithm configuration error");
            if(syserr == 0x0A) printf("Sensor configuration error");    
        }  

//        if(1) {
//            printf("ax = %d", ax);  
//            printf(" ay = %d", ay); 
//            printf(" az = %d mg\n",az);
//            printf("gx = %d", gx); 
//            printf(" gy = %d", gy); 
//            printf(" gz = %d deg/s\n", gz);
//            printf("mx = %d", mx ); 
//            printf(" my = %d", my ); 
//            printf(" mz = %d mG\n", mz );
//
//            printf("qx = %f", q[0]);
//            printf(" qy = %f", q[1]); 
//            printf(" qz = %f", q[2]); 
//            printf(" qw = %f\n", q[3]); 
//            printf("quatw = %f", quat[0]);
//            printf(" quatx = %f", quat[1]); 
//            printf(" quaty = %f", quat[2]); 
//            printf(" quatz = %f\n", quat[3]); 
//        } 

        tempGCount = readGyroTempData();  // Read the gyro adc values
        Gtemperature = (float) tempGCount; // Gyro chip temperature in degrees Centigrade
       // Print gyro die temperature in degrees Centigrade      
        printf("Gyro temperature is = %f degrees C\n", Gtemperature); // Print T values to tenths of a degree C

      // Define output variables from updated quaternion---these are Tait-Bryan angles, commonly used in aircraft orientation.
      // In this coordinate system, the positive z-axis is down toward Earth. 
      // Yaw is the angle between Sensor x-axis and Earth magnetic North (or true North if corrected for local declination, looking down on the sensor positive yaw is counterclockwise.
      // Pitch is angle between sensor x-axis and Earth ground plane, toward the Earth is positive, up toward the sky is negative.
      // Roll is angle between sensor y-axis and Earth ground plane, y-axis up is positive roll.
      // These arise from the definition of the homogeneous rotation matrix constructed from quaternions.
      // Tait-Bryan angles as well as Euler angles are non-commutative; that is, the get the correct orientation the rotations must be
      // applied in the correct order which for this configuration is yaw, pitch, and then roll.
      // For more see http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles which has additional links.
       // yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);   
       // pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
       // roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
      //  pitch *= 180.0f / PI;
     //   yaw   *= 180.0f / PI; 
     //   yaw   -= 13.8f; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04
       // roll  *= 180.0f / PI;

        if(1) {
//            printf("Software Yaw, Pitch, Roll:\n ");
//            printf("         %f   %f     %f",yaw, pitch, roll);
//
//            printf("Software Yaw, Pitch, Roll:\n ");
//            printf("         %f   %f     %f",yaw, pitch, roll);

            printf("Hardware x, y, z linear acceleration:");
            printf(" %f.1, %f.1,%f.1",LIAx, LIAy, LIAz);
            Delay(50);
            printf("Hardware x, y, z gravity vector: ");
            printf(" %f.1, %f.1,%f.1\n",GRVx, GRVy, GRVz);
            Delay(50);
            printf("rate = %f.1 Hz\n", sumCount/sum);
        }

        //digitalWrite(myLed, !digitalRead(myLed));
        //count = millis(); 
        sumCount = 0;
        sum = 0;    
    }

}

//===================================================================================================================
//====== Set of useful function to access acceleration. gyroscope, magnetometer, and temperature data
//===================================================================================================================

void readAccelData(int * destination){
  char rawData[6];  // x/y/z accel register data stored here
  readBytes(BNO055_ADDRESS, BNO055_ACC_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers into data array
  destination[0] = ((int)rawData[1] << 8) | rawData[0] ;      // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int)rawData[3] << 8) | rawData[2] ;  
  destination[2] = ((int)rawData[5] << 8) | rawData[4] ; 
}


void readGyroData(int * destination){
  char rawData[6];  // x/y/z gyro register data stored here
  readBytes(BNO055_ADDRESS, BNO055_GYR_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int)rawData[3] << 8) | rawData[2] ;  
  destination[2] = ((int)rawData[5] << 8) | rawData[4] ; 
}

char readGyroTempData(){
  return readByte(BNO055_ADDRESS, BNO055_TEMP);  // Read the two raw data registers sequentially into data array 
}

void readMagData(int * destination){
  char rawData[6];  // x/y/z gyro register data stored here
  readBytes(BNO055_ADDRESS, BNO055_MAG_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int)rawData[3] << 8) | rawData[2] ;  
  destination[2] = ((int)rawData[5] << 8) | rawData[4] ;
}

void readQuatData(int * destination){
  char rawData[8];  // x/y/z gyro register data stored here
  readBytes(BNO055_ADDRESS, BNO055_QUA_DATA_W_LSB, 8, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int)rawData[3] << 8) | rawData[2] ;  
  destination[2] = ((int)rawData[5] << 8) | rawData[4] ;
  destination[3] = ((int)rawData[7] << 8) | rawData[6] ;
}

void readEulData(int * destination){
  char rawData[6];  // x/y/z gyro register data stored here
  readBytes(BNO055_ADDRESS, BNO055_EUL_HEADING_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int)rawData[3] << 8) | rawData[2] ;  
  destination[2] = ((int)rawData[5] << 8) | rawData[4] ;
}

void readLIAData(int * destination){
  char rawData[6];  // x/y/z gyro register data stored here
  readBytes(BNO055_ADDRESS, BNO055_LIA_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int)rawData[3] << 8) | rawData[2] ;  
  destination[2] = ((int)rawData[5] << 8) | rawData[4] ;
}

void readGRVData(int * destination){
  char rawData[6];  // x/y/z gyro register data stored here
  readBytes(BNO055_ADDRESS, BNO055_GRV_DATA_X_LSB, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int)rawData[1] << 8) | rawData[0] ;       // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int)rawData[3] << 8) | rawData[2] ;  
  destination[2] = ((int)rawData[5] << 8) | rawData[4] ;
}

void initBNO055() {
   // Select BNO055 config mode
   writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
   Delay(25);
   // Select page 1 to configure sensors
   writeByte(BNO055_ADDRESS, BNO055_PAGE_ID, 0x01);
   // Configure ACC
   writeByte(BNO055_ADDRESS, BNO055_ACC_CONFIG, APwrMode << 5 | Abw << 2 | Ascale );
   // Configure GYR
   writeByte(BNO055_ADDRESS, BNO055_GYRO_CONFIG_0, Gbw << 3 | Gscale );
   writeByte(BNO055_ADDRESS, BNO055_GYRO_CONFIG_1, GPwrMode);
   // Configure MAG
   writeByte(BNO055_ADDRESS, BNO055_MAG_CONFIG, MPwrMode << 5 | MOpMode << 3 | Modr );
   
   // Select page 0 to read sensors
   writeByte(BNO055_ADDRESS, BNO055_PAGE_ID, 0x00);

   // Select BNO055 gyro temperature source 
   writeByte(BNO055_ADDRESS, BNO055_TEMP_SOURCE, 0x01 );

   // Select BNO055 sensor units (temperature in degrees C, rate in dps, accel in mg)
   writeByte(BNO055_ADDRESS, BNO055_UNIT_SEL, 0x01 );
   
   // Select BNO055 system power mode
   writeByte(BNO055_ADDRESS, BNO055_PWR_MODE, PWRMode );
 
   // Select BNO055 system operation mode
   writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, OPRMode );
   Delay(25);
  }

void accelgyroCalBNO055(float * dest1, float * dest2) {
  char data[6]; // data array to hold accelerometer and gyro x, y, z, data
  long ii = 0;
  long sample_count = 0;
  long gyro_bias[3]  = {0, 0, 0};
  long accel_bias[3] = {0, 0, 0};
 
  printf("Accel/Gyro Calibration: Put device on a level surface and keep motionless! Wait......");
  Delay(4000);
  
  // Select page 0 to read sensors
   writeByte(BNO055_ADDRESS, BNO055_PAGE_ID, 0x00);
   // Select BNO055 system operation mode as AMG for calibration
   writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
   Delay(25);
   writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, AMG);
   
 // In NDF fusion mode, accel full scale is at +/- 4g, ODR is 62.5 Hz, set it the same here
   writeByte(BNO055_ADDRESS, BNO055_ACC_CONFIG, APwrMode << 5 | Abw << 2 | AFS_4G );
   sample_count = 256;
   for(ii = 0; ii < sample_count; ii++) {
    int accel_temp[3] = {0, 0, 0};
    readBytes(BNO055_ADDRESS, BNO055_ACC_DATA_X_LSB, 6, &data[0]);  // Read the six raw data registers into data array
    accel_temp[0] = (int) (((int)data[1] << 8) | data[0]) ; // Form signed 16-bit integer for each sample in FIFO
    accel_temp[1] = (int) (((int)data[3] << 8) | data[2]) ;
    accel_temp[2] = (int) (((int)data[5] << 8) | data[4]) ;
    accel_bias[0]  += (long) accel_temp[0];
    accel_bias[1]  += (long) accel_temp[1];
    accel_bias[2]  += (long) accel_temp[2];
    Delay(20);  // at 62.5 Hz ODR, new accel data is available every 16 ms
   }
    accel_bias[0]  /= (long) sample_count;  // get average accel bias in mg
    accel_bias[1]  /= (long) sample_count;
    accel_bias[2]  /= (long) sample_count;
    
    if(accel_bias[2] > 0.0) {
        accel_bias[2] -= (long) 1000;
    }  // Remove gravity from the z-axis accelerometer bias calculation
    else {
        accel_bias[2] += (long) 1000;
    }

    dest1[0] = (float) accel_bias[0];  // save accel biases in mg for use in main program
    dest1[1] = (float) accel_bias[1];  // accel data is 1 LSB/mg
    dest1[2] = (float) accel_bias[2];          

 // In NDF fusion mode, gyro full scale is at +/- 2000 dps, ODR is 32 Hz
   writeByte(BNO055_ADDRESS, BNO055_GYRO_CONFIG_0, Gbw << 3 | GFS_2000DPS );
   writeByte(BNO055_ADDRESS, BNO055_GYRO_CONFIG_1, GPwrMode);for(ii = 0; ii < sample_count; ii++) {
    int gyro_temp[3] = {0, 0, 0};
    readBytes(BNO055_ADDRESS, BNO055_GYR_DATA_X_LSB, 6, &data[0]);  // Read the six raw data registers into data array
    gyro_temp[0] = (int) (((int)data[1] << 8) | data[0]) ;  // Form signed 16-bit integer for each sample in FIFO
    gyro_temp[1] = (int) (((int)data[3] << 8) | data[2]) ;
    gyro_temp[2] = (int) (((int)data[5] << 8) | data[4]) ;
    gyro_bias[0]  += (long) gyro_temp[0];
    gyro_bias[1]  += (long) gyro_temp[1];
    gyro_bias[2]  += (long) gyro_temp[2];
    Delay(35);  // at 32 Hz ODR, new gyro data available every 31 ms
   }
    gyro_bias[0]  /= (long) sample_count;  // get average gyro bias in counts
    gyro_bias[1]  /= (long) sample_count;
    gyro_bias[2]  /= (long) sample_count;
 
    dest2[0] = (float) gyro_bias[0]/16.;  // save gyro biases in dps for use in main program
    dest2[1] = (float) gyro_bias[1]/16.;  // gyro data is 16 LSB/dps
    dest2[2] = (float) gyro_bias[2]/16.;          

  // Return to config mode to write accelerometer biases in offset register
  // This offset register is only used while in fusion mode when accelerometer full-scale is +/- 4g
  writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
  Delay(25);
  
  //write biases to accelerometer offset registers ad 16 LSB/dps
  writeByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_LSB, (int)accel_bias[0] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_MSB, ((int)accel_bias[0] >> 8) & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_LSB, (int)accel_bias[1] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_MSB, ((int)accel_bias[1] >> 8) & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_LSB, (int)accel_bias[2] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_MSB, ((int)accel_bias[2] >> 8) & 0xFF);
  
  // Check that offsets were properly written to offset registers
//  printf("Average accelerometer bias = "); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_X_LSB))); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Y_LSB))); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_ACC_OFFSET_Z_LSB)));

   //write biases to gyro offset registers
  writeByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_LSB, (int)gyro_bias[0] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_MSB, ((int)gyro_bias[0] >> 8) & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_LSB, (int)gyro_bias[1] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_MSB, ((int)gyro_bias[1] >> 8) & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_LSB, (int)gyro_bias[2] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_MSB, ((int)gyro_bias[2] >> 8) & 0xFF);
  
  // Select BNO055 system operation mode
  writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, OPRMode );

 // Check that offsets were properly written to offset registers
//  printf("Average gyro bias = "); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_X_LSB))); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Y_LSB))); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_GYR_OFFSET_Z_LSB)));

   printf("Accel/Gyro Calibration done!");
}

void magCalBNO055(float * dest1){
  char data[6]; // data array to hold mag x, y, z, data
  char ii = 0, sample_count = 0;
  long mag_bias[3] = {0, 0, 0};
  int mag_max[3] = {0, 0, 0}, mag_min[3] = {0, 0, 0};
 
  printf("Mag Calibration: Wave device in a figure eight until done!");
  Delay(4000);
  
  // Select page 0 to read sensors
   writeByte(BNO055_ADDRESS, BNO055_PAGE_ID, 0x00);
   // Select BNO055 system operation mode as NDOF for calibration
   writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
   Delay(25);
   writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, AMG );

 // In NDF fusion mode, mag data is in 16 LSB/microTesla, ODR is 20 Hz in forced mode
   sample_count = 256;
   for(ii = 0; ii < sample_count; ii++) {
    int mag_temp[3] = {0, 0, 0};
    readBytes(BNO055_ADDRESS, BNO055_MAG_DATA_X_LSB, 6, &data[0]);  // Read the six raw data registers into data array
    mag_temp[0] = (int) (((int)data[1] << 8) | data[0]) ;   // Form signed 16-bit integer for each sample in FIFO
    mag_temp[1] = (int) (((int)data[3] << 8) | data[2]) ;
    mag_temp[2] = (int) (((int)data[5] << 8) | data[4]) ;
    for (int jj = 0; jj < 3; jj++) {
      if (ii == 0) {
        mag_max[jj] = mag_temp[jj]; // Offsets may be large enough that mag_temp[i] may not be bipolar! 
        mag_min[jj] = mag_temp[jj]; // This prevents max or min being pinned to 0 if the values are unipolar...
      } else {
        if(mag_temp[jj] > mag_max[jj]) mag_max[jj] = mag_temp[jj];
        if(mag_temp[jj] < mag_min[jj]) mag_min[jj] = mag_temp[jj];
      }
    }
    Delay(105);  // at 10 Hz ODR, new mag data is available every 100 ms
   }

 //   printf("mag x min/max:"); printf(mag_max[0]); printf(mag_min[0]);
 //   printf("mag y min/max:"); printf(mag_max[1]); printf(mag_min[1]);
 //   printf("mag z min/max:"); printf(mag_max[2]); printf(mag_min[2]);

    mag_bias[0]  = (mag_max[0] + mag_min[0])/2;  // get average x mag bias in counts
    mag_bias[1]  = (mag_max[1] + mag_min[1])/2;  // get average y mag bias in counts
    mag_bias[2]  = (mag_max[2] + mag_min[2])/2;  // get average z mag bias in counts
    
    dest1[0] = (float) mag_bias[0] / 1.6;  // save mag biases in mG for use in main program
    dest1[1] = (float) mag_bias[1] / 1.6;  // mag data is 1.6 LSB/mg
    dest1[2] = (float) mag_bias[2] / 1.6;          

  // Return to config mode to write mag biases in offset register
  // This offset register is only used while in fusion mode when magnetometer sensitivity is 16 LSB/microTesla
  writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, CONFIGMODE );
  Delay(25);
  
  //write biases to accelerometer offset registers as 16 LSB/microTesla
  writeByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_LSB, (int)mag_bias[0] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_MSB, ((int)mag_bias[0] >> 8) & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_LSB, (int)mag_bias[1] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_MSB, ((int)mag_bias[1] >> 8) & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_LSB, (int)mag_bias[2] & 0xFF);
  writeByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_MSB, ((int)mag_bias[2] >> 8) & 0xFF);
 
  // Check that offsets were properly written to offset registers
//  printf("Average magnetometer bias = "); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_X_LSB))); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Y_LSB))); 
//  printf((int)((int)readByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_MSB) << 8 | readByte(BNO055_ADDRESS, BNO055_MAG_OFFSET_Z_LSB)));
  // Select BNO055 system operation mode
  writeByte(BNO055_ADDRESS, BNO055_OPR_MODE, OPRMode );
  Delay(25);
  
   printf("Mag Calibration done!");
}

// I2C read/write functions for the BNO055 sensor

char writeByte(char address, char subAddress, char data)
{
//	Wire.beginTransmission(address);  // Initialize the Tx buffer
//	Wire.write(subAddress);           // Put slave register address in Tx buffer
//	Wire.write(data);                 // Put data in Tx buffer
//	Wire.endTransmission();           // Send the Tx buffer
    I2C1_MESSAGE_STATUS status;
    char timeOut = 0;
    char Data[3];
    Data[0] = subAddress;
    Data[1] = data;
    while(status != I2C1_MESSAGE_FAIL)
    {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(  Data,2,address,&status);

        // wait for the message to be sent or status has changed.
        while(status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
    timeOut = 0;  
}

char readByte(char address, char subAddress)
{
	char data; // `data` will store the register data	 
//	Wire.beginTransmission(address);         // Initialize the Tx buffer
//	Wire.write(subAddress);	                 // Put slave register address in Tx buffer
//	Wire.endTransmission(I2C_NOSTOP);        // Send the Tx buffer, but send a restart to keep connection alive
////	Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
////	Wire.requestFrom(address, 1);  // Read one char from slave register address 
//	Wire.requestFrom(address, (size_t) 1);   // Read one char from slave register address 
//	data = Wire.read();                      // Fill Rx buffer with result
    I2C1_MESSAGE_STATUS status;
    char Data[3];
    Data[0] = subAddress;
    char timeOut = 0;
    while(status != I2C1_MESSAGE_FAIL)
    {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(Data,1,address,&status);

        // wait for the message to be sent or status has changed.
        while(status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
    timeOut = 0;
    while(status != I2C1_MESSAGE_FAIL)
    {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterRead(  Data,
                                1,
                                address,
                                &status);

        // wait for the message to be sent or status has changed.
        while(status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
	return Data[0];                             // Return data read from slave register
}

void readBytes(char address, char subAddress, char count, char * dest)
{  
//	Wire.beginTransmission(address);   // Initialize the Tx buffer
//	Wire.write(subAddress);            // Put slave register address in Tx buffer
//	Wire.endTransmission(I2C_NOSTOP);  // Send the Tx buffer, but send a restart to keep connection alive
////	Wire.endTransmission(false);       // Send the Tx buffer, but send a restart to keep connection alive
//	char i = 0;
////        Wire.requestFrom(address, count);  // Read chars from slave register address 
//        Wire.requestFrom(address, (size_t) count);  // Read chars from slave register address 
//	while (Wire.available()) {
//        dest[i++] = Wire.read(); }         // Put read results in the Rx buffer
    I2C1_MESSAGE_STATUS status;
    char timeOut = 0;
    char Data[3];
    Data[0] = subAddress;
    while(status != I2C1_MESSAGE_FAIL)
    {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterWrite(Data,1,address,&status);

        // wait for the message to be sent or status has changed.
        while(status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
    timeOut = 0;
    while(status != I2C1_MESSAGE_FAIL)
    {
        // write one byte to EEPROM (3 is the number of bytes to write)
        I2C1_MasterRead(  dest,
                                count,
                                address,
                                &status);

        // wait for the message to be sent or status has changed.
        while(status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
}
        
//void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
//{
//    float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   // short name local variable for readability
//    float norm;
//    float hx, hy, _2bx, _2bz;
//    float s1, s2, s3, s4;
//    float qDot1, qDot2, qDot3, qDot4;
//
//    // Auxiliary variables to avoid repeated arithmetic
//    float _2q1mx;
//    float _2q1my;
//    float _2q1mz;
//    float _2q2mx;
//    float _4bx;
//    float _4bz;
//    float _2q1 = 2.0f * q1;
//    float _2q2 = 2.0f * q2;
//    float _2q3 = 2.0f * q3;
//    float _2q4 = 2.0f * q4;
//    float _2q1q3 = 2.0f * q1 * q3;
//    float _2q3q4 = 2.0f * q3 * q4;
//    float q1q1 = q1 * q1;
//    float q1q2 = q1 * q2;
//    float q1q3 = q1 * q3;
//    float q1q4 = q1 * q4;
//    float q2q2 = q2 * q2;
//    float q2q3 = q2 * q3;
//    float q2q4 = q2 * q4;
//    float q3q3 = q3 * q3;
//    float q3q4 = q3 * q4;
//    float q4q4 = q4 * q4;
//
//    // Normalise accelerometer measurement
//    norm = sqrt(ax * ax + ay * ay + az * az);
//    if (norm == 0.0f) return; // handle NaN
//    norm = 1.0f/norm;
//    ax *= norm;
//    ay *= norm;
//    az *= norm;
//
//    // Normalise magnetometer measurement
//    norm = sqrt(mx * mx + my * my + mz * mz);
//    if (norm == 0.0f) return; // handle NaN
//    norm = 1.0f/norm;
//    mx *= norm;
//    my *= norm;
//    mz *= norm;
//
//    // Reference direction of Earth's magnetic field
//    _2q1mx = 2.0f * q1 * mx;
//    _2q1my = 2.0f * q1 * my;
//    _2q1mz = 2.0f * q1 * mz;
//    _2q2mx = 2.0f * q2 * mx;
//    hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
//    hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
//    _2bx = sqrt(hx * hx + hy * hy);
//    _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
//    _4bx = 2.0f * _2bx;
//    _4bz = 2.0f * _2bz;
//
//    // Gradient decent algorithm corrective step
//    float i1 = ((2.0f * q2q4) - _2q1q3 - ax);
//    float i2 = ((2.0f * q1q2) + _2q3q4 - ay);
//    float i3 = (_2bx * (0.5f - q3q3 - q4q4));
//    float i4 = ((-_2bx * q4) + (_2bz * q2));
//    //s1 = -_2q3 * (i1) + _2q2 * (i2) - _2bz * q3 * (i3) + _2bz * (q2q4 - q1q3) - mx) + (i4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
//    //s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
//    //s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
//    //s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
//    norm = sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
//    norm = 1.0f/norm;
//    s1 *= norm;
//    s2 *= norm;
//    s3 *= norm;
//    s4 *= norm;
//
//    // Compute rate of change of quaternion
//    qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
//    qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
//    qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
//    qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;
//
//    // Integrate to yield quaternion
//    q1 += qDot1 * deltat;
//    q2 += qDot2 * deltat;
//    q3 += qDot3 * deltat;
//    q4 += qDot4 * deltat;
//    norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
//    norm = 1.0f/norm;
//    q[0] = q1 * norm;
//    q[1] = q2 * norm;
//    q[2] = q3 * norm;
//    q[3] = q4 * norm;
//
//}