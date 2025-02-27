#pragma once
// MESSAGE MEASUREMENT PACKING

#define MAVLINK_MSG_ID_MEASUREMENT 29


typedef struct __mavlink_measurement_t {
 float x; /*<  */
 float y; /*<  */
 float z; /*<  */
 float r; /*<  */
 float yaw; /*<  */
} mavlink_measurement_t;

#define MAVLINK_MSG_ID_MEASUREMENT_LEN 20
#define MAVLINK_MSG_ID_MEASUREMENT_MIN_LEN 20
#define MAVLINK_MSG_ID_29_LEN 20
#define MAVLINK_MSG_ID_29_MIN_LEN 20

#define MAVLINK_MSG_ID_MEASUREMENT_CRC 206
#define MAVLINK_MSG_ID_29_CRC 206



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MEASUREMENT { \
    29, \
    "MEASUREMENT", \
    5, \
    {  { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_measurement_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_measurement_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_measurement_t, z) }, \
         { "r", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_measurement_t, r) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_measurement_t, yaw) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MEASUREMENT { \
    "MEASUREMENT", \
    5, \
    {  { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_measurement_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_measurement_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_measurement_t, z) }, \
         { "r", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_measurement_t, r) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_measurement_t, yaw) }, \
         } \
}
#endif

/**
 * @brief Pack a measurement message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x  
 * @param y  
 * @param z  
 * @param r  
 * @param yaw  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_measurement_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float x, float y, float z, float r, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MEASUREMENT_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_float(buf, 12, r);
    _mav_put_float(buf, 16, yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MEASUREMENT_LEN);
#else
    mavlink_measurement_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.r = r;
    packet.yaw = yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MEASUREMENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MEASUREMENT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_MEASUREMENT_LEN, MAVLINK_MSG_ID_MEASUREMENT_CRC);
}

/**
 * @brief Pack a measurement message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param x  
 * @param y  
 * @param z  
 * @param r  
 * @param yaw  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_measurement_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float x,float y,float z,float r,float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MEASUREMENT_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_float(buf, 12, r);
    _mav_put_float(buf, 16, yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MEASUREMENT_LEN);
#else
    mavlink_measurement_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.r = r;
    packet.yaw = yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MEASUREMENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MEASUREMENT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_MEASUREMENT_LEN, MAVLINK_MSG_ID_MEASUREMENT_CRC);
}

/**
 * @brief Encode a measurement struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param measurement C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_measurement_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_measurement_t* measurement)
{
    return mavlink_msg_measurement_pack(system_id, component_id, msg, measurement->x, measurement->y, measurement->z, measurement->r, measurement->yaw);
}

/**
 * @brief Encode a measurement struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param measurement C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_measurement_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_measurement_t* measurement)
{
    return mavlink_msg_measurement_pack_chan(system_id, component_id, chan, msg, measurement->x, measurement->y, measurement->z, measurement->r, measurement->yaw);
}

/**
 * @brief Send a measurement message
 * @param chan MAVLink channel to send the message
 *
 * @param x  
 * @param y  
 * @param z  
 * @param r  
 * @param yaw  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_measurement_send(mavlink_channel_t chan, float x, float y, float z, float r, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MEASUREMENT_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_float(buf, 12, r);
    _mav_put_float(buf, 16, yaw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEASUREMENT, buf, MAVLINK_MSG_ID_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_MEASUREMENT_LEN, MAVLINK_MSG_ID_MEASUREMENT_CRC);
#else
    mavlink_measurement_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.r = r;
    packet.yaw = yaw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEASUREMENT, (const char *)&packet, MAVLINK_MSG_ID_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_MEASUREMENT_LEN, MAVLINK_MSG_ID_MEASUREMENT_CRC);
#endif
}

/**
 * @brief Send a measurement message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_measurement_send_struct(mavlink_channel_t chan, const mavlink_measurement_t* measurement)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_measurement_send(chan, measurement->x, measurement->y, measurement->z, measurement->r, measurement->yaw);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEASUREMENT, (const char *)measurement, MAVLINK_MSG_ID_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_MEASUREMENT_LEN, MAVLINK_MSG_ID_MEASUREMENT_CRC);
#endif
}

#if MAVLINK_MSG_ID_MEASUREMENT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_measurement_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float x, float y, float z, float r, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_float(buf, 12, r);
    _mav_put_float(buf, 16, yaw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEASUREMENT, buf, MAVLINK_MSG_ID_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_MEASUREMENT_LEN, MAVLINK_MSG_ID_MEASUREMENT_CRC);
#else
    mavlink_measurement_t *packet = (mavlink_measurement_t *)msgbuf;
    packet->x = x;
    packet->y = y;
    packet->z = z;
    packet->r = r;
    packet->yaw = yaw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEASUREMENT, (const char *)packet, MAVLINK_MSG_ID_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_MEASUREMENT_LEN, MAVLINK_MSG_ID_MEASUREMENT_CRC);
#endif
}
#endif

#endif

// MESSAGE MEASUREMENT UNPACKING


/**
 * @brief Get field x from measurement message
 *
 * @return  
 */
static inline float mavlink_msg_measurement_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field y from measurement message
 *
 * @return  
 */
static inline float mavlink_msg_measurement_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field z from measurement message
 *
 * @return  
 */
static inline float mavlink_msg_measurement_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field r from measurement message
 *
 * @return  
 */
static inline float mavlink_msg_measurement_get_r(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field yaw from measurement message
 *
 * @return  
 */
static inline float mavlink_msg_measurement_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a measurement message into a struct
 *
 * @param msg The message to decode
 * @param measurement C-struct to decode the message contents into
 */
static inline void mavlink_msg_measurement_decode(const mavlink_message_t* msg, mavlink_measurement_t* measurement)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    measurement->x = mavlink_msg_measurement_get_x(msg);
    measurement->y = mavlink_msg_measurement_get_y(msg);
    measurement->z = mavlink_msg_measurement_get_z(msg);
    measurement->r = mavlink_msg_measurement_get_r(msg);
    measurement->yaw = mavlink_msg_measurement_get_yaw(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MEASUREMENT_LEN? msg->len : MAVLINK_MSG_ID_MEASUREMENT_LEN;
        memset(measurement, 0, MAVLINK_MSG_ID_MEASUREMENT_LEN);
    memcpy(measurement, _MAV_PAYLOAD(msg), len);
#endif
}
