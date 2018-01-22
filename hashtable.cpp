//File:			hashtable.cpp
//Author:		Duc-Phuong Nguyen
//Date:			April 8, 2016
//Description:	Implementation of a hash table class for CMPT 225 assignment 5

#include "hashtable.h"

int HashTable::Hash(string str) const {
	int result = str[0] - 'a' + 1;	
	for (int i = 1; i < str.length(); i ++) 
		result = (result * 32 + (str[i] - 'a' + 1)) % maxsize;

	return result;
}

int HashTable::SmallestPrime(int n) const {
	int result = n;
	while (true) {
		result ++;
		if (IsPrime(result)) return result;
	}
}

bool HashTable::IsPrime(int n) const {
	for (int i = 2; i <= n / 2; i ++) 
		if (n % i == 0) return false;
	return true;
}

bool HashTable::Resize(int n) {
	if (n < maxsize) return false;

	vector<UserAccount> vt; //vector to store all accounts
	for (int i = 0; i < maxsize; i ++) {
		vector<UserAccount> temp = table[i].Dump();
		vt.insert(vt.end(),temp.begin(),temp.end());
	}

	//delete old table
	for (int i = 0; i < maxsize; i ++) 
		table[i].RemoveAll();
	delete [] table;

	//creat a new one
	size = vt.size();
	maxsize = SmallestPrime(n);
	table = new SLinkedList<UserAccount> [maxsize];

	for (int i = 0; i < vt.size(); i ++) {
		int hash_value = Hash(vt[i].GetUsername());
		table[hash_value].InsertBack(vt[i]);
	}

	return true;
}

HashTable::HashTable() {
	size = 0;
	maxsize = 101;
	table = new SLinkedList<UserAccount> [maxsize];
}

HashTable::HashTable(int n) {
	size = 0;
	maxsize = SmallestPrime(2 * n);
	table = new SLinkedList<UserAccount> [maxsize];
}

HashTable::HashTable(const HashTable& sourceht) {
	size = sourceht.Size();
	maxsize = sourceht.MaxSize();
	table = new SLinkedList<UserAccount> [maxsize];

	for (int i = 0; i < maxsize; i ++)
		table[i] = sourceht.table[i];
}

HashTable::~HashTable() {
	for (int i = 0; i < maxsize; i ++) 
		table[i].RemoveAll();
	delete [] table;
}

HashTable& HashTable::operator = (const HashTable& sourceht) {
	for (int i = 0; i < maxsize; i ++) 
		table[i].RemoveAll();
	delete [] table;

	size = sourceht.Size();
	maxsize = sourceht.MaxSize();
	table = new SLinkedList<UserAccount> [maxsize];

	for (int i = 0; i < maxsize; i ++)
		table[i] = sourceht.table[i];

	return *this;
}

bool HashTable::Insert(UserAccount acct) {
	int hash_value = Hash(acct.GetUsername());
	if (table[hash_value].Contains(acct)) return false;

	if (LoadFactor() > 2/3) Resize(2 * maxsize);
	hash_value = Hash(acct.GetUsername());
	table[hash_value].InsertBack(acct);

	size ++;
	return true;
}

bool HashTable::Remove(UserAccount acct) {
	int hash_value = Hash(acct.GetUsername());
	if (table[hash_value].Contains(acct)) {
		table[hash_value].Remove(acct);
		size --;
		return true;
	}

	return false;
}

bool HashTable::Search(UserAccount acct) const {
	int hash_value = Hash(acct.GetUsername());
	if (table[hash_value].Contains(acct)) return true;
	return false;
}

UserAccount* HashTable::Retrieve(UserAccount acct) {
	int hash_value = Hash(acct.GetUsername());
	return table[hash_value].Retrieve(acct);
}

int HashTable::Size() const {
	return size;
}

int HashTable::MaxSize() const {
	return maxsize;
}

double HashTable::LoadFactor() const {
	return (double)size / maxsize;
}