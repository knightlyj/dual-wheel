/**********************************************
    ʹ������:

    ����
    CL_FsmState fsmStates[] =
    {
        CL_FSM_STATE(PowerUpStart, PowerUpStop, PowerUpUpdate),      //power up
        CL_FSM_STATE(CL_NULL, CL_NULL, WorkingUpdate),      //working
        CL_FSM_STATE(RebootStart, RebootStop, RebootUpdate),      //reboot
    };

    CL_FSM_DEF_INIT(testFsm, fsmStates);

    ����
    CL_FsmUpdate(&testFsm, interval);
 **********************************************/
#include "cl_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct CL_Fsm CL_Fsm_t;

//------------����ָ��ԭ��---------------------
typedef void(*CL_StateAction)(CL_Fsm_t* fsm);
typedef void(*CL_StateUpdate)(CL_Fsm_t* fsm, uint16_t interval); //��λΪms



typedef struct CL_FsmState
{
    CL_StateAction onStart;	//��ʼ
    CL_StateUpdate update;	//update
    CL_StateAction onStop;	//����
} CL_FsmState_t;

struct CL_Fsm
{
    CL_FsmState_t* states;
    uint8_t statesNum;	//state����
    uint8_t curStateIdx; //��ǰ״̬������
    CL_BOOL initialized;
};


extern void CL_FsmUpdate(CL_Fsm_t* fsm, uint16_t interval);
extern void CL_FsmChangeState(CL_Fsm_t* fsm, uint8_t stateIndex);


#define CL_FSM_STATE(start, update, stop) \
    {start, update, stop}

/**
* @brief FSM����,��Ҫ״̬����
*/
#define CL_FSM_DEF_INIT(name, state_array) \
CL_Fsm_t name = {state_array, CL_ARRAY_LENGTH(state_array), 0, CL_FALSE};

/**
* @brief ͬ��,������������
*/
#define CL_FSM_DECL(name) \
extern CL_Fsm name;

#ifdef __cplusplus
}
#endif


