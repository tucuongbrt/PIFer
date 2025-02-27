/*
 * IMU.c
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */

#ifndef USERCODE_IMU_IMU_C_
#define USERCODE_IMU_IMU_C_

#include <application/imu/imu.h>
#include <application/params/params.h>
#include <application/user_define.h>
#include <math.h>

#include "utils.h"
#include "madgwick/madgwick.h"
#include "complementary/complementary.h"

static float roll;
static float pitch;
static float gam_raw[9];
static float gam_cab[9];

TID(gtid_tilt_callback);
TID(gtid_rpy_callback);

static void tilt_callback(void* ctx){
	if(mpu9250_get_accel_gyro(&gam_raw[0], &gam_raw[1], &gam_raw[2], &gam_raw[3], &gam_raw[4], &gam_raw[5]) < 0) return;

	float accel_roll  = atan2(gam_raw[1], sqrt(gam_raw[0]*gam_raw[0] + gam_raw[2]*gam_raw[2]))*180.f/M_PI;
	float accel_pitch = atan2(-gam_raw[0], sqrt(gam_raw[1]*gam_raw[1] + gam_raw[2]*gam_raw[2]))*180.f/M_PI;
	float roll_rate = (gam_raw[3]-params.gx_bias)*0.001f*TILT_PERIOD_MS;
	float pitch_rate = (gam_raw[4]-params.gy_bias)*0.001f*TILT_PERIOD_MS;
	roll = params.g_believe*(roll+roll_rate) + (1-params.g_believe)*accel_roll;
	pitch = params.g_believe*(pitch+pitch_rate) + (1-params.g_believe)*accel_pitch;
	if(isnan(roll)) roll = 0;
	if(isnan(pitch)) pitch = 0;
}

static void rpy_callback(void* ctx){
	if(mpu9250_get_accel_gyro(&gam_raw[0], &gam_raw[1], &gam_raw[2], &gam_raw[3], &gam_raw[4], &gam_raw[5]) < 0) return;
	if(mpu9250_get_mag(&gam_raw[6], &gam_raw[7], &gam_raw[8]) < 0) return;

	gam_cab[0] = (gam_raw[3] - params.gx_bias)*M_PI/180.0f;
	gam_cab[1] = (gam_raw[4] - params.gy_bias)*M_PI/180.0f;
	gam_cab[2] = (gam_raw[5] - params.gz_bias)*M_PI/180.0f;
	gam_cab[3] = gam_raw[0] - params.ax_bias;
	gam_cab[4] = gam_raw[1] - params.ay_bias;
	gam_cab[5] = gam_raw[2] - params.az_bias;
	gam_cab[6] = (gam_raw[6] - params.mx_bias)/params.mx_scale;
	gam_cab[7] = (gam_raw[7] - params.my_bias)/params.my_scale;
	gam_cab[8] = (gam_raw[8] - params.mz_bias)/params.mz_scale;

	complementary_update(gam_cab[0], gam_cab[1], gam_cab[2],
							gam_cab[3], gam_cab[4], gam_cab[5], gam_cab[6], gam_cab[7], gam_cab[8], 0.001f*RPY_PERIOD_MS);
}


int imu_init(void){
	mpu9250_init();

	gtid_tilt_callback = timer_register_callback(tilt_callback, TILT_PERIOD_MS, 0, TIMER_MODE_REPEAT);
	gtid_rpy_callback = timer_register_callback(rpy_callback, RPY_PERIOD_MS, 0, TIMER_MODE_REPEAT);

	complementary_init();

	return 0;
}

int imu_deinit(void){
	timer_unregister_callback(gtid_tilt_callback);
	timer_unregister_callback(gtid_rpy_callback);
	return 0;
}

int imu_test_connection(){
	return mpu9250_test();
}

float imu_get_roll(void){
	return roll;
}

float imu_get_pitch(void){
	return pitch;
}

float imu_get_yaw(void){
	return 0;
}

int imu_get_rpy(float rpy[3]){
	float q[4];
	complementary_get_q(q);
	quaternion_to_rpy(rpy, q);
	return 0;
}

int imu_get_gyro_raw(float raw[3]){
	raw[0] = gam_raw[3];
	raw[1] = gam_raw[4];
	raw[2] = gam_raw[5];
	return 0;
}

int imu_get_accel_raw(float raw[3]){
	raw[0] = gam_raw[0];
	raw[1] = gam_raw[1];
	raw[2] = gam_raw[2];
	return 0;
}

int imu_get_mag_raw(float raw[3]){
	raw[0] = gam_raw[6];
	raw[1] = gam_raw[7];
	raw[2] = gam_raw[8];
	return 0;
}

int imu_get_gyro_cal(float raw[3]){
	raw[0] = gam_cab[0];
	raw[1] = gam_cab[1];
	raw[2] = gam_cab[2];
	return 0;
}

int imu_get_accel_cal(float raw[3]){
	raw[0] = gam_cab[3];
	raw[1] = gam_cab[4];
	raw[2] = gam_cab[5];
	return 0;
}

int imu_get_mag_cal(float raw[3]){
	raw[0] = gam_cab[6];
	raw[1] = gam_cab[7];
	raw[2] = gam_cab[8];
	return 0;
}


#endif /* USERCODE_IMU_IMU_C_ */
