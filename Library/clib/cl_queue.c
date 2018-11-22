#include "cl_queue.h"
#include "cl_atomic.h"

#define DATA_CPY(DST, SRC, SIZE) memcpy(DST, SRC, SIZE)

CL_RESULT CL_QueueAdd(CL_QueueInfo_t *q, void *data)
{
    if (CL_QueueFull(q))
        return CL_FAILED;

    DATA_CPY((char *)q->data + (q->tail * q->data_size), data, q->data_size);
    q->tail += 1;
    if (q->tail >= q->capacity)
    {
        q->tail = 0;
    }

    atomic_add(&q->length, 1);

    assert(q->head >= 0 && q->head < q->capacity);
    assert(q->tail >= 0 && q->tail < q->capacity);
    assert(q->length >= 0 && q->length <= q->capacity);


    return CL_SUCCESS;
}

CL_RESULT CL_QueuePoll(CL_QueueInfo_t *q, void *data)
{
    if (CL_QueueEmpty(q))
        return CL_FAILED;
    DATA_CPY(data, (char *)q->data + (q->head * q->data_size), q->data_size);
    q->head += 1;
    if (q->head >= q->capacity)
    {
        q->head = 0;
    }

    atomic_add(&q->length, -1);

    assert(q->head >= 0 && q->head < q->capacity);
    assert(q->tail >= 0 && q->tail < q->capacity);
    assert(q->length >= 0 && q->length <= q->capacity);


    return CL_SUCCESS;
}

CL_RESULT CL_QueuePeek(CL_QueueInfo_t *q, void *data)
{
    if (CL_QueueEmpty(q))
        return CL_FAILED;

    DATA_CPY(data, (char *)q->data + (q->head * q->data_size), q->data_size);

    return CL_SUCCESS;
}
