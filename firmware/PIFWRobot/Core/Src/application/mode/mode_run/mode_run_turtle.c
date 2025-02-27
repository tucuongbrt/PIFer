/*
 * Mode_RUN.c
 *
 *  Created on: Oct 12, 2019
 *      Author: 16138
 */

#include "mode_run.h"

#if ROBOT_MODEL==1

//TID(gimu_report);

//static void mode_run_report_callback(void *ctx){
//	mavlink_message_t msg;
//	float rpy[3];
//	imu_get_rpy(rpy);
//	mavlink_msg_evt_rpy_pack(0,0,&msg,rpy[0],rpy[1],rpy[2]);
//	mav_send_msg(&msg);
//}

void mode_run_init(){
	// Hardware initialization
	stepmotor_init();
	imu_init();

	// Periodic task initialization
	// gimu_report = timer_register_callback(mode_run_report_callback, MODE_RUN_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_run_deinit(){
	// Hardware de-initialization
	// timer_unregister_callback(gimu_report);
}

void on_mode_run_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_VELOCITY:
		{
			mavlink_cmd_velocity_t cmd_velocity;
			mavlink_msg_cmd_velocity_decode(msg, &cmd_velocity);
			stepmotor_vw(cmd_velocity.v,  cmd_velocity.omega);
		}
		break;
	case MAVLINK_MSG_ID_DISTANCE:
		{
			float rpy[3];
			mavlink_distance_t distance;

			imu_get_rpy(rpy);
			mavlink_msg_distance_decode(msg, &distance);

			mavlink_msg_measurement_pack(0, 0, msg, distance.node_id, distance.x, distance.y, distance.z, distance.r, rpy[2]);
			mav_send_msg(msg);
		}
		break;
	}
}

#endif
