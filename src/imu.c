#include"imu.h"

int imufd;

void IMU_Init(){

	imufd = wiringPiI2CSetup(Device_Address);   /*Initializes I2C with device Address*/
	wiringPiI2CWriteReg8 (imufd, SMPLRT_DIV, 0x07);	/* Write to sample rate register */
	wiringPiI2CWriteReg8 (imufd, PWR_MGMT_1, 0x01);	/* Write to power management register */
	wiringPiI2CWriteReg8 (imufd, CONFIG, 0);		/* Write to Configuration register */
	wiringPiI2CWriteReg8 (imufd, GYRO_CONFIG, 24);	/* Write to Gyro Configuration register */
	wiringPiI2CWriteReg8 (imufd, INT_ENABLE, 0x01);	/*Write to interrupt enable register */

}




short read_raw_data(int addr){
	short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(imufd, addr);
	low_byte = wiringPiI2CReadReg8(imufd, addr+1);
	value = (high_byte << 8) | low_byte;
	return value;
}




void ms_delay(int val){
	int i,j;
	for(i=0;i<=val;i++)
		for(j=0;j<1200;j++);
}




float* read_accel_data(){
    float Ax=0, Ay=0, Az=0;
    float Acc_x,Acc_y,Acc_z;
    static float Accel_data[] = {0,0,0}; 
    /*Read raw value of Accelerometer and gyroscope from MPU6050*/
    Acc_x = read_raw_data(ACCEL_XOUT_H);
    Acc_y = read_raw_data(ACCEL_YOUT_H);
    Acc_z = read_raw_data(ACCEL_ZOUT_H);

    /* Divide raw value by sensitivity scale factor */
    Ax = Acc_x/16384.0;
    Ay = Acc_y/16384.0;
    Az = Acc_z/16384.0;

    Accel_data[0] = Ax;
    Accel_data[1] = Ay;
    Accel_data[2] = Az;
    // printf("Accel Data: X=%.2f, Y=%.2f, Z=%.2f\n", Accel_data[0], Accel_data[1], Accel_data[2]);
    return Accel_data;
    

}



float* read_gyro_data(){

    float Gx=0, Gy=0, Gz=0;
    float Gyro_x,Gyro_y,Gyro_z;
    static float Gyro_data[] = {0,0,0};
    
    Gyro_x = read_raw_data(GYRO_XOUT_H);
    Gyro_y = read_raw_data(GYRO_YOUT_H);
    Gyro_z = read_raw_data(GYRO_ZOUT_H);

    /* Divide raw value by sensitivity scale factor */
    Gx = Gyro_x/131.0;
    Gy = Gyro_y/131.0;
    Gz = Gyro_z/131.0;

    Gyro_data[0] = Gx;
    Gyro_data[1] = Gy;
    Gyro_data[2] = Gz;

    // printf("Gyro Data: X=%.2f, Y=%.2f, Z=%.2f\n", Gyro_data[0], Gyro_data[1], Gyro_data[2]);

    return Gyro_data;


}



void* imu_thread(void *arg) {
    while (1) {
        float *acc = read_accel_data();
        float *gyro = read_gyro_data();

        printf("ACC -> X: %.2f Y: %.2f Z: %.2f | ",
               acc[0], acc[1], acc[2]);

        printf("GYRO -> X: %.2f Y: %.2f Z: %.2f\n",
               gyro[0], gyro[1], gyro[2]);

        ms_delay(10000); // Delay for 1 second
        }

    return NULL;
}

int start_imu_thread(void) {
    pthread_t imu_tid;

    IMU_Init();

    if (pthread_create(&imu_tid, NULL, imu_thread, NULL) != 0) {
        perror("Failed to create IMU thread");
        return -1;
    }

    if (pthread_join(imu_tid, NULL) != 0) {
        perror("Failed to join IMU thread");
        return -1;
    }

    return 0;
}