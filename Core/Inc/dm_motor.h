#ifndef __DM_MOTOR_H__
#define __DM_MOTOR_H__

#include "stdint.h"


#define DM_MOTOR_MIT_MIN_KP             0.f
#define DM_MOTOR_MIT_MAX_KP             500.f
#define DM_MOTOR_MIT_MIN_KD             0.f
#define DM_MOTOR_MIT_MAX_KD             5.f

#define DM_MOTOR_MAX_NUM                16

enum DM_CtrlMode {
    MIT,                                    /* MIT模式 */
    POS_VEL,                                /* 位置速度模式 */
    VEL                                     /* 速度模式 */
};

enum DM_State {
    NOT_INIT,                               /* 还未初始化 */
    READY,                                  /* 初始化完毕，还没使能 */
    RUNNING,                                /* 已经使能，可以随时进行控制 */
    ERR                                     /* 错误状态 */
};

struct DM_Motor {
    /* 电机固定的参数 */
    uint16_t id;                     /* 电机的ID号 */
    enum DM_CtrlMode mode;                   /* 电机的控制模式 */
    float minPos;                 /* 限制的最小位置 */
    float maxPos;                 /* 限制的最大位置 */
    float minVel;                 /* 限制的最小速度 */
    float maxVel;                 /* 限制的最大速度 */
    float minTor;                 /* 限制的最小力矩 */
    float maxTor;                 /* 限制的最大力矩 */

    /*  */
    enum DM_State state;                  /* 用于实时更新电机目前的状态 */

    /* 驱动反馈的实时参数 */
    uint8_t err;                    /* 电机的错误码 */
    float pos;                    /* 读取到的当前位置 */
    float vel;                    /* 读取到的当前速度 */
    float tor;                    /* 读取到的当前力矩 */
    int8_t mosTemp;                /* MOS管的平均温度 */
    int8_t rotorTemp;              /* 电机线圈的平均温度 */
};
typedef struct DM_Motor *DM_Motor_t;         /* 定义一个指针类型方便调用 */

void DM_Motor_Send(uint16_t id, uint8_t *data, uint8_t size);

void DM_Motor_Enable(DM_Motor_t motor);

void DM_Motor_Disable(DM_Motor_t motor);

void DM_Motor_SaveZore(DM_Motor_t motor);

void DM_Motor_CleanErr(DM_Motor_t motor);

void DM_Motor_VelCtrl(DM_Motor_t motor, float vel);

void DM_Motor_PosVelCtrl(DM_Motor_t motor, float pos, float vel);

void DM_Motor_MitCtrl(DM_Motor_t motor, float pos, float vel, float tor, float kp, float kd);

void DM_Motor_Init(DM_Motor_t motor, uint16_t id, enum DM_CtrlMode mode,
                   float minPos, float maxPos,
                   float minVel, float maxVel,
                   float minTor, float maxTor);

void DM_Motor_RecieveHandle(uint8_t *data);

#endif
