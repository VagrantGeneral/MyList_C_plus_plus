#ifndef MY_LIST_HPP
#define MY_LIST_HPP
#include <stdio.h>

template <typename Param>
class MyList {

public:

	//��������	//��ģ����˵�ὫԪ�ط�Ϊ����5������******************************************
	typedef Param value_type;				//ֵ����***************************************
	typedef Param* pointer;					//ָ������*************************************
	typedef Param const* const_pointer;		//��ָ������***********************************
	typedef Param& reference;				//��������*************************************
	typedef Param const& const_reference;	//����������***********************************

private:

	struct _Node;//�����ڵ�����
	using _NodePtr = _Node*;				//�ڵ�ָ��************************************

	//�ڵ����ݵĽṹ
	struct _Node {

		_NodePtr _Prev;						//ǰ��
		_NodePtr _Next;						//���
		Param _Value;						//�ڵ�����

	};
    

	//ֻΪstruct _Node�ṩ����
	struct _Acc {
		
		static Param& _Value(_NodePtr ptr) {
			return ptr->_Value;
		}

		typedef _Node*& _Nodepref;			//�ڵ�ָ�������(ָ��ı���)*********************

		static _Nodepref _Prev(_NodePtr ptr) {
			return (ptr->_Prev);
		}

		static _Nodepref _Next(_NodePtr ptr) {
			return (ptr->_Next);
		}

		/*
		_Node* sp = _Acc::_Prev();

		_Node* sn = _Acc::_Next();

		*/
	};


private:

	_NodePtr _Head;							//�ڱ��ڵ�
	size_t _Size;

	//����һ���ڵ�
	static _NodePtr _Buynode(/*ǰ��ָ��*/_NodePtr _Parg = nullptr, /*����ָ��*/_NodePtr _Narg = nullptr) {

		_NodePtr s = (_NodePtr)malloc(sizeof(*s));
		if (s == nullptr) {
			exit(EXIT_FAILURE);
		}
		_Acc::_Prev(s) = (_Parg == nullptr ? s : _Parg);
		_Acc::_Next(s) = (_Narg == nullptr ? s : _Narg);
		return s;
	}


	//�ͷŽڵ�ռ䣨�������ͷſռ䣬û�е��ô洢�������������
	static void FreeNode(_NodePtr p) {
		free(p);
	}



public:

	//��������
	class const_iterator {

	public:

		_NodePtr _Ptr;

	public:

		const_iterator(_NodePtr _P = nullptr) : _Ptr(_P) {
			//std::cout << "const_iterator create successful" << std::endl;
		}
		~const_iterator() {}

		//Param const&
		const_reference operator*() const {
			return _Acc::_Value(_Ptr);
		}

		//Param const*
		const_pointer operator->() const {
			return &(*(*this));
		}

		// ǰ��/���� ++/--
		const_iterator& operator++() {
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		const_iterator& operator++(int) {
			const_iterator _tmp = *this;
			++(*this);
			return _tmp;
		}
		const_iterator& operator--() {
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		const_iterator& operator--(int) {
			const_iterator _tmp = *this;
			--(*this);
			return _tmp;
		}
		bool operator==(const const_iterator& x) const
		{
			return (this->_Ptr == x._Ptr);
		}
		bool operator!=(const const_iterator& x) const
		{
			return !(*this == x);
		}

		_NodePtr MyNode() const { 
			return _Ptr;
		}

	};

	//��ͨ������
	class iterator : public const_iterator {

	/*
	protected:

		_NodePtr _Ptr;
	*/

	public:

		iterator(_NodePtr _P = nullptr) 
			: const_iterator(_P) {
			//std::cout << "iterator create successful" << std::endl;
		}
		~iterator() {}

		//Param &
		reference operator*() const {
			return _Acc::_Value(const_iterator::_Ptr);
		}

		//Param *
		pointer operator->() const {
			return &(*(*this));
		}

		//
		iterator& operator++() {
			const_iterator::_Ptr = _Acc::_Next(const_iterator::_Ptr);
			return *this;
		}
		iterator& operator++(int) {
			iterator _tmp = *this;
			++(*this);
			return _tmp;
		}
		iterator& operator--() {
			const_iterator::_Ptr = _Acc::_Prev(const_iterator::_Ptr);
			return *this;
		}
		iterator& operator--(int) {
			iterator _tmp = *this;
			--(*this);
			return _tmp;
		}
		bool operator==(const iterator& _X) const
		{
			return (this->_Ptr == _X._Ptr);
		}
		bool operator!=(const iterator& _X) const
		{
			return !(*this == _X);
		}
	};


public:
	//����
	MyList() 
		: _Head(_Buynode()), 
		_Size(0) {
		std::cout << "create successful" << std::endl;
	}

	//��������
	MyList(const MyList& x)
		:_Head(_Buynode()), _Size(0) {
		insert(end(), x.begin(), x.end());
	}

	//�ƶ�����
	MyList(MyList&& x)
		:_Head(x._Head), _Size(x.size) {
		x._Head = _Buynode();
		x._Size = 0;
	}

	//������ֵ
	MyList& operator=(const MyList& x) {
		_Head = _Buynode();
		_Size = 0;
		insert(end(), x.begin(), x.end());
	}

	//�ƶ���ֵ
	MyList& operator=(const MyList&& x) {
		_Head = x._Head;
		_Size = x._Size;
		x._Head = _Buynode();
		x._Size = 0;
	}

	//����
	~MyList() {
		std::cout << "delete successful" << std::endl;
	}

	//��ȡԪ�ظ���
	size_t size() const { return _Size; }

	//�ж��Ƿ�Ϊ��
	bool empty() const { return size() == 0; }

	iterator begin() { 
		return iterator(_Acc::_Next(_Head)); 
	}

	iterator end() { 
		return iterator(_Head); 
	}

	const_iterator begin() const { 
		return const_iterator(_Acc::_Next(_Head)); 
	}

	const_iterator end() const { 
		return const_iterator(_Head); 
	}

	//ָ��λ�ò��루 Ϊ�Ժ�ĸ�������׼��
	iterator insert(const_iterator pos, const Param& value) {
		_NodePtr p = pos.MyNode();//��ȡ����ָ��

		_Acc::_Prev(p) = _Buynode(_Acc::_Prev(p), p);
		p = _Acc::_Prev(p); 
		_Acc::_Next(_Acc::_Prev(p)) = p;

		new(&_Acc::_Value(p)) Param(value);//���죨���� ֵ ���� �ռ䣩

		_Size += 1;

		return iterator(p);
	}

	//ָ��λ�� �ظ���� ����
	void insert(const_iterator pos, size_t count, const Param& value) {
		while (count--) {
			insert(pos, value);//**************************************************
		}
	}

	//ָ��λ�� ������Σ������ڴ棩 ����
	void insert(const_iterator pos, const Param* _F, const Param* _L) {
		for (; _F != _L; ++_F) {
			insert(pos, *_F);  //**************************************************
		}
	}

	//ָ��λ�� ���� �����������Ƭ
	void insert(const_iterator pos, const_iterator _F, const_iterator _L) {
		for (; _F != _L; ++_F) {
			insert(pos, *_F);  //**************************************************
		}
	}

	//ָ��λ��ɾ��
	iterator erase(iterator pos) {
		/*
		_NodePtr p = pos.MyNode();

		_Acc::_Next(_Acc::_Prev(p)) = _Acc::_Next(p);
		_Acc::_Prev(_Acc::_Next(p)) = _Acc::_Prev(p);

		_Acc::_Prev(p) = nullptr;
		_Acc::_Next(p) = nullptr;

		~Param(p);
		_Size--;

		//Ҫ���ص�����������ֱ��ʹ�����Ϸ���
		*/

		_NodePtr p = (pos++).MyNode();

		_Acc::_Next(_Acc::_Prev(p)) = _Acc::_Next(p);
		_Acc::_Prev(_Acc::_Next(p)) = _Acc::_Prev(p);

		(&_Acc::_Value(p))->~Param();

		FreeNode(p);

		return pos;
	}

	
	void push_back(const Param& value) {
		insert(end(), value);
	}
	void push_front(const Param& value) {
		insert(begin(), value);
	}
	void pop_back() {
		erase(end());
	}
	void pop_front() {
		erase(begin());
	}


	//��Χɾ��
	void erase(iterator _F, iterator _L) {
		for (; _F != _L;) {
			erase(_F++);
		}
	}

	//�������
	void clear() {
		erase(begin(), end());
	}

	//
	iterator find(const Param& val) {
		_NodePtr p = begin();
		for (; p != end(); p++) {
			if (_Acc::_Value(p) == val) {
				return iterator(p);
			}
		}
		return end();
	}

	//
	void remove(const Param& val) {
		erase(find(val));
	}

};

#endif