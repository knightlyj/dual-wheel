/*********************************************************************************
*Description:  ����һ�����ͻ��ζ���,������������Ϊconst(����ʱȷ��)
*Warnings:     add��poll���ܿ���ͬʱ����,������add��poll���ܲ�������
**********************************************************************************/

#pragma once

#include "cl_common.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
* @brief �����������ݽṹ
*/
typedef struct{ 
    void *data; 
    int32_t head;
    int32_t tail;
    int32_t length;
    int32_t capacity;
    int32_t data_size;
} CL_QueueInfo_t;

/** 
 * @brief ���岢��ʼ������
 * @param q_name ������
 * @param capacity ��������
 * @param data_type ������������
 * @param modifier ���ӵ����Σ���static��
 *
 * example: 
 *      CL_QUEUE_DEF_INIT(my_queue, 10, char, static);
 *      ���϶�����һ��static�Ķ��У�������Ϊmy_queue, ����Ϊ10�������е���������Ϊchar
 */
#define CL_QUEUE_DEF_INIT(q_name, capacity, data_type, modifier) \
modifier data_type q_name##_buf[capacity]; \
modifier CL_QueueInfo_t q_name = {q_name##_buf, 0, 0, 0, capacity, sizeof(data_type)};

/** 
 * @brief ͬ��,������������
 */
#define CL_QUEUE_DECL(q_name) \
extern CL_QueueInfo_t q_name;

/** 
 * @brief ���������һ������
 * @param q ����ָ��
 * @param data ��Ҫ������е����ݵ�ָ��
 *
 * @return
 *     FAILED ����ʧ��,һ���Ƕ�������
 *     SUCCESS �����ɹ�
 */
CL_RESULT CL_QueueAdd(CL_QueueInfo_t *q, void *data);

/** 
 * @brief �Ӷ���ͷ����ȡһ������,����������ݴӶ����Ƴ�
 * @param q ����ָ��
 * @param data ָ��,ָ���ȡ���ݴ�ŵ�ַ
 *
 * @return 
 *     FAILED ����ʧ��,һ���Ƕ���Ϊ��
 *     SUCCESS �����ɹ�
 */
CL_RESULT CL_QueuePoll(CL_QueueInfo_t *q, void *data);

/** 
 * @brief ��ȡ����ͷ������,�����Ӷ����Ƴ�������
 * @param q ����ָ��
 * @param data ָ��,ָ���ȡ���ݴ�ŵ�ַ
 *
 * @return 
 *     FAILED ����ʧ��,һ���Ƕ���Ϊ��
 *     SUCCESS �����ɹ�
 */
CL_RESULT CL_QueuePeek(CL_QueueInfo_t *q, void *data);

/** 
 * @brief ��ȡ���е�ǰ����
 * @param q ����ָ��
 *
 * @return 
 *    ���ض��е�ǰ����
 */
CL_STATIC_INLINE int32_t CL_QueueLength(CL_QueueInfo_t *q){
    return q->length;
}

/** 
 * @brief ��ն���
 * @param q ����ָ��
 *
 */
CL_STATIC_INLINE void CL_QueueClear(CL_QueueInfo_t *q){
    q->head = q->tail = 0;
    q->length = 0;
}

/** 
 * @brief ��ȡ��������
 * @param q ����ָ��
 *
 * @return 
 *    ���ض��ж�������
 */
CL_STATIC_INLINE int32_t CL_QueueCapacity(CL_QueueInfo_t *q){
    return q->capacity;
}

/** 
 * @brief �����Ƿ��
 * @param q ����ָ��
 *
 * @return 
 *    TRUE ����Ϊ��
 *    FALSE ���зǿ�
 */
CL_STATIC_INLINE CL_BOOL CL_QueueEmpty(CL_QueueInfo_t *q){
    return (q->length <= 0) ? CL_TRUE : CL_FALSE;
}

/** 
 * @brief �����Ƿ���
 * @param q ����ָ��
 *
 * @return 
 *    TRUE ������
 *    FALSE ����û��
 */
CL_STATIC_INLINE CL_BOOL CL_QueueFull(CL_QueueInfo_t *q){
    return (q->length >= q->capacity) ? CL_TRUE : CL_FALSE;
}

/** 
 * @brief �������ʶ����е�ÿ��Ԫ��
 * @param q_ptr ����ָ��
 * @param data_ptr ָ�����ݵ�ַ��ָ��
 * @param data_type ���ݵ�����
 * 
 * example: 
 *      CL_QUEUE_DEF_INIT(my_queue, 10, char, static);
 *      //���϶�����һ��static�Ķ��У�������Ϊmy_queue, ����Ϊ10�������е���������Ϊchar
 *      char* data;
 *      CL_QUEUE_FOR_EACH(my_queue, data, char)    //�������ʶ�����ÿ������
 *      {
 *          printf("%c", *data);    //��������ݴ�ӡ����               
 *      }
 */
#define CL_QUEUE_FOR_EACH(q_ptr, data_ptr, data_type) \
    data_ptr = ((data_type *)((q_ptr)->data)) + (q_ptr)->head; \
	for(int ___q_itrcnt___ = (q_ptr)->length; \
		___q_itrcnt___ != 0; \
		___q_itrcnt___--, (++data_ptr) >= ((data_type *)((q_ptr)->data) + (q_ptr)->capacity) ? data_ptr = (data_type *)((q_ptr)->data) : data_ptr)


#ifdef __cplusplus
}
#endif


