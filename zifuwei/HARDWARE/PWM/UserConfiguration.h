#ifndef __USER_H
#define __USER_H

#define PWMPeriod   3599

#define MotorOneForward  1
#define MotorTwoForward  0
#define MotorOneBack     0
#define MotorTwoBack     1
#define MotorSpdZero     0

extern void UserTIM_Configuration(void);
extern void UserNVIC_Configuration(void);
extern void  TIM1_Configuration(void);

extern void UserMotorSpeedSetOne(void);
extern void UserMotorSpeedSetTwo(s32 MotorSpeed);
extern void UserMotorSpeedSetThr(s32 MotorSpeed);
extern void UserMotorSpeedSetFou(s32 MotorSpeed);

#endif


















