/* AUTO-GENERATED FILE.  DO NOT MODIFY.
 *
 * This class was automatically generated by the
 * java mavlink generator tool. It should not be modified by hand.
 */

// MESSAGE EVT_GYRO_ACCEL_MAG_CALIBRATED PACKING
package com.MAVLink.protocol;
import com.MAVLink.MAVLinkPacket;
import com.MAVLink.Messages.MAVLinkMessage;
import com.MAVLink.Messages.MAVLinkPayload;
        
/**
 * IMU calibrated value
 */
public class msg_evt_gyro_accel_mag_calibrated extends MAVLinkMessage {

    public static final int MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED = 16;
    public static final int MAVLINK_MSG_LENGTH = 36;
    private static final long serialVersionUID = MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED;

      
    /**
     * Gyro X
     */
    public float gx;
      
    /**
     * Gyro Y
     */
    public float gy;
      
    /**
     * Gyro Z
     */
    public float gz;
      
    /**
     * Accel X
     */
    public float ax;
      
    /**
     * Accel Y
     */
    public float ay;
      
    /**
     * Accel Z
     */
    public float az;
      
    /**
     * Mag X
     */
    public float mx;
      
    /**
     * Mag Y
     */
    public float my;
      
    /**
     * Mag Z
     */
    public float mz;
    

    /**
     * Generates the payload for a mavlink message for a message of this type
     * @return
     */
    @Override
    public MAVLinkPacket pack() {
        MAVLinkPacket packet = new MAVLinkPacket(MAVLINK_MSG_LENGTH,isMavlink2);
        packet.sysid = 255;
        packet.compid = 190;
        packet.msgid = MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED;
        
        packet.payload.putFloat(gx);
        packet.payload.putFloat(gy);
        packet.payload.putFloat(gz);
        packet.payload.putFloat(ax);
        packet.payload.putFloat(ay);
        packet.payload.putFloat(az);
        packet.payload.putFloat(mx);
        packet.payload.putFloat(my);
        packet.payload.putFloat(mz);
        
        if (isMavlink2) {
            
        }
        return packet;
    }

    /**
     * Decode a evt_gyro_accel_mag_calibrated message into this class fields
     *
     * @param payload The message to decode
     */
    @Override
    public void unpack(MAVLinkPayload payload) {
        payload.resetIndex();
        
        this.gx = payload.getFloat();
        this.gy = payload.getFloat();
        this.gz = payload.getFloat();
        this.ax = payload.getFloat();
        this.ay = payload.getFloat();
        this.az = payload.getFloat();
        this.mx = payload.getFloat();
        this.my = payload.getFloat();
        this.mz = payload.getFloat();
        
        if (isMavlink2) {
            
        }
    }

    /**
     * Constructor for a new message, just initializes the msgid
     */
    public msg_evt_gyro_accel_mag_calibrated() {
        this.msgid = MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED;
    }
    
    /**
     * Constructor for a new message, initializes msgid and all payload variables
     */
    public msg_evt_gyro_accel_mag_calibrated( float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz) {
        this.msgid = MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED;

        this.gx = gx;
        this.gy = gy;
        this.gz = gz;
        this.ax = ax;
        this.ay = ay;
        this.az = az;
        this.mx = mx;
        this.my = my;
        this.mz = mz;
        
    }
    
    /**
     * Constructor for a new message, initializes everything
     */
    public msg_evt_gyro_accel_mag_calibrated( float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, int sysid, int compid, boolean isMavlink2) {
        this.msgid = MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED;
        this.sysid = sysid;
        this.compid = compid;
        this.isMavlink2 = isMavlink2;

        this.gx = gx;
        this.gy = gy;
        this.gz = gz;
        this.ax = ax;
        this.ay = ay;
        this.az = az;
        this.mx = mx;
        this.my = my;
        this.mz = mz;
        
    }

    /**
     * Constructor for a new message, initializes the message with the payload
     * from a mavlink packet
     *
     */
    public msg_evt_gyro_accel_mag_calibrated(MAVLinkPacket mavLinkPacket) {
        this.msgid = MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED;
        
        this.sysid = mavLinkPacket.sysid;
        this.compid = mavLinkPacket.compid;
        this.isMavlink2 = mavLinkPacket.isMavlink2;
        unpack(mavLinkPacket.payload);
    }

                      
    /**
     * Returns a string with the MSG name and data
     */
    @Override
    public String toString() {
        return "MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED - sysid:"+sysid+" compid:"+compid+" gx:"+gx+" gy:"+gy+" gz:"+gz+" ax:"+ax+" ay:"+ay+" az:"+az+" mx:"+mx+" my:"+my+" mz:"+mz+"";
    }
    
    /**
     * Returns a human-readable string of the name of the message
     */
    @Override
    public String name() {
        return "MAVLINK_MSG_ID_EVT_GYRO_ACCEL_MAG_CALIBRATED";
    }
}
        