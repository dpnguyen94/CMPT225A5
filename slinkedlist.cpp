//File:			slinkedlist.cpp
//Author:		Duc-Phuong Nguyen
//Date:			April 8, 2016
//Description:	Implementation of a template singly-linked-list class for CMPT225 assignment 5

#ifdef _SLINKEDLIST_H_

template <class T>
void SLinkedList<T>::CopyList(const SLinkedList& ll) {
	size = 0;
	front = NULL;
	back = NULL;

	vector<T> temp = ll.Dump();
	for (int i = 0; i < temp.size(); i ++)
		InsertBack(temp[i]);
}

template <class T>
void SLinkedList<T>::DeleteList() {
	Node<T> *ptr;
	while (front != NULL) {
		size --;
		ptr = front;
		front = front -> next;
		delete ptr;
	}
	back = NULL;
}

template <class T>
SLinkedList<T>::SLinkedList() {
	size = 0;
	front = NULL;
	back = NULL;
}

template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList& ll) {
	CopyList(ll);
}


template <class T>
SLinkedList<T>::~SLinkedList() {
	DeleteList();
}

template <class T>
void SLinkedList<T>::InsertFront(T item) {
	Node<T> *newnode = new Node<T>(item);
	if (front != NULL) 
		newnode -> next = front;

	front = newnode;
	size ++;
	if (size == 1) back = front;
}

template <class T>
void SLinkedList<T>::InsertBack(T item) {
	Node<T>* newnode = new Node<T>(item);
	if (back != NULL) 
		back -> next = newnode;

	back = newnode;
	size ++;
	if (size == 1) front = back;
}


template <class T>
bool SLinkedList<T>::Remove (T item) {
	if (front == NULL) return false;
	if (front -> data == item) {
		Node<T> *temp = front;
		front = front -> next;
		delete temp;
		size --;
		return true;
	}

	Node<T> *ptr = front;
	while (ptr -> next != NULL) {
		if (ptr -> next -> data == item) {
			Node<T> *temp = ptr -> next;
			ptr -> next = ptr -> next -> next;

			if (temp == back) back = ptr;
			delete temp;
			size --;
			return true;
		}
		
		ptr = ptr -> next;
	}

	return false;
}

template <class T>
void SLinkedList<T>::RemoveAll() {
	DeleteList();
}

template <class T>
int SLinkedList<T>::Size() const {
	return size;
}

template <class T>
bool SLinkedList<T>::IsEmpty() const {
	return (size == 0);
}

template <class T>
bool SLinkedList<T>::Contains(T item) const {
	Node<T> *ptr = front;
	while (ptr != NULL) {
		if (ptr -> data == item) return true;
		ptr = ptr -> next;
	}

	return false;
}

template <class T>
T* SLinkedList<T>::Retrieve(T item) {
	Node<T> *ptr = front;
	while (ptr != NULL) {
		if (ptr -> data == item) return &ptr -> data;
		ptr = ptr -> next;	
	}

	return NULL;
}

template <class T>
vector<T> SLinkedList<T>::Dump() const {
	vector<T> vt;
	Node<T> *ptr = front;
	while (ptr != NULL) {
		vt.push_back(ptr -> data);
		ptr = ptr -> next;
	}

	return vt;
}

template <class T>
SLinkedList<T>& SLinkedList<T>::operator = (const SLinkedList& ll) {
	if (front != ll.front) {
		DeleteList();
		CopyList(ll);
	}

	return *this;
}

#endif