#ifndef LISTSTACK_HPP
#define LISTSTACK_HPP
//��Listʵ��ջ�ṹ

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "MyList.hpp"

template <typename Param>
class ListStack {

private:
	MyList<Param> liststack;


public:
	//����
	ListStack()
		:liststack(MyList<Param>()) {
	}

	//��������
	ListStack(const ListStack& ls)
		:liststack(MyList<Param>(ls)) {
	}

	//�ƶ�����
	ListStack(ListStack&& ls)
		:liststack(MyList<Param>(ls)) {
	}

	//����
	~ListStack() {

	}


public:
	//��ȡջ��Ԫ�ظ���
	size_t size() const {
		return liststack.size();
	}

	//�ж��Ƿ�Ϊ��
	bool empty() const {
		return liststack.size() == 0;
	}

	//��ȡջ��Ԫ��
	Param GetTopValue() const {
		return *((liststack.end())--)
	}

	//��ջ�����Ԫ��
	void PushTop(const Param& val) {
		liststack.push_back(val);
	}

	//����ջ��Ԫ��
	void PopTop() {
		liststack.pop_back();
	}




};
























#endif