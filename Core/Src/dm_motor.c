#include "dm_motor.h"
#include "stm32f4xx_hal.h"

/* 电机列表，存储所有初始化完成的电机 */
static DM_Motor_t motorTable[DM_MOTOR_MAX_NUM] = {0};
static uint8_t i = 0;

/**
 * @brief   整型变为浮点型
 * @param   input   输入的整形数
 * @param   min     映射区间的左边界
 * @param   max     映射区间的右边界
 * @param   bits    映射区间的位数
 * @return  返回真实的大小
 */
static float uint2float(uint32_t input, float min, float max, uint8_t bits) {
    return ((float) input / (float) ((1 << bits) - 1)) * (max - min) + min;
}

/**
 * @brief   浮点变为整型
 * @param   input   输入的整形数
 * @param   min     映射区间的左边界
 * @param   max     映射区间的右边界
 * @param   bits    映射区间的位数
 * @return  返回变量在区间中映射的值
 */
static uint32_t float2uint(float input, float min, float max, uint8_t bits) {
    return (uint32_t) ((input - min) / (max - min) * ((1 << bits) - 1));
}

/**
 * @brief   发送CAN的数据帧
 * @param   can_id  帧头的ID号
 * @param   data    发送的数据的首地址
 * @param   size    发送数据的大小(0-8)
 * @return  NULL
 */
__weak void DM_Motor_CanSend(uint16_t can_id, uint8_t *data, uint8_t size) {
    //TODO: 完成对应MCU上的CAN发送实现
}

/**
 * @brief   达秒电机使能
 * @param   motor   电机句柄，注意是指针类型
 * @return  
 */
void DM_Motor_Enable(DM_Motor_t motor) {
    uint16_t offset;
    switch (motor->mode) {
        case MIT:
            offset = 0;
            break;
        case POS_VEL:
            offset = 0x100;
            break;
        case VEL:
            offset = 0x200;
            break;
    }
    if (motor->state == READY) {
        uint8_t txData[8];
        txData[0] = 0xFF;
        txData[1] = 0xFF;
        txData[2] = 0xFF;
        txData[3] = 0xFF;
        txData[4] = 0xFF;
        txData[5] = 0xFF;
        txData[6] = 0xFF;
        txData[7] = 0xFC;
        DM_Motor_CanSend(motor->id + offset, txData, 8);

        motor->state = RUNNING;
    } else return;
}

/**
 * @brief   达秒电机失能
 * @param   motor   电机句柄，注意是指针类型
 * @return  
 */
void DM_Motor_Disable(DM_Motor_t motor) {
    uint16_t offset;
    switch (motor->mode) {
        case MIT:
            offset = 0;
            break;
        case POS_VEL:
            offset = 0x100;
            break;
        case VEL:
            offset = 0x200;
            break;
    }
    if (motor->state == RUNNING) {
        uint8_t txData[8];
        txData[0] = 0xFF;
        txData[1] = 0xFF;
        txData[2] = 0xFF;
        txData[3] = 0xFF;
        txData[4] = 0xFF;
        txData[5] = 0xFF;
        txData[6] = 0xFF;
        txData[7] = 0xFD;
        DM_Motor_CanSend(motor->id + offset, txData, 8);

        motor->state = READY;
    } else return;
}

/**
 * @brief   达秒电机保存0点（设置当前位置为0点）
 * @param   motor   电机句柄，注意是指针类型
 * @return  
 */
void DM_Motor_SaveZore(DM_Motor_t motor) {
    uint16_t offset;
    switch (motor->mode) {
        case MIT:
            offset = 0;
            break;
        case POS_VEL:
            offset = 0x100;
            break;
        case VEL:
            offset = 0x200;
            break;
    }
    if (motor->state == READY) {
        uint8_t txData[8];
        txData[0] = 0xFF;
        txData[1] = 0xFF;
        txData[2] = 0xFF;
        txData[3] = 0xFF;
        txData[4] = 0xFF;
        txData[5] = 0xFF;
        txData[6] = 0xFF;
        txData[7] = 0xFE;
        DM_Motor_CanSend(motor->id + offset, txData, 8);
    } else return;
}

/**
 * @brief   达秒电机清除错误
 * @param   motor   电机句柄，注意是指针类型
 * @return  
 */
void DM_Motor_CleanErr(DM_Motor_t motor) {
    uint16_t offset;
    switch (motor->mode) {
        case MIT:
            offset = 0;
            break;
        case POS_VEL:
            offset = 0x100;
            break;
        case VEL:
            offset = 0x200;
            break;
    }
    if (motor->state == ERR) {
        uint8_t txData[8];
        txData[0] = 0xFF;
        txData[1] = 0xFF;
        txData[2] = 0xFF;
        txData[3] = 0xFF;
        txData[4] = 0xFF;
        txData[5] = 0xFF;
        txData[6] = 0xFF;
        txData[7] = 0xFB;
        DM_Motor_CanSend(motor->id + offset, txData, 8);
        motor->state = READY;
    } else return;
}

/**
 * @brief   达秒电机速度模式控制
 * @param   motor   电机句柄，注意是指针类型
 * @param   vel     目标速度（单位：rad/s）
 * @return  
 */
void DM_Motor_VelCtrl(DM_Motor_t motor, float vel) {
    if (motor->state != RUNNING) {
        return;
    }

    uint8_t *v;

    if ((vel >= motor->minVel) || (vel <= motor->maxVel)) {
        v = (uint8_t *) &vel;
    } else return;

    uint8_t txData[4];

    txData[0] = *v;
    txData[1] = *(v + 1);
    txData[2] = *(v + 2);
    txData[3] = *(v + 3);
    DM_Motor_CanSend(0x200 + motor->id, txData, 4);
}

/**
 * @brief   达秒电机位置速度模式控制
 * @param   motor   电机句柄，注意是指针类型
 * @param   pos     目标位置（单位：rad）
 * @param   vel     目标速度（单位：rad/s）
 * @return  
 */
void DM_Motor_PosVelCtrl(DM_Motor_t motor, float pos, float vel) {
    if (motor->state != RUNNING) {
        return;
    }

    uint8_t *p;
    uint8_t *v;

    if ((pos >= motor->minPos) || (pos <= motor->maxPos)) {
        p = (uint8_t *) &pos;
    } else return;
    if ((vel >= motor->minVel) || (vel <= motor->maxVel)) {
        v = (uint8_t *) &vel;
    } else return;
    uint8_t txData[8];
    txData[0] = *p;
    txData[1] = *(p + 1);
    txData[2] = *(p + 2);
    txData[3] = *(p + 3);
    txData[4] = *v;
    txData[5] = *(v + 1);
    txData[6] = *(v + 2);
    txData[7] = *(v + 3);
    DM_Motor_CanSend(0x100 + motor->id, txData, 8);
}

/**
 * @brief   达秒电机MIT模式控制
 * @param   motor   电机句柄，注意是指针类型
 * @param   pos     目标位置（单位：rad）
 * @param   vel     目标速度（单位：rad/s）
 * @param   tor     目标转矩（单位：N*m）
 * @param   kp      控制的kp参数
 * @param   kd      控制的kd参数
 * @return  
 */
void DM_Motor_MitCtrl(DM_Motor_t motor, float pos, float vel, float tor, float kp, float kd) {
    if (motor->state != RUNNING) {
        return;
    }

    uint16_t posTmp, velTmp, torTmp, kpTmp, kdTmp;
    if ((pos >= motor->minPos) || (pos <= motor->maxPos)) {
        posTmp = float2uint(pos, motor->minPos, motor->maxPos, 16);
    } else return;
    if ((vel >= motor->minVel) || (vel <= motor->maxVel)) {
        velTmp = float2uint(vel, motor->minVel, motor->maxVel, 12);
    } else return;
    if ((tor >= motor->minTor) || (tor <= motor->maxTor)) {
        torTmp = float2uint(tor, motor->minTor, motor->maxTor, 12);
    } else return;
    if ((kp >= DM_MOTOR_MIT_MIN_KP) || (kp <= DM_MOTOR_MIT_MAX_KP)) {
        kpTmp = float2uint(kp, DM_MOTOR_MIT_MIN_KP, DM_MOTOR_MIT_MAX_KP, 12);
    } else return;
    if ((kd >= DM_MOTOR_MIT_MIN_KD) || (kd <= DM_MOTOR_MIT_MAX_KD)) {
        kdTmp = float2uint(kd, DM_MOTOR_MIT_MIN_KD, DM_MOTOR_MIT_MAX_KD, 12);
    } else return;

    uint8_t txData[8];
    txData[0] = (uint8_t) (posTmp >> 8);
    txData[1] = (uint8_t) posTmp;
    txData[2] = (uint8_t) (velTmp >> 4);
    txData[3] = (uint8_t) ((velTmp & 0xF) << 4) | (uint8_t) (kpTmp >> 8);
    txData[4] = (uint8_t) kpTmp;
    txData[5] = (uint8_t) (kdTmp >> 4);
    txData[6] = (uint8_t) ((kdTmp & 0xF) << 4) | (uint8_t) (torTmp >> 8);
    txData[7] = (uint8_t) torTmp;
    DM_Motor_CanSend(motor->id, txData, 8);
}

/**
 * @brief   达秒电机句柄初始化
 * @param   motor   电机句柄，注意是指针类型
 * @param   id      电机的canId号
 * @param   mode    电机控制模式
 * @param   minPos/maxPos   设定的最小最大位置参数
 * @param   minVel/maxVel   设定的最小最大速度参数
 * @param   minTor/maxTor   设定的最小最大转矩参数
 * @return  
 */
void DM_Motor_Init(DM_Motor_t motor, uint16_t id, enum DM_CtrlMode mode,
                   float minPos, float maxPos,
                   float minVel, float maxVel,
                   float minTor, float maxTor) {
    if (motor == 0) {
        return;
    }

    motor->id = id;
    motor->mode = mode;
    motor->minPos = minPos;
    motor->maxPos = maxPos;
    motor->minVel = minVel;
    motor->maxVel = maxVel;
    motor->minTor = minTor;
    motor->maxTor = maxTor;

    motor->state = READY;
    /* 添加到列表里面方便管理 */
    motorTable[i] = motor;
    i++;
    if (i >= 16) {
        return;
    }
}

/**
 * @brief   达秒电机中断处理函数，当接收到CAN ID  为主机ID的时候进入
 * @param   data    接收到的CAN帧的数据段
 * @return  成功为HAL_OK,失败为HAL_ERROR
 */
void DM_Motor_RecieveHandle(uint8_t *data) {
    uint8_t id = (uint8_t) (data[0] & 0x0F);
    /* 从id号获取对应的句柄 */
    DM_Motor_t curMotor;
    for (uint8_t m = 0; m < 16; m++) {
        if (motorTable[m]->id == id) {
            curMotor = motorTable[m];
        }
    }
    /* 读取数据 */
    uint16_t posTmp, velTmp, torTmp;
    posTmp = (data[1] << 8) | data[2];
    velTmp = (data[3] << 4) | (data[4] >> 4);
    torTmp = ((data[4] & 0xF) << 8) | data[5];

    curMotor->err = data[0] >> 4;
    curMotor->pos = uint2float(posTmp, curMotor->minPos, curMotor->maxPos, 16);
    curMotor->vel = uint2float(velTmp, curMotor->minVel, curMotor->maxVel, 12);
    curMotor->tor = uint2float(torTmp, curMotor->minTor, curMotor->maxTor, 12);
    curMotor->mosTemp = data[6];
    curMotor->rotorTemp = data[7];

    if (curMotor->err != 0) {
        curMotor->state = ERR;
    }
}
