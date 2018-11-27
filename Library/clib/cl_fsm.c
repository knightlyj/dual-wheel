#include "cl_fsm.h"

void CL_FsmUpdate(CL_Fsm_t* fsm, uint16_t interval)
{
    CL_StateAction actionFunc;
    CL_StateUpdate updateFunc;

    assert(fsm->curStateIdx < fsm->statesNum);

    if (fsm->initialized == CL_FALSE)
    {
        actionFunc = fsm->states[fsm->curStateIdx].onStart;
        if (actionFunc != CL_NULL)
            actionFunc(fsm);

        fsm->initialized = CL_TRUE;
    }

    updateFunc = fsm->states[fsm->curStateIdx].update;
    if (updateFunc != CL_NULL)
        updateFunc(fsm, interval);
}

void CL_FsmChangeState(CL_Fsm_t* fsm, uint8_t stateIndex)
{
    CL_StateAction actionFunc;
    assert(fsm->curStateIdx < fsm->statesNum);

    if (stateIndex < fsm->statesNum)
    {
        //ֹͣ��ǰ״̬
        actionFunc = fsm->states[fsm->curStateIdx].onStop;
        if (actionFunc != CL_NULL)
            actionFunc(fsm);

        //��ʼ��״̬
        fsm->curStateIdx = stateIndex;
        actionFunc = fsm->states[fsm->curStateIdx].onStart;
        if (actionFunc != CL_NULL)
            actionFunc(fsm);
    }
}

