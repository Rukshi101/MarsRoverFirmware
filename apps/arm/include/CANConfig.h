#pragma once

#include "CANInterface.h"
#include "CANMsg.h"
#include "hw_bridge.h"

static mbed_error_status_t armSetControlMode(CANMsg& msg);
static mbed_error_status_t armSetJointPIDParams(CANMsg& msg);

namespace CANConfig {

using namespace HWBRIDGE;

static CANMsgMap rxStreamedMsgMap = {
    {CANID::ARM_SET_JOINT_POSITION,
     {
         {CANSIGNAL::ARM_TURNTABLE_SET_POSITION,
          (CANSignalValue_t)ARM_TURNTABLE_SET_POSITION_VALUES::ARM_TURNTABLE_SET_POSITION_SNA},
         {CANSIGNAL::ARM_SHOULDER_SET_POSITION,
          (CANSignalValue_t)ARM_SHOULDER_SET_POSITION_VALUES::ARM_SHOULDER_SET_POSITION_SNA},
         {CANSIGNAL::ARM_ELBOW_SET_POSITION,
          (CANSignalValue_t)ARM_ELBOW_SET_POSITION_VALUES::ARM_ELBOW_SET_POSITION_SNA},
         {CANSIGNAL::ARM_LEFT_WRIST_SET_POSITION,
          (CANSignalValue_t)ARM_LEFT_WRIST_SET_POSITION_VALUES::ARM_LEFT_WRIST_SET_POSITION_SNA},
         {CANSIGNAL::ARM_RIGHT_WRIST_SET_POSITION,
          (CANSignalValue_t)ARM_RIGHT_WRIST_SET_POSITION_VALUES::ARM_RIGHT_WRIST_SET_POSITION_SNA},
         {CANSIGNAL::ARM_CLAW_SET_POSITION, (CANSignalValue_t)ARM_CLAW_SET_POSITION_VALUES::ARM_CLAW_SET_POSITION_SNA},
         {CANSIGNAL::ARM_TOOL_TIP_SET_POSITION,
          (CANSignalValue_t)ARM_TOOL_TIP_SET_POSITION_VALUES::ARM_TOOL_TIP_SET_POSITION_SNA},
     }},
    {CANID::ARM_SET_JOINT_ANGULAR_VELOCITY,
     {
         {CANSIGNAL::ARM_SET_TURNTABLE_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_SET_TURNTABLE_ANGULAR_VELOCITY_VALUES::ARM_SET_TURNTABLE_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_SET_SHOULDER_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_SET_SHOULDER_ANGULAR_VELOCITY_VALUES::ARM_SET_SHOULDER_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_SET_ELBOW_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_SET_ELBOW_ANGULAR_VELOCITY_VALUES::ARM_SET_ELBOW_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_SETLEFT_WRIST_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_SETLEFT_WRIST_ANGULAR_VELOCITY_VALUES::ARM_SETLEFT_WRIST_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_SETRIGHT_WRIST_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_SETRIGHT_WRIST_ANGULAR_VELOCITY_VALUES::ARM_SETRIGHT_WRIST_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_SETCLAW_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_SETCLAW_ANGULAR_VELOCITY_VALUES::ARM_SETCLAW_ANGULAR_VELOCITY_SNA},
     }},
    {CANID::ARM_SET_JOINT_CURRENT,
     {
         {CANSIGNAL::ARM_SET_TURNTABLE_CURRENT,
          (CANSignalValue_t)ARM_SET_TURNTABLE_CURRENT_VALUES::ARM_SET_TURNTABLE_CURRENT_SNA},
         {CANSIGNAL::ARM_SET_SHOULDER_CURRENT,
          (CANSignalValue_t)ARM_SET_SHOULDER_CURRENT_VALUES::ARM_SET_SHOULDER_CURRENT_SNA},
         {CANSIGNAL::ARM_SET_ELBOW_CURRENT, (CANSignalValue_t)ARM_SET_ELBOW_CURRENT_VALUES::ARM_SET_ELBOW_CURRENT_SNA},
         {CANSIGNAL::ARM_SETLEFT_WRIST_CURRENT,
          (CANSignalValue_t)ARM_SETLEFT_WRIST_CURRENT_VALUES::ARM_SETLEFT_WRIST_CURRENT_SNA},
         {CANSIGNAL::ARM_SETRIGHT_WRIST_CURRENT,
          (CANSignalValue_t)ARM_SETRIGHT_WRIST_CURRENT_VALUES::ARM_SETRIGHT_WRIST_CURRENT_SNA},
         {CANSIGNAL::ARM_SETCLAW_CURRENT, (CANSignalValue_t)ARM_SETCLAW_CURRENT_VALUES::ARM_SETCLAW_CURRENT_SNA},
     }},
};

static CANMsgMap txStreamedMsgMap = {
    {CANID::ARM_REPORT_JOINT_POSITION,
     {
         {CANSIGNAL::ARM_REPORT_TURNTABLE_POSITION,
          (CANSignalValue_t)ARM_REPORT_TURNTABLE_POSITION_VALUES::ARM_REPORT_TURNTABLE_POSITION_SNA},
         {CANSIGNAL::ARM_REPORT_SHOULDER_POSITION,
          (CANSignalValue_t)ARM_REPORT_SHOULDER_POSITION_VALUES::ARM_REPORT_SHOULDER_POSITION_SNA},
         {CANSIGNAL::ARM_REPORT_ELBOW_POSITION,
          (CANSignalValue_t)ARM_REPORT_ELBOW_POSITION_VALUES::ARM_REPORT_ELBOW_POSITION_SNA},
         {CANSIGNAL::ARM_REPORT_LEFT_WRIST_POSITION,
          (CANSignalValue_t)ARM_REPORT_LEFT_WRIST_POSITION_VALUES::ARM_REPORT_LEFT_WRIST_POSITION_SNA},
         {CANSIGNAL::ARM_REPORT_RIGHT_WRIST_POSITION,
          (CANSignalValue_t)ARM_REPORT_RIGHT_WRIST_POSITION_VALUES::ARM_REPORT_RIGHT_WRIST_POSITION_SNA},
         {CANSIGNAL::ARM_REPORT_CLAW_POSITION,
          (CANSignalValue_t)ARM_REPORT_CLAW_POSITION_VALUES::ARM_REPORT_CLAW_POSITION_SNA},
     }},
    {CANID::ARM_REPORT_JOINT_ANGULAR_VELOCITY,
     {
         {CANSIGNAL::ARM_REPORT_TURNTABLE_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_REPORT_TURNTABLE_ANGULAR_VELOCITY_VALUES::ARM_REPORT_TURNTABLE_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_REPORT_SHOULDER_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_REPORT_SHOULDER_ANGULAR_VELOCITY_VALUES::ARM_REPORT_SHOULDER_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_REPORT_ELBOW_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_REPORT_ELBOW_ANGULAR_VELOCITY_VALUES::ARM_REPORT_ELBOW_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_REPORT_LEFT_WRIST_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_REPORT_LEFT_WRIST_ANGULAR_VELOCITY_VALUES::ARM_REPORT_LEFT_WRIST_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_REPORT_RIGHT_WRIST_ANGULAR_VELOCITY,
          (CANSignalValue_t)
              ARM_REPORT_RIGHT_WRIST_ANGULAR_VELOCITY_VALUES::ARM_REPORT_RIGHT_WRIST_ANGULAR_VELOCITY_SNA},
         {CANSIGNAL::ARM_REPORT_CLAW_ANGULAR_VELOCITY,
          (CANSignalValue_t)ARM_REPORT_CLAW_ANGULAR_VELOCITY_VALUES::ARM_REPORT_CLAW_ANGULAR_VELOCITY_SNA},
     }},
    {CANID::ARM_REPORT_JOINT_CURRENT,
     {
         {CANSIGNAL::ARM_REPORT_TURNTABLE_CURRENT,
          (CANSignalValue_t)ARM_REPORT_TURNTABLE_CURRENT_VALUES::ARM_REPORT_TURNTABLE_CURRENT_SNA},
         {CANSIGNAL::ARM_REPORT_SHOULDER_CURRENT,
          (CANSignalValue_t)ARM_REPORT_SHOULDER_CURRENT_VALUES::ARM_REPORT_SHOULDER_CURRENT_SNA},
         {CANSIGNAL::ARM_REPORT_ELBOW_CURRENT,
          (CANSignalValue_t)ARM_REPORT_ELBOW_CURRENT_VALUES::ARM_REPORT_ELBOW_CURRENT_SNA},
         {CANSIGNAL::ARM_REPORT_LEFT_WRIST_CURRENT,
          (CANSignalValue_t)ARM_REPORT_LEFT_WRIST_CURRENT_VALUES::ARM_REPORT_LEFT_WRIST_CURRENT_SNA},
         {CANSIGNAL::ARM_REPORT_RIGHT_WRIST_CURRENT,
          (CANSignalValue_t)ARM_REPORT_RIGHT_WRIST_CURRENT_VALUES::ARM_REPORT_RIGHT_WRIST_CURRENT_SNA},
         {CANSIGNAL::ARM_REPORT_CLAW_CURRENT,
          (CANSignalValue_t)ARM_REPORT_CLAW_CURRENT_VALUES::ARM_REPORT_CLAW_CURRENT_SNA},
     }},
    {CANID::ARM_REPORT_FAULTS,
     {
         {CANSIGNAL::ARM_TURNTABLE_ENCODER_STATE,
          (CANSignalValue_t)ARM_TURNTABLE_ENCODER_STATE_VALUES::ARM_TURNTABLE_ENCODER_STATE_SNA},
         {CANSIGNAL::ARM_TURNTABLE_CURRENT_SENSOR_STATE,
          (CANSignalValue_t)ARM_TURNTABLE_CURRENT_SENSOR_STATE_VALUES::ARM_TURNTABLE_CURRENT_SENSOR_STATE_SNA},
         {CANSIGNAL::ARM_SHOULDER_ENCODER_STATE,
          (CANSignalValue_t)ARM_SHOULDER_ENCODER_STATE_VALUES::ARM_SHOULDER_ENCODER_STATE_SNA},
         {CANSIGNAL::ARM_SHOULDER_CURRENT_SENSOR_STATE,
          (CANSignalValue_t)ARM_SHOULDER_CURRENT_SENSOR_STATE_VALUES::ARM_SHOULDER_CURRENT_SENSOR_STATE_SNA},
         {CANSIGNAL::ARM_ELBOW_ENCODER_STATE,
          (CANSignalValue_t)ARM_ELBOW_ENCODER_STATE_VALUES::ARM_ELBOW_ENCODER_STATE_SNA},
         {CANSIGNAL::ARM_ELBOW_CURRENT_SENSOR_STATE,
          (CANSignalValue_t)ARM_ELBOW_CURRENT_SENSOR_STATE_VALUES::ARM_ELBOW_CURRENT_SENSOR_STATE_SNA},
         {CANSIGNAL::ARM_LEFT_WRIST_ENCODER_STATE,
          (CANSignalValue_t)ARM_LEFT_WRIST_ENCODER_STATE_VALUES::ARM_LEFT_WRIST_ENCODER_STATE_SNA},
         {CANSIGNAL::ARM_LEFT_WRIST_CURRENT_SENSOR_STATE,
          (CANSignalValue_t)ARM_LEFT_WRIST_CURRENT_SENSOR_STATE_VALUES::ARM_LEFT_WRIST_CURRENT_SENSOR_STATE_SNA},
         {CANSIGNAL::ARM_RIGHT_WRIST_ENCODER_STATE,
          (CANSignalValue_t)ARM_RIGHT_WRIST_ENCODER_STATE_VALUES::ARM_RIGHT_WRIST_ENCODER_STATE_SNA},
         {CANSIGNAL::ARM_RIGHT_WRIST_CURRENT_SENSOR_STATE,
          (CANSignalValue_t)ARM_RIGHT_WRIST_CURRENT_SENSOR_STATE_VALUES::ARM_RIGHT_WRIST_CURRENT_SENSOR_STATE_SNA},
         {CANSIGNAL::ARM_CLAW_ENCODER_STATE,
          (CANSignalValue_t)ARM_CLAW_ENCODER_STATE_VALUES::ARM_CLAW_ENCODER_STATE_SNA},
         {CANSIGNAL::ARM_CLAW_CURRENT_SENSOR_STATE,
          (CANSignalValue_t)ARM_CLAW_CURRENT_SENSOR_STATE_VALUES::ARM_CLAW_CURRENT_SENSOR_STATE_SNA},
     }},
};

const static CANMsg::CANMsgHandlerMap rxOneShotMsgHandler = {
    {CANID::ARM_SET_CONTROL_MODE, &armSetControlMode},
    {CANID::ARM_SET_JOINT_PID_PARAMS, &armSetJointPIDParams},
};

CANInterface::Config config = {
    // CAN bus pins
    .can1_RX = CAN1_RX,
    .can1_TX = CAN1_TX,
    .can2_RX = CAN2_RX,
    .can2_TX = CAN2_TX,

    // Message maps and handlers
    .rxStreamedMsgMap    = &rxStreamedMsgMap,
    .txStreamedMsgMap    = &txStreamedMsgMap,
    .rxOneShotMsgHandler = &rxOneShotMsgHandler,
};

}  // namespace CANConfig
