/*
 * Mode_IMU.c
 *
 *  Created on: Oct 13, 2019
 *      Author: 16138
 */

#include "mode_imu.h"

TID(gtid_imu_raw);
TID(gtid_imu_cal);
TID(gtid_imu_rpy);

static void imu_raw_callback(void* ctx){
	mavlink_message_t msg;
	float raw[9];

	imu_get_gyro_raw(raw);
	imu_get_accel_raw(&raw[3]);
	imu_get_mag_raw(&raw[6]);

	mavlink_msg_evt_gyro_accel_mag_raw_pack(0, 0, &msg, raw[0], raw[1], raw[2], raw[3], raw[4], raw[5], raw[6], raw[7], raw[8]);
	mav_send_msg(&msg);

	float tilt;
	switch(params.tilt_type){
	case ROLL:
		tilt = imu_get_roll();
		break;
	case PITCH:
		tilt = imu_get_pitch();
		break;
	default:
		tilt = 0;
	}
	mavlink_msg_evt_tilt_raw_pack(0,0,&msg,tilt);
	mav_send_msg(&msg);
}

static void imu_cal_callback(void* ctx){
	mavlink_message_t msg;
	float raw[9];

	imu_get_gyro_cal(raw);
	imu_get_accel_cal(&raw[3]);
	imu_get_mag_cal(&raw[6]);

	mavlink_msg_evt_gyro_accel_mag_calibrated_pack(0, 0, &msg, raw[0], raw[1], raw[2], raw[3], raw[4], raw[5], raw[6], raw[7], raw[8]);
	mav_send_msg(&msg);

	float tilt;
	switch(params.tilt_type){
	case ROLL:
		tilt = imu_get_roll();
		break;
	case PITCH:
		tilt = imu_get_pitch();
		break;
	default:
		tilt = 0;
	}
	tilt -= params.tilt_offset;
	mavlink_msg_evt_tilt_cal_pack(0,0,&msg,tilt);
	mav_send_msg(&msg);
}

static void imu_rpy_callback(void* ctx){
	mavlink_message_t msg;;
	float rpy[3];
	imu_get_rpy(rpy);
	mavlink_msg_evt_rpy_pack(0,0,&msg,rpy[0],rpy[1],rpy[2]);
	mav_send_msg(&msg);
}

static int load_imu_params(){
	// Load parameters from non-volatile memory
	params_load();

	// Send parameters to GCS
	mavlink_message_t msg;

	mavlink_msg_gyro_params_pack(0,0,&msg, params.gx_bias, params.gy_bias, params.gz_bias);
	mav_send_msg(&msg);

	mavlink_msg_accel_params_pack(0,0,&msg, params.ax_bias, params.ay_bias, params.az_bias);
	mav_send_msg(&msg);

	mavlink_msg_mag_params_pack(0,0,&msg, params.mx_bias, params.my_bias, params.mz_bias, params.mx_scale, params.my_scale, params.mz_scale);
	mav_send_msg(&msg);

	mavlink_msg_filter_params_pack(0,0,&msg, params.tilt_type, params.tilt_offset, params.g_believe, params.complementary_gain, params.madgwick_beta);
	mav_send_msg(&msg);

	return 0;
}

static int save_imu_params(){
	// Save parameters to non-volatile memory
	params_save();

	return 0;
}

void mode_imu_init(){
	// Hardware initialization
	imu_init();

	// Periodic task initialization
	gtid_imu_raw = timer_register_callback(imu_raw_callback, IMU_RAW_RP_PERIOD, 0, TIMER_MODE_REPEAT);
	gtid_imu_cal = timer_register_callback(imu_cal_callback, IMU_CAL_RP_PERIOD, 0, TIMER_MODE_REPEAT);
	gtid_imu_rpy = timer_register_callback(imu_rpy_callback, IMU_RPY_RP_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_imu_deinit(){
	// Hardware de-initialization
	imu_deinit();

	// Periodic task initialization
	timer_unregister_callback(gtid_imu_raw);
	timer_unregister_callback(gtid_imu_cal);
	timer_unregister_callback(gtid_imu_rpy);
}

void on_mode_imu_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_PARAMS:
		{
			mavlink_cmd_params_t cmd_msg;
			mavlink_msg_cmd_params_decode(msg, &cmd_msg);
			if(cmd_msg.cmd_params == CMD_LOAD) {
				if(load_imu_params() < 0) respond_error();
				else respond_ok();
			}
			else if(cmd_msg.cmd_params == CMD_SAVE) {
				if(save_imu_params() < 0) respond_error();
				else respond_ok();
			}
		}
	break;
	case MAVLINK_MSG_ID_GYRO_PARAMS:
	{
		mavlink_gyro_params_t params_msg;
		mavlink_msg_gyro_params_decode(msg,&params_msg);
		params.gx_bias = params_msg.gyro_bias_x;
		params.gy_bias = params_msg.gyro_bias_y;
		params.gz_bias = params_msg.gyro_bias_z;
		respond_ok();
	}
	break;
	case MAVLINK_MSG_ID_ACCEL_PARAMS:
	{
		mavlink_accel_params_t params_msg;
		mavlink_msg_accel_params_decode(msg,&params_msg);
		params.ax_bias = params_msg.accel_bias_x;
		params.ay_bias = params_msg.accel_bias_y;
		params.az_bias = params_msg.accel_bias_z;
		respond_ok();
	}
	break;
	case MAVLINK_MSG_ID_MAG_PARAMS:
	{
		mavlink_mag_params_t params_msg;
		mavlink_msg_mag_params_decode(msg,&params_msg);
		params.mx_bias = params_msg.mag_bias_x;
		params.my_bias = params_msg.mag_bias_y;
		params.mz_bias = params_msg.mag_bias_z;
		params.mx_scale = params_msg.mag_scale_x;
		params.my_scale = params_msg.mag_scale_y;
		params.mz_scale = params_msg.mag_scale_z;
		respond_ok();
	}
	break;
	case MAVLINK_MSG_ID_FILTER_PARAMS:
	{
		mavlink_filter_params_t filter_params_msg;
		mavlink_msg_filter_params_decode(msg,&filter_params_msg);
		params.tilt_type = filter_params_msg.tilt_type;
		params.g_believe = filter_params_msg.g_believe;
		params.tilt_offset = filter_params_msg.tilt_offset;
		params.complementary_gain = filter_params_msg.complementary_gain;
		params.madgwick_beta = filter_params_msg.madgwick_beta;
		respond_ok();
	}
	break;
	default:
		break;
	}
}
