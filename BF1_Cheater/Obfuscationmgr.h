/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

*****************************************************************************************************/
#ifndef OBFUSCATIONMGR_H
#define OBFUSCATIONMGR_H

#include "Base.h"
#include "Frosbite.h"

typedef DWORD64 QWORD;
typedef QWORD _QWORD;

typedef BYTE _BYTE;
typedef DWORD _DWORD;
typedef WORD _WORD;

template<typename T1, typename T2>
struct pair
{
	T1 first;
	T2 second;
};
template<typename T>
struct hash_node
{
	pair<_QWORD, T*> mValue;
	hash_node<T>* mpNext;
};

template<typename T>
struct hashtable
{
	_QWORD vtable;
	hash_node<T>** mpBucketArray;
	unsigned int mnBucketCount;
	unsigned int mnElementCount;
	//...
};

template<typename T>
struct hashtable_iterator
{
	hash_node<T>* mpNode;
	hash_node<T>** mpBucket;
};

hashtable_iterator<_QWORD>* __fastcall hashtable_find(hashtable<_QWORD>* table, hashtable_iterator<_QWORD>* iterator, _QWORD key);

fb::ClientPlayer* GetPlayerById(int id);
fb::ClientPlayer* GetLocalPlayer(void);

#endif // !OBFUSCATIONMGR_H

