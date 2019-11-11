#ifndef __RING_QUEUE_H__
#define __RING_QUEUE_H__

#include <stdint.h>

// 环形队列
template<typename ObjType>
class CRingQueue
{
public:
    CRingQueue():m_uMaxObjNum(0), m_pObjRoot(NULL), m_uObjHead(0), m_uObjTail(0)
    {

    }
    ~CRingQueue()
    {
        if (m_pObjRoot)
        {
            delete[] m_pObjRoot;
            m_pObjRoot = NULL;
        }
    }
public:
    // 初始化环形队列的长度
    bool Init(uint32_t uMaxNode);
    // 向环形队列中写入数据
    bool Write(const ObjType &obj);
    // 从环形队列中读取数据
    ObjType* Read();
    // 弹出首个数据
    bool PopHead();
    // 获取消息数量
    uint32_t GetUsedMsgNum();
private:
    uint32_t m_uMaxObjNum;
    ObjType* m_pObjRoot;
    uint32_t m_uObjHead;
    uint32_t m_uObjTail;
};

template<typename ObjType>
bool CRingQueue<ObjType>::Init(uint32_t uMaxNode)
{
    if (uMaxNode <= 0)
    {
        return false;
    }

    m_pObjRoot = new ObjType[uMaxNode];
    m_uMaxObjNum = uMaxNode;
    m_uObjHead = 0;
    m_uObjTail = 0;

    return true;
}

template<typename ObjType>
bool CRingQueue<ObjType>::Write(const ObjType &obj)
{
    uint32_t uHeadPos = m_uObjHead;
    uint32_t uNextTailPos = (m_uObjTail + 1) % m_uMaxObjNum;

    if (uNextTailPos == uHeadPos)
    {
        return false;
    }

    m_pObjRoot[uNextTailPos] = obj;
    m_uObjTail = uNextTailPos;

    return true;
}

template<typename ObjType>
ObjType* CRingQueue<ObjType>::Read()
{
    uint32_t uTailPos = m_uObjTail;
    
    if (m_uObjHead == uTailPos)
    {
        return NULL;
    }

    return &(m_pObjRoot[uTailPos]);
}

template<typename ObjType>
bool CRingQueue<ObjType>::PopHead()
{
    uint32_t uTailPos = m_uObjTail;
    if (m_uObjHead == uTailPos)
    {
        return false;
    }

    uint32_t uNextHeadPos = (m_uObjHead + 1) % m_uMaxObjNum;
    m_uObjHead = uNextHeadPos;

    return true;
}

template<typename ObjType>
uint32_t CRingQueue<ObjType>::GetUsedMsgNum()
{
    if (m_uMaxObjNum <= 0)
    {
        return 0;
    }

    return (m_uObjTail - m_uObjHead + m_uMaxObjNum) % m_uMaxObjNum;
}

#undef //__RING_QUEUE_H__