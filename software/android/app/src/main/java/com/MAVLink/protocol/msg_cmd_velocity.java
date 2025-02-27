/* AUTO-GENERATED FILE.  DO NOT MODIFY.
 *
 * This class was automatically generated by the
 * java mavlink generator tool. It should not be modified by hand.
 */

// MESSAGE CMD_VELOCITY PACKING
package com.MAVLink.protocol;
import com.MAVLink.MAVLinkPacket;
import com.MAVLink.Messages.MAVLinkMessage;
import com.MAVLink.Messages.MAVLinkPayload;
        
/**
 * Velocity command. No need a respond message for confimation
 */
public class msg_cmd_velocity extends MAVLinkMessage {

    public static final int MAVLINK_MSG_ID_CMD_VELOCITY = 3;
    public static final int MAVLINK_MSG_LENGTH = 8;
    private static final long serialVersionUID = MAVLINK_MSG_ID_CMD_VELOCITY;

      
    /**
     * Velocity
     */
    public float v;
      
    /**
     * Omega
     */
    public float omega;
    

    /**
     * Generates the payload for a mavlink message for a message of this type
     * @return
     */
    @Override
    public MAVLinkPacket pack() {
        MAVLinkPacket packet = new MAVLinkPacket(MAVLINK_MSG_LENGTH,isMavlink2);
        packet.sysid = 255;
        packet.compid = 190;
        packet.msgid = MAVLINK_MSG_ID_CMD_VELOCITY;
        
        packet.payload.putFloat(v);
        packet.payload.putFloat(omega);
        
        if (isMavlink2) {
            
        }
        return packet;
    }

    /**
     * Decode a cmd_velocity message into this class fields
     *
     * @param payload The message to decode
     */
    @Override
    public void unpack(MAVLinkPayload payload) {
        payload.resetIndex();
        
        this.v = payload.getFloat();
        this.omega = payload.getFloat();
        
        if (isMavlink2) {
            
        }
    }

    /**
     * Constructor for a new message, just initializes the msgid
     */
    public msg_cmd_velocity() {
        this.msgid = MAVLINK_MSG_ID_CMD_VELOCITY;
    }
    
    /**
     * Constructor for a new message, initializes msgid and all payload variables
     */
    public msg_cmd_velocity( float v, float omega) {
        this.msgid = MAVLINK_MSG_ID_CMD_VELOCITY;

        this.v = v;
        this.omega = omega;
        
    }
    
    /**
     * Constructor for a new message, initializes everything
     */
    public msg_cmd_velocity( float v, float omega, int sysid, int compid, boolean isMavlink2) {
        this.msgid = MAVLINK_MSG_ID_CMD_VELOCITY;
        this.sysid = sysid;
        this.compid = compid;
        this.isMavlink2 = isMavlink2;

        this.v = v;
        this.omega = omega;
        
    }

    /**
     * Constructor for a new message, initializes the message with the payload
     * from a mavlink packet
     *
     */
    public msg_cmd_velocity(MAVLinkPacket mavLinkPacket) {
        this.msgid = MAVLINK_MSG_ID_CMD_VELOCITY;
        
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
        return "MAVLINK_MSG_ID_CMD_VELOCITY - sysid:"+sysid+" compid:"+compid+" v:"+v+" omega:"+omega+"";
    }
    
    /**
     * Returns a human-readable string of the name of the message
     */
    @Override
    public String name() {
        return "MAVLINK_MSG_ID_CMD_VELOCITY";
    }
}
        