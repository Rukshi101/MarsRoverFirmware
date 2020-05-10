#include "mbed.h"
#include "mbed_config.h"
#include "can_config.h"
#include "ros_config.h"

#include "ArmConfig.h"
#include "Encoder.h"
#include "EncoderAbsolute_PWM.h"
#include "EncoderRelative_Quadrature.h"
#include "ActuatorController.h"
#include "DifferentialWristController.h"
#include "ClawController.h"
#include "CANMsg.h"
#include "CANBuffer.h"
#include "Servo.h"

/*** ARM COMPONENTS ***/
/**********************/

// Motors
Motor turnTableMotor(MTR_PWM_TRNTBL, MTR_DIR_TRNTBL, false);
Motor shoulderMotor(MTR_PWM_SHLDR, MTR_DIR_SHLDR, false);
Motor elbowMotor(MTR_PWM_ELBW, MTR_DIR_ELBW, false);
Motor wristLeftMotor(MTR_PWM_WRST_LHS, MTR_DIR_WRST_LHS, false);
Motor wristRightMotor(MTR_PWM_WRST_RHS, MTR_DIR_WRST_RHS, false);
Motor clawMotor(MTR_PWM_CLAW, MTR_DIR_CLAW, false);
Servo clawTooltipServo(SRVO_PWM_CLAW, Servo::LIM_SERVO, 180.0, 2.0, 1.0);

// Encoders
EncoderAbsolute_PWM turnTableEncoder(ArmConfig::turnTableEncoderConfig);
EncoderAbsolute_PWM shoulderEncoder(ArmConfig::shoulderEncoderConfig);
EncoderAbsolute_PWM elbowEncoder(ArmConfig::elbowEncoderConfig);
EncoderRelative_Quadrature wristLeftEncoder(ArmConfig::wristLeftEncoderConfig);
EncoderRelative_Quadrature wristRightEncoder(ArmConfig::wristRightEncoderConfig);
EncoderRelative_Quadrature clawEncoder(ArmConfig::clawEncoderConfig);

// Limit switches
DigitalIn turnTableLimLeft(LIM_TRNTBL_LHS);
DigitalIn turnTableLimRight(LIM_TRNTBL_RHS);
DigitalIn elbowLimUp(LIM_ELBW_UP);
DigitalIn elbowLimDown(LIM_ELBW_DN);
DigitalIn wristLimUp(LIM_WRST_UP);
DigitalIn wristLimDown(LIM_WRST_DN);
DigitalIn wristLimCenter(LIM_WRST_CNTR);
DigitalIn clawLimOpen(LIM_CLAW_OPEN);

// Analog inputs
AnalogIn clawForceSensor(FORCE_CLAW);

// Rotary actuators
ActuatorController turnTableActuator(ArmConfig::turnTableActuatorConfig, turnTableMotor, turnTableEncoder, turnTableLimRight, turnTableLimLeft);
ActuatorController shoulderActuator(ArmConfig::shoulderActuatorConfig, shoulderMotor, shoulderEncoder);
ActuatorController elbowActuator(ArmConfig::elbowActuatorConfig, elbowMotor, elbowEncoder, elbowLimDown, elbowLimUp);
ActuatorController wristLeftActuator(ArmConfig::wristLeftActuatorConfig, wristLeftMotor, wristLeftEncoder);
ActuatorController wristRightActuator(ArmConfig::wristRightActuatorConfig, wristRightMotor, wristRightEncoder);

// Complex controllers
DifferentialWristController wristController(wristLeftActuator, wristRightActuator, wristLimUp, wristLimCenter, wristLimDown);
ClawController clawController(ArmConfig::clawActuatorConfig, clawMotor, clawEncoder, clawLimOpen, clawForceSensor, clawTooltipServo, 180.0, 0.0);

/*** ARM COMMAND HANDLER FUNCTIONS ***/
/*************************************/

static mbed_error_status_t setOverrideFlags(CANMsg &msg) {
    uint8_t flags;
    msg.getPayload(flags);

    if (flags & FLAG_DISABLE_LIMIT_SWITCH_CHECKS) {
        // TODO
    } 
    else {

    }

    if (flags & FLAG_DISABLE_ANGLE_BOUNDS_CHECKS) {
        // TODO
    }
    else {

    }

    if (flags & FLAG_DISABLE_FEEDBACK) {
        // TODO
    }
    else {
        
    }

    return MBED_SUCCESS;
}

// Set the control mode of a joint (motor power / velocity / position)
static mbed_error_status_t setControlMode(CANMsg &msg) {
    ActuatorController::t_actuatorControlMode controlMode;
    msg.getPayload(controlMode);

    switch(msg.id) {
        case CANID::SET_TURNTABLE_CONTROL_MODE:
            return turnTableActuator.setControlMode(controlMode);
        case CANID::SET_SHOULDER_CONTROL_MODE:
            return shoulderActuator.setControlMode(controlMode);
        case CANID::SET_ELBOW_CONTROL_MODE:
            return elbowActuator.setControlMode(controlMode);
        case CANID::SET_WRIST_CONTROL_MODE:
            return wristController.setControlMode(controlMode);
        case CANID::SET_CLAW_CONTROL_MODE:
            return clawController.setControlMode(controlMode);
        default:
            return MBED_ERROR_INVALID_ARGUMENT;
    }

    return MBED_SUCCESS;
}

// Set the motion data (motor power / velocity / position) of a joint
static mbed_error_status_t setMotionData(CANMsg &msg) {
    float motionData;
    msg.getPayload(motionData);

    switch(msg.id) {
        case CANID::SET_TURNTABLE_MOTIONDATA:
            return turnTableActuator.setMotionData(motionData);
        case CANID::SET_SHOULDER_MOTIONDATA:
            return shoulderActuator.setMotionData(motionData);
        case CANID::SET_ELBOW_MOTIONDATA:
            return elbowActuator.setMotionData(motionData);
        case CANID::SET_WRIST_PITCH_MOTIONDATA:
            return wristController.setPitchMotionData(motionData);
        case CANID::SET_WRIST_ROLL_MOTIONDATA:
            return wristController.setRollMotionData(motionData);
        case CANID::SET_CLAW_MOTIONDATA:
            return clawController.setMotionData(motionData);
        default:
            return MBED_ERROR_INVALID_ARGUMENT;
    }

    return MBED_SUCCESS;
}

// Run wrist calibration routine
static mbed_error_status_t runWristCalibration(CANMsg &msg) {
    bool runCalibration;
    msg.getPayload(runCalibration);

    if (runCalibration) {
        return wristController.runPositionCalibration();
    }

    return MBED_SUCCESS;
}

// Run claw calibration routine
static mbed_error_status_t runClawCalibration(CANMsg &msg) {
    bool runCalibration;
    msg.getPayload(runCalibration);

    if (runCalibration) {
        return clawController.runPositionCalibration();
    }

    return MBED_SUCCESS;
}

// Deploy or retract tool tip
static mbed_error_status_t setToolTipDeployment(CANMsg &msg) {
    bool extend;
    msg.getPayload(extend);

    if (extend) {
        return clawController.extendToolTip();
    }
    else {
        return clawController.retractToolTip();
    }
}

// Enable or disable PID tuning mode10
static mbed_error_status_t setPIDTuningMode(CANMsg &msg) {
    return MBED_SUCCESS; // TODO
}

// Configure PID parameters
static mbed_error_status_t setPIDParameter(CANMsg &msg) {
    /** -----------------------------------------------
     * | 32 bits  | 8 bits   | 8 bits   |  8 bits     |
     * | data     | vel/pos  | param    |  Actuator ID|
     *  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
    struct __attribute__ ((packed)){
        float value;
        bool velocity;
        uint8_t param;
        uint8_t actuatorID;
    } payload;
    msg >> payload;
    ActuatorController *temp = nullptr;
    switch(payload.actuatorID){
        case ROSID::TURNTABLEACTUATORID:
            temp = &turnTableActuator;
            break;
        case ROSID::SHOULDERACTUATORID:
            temp = &shoulderActuator;
            break;
        case ROSID::ELBOWACTUATORID:
            temp = &elbowActuator;
            break;
        case ROSID::WRISTLEFTACTUATORID:
            temp = &wristLeftActuator;
            break;
        case ROSID::WRISTRIGHTACTUATORID:
            temp = &wristRightActuator;
            break;
        case ROSID::CLAWACTUATORID:
            temp = &clawController;
            break;
        default:
            return MBED_ERROR_INVALID_ARGUMENT;
    }
    switch (msg.id){
        case CANID::SET_JOINT_PID_PID:
            switch(payload.param){
                case ROSID::P:
                    payload.velocity ? temp->setVelocityPID_P(payload.value) :
                    temp->setPositionPID_P(payload.value);
                    return MBED_SUCCESS;
                case ROSID::I:
                    payload.velocity ? temp->setVelocityPID_I(payload.value) :
                    temp->setPositionPID_I(payload.value);
                    return MBED_SUCCESS;
                case ROSID::D:
                    payload.velocity ? temp->setVelocityPID_D(payload.value) :
                    temp->setPositionPID_D(payload.value);
                    return MBED_SUCCESS;                    
                default:
                    return MBED_ERROR_INVALID_ARGUMENT;
            }
        case CANID::SET_JOINT_PID_DEADZONE:
            payload.velocity ? temp->setVelocityPID_DeadZoneError(payload.value) : 
            temp->setPositionPID_DeadZoneError(payload.value);
            return MBED_SUCCESS;
        case CANID::SET_JOINT_PID_BIAS:
            payload.velocity ? temp->setVelocityPID_bias(payload.value) :
            temp->setPositionPID_bias(payload.value);
            return MBED_SUCCESS;
        default:
            return MBED_ERROR_INVALID_ARGUMENT;
    }
}

// Handler function mappings
static CANMsg::CANMsgHandlerMap canHandlerMap = {
    {CANID::SET_OVERRIDE_FLAGS,         &setOverrideFlags},

    {CANID::SET_TURNTABLE_CONTROL_MODE, &setControlMode},
    {CANID::SET_SHOULDER_CONTROL_MODE,  &setControlMode},
    {CANID::SET_ELBOW_CONTROL_MODE,     &setControlMode},
    {CANID::SET_WRIST_CONTROL_MODE,     &setControlMode},
    {CANID::SET_CLAW_CONTROL_MODE,      &setControlMode},

    {CANID::SET_TURNTABLE_MOTIONDATA,   &setMotionData},
    {CANID::SET_SHOULDER_MOTIONDATA,    &setMotionData},
    {CANID::SET_ELBOW_MOTIONDATA,       &setMotionData},
    {CANID::SET_WRIST_PITCH_MOTIONDATA, &setMotionData},
    {CANID::SET_WRIST_ROLL_MOTIONDATA,  &setMotionData},
    {CANID::SET_CLAW_MOTIONDATA,        &setMotionData},
    {CANID::SET_TOOL_TIP_DEPLOYMENT,    &setToolTipDeployment},

    {CANID::RUN_WRIST_CALIBRATION,      &runWristCalibration},
    {CANID::RUN_CLAW_CALIBRATION,       &runClawCalibration},

    {CANID::SET_PID_TUNING_MODE,        &setPIDTuningMode},

    {CANID::SET_JOINT_PID_DEADZONE,     &setPIDParameter},
    {CANID::SET_JOINT_PID_PID,          &setPIDParameter},
    {CANID::SET_JOINT_PID_BIAS,         &setPIDParameter}
};

/*** ARM CANBus ***/
/******************/

// Interface and recieve buffer
CAN can1(CAN1_RX, CAN1_TX, ROVER_CANBUS_FREQUENCY);
// CANBuffer rxCANBuffer(can1, CANBuffer::BufferType::rx);

// Incoming message processor
void rxCANProcessor() {
    CANMsg rxMsg;

    while (true) {
        if (can1.read(rxMsg)) {
            if (canHandlerMap.count(rxMsg.id) > 0) {
                canHandlerMap[rxMsg.id](rxMsg);
            }
            else {
                // TODO: Warn about unsupported CAN command (without flooding)
            }
        }

        // rxCANBuffer.waitFlagsAny(CANBUFFER_FLAG_DATA_READY);

        // if (rxCANBuffer.pop(rxMsg) && (canHandlerMap.find(rxMsg.id) != canHandlerMap.end())) {
        //     if (canHandlerMap.count(rxMsg.id) > 0) {
        //         canHandlerMap[rxMsg.id](rxMsg);
        //     }
        //     else {
        //         // TODO: Warn about unsupported CAN command (without flooding serial)
        //     }
        // }
        
        ThisThread::sleep_for(2);
    }
}

// Outgoing message processor
void txCANProcessor() {
    const int txInterdelay_millisec = 2;
    const int txPeriod_millisec = 10;

    CANMsg txMsg;

    struct __attribute__((__packed__)) motionReport {
        float position;
        float velocity;
    } motionReport;

    while (true) {
        txMsg.id = REPORT_TURNTABLE_MOTION;
        motionReport.position = turnTableActuator.getAngle_Degrees();
        motionReport.velocity = turnTableActuator.getVelocity_DegreesPerSec();
        txMsg.setPayload(motionReport);
        can1.write(txMsg);
        ThisThread::sleep_for(txInterdelay_millisec);

        txMsg.id = REPORT_SHOULDER_MOTION;
        motionReport.position = shoulderActuator.getAngle_Degrees();
        motionReport.velocity = shoulderActuator.getVelocity_DegreesPerSec();
        txMsg.setPayload(motionReport);
        can1.write(txMsg);
        ThisThread::sleep_for(txInterdelay_millisec);

        txMsg.id = REPORT_ELBOW_MOTION;
        motionReport.position = elbowActuator.getAngle_Degrees();
        motionReport.velocity = elbowActuator.getVelocity_DegreesPerSec();
        txMsg.setPayload(motionReport);
        can1.write(txMsg);
        ThisThread::sleep_for(txInterdelay_millisec);

        txMsg.id = REPORT_WRIST_PITCH_MOTION;
        motionReport.position = wristController.getPitchAngle_Degrees();
        motionReport.velocity = wristController.getPitchVelocity_DegreesPerSec();
        txMsg.setPayload(motionReport);
        can1.write(txMsg);
        ThisThread::sleep_for(txInterdelay_millisec);

        txMsg.id = REPORT_WRIST_PITCH_MOTION;
        motionReport.position = wristController.getRollAngle_Degrees();
        motionReport.velocity = wristController.getRollVelocity_DegreesPerSec();
        txMsg.setPayload(motionReport);
        can1.write(txMsg);
        ThisThread::sleep_for(txInterdelay_millisec);

        txMsg.id = REPORT_CLAW_MOTION;
        motionReport.position = clawController.getGapDistance_Cm();
        motionReport.velocity = clawController.getGapVelocity_CmPerSec();
        txMsg.setPayload(motionReport);
        can1.write(txMsg);
        ThisThread::sleep_for(txInterdelay_millisec);

        ThisThread::sleep_for(txPeriod_millisec);
    }
}

Thread rxCANProcessorThread(osPriorityAboveNormal);
Thread txCANProcessorThread(osPriorityBelowNormal);

DigitalOut led1(LED1);

int main()
{
    printf("\r\n\r\n");
    printf("ARM APPLICATION STARTED\r\n");
    printf("=======================\r\n");

    rxCANProcessorThread.start(rxCANProcessor);
    txCANProcessorThread.start(txCANProcessor);

    while (true) {

        // Compute actuator controls
        turnTableActuator.update();
        shoulderActuator.update();
        elbowActuator.update();
        wristController.update();
        clawController.update();

        ThisThread::sleep_for(2);
    }
}
