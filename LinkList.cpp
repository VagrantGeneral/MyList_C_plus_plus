#include<stdlib.h>  // malloc free;	  exit;
#include<string.h> // memset;
#include<assert.h>


#include"LinkList.hpp"
/*
typedef struct ListNode
{
	struct ListNode* prev;
	struct ListNode* next;
	void* data; // double // struct Student;
}ListNode, * pListNode;
typedef struct
{
	pListNode Head;
	int cursize;
	size_t elemsize;  // char  , short , int ; // long int; long long; float; double; long double;
}LinkList;
*/


//����ڵ�
static ListNode* Buynode()
{
	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	if (nullptr == s) exit(1);
	memset(s, 0, sizeof(ListNode));
	return s;
}
//�ͷŽڵ�
static void Freenode(ListNode* p)
{
	free(p);
}
//��s����Ϊp��ǰ��
static void InserPrev(ListNode* p, ListNode* s) {
	s->next = p;
	s->prev = p->prev;
	p->prev = s;
	s->prev->next = s;
}
//
static void* GetElemmem(size_t size) {
	void* s = malloc(size);
	if (nullptr == s) exit(1);
	memset(s, 0, size);
	return s;
}









//��ʼ��List
void InitList(LinkList* plist, size_t elemsize)
{
	assert(plist != nullptr);
	plist->Head = Buynode();
	plist->Head->next = plist->Head->prev = plist->Head;
	plist->cursize = 0;
	plist->elemsize = elemsize;
}
//�ݻ�List
void DestroyList(LinkList* plist) {

}
//��ȡԪ�ظ���
size_t GetSize(const LinkList* plist)
{
	assert(plist != nullptr);
	return plist->cursize;
}
//�ж��Ƿ�Ϊ��
bool IsEmpty(const LinkList* plist)
{
	assert(plist != nullptr);
	return GetSize(plist) == 0;
}
//���List
void ClearList(LinkList* plist) {

}
//��λָ��λ�õĽڵ�
ListNode* FindPos(const LinkList* plist, size_t pos) {
	assert(plist != nullptr);
	if (pos == 0) return nullptr;
	if (pos == 1) return plist->Head->next;
	if (GetSize(plist) == pos) return plist->Head->prev;
	if (GetSize(plist) < pos) return nullptr;
	ListNode* p = plist->Head;
	while (pos--) {
		p = p->next;
	}
	return p;
}
//ָ��λ�ò����½ڵ�
bool InsertList(LinkList* plist, int pos, void* pval) {
	assert(plist != nullptr);
	assert(pval != nullptr);
	ListNode* p = FindPos(plist, pos);
	if (nullptr == p) return false;
	ListNode* s = Buynode();
	InserPrev(p, s);
	if (plist->elemsize <= 4) {
		memmove(&s->data, pval, plist->elemsize);
	}
	else {
		void* newval = GetElemmem(plist->elemsize);
		s->data = newval;
	}
	plist->cursize += 1;

	return true;
}
//β��
void Push_back(LinkList* plist, void* pval) {

}
//ͷ��
void Push_front(LinkList* plist, void* pval) {

}
//����Ԫ��
//ListNode* FindValue(const LinkList* plist, void* pval) {
//
//}

//ɾ��ָ��λ�ýڵ�
//bool EraseList(LinkList* plist, int pos) {
//
//}
//βɾ
void Pop_back(LinkList* plist) {

}
//ͷɾ
void Pop_Front(LinkList* plist) {

}
////��ȡͷ
//bool GetFront(const LinkList* plist, void* pval) {
//
//}
////��ȡβ
//bool GetBack(const LinkList* plist, void* pval) {
//
//}
////�Ƴ�ָ���ڵ�
//bool Remove(LinkList* plist, void* pval) {
//
//}
