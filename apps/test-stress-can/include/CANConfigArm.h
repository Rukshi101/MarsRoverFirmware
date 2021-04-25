#pragma once

#include "CANInterface.h"
#include "CANMsg.h"
#include "hw_bridge.h"

const HWBRIDGE::CANFILTER targetCANIDFilter             = HWBRIDGE::CANFILTER::ARM_RX_FILTER;
const HWBRIDGE::CANID targetReportDiagnosticsCANID      = HWBRIDGE::CANID::ARM_REPORT_DIAGNOSTICS;
const HWBRIDGE::CANSIGNAL targetReportNumStreamedSignal = HWBRIDGE::CANSIGNAL::ARM_REPORT_NUM_STREAMED_MSGS_RECEIVED;
const HWBRIDGE::CANSIGNAL targetReportNumOneShotsSignal = HWBRIDGE::CANSIGNAL::ARM_REPORT_NUM_ONE_SHOT_MSGS_RECEIVED;
const HWBRIDGE::CANID targetReportFaultsCANID           = HWBRIDGE::CANID::ARM_REPORT_FAULTS;
const HWBRIDGE::CANSIGNAL targetNumCANRXFaultsSignal    = HWBRIDGE::CANSIGNAL::ARM_NUM_CANRX_FAULTS;
const HWBRIDGE::CANSIGNAL targetNumCANTXFaultsSignal    = HWBRIDGE::CANSIGNAL::ARM_NUM_CANTX_FAULTS;

static mbed_error_status_t oneShotHandler(void);
static mbed_error_status_t switchCANBus(void);

namespace CANConfig {

using namespace HWBRIDGE;

static CANMsgMap rxMsgMap = {
    // Streamed messages
    {CANID::ARM_SET_JOINT_POSITION,
     {
         {CANSIGNAL::ARM_SET_TURNTABLE_POSITION, 0},
         {CANSIGNAL::ARM_SET_SHOULDER_POSITION, 0},
         {CANSIGNAL::ARM_SET_ELBOW_POSITION, 0},
         {CANSIGNAL::ARM_SET_LEFT_WRIST_POSITION, 0},
         {CANSIGNAL::ARM_SET_RIGHT_WRIST_POSITION, 0},
         {CANSIGNAL::ARM_SET_CLAW_POSITION, 0},
         {CANSIGNAL::ARM_SET_TOOL_TIP_POSITION, 0},
     }},
    {CANID::ARM_SET_JOINT_ANGULAR_VELOCITY,
     {
         {CANSIGNAL::ARM_SET_TURNTABLE_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_SET_SHOULDER_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_SET_ELBOW_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_SET_LEFT_WRIST_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_SET_RIGHT_WRIST_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_SET_CLAW_ANGULAR_VELOCITY, 0},
     }},
    {CANID::ARM_SET_JOINT_CURRENT,
     {
         {CANSIGNAL::ARM_SET_TURNTABLE_CURRENT, 0},
         {CANSIGNAL::ARM_SET_SHOULDER_CURRENT, 0},
         {CANSIGNAL::ARM_SET_ELBOW_CURRENT, 0},
         {CANSIGNAL::ARM_SET_LEFT_WRIST_CURRENT, 0},
         {CANSIGNAL::ARM_SET_RIGHT_WRIST_CURRENT, 0},
         {CANSIGNAL::ARM_SET_CLAW_CURRENT, 0},
     }},

    // One-shot messages
    {CANID::ARM_SET_CONTROL_MODE,
     {
         {CANSIGNAL::ARM_TURNTABLE_CONTROL_MODE,
          (CANSignalValue_t)ARM_TURNTABLE_CONTROL_MODE_VALUES::ARM_TURNTABLE_CONTROL_MODE_SNA},
         {CANSIGNAL::ARM_SHOULDER_CONTROL_MODE,
          (CANSignalValue_t)ARM_SHOULDER_CONTROL_MODE_VALUES::ARM_SHOULDER_CONTROL_MODE_SNA},
         {CANSIGNAL::ARM_ELBOW_CONTROL_MODE,
          (CANSignalValue_t)ARM_ELBOW_CONTROL_MODE_VALUES::ARM_ELBOW_CONTROL_MODE_SNA},
         {CANSIGNAL::ARM_LEFT_WRIST_CONTROL_MODE,
          (CANSignalValue_t)ARM_LEFT_WRIST_CONTROL_MODE_VALUES::ARM_LEFT_WRIST_CONTROL_MODE_SNA},
         {CANSIGNAL::ARM_RIGHT_WRIST_CONTROL_MODE,
          (CANSignalValue_t)ARM_RIGHT_WRIST_CONTROL_MODE_VALUES::ARM_RIGHT_WRIST_CONTROL_MODE_SNA},
         {CANSIGNAL::ARM_CLAW_CONTROL_MODE, (CANSignalValue_t)ARM_CLAW_CONTROL_MODE_VALUES::ARM_CLAW_CONTROL_MODE_SNA},
     }},
    {CANID::ARM_SET_JOINT_PID_PARAMS,
     {
         {CANSIGNAL::ARM_JOINT_PIDID, (CANSignalValue_t)ARM_JOINT_PIDID_VALUES::ARM_JOINT_PIDID_SNA},
         {CANSIGNAL::ARM_JOINT_PID_PROPORTIONAL_GAIN,
          (CANSignalValue_t)ARM_JOINT_PID_PROPORTIONAL_GAIN_VALUES::ARM_JOINT_PID_PROPORTIONAL_GAIN_SNA},
         {CANSIGNAL::ARM_JOINT_PID_INTEGRAL_GAIN,
          (CANSignalValue_t)ARM_JOINT_PID_INTEGRAL_GAIN_VALUES::ARM_JOINT_PID_INTEGRAL_GAIN_SNA},
         {CANSIGNAL::ARM_JOINT_PID_DERIVATIVE_GAIN,
          (CANSignalValue_t)ARM_JOINT_PID_DERIVATIVE_GAIN_VALUES::ARM_JOINT_PID_DERIVATIVE_GAIN_SNA},
         {CANSIGNAL::ARM_JOINT_PID_DEADZONE,
          (CANSignalValue_t)ARM_JOINT_PID_DEADZONE_VALUES::ARM_JOINT_PID_DEADZONE_SNA},
     }},
    {CANID::COMMON_SWITCH_CAN_BUS,
     {
         {CANSIGNAL::COMMON_CAN_BUS_ID, (CANSignalValue_t)COMMON_CAN_BUS_ID_VALUES::COMMON_CAN_BUS_ID_SNA},
     }},
};

static CANMsgMap txMsgMap = {
    {CANID::ARM_REPORT_JOINT_POSITION,
     {
         {CANSIGNAL::ARM_REPORT_TURNTABLE_POSITION, 0},
         {CANSIGNAL::ARM_REPORT_SHOULDER_POSITION, 0},
         {CANSIGNAL::ARM_REPORT_ELBOW_POSITION, 0},
         {CANSIGNAL::ARM_REPORT_LEFT_WRIST_POSITION, 0},
         {CANSIGNAL::ARM_REPORT_RIGHT_WRIST_POSITION, 0},
         {CANSIGNAL::ARM_REPORT_CLAW_POSITION, 0},
     }},
    {CANID::ARM_REPORT_JOINT_ANGULAR_VELOCITY,
     {
         {CANSIGNAL::ARM_REPORT_TURNTABLE_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_REPORT_SHOULDER_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_REPORT_ELBOW_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_REPORT_LEFT_WRIST_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_REPORT_RIGHT_WRIST_ANGULAR_VELOCITY, 0},
         {CANSIGNAL::ARM_REPORT_CLAW_ANGULAR_VELOCITY, 0},
     }},
    {CANID::ARM_REPORT_JOINT_CURRENT,
     {
         {CANSIGNAL::ARM_REPORT_TURNTABLE_CURRENT, 0},
         {CANSIGNAL::ARM_REPORT_SHOULDER_CURRENT, 0},
         {CANSIGNAL::ARM_REPORT_ELBOW_CURRENT, 0},
         {CANSIGNAL::ARM_REPORT_LEFT_WRIST_CURRENT, 0},
         {CANSIGNAL::ARM_REPORT_RIGHT_WRIST_CURRENT, 0},
         {CANSIGNAL::ARM_REPORT_CLAW_CURRENT, 0},
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
         {CANSIGNAL::ARM_NUM_CANRX_FAULTS, 0},
         {CANSIGNAL::ARM_NUM_CANTX_FAULTS, 0},
     }},
    {CANID::ARM_REPORT_DIAGNOSTICS,
     {
         {CANSIGNAL::ARM_REPORT_NUM_STREAMED_MSGS_RECEIVED, 0},
         {CANSIGNAL::ARM_REPORT_NUM_ONE_SHOT_MSGS_RECEIVED, 0},
     }},
};

const static CANMsg::CANMsgHandlerMap rxOneShotMsgHandler = {
    {CANID::ARM_SET_CONTROL_MODE, &oneShotHandler},
    {CANID::ARM_SET_JOINT_PID_PARAMS, &oneShotHandler},
    {CANID::COMMON_SWITCH_CAN_BUS, &switchCANBus},
};

CANInterface::Config config = {
    // CAN bus pins
    .can1_RX = CAN1_RX,
    .can1_TX = CAN1_TX,
    .can2_RX = CAN2_RX,
    .can2_TX = CAN2_TX,

    // Message maps and handlers
    .rxMsgMap            = &rxMsgMap,
    .txMsgMap            = &txMsgMap,
    .rxOneShotMsgHandler = &rxOneShotMsgHandler,
};

}  // namespace CANConfig
