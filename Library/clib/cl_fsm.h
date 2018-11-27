/**********************************************
    使用例子:

    定义
    CL_FsmState fsmStates[] =
    {
        CL_FSM_STATE(PowerUpStart, PowerUpStop, PowerUpUpdate),      //power up
        CL_FSM_STATE(CL_NULL, CL_NULL, WorkingUpdate),      //working
        CL_FSM_STATE(RebootStart, RebootStop, RebootUpdate),      //reboot
    };

    CL_FSM_DEF_INIT(testFsm, fsmStates);

    调用
    CL_FsmUpdate(&testFsm, interval);
 **********************************************/
#include "cl_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct CL_Fsm CL_Fsm_t;

//------------函数指针原型---------------------
typedef void(*CL_StateAction)(CL_Fsm_t* fsm);
typedef void(*CL_StateUpdate)(CL_Fsm_t* fsm, uint16_t interval); //单位为ms



typedef struct CL_FsmState
{
    CL_StateAction onStart;	//开始
    CL_StateUpdate update;	//update
    CL_StateAction onStop;	//结束
} CL_FsmState_t;

struct CL_Fsm
{
    CL_FsmState_t* states;
    uint8_t statesNum;	//state总数
    uint8_t curStateIdx; //当前状态的索引
    CL_BOOL initialized;
};


extern void CL_FsmUpdate(CL_Fsm_t* fsm, uint16_t interval);
extern void CL_FsmChangeState(CL_Fsm_t* fsm, uint8_t stateIndex);


#define CL_FSM_STATE(start, update, stop) \
    {start, update, stop}

/**
* @brief FSM定义,需要状态数组
*/
#define CL_FSM_DEF_INIT(name, state_array) \
CL_Fsm_t name = {state_array, CL_ARRAY_LENGTH(state_array), 0, CL_FALSE};

/**
* @brief 同上,但是用来声明
*/
#define CL_FSM_DECL(name) \
extern CL_Fsm name;

#ifdef __cplusplus
}
#endif


