/*
 * Map.hpp
 *
 *  Created on: Mar 1, 2017
 *      Author: sumeet
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <initializer_list>
#include <vector>
#include <stdexcept>
#define skip_list_max_level 100

#ifndef MAP_HPP_
#define MAP_HPP_

namespace cs540 {

using namespace std;

class Iterator;
class ConstIterator;
class ReverseIterator;
template<typename Key_T, typename Mapped_T>
class Map;

template<typename Key_T, typename Mapped_T>
class SkipNode {

	typedef std::pair<const Key_T, Mapped_T> ValueType;

	ValueType *data;

	// a vector of pointers to the next element
	vector<SkipNode*> next;

	// pointer to the previous element
	SkipNode *prev;

public:

	friend class Map<Key_T, Mapped_T> ;

	SkipNode() {
		data = nullptr;
		for (int i = 0; i < skip_list_max_level; i++) {
			next.emplace_back(nullptr);
		}
		//prev = nullptr;
	}

	SkipNode(const ValueType& value) {

		data = new std::pair<const Key_T, Mapped_T>(value);

		for (int i = 0; i < skip_list_max_level; i++) {
			next.emplace_back(nullptr);
		}
		//prev = nullptr;

	}

	~SkipNode() {

		//cout << "destructing SkipNode" << this << endl;
		delete data;
	}

};

template<typename Key_T, typename Mapped_T>
class Map {

private:

	typedef std::pair<const Key_T, Mapped_T> ValueType;

	SkipNode<Key_T, Mapped_T> *head;
	SkipNode<Key_T, Mapped_T> *tail;

	size_t map_size;

public:

	// nested iterator classes
	class Iterator {

	private:

		SkipNode<Key_T, Mapped_T> *current;

	public:
		//Iterator(const Iterator &);
		Iterator(SkipNode<Key_T, Mapped_T> *skip_node);
		~Iterator();
		Iterator& operator=(const Iterator &);
		Iterator &operator++();
		Iterator operator++(int);
		Iterator &operator--();
		Iterator operator--(int);
		ValueType &operator*() const;
		ValueType *operator->() const;

		SkipNode<Key_T, Mapped_T>* get_current() const;

	};

	class ConstIterator {

	private:

		SkipNode<Key_T, Mapped_T> *current;

	public:

		//ConstIterator(const ConstIterator &);
		ConstIterator(const Iterator &);
		ConstIterator(SkipNode<Key_T, Mapped_T> *skip_node);
		~ConstIterator();
		ConstIterator& operator=(const ConstIterator &);
		ConstIterator &operator++();
		ConstIterator operator++(int);
		ConstIterator &operator--();
		ConstIterator operator--(int);
		const ValueType &operator*() const;
		const ValueType *operator->() const;

		SkipNode<Key_T, Mapped_T>* get_current() const;
	};

	class ReverseIterator {

	private:

		SkipNode<Key_T, Mapped_T> *current;

	public:
		//ReverseIterator(const ReverseIterator &);
		ReverseIterator(SkipNode<Key_T, Mapped_T> *skip_node);
		~ReverseIterator();
		ReverseIterator& operator=(const ReverseIterator &);
		ReverseIterator &operator++();
		ReverseIterator operator++(int);
		ReverseIterator &operator--();
		ReverseIterator operator--(int);
		ValueType &operator*() const;
		ValueType *operator->() const;

		SkipNode<Key_T, Mapped_T>* get_current() const;
	};

	//Constructors and Assignment Operator
	Map();
	Map(const Map &);
	Map &operator=(const Map &);
	Map (std::initializer_list<std::pair<const Key_T, Mapped_T>>);
	~Map();

	//Size
	size_t size() const;
	bool empty() const;

	//Iterators
	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ReverseIterator rbegin();
	ReverseIterator rend();

	//Element Access
	Iterator find(const Key_T &a);
	ConstIterator find(const Key_T &) const;
	Mapped_T &at(const Key_T &);
	const Mapped_T &at(const Key_T &) const;
	Mapped_T &operator[](const Key_T &);

	//Modifiers
	std::pair<Iterator, bool> insert(const ValueType &);
	template<typename IT_T>
	void insert(IT_T range_beg, IT_T range_end);
	void erase(Iterator pos);
	void erase(const Key_T &);
	void clear();

	// auxillary functions
	SkipNode<Key_T, Mapped_T>* get_head() const;
	SkipNode<Key_T, Mapped_T>* get_tail() const;
	int get_current_max_level();
	int get_random_level();
	SkipNode<Key_T, Mapped_T>* search(Key_T search_key) const;
	//void print_skip_list(); // only for debug purpose

	// Compare any combination of Iterator and ConstIterator
	// Comparison Operators for Iterators defined as friend functions

	friend bool operator==(const Iterator &iter1, const Iterator &iter2) {

		return (iter1.get_current() == iter2.get_current());
	}

	friend bool operator==(const ConstIterator &const_iter1,
			const ConstIterator &const_iter2) {

		return (const_iter1.get_current() == const_iter2.get_current());

	}

	friend bool operator==(const Iterator &iter,
			const ConstIterator &const_iter) {

		return (iter.get_current() == const_iter.get_current());

	}

	friend bool operator==(const ConstIterator &const_iter,
			const Iterator &iter) {

		return (const_iter.get_current() == iter.get_current());

	}

	friend bool operator!=(const Iterator &iter1, const Iterator &iter2) {

		return (iter1.get_current() != iter2.get_current());
	}

	friend bool operator!=(const ConstIterator &const_iter1,
			const ConstIterator &const_iter2) {

		return (const_iter1.get_current() != const_iter2.get_current());
	}

	friend bool operator!=(const Iterator &iter,
			const ConstIterator &const_iter) {

		return (iter.get_current() != const_iter.get_current());
	}

	friend bool operator!=(const ConstIterator &const_iter,
			const Iterator &iter) {

		return (const_iter.get_current() != iter.get_current());
	}

	friend bool operator==(const ReverseIterator &rev_iter1,
			const ReverseIterator &rev_iter2) {

		return (rev_iter1.get_current() == rev_iter2.get_current());

	}

	friend bool operator!=(const ReverseIterator &rev_iter1,
			const ReverseIterator &rev_iter2) {

		return (rev_iter1.get_current() != rev_iter2.get_current());;
	}

};

//Constructors and Assignment Operator

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Map() {

	map_size = 0;

	tail = new SkipNode<Key_T, Mapped_T>();
	tail->next[0] = nullptr;

	head = new SkipNode<Key_T, Mapped_T>();
	for (int i = skip_list_max_level - 1; i >= 0; i--) {
		head->next[i] = tail;

	}
	tail->prev = head;

}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Map(const Map &map) {

	//--------------------------------------------------

	map_size = 0;

	tail = new SkipNode<Key_T, Mapped_T>();
	tail->next[0] = nullptr;

	head = new SkipNode<Key_T, Mapped_T>();
	for (int i = skip_list_max_level - 1; i >= 0; i--) {
		head->next[i] = tail;
	}
	tail->prev = head;
	//--------------------------------------------------

	SkipNode<Key_T, Mapped_T> *p = map.get_head()->next[0];
	while (p != map.get_tail()) {
		ValueType& val = *(p->data);
		insert(val);
		p = p->next[0];
	}

}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T> & Map<Key_T, Mapped_T>::operator=(const Map &map) {

	// handle self-assignment
	if (this == &map) {
		return *this;
	}

	// empty 'this' (map)
	clear();

	// check if map is empty, if yes then return 'this' (coz we just emptied this)
	SkipNode<Key_T, Mapped_T> *p = map.get_head()->next[0];
	if (p == map.get_tail()) {
		return *this;
	}

	// if not empty, then insert elements one by one and return
	while (p != map.get_tail()) {
		insert(*(p->data));
		p = p->next[0];
	}
	return *this;

}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Map(
		std::initializer_list<std::pair<const Key_T, Mapped_T>> init_list) {

	map_size = 0;

	tail = new SkipNode<Key_T, Mapped_T>();
	tail->next[0] = nullptr;

	head = new SkipNode<Key_T, Mapped_T>();

	for (int i = skip_list_max_level - 1; i >= 0; i--) {
		head->next[i] = tail;
	}
	tail->prev = head;

	auto iter = init_list.begin();
	while (iter != init_list.end()) {
		insert(*iter);
		iter++;
	}

}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::~Map() {

	SkipNode<Key_T, Mapped_T> *p = head;
	SkipNode<Key_T, Mapped_T> *trail_p;

	while (p->next[0] != nullptr) {
		trail_p = p;
		p = p->next[0];
		delete trail_p;
	}

	delete tail;
}

//Size
template<typename Key_T, typename Mapped_T>
size_t Map<Key_T, Mapped_T>::size() const {
	return map_size;
}

template<typename Key_T, typename Mapped_T>
bool Map<Key_T, Mapped_T>::empty() const {
	return map_size == 0;
}

//Iterators
template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::begin() {
	return Map<Key_T, Mapped_T>::Iterator(head->next[0]);
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::end() {
	return Map<Key_T, Mapped_T>::Iterator(tail);
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::begin() const {
	return ConstIterator(head->next[0]);
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::end() const {
	return ConstIterator(tail);
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rbegin() {
	return ReverseIterator(tail->prev);
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rend() {
	return ReverseIterator(head);
}

//Element Access

template<typename Key_T, typename Mapped_T>
SkipNode<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::get_head() const {
	return head;
}

template<typename Key_T, typename Mapped_T>
SkipNode<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::get_tail() const {
	return tail;
}

template<typename Key_T, typename Mapped_T>
int Map<Key_T, Mapped_T>::get_current_max_level() {

	int currentMaximum = 1;
	for (int i = 0; i < skip_list_max_level; i++) {
		if (head->next[i] != tail) {
			currentMaximum++;
		} else {
			break;
		}
	}
	return currentMaximum;
}

template<typename Key_T, typename Mapped_T>
int Map<Key_T, Mapped_T>::get_random_level() {

	int level = 1;
	float probability = 0.5;

	while ((((double) std::rand() / RAND_MAX)) < probability
			&& level < skip_list_max_level) {

		level++;
	}

	return level;
}

//template<typename Key_T, typename Mapped_T>
//void Map<Key_T, Mapped_T>::print_skip_list() {
//
//	SkipNode<Key_T, Mapped_T> *p = head;
//
//	if (p == NULL) {
//		cout << "Skip list is empty!" << endl;
//		return;
//	}
//
//	int currentMaximum = get_current_max_level();
//
//	cout << "skip-list" << endl << "--------------------------------------"
//			<< endl;
//	for (int i = currentMaximum; i-- > 0;) {
//		//cout << ";";
//		p = head;
//		cout << p << "(head) -> ";
//		while (p->next[i] != tail) {
//
//			p = p->next[i];
//			cout << p << "(" << p->data->first << ", " << p->data->second
//					<< ") -> ";
//		}
//		cout << tail << "(tail)" << endl;
//	}
//}

template<typename Key_T, typename Mapped_T>
SkipNode<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::search(
		Key_T search_key) const {

	SkipNode<Key_T, Mapped_T> *p = head;

	// calculate the current max level
	unsigned int currentMaximum = 1;
	for (int i = 0; i < skip_list_max_level; i++) {
		if (head->next[i] != tail) {
			currentMaximum++;
		} else {
			break;
		}
	}

	//start from head at the current max level
	for (unsigned int i = currentMaximum; i-- > 0;) {
		while ((p->next[i] != tail)
				&& (p->next[i]->data->first < search_key
						|| p->next[i]->data->first == search_key)) {
			p = p->next[i];
		}
	}

	return p;
}

/* Returns an iterator to the given key. If the key is not found, these functions return the end() iterator.*/
template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::find(
		const Key_T &find_key) {

	SkipNode<Key_T, Mapped_T> *p = search(find_key);

	if (p == head) {
		return Map<Key_T, Mapped_T>::Iterator(tail);
	}

	if (p->data->first == find_key) {
		return Map<Key_T, Mapped_T>::Iterator(p);
	} else {
		return Map<Key_T, Mapped_T>::Iterator(tail);
	}

}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::find(
		const Key_T &find_key) const {

	SkipNode<Key_T, Mapped_T> *p = search(find_key);

	if (p == head) {
		return Map<Key_T, Mapped_T>::ConstIterator(tail);
	}

	if (p->data->first == find_key) {
		return Map<Key_T, Mapped_T>::ConstIterator(p);
	} else {
		return Map<Key_T, Mapped_T>::ConstIterator(tail);
	}

}

template<typename Key_T, typename Mapped_T>
Mapped_T & Map<Key_T, Mapped_T>::at(const Key_T &key) {

	SkipNode<Key_T, Mapped_T> *p = search(key);

	if (p == head) {
		throw std::out_of_range("Specified key is not in the Map!");
	}

	if (p->data->first == key) {
		return p->data->second;
	} else {
		throw std::out_of_range("Specified key is not in the Map!");
	}
}

template<typename Key_T, typename Mapped_T>
const Mapped_T & Map<Key_T, Mapped_T>::at(const Key_T &key) const {

	SkipNode<Key_T, Mapped_T> *p = search(key);

	if (p == head) {
		throw std::out_of_range("Specified key is not in the Map!");
	}

	if (p->data->first == key) {
		return p->data->second;
	} else {
		throw std::out_of_range("Specified key is not in the Map!");
	}
}

template<typename Key_T, typename Mapped_T>
Mapped_T & Map<Key_T, Mapped_T>::operator[](const Key_T &key) {

	SkipNode<Key_T, Mapped_T> *p = search(key);

	if (p == head) {

		Map<Key_T, Mapped_T>::Iterator iter = insert(
				std::make_pair(key, Mapped_T())).first;

		return iter.get_current()->data->second;
	}

	if (p->data->first == key) {
		return p->data->second;
	} else {

		Map<Key_T, Mapped_T>::Iterator iter = insert(
				std::make_pair(key, Mapped_T())).first;
		return iter.get_current()->data->second;
	}

}

//Modifiers
template<typename Key_T, typename Mapped_T>
std::pair<typename Map<Key_T, Mapped_T>::Iterator, bool> Map<Key_T, Mapped_T>::insert(
		const ValueType &value) {

	SkipNode<Key_T, Mapped_T> *p = search(value.first);

	if (p != head) {
		if (p->data->first == value.first) {
			return std::make_pair(Map<Key_T, Mapped_T>::Iterator(p), false);
		}
	}

	// update vector
	vector<SkipNode<Key_T, Mapped_T>*> update(head->next);

	SkipNode<Key_T, Mapped_T> *newNode = new SkipNode<Key_T, Mapped_T>(value);

	int newNodeLevel = get_random_level();

	//-------------------------------------------------------------
	p = head;

	int currentMaximum = get_current_max_level();

	//start from head at the current max level
	unsigned int i;
	for (i = currentMaximum; i-- > 0;) {
		while (p->next[i] != tail && p->next[i]->data->first < value.first) {
			p = p->next[i];
		}
		update[i] = p;
	}

	// for those levels above the index of the update vector, update those indices(levels) with HEAD
	if (newNodeLevel > currentMaximum) {
		for (int i = currentMaximum; i <= newNodeLevel; i++) {
			update[i] = head;
		}
	}

	// adjust the newNode in-between 2 nodes
	// first update the next pointers of newNode???
	for (int i = 0; i < newNodeLevel; i++) {

		newNode->next[i] = update[i]->next[i];

		if (i == 0) {
			update[i]->next[i]->prev = newNode;
			newNode->prev = update[i];
		}

		update[i]->next[i] = newNode;

	}

	map_size++;

	return std::make_pair(Map<Key_T, Mapped_T>::Iterator(newNode), true);

}

template<typename Key_T, typename Mapped_T>
template<typename IT_T>
void Map<Key_T, Mapped_T>::insert(IT_T range_beg, IT_T range_end) {

	auto _iter = range_beg;
	while (_iter != range_end) {
		insert(*_iter);
		++_iter;
	}
}

template<typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::erase(Iterator pos) {

	Key_T erase_key = pos.get_current()->data->first;

	SkipNode<Key_T, Mapped_T> *p = head;

	// update vector
	vector<SkipNode<Key_T, Mapped_T>*> update(head->next);

	int currentMaximum = get_current_max_level();

	//start from head at the current max level
	unsigned int i;
	for (i = currentMaximum; i-- > 0;) {
		while (p->next[i] != tail && p->next[i]->data->first < erase_key) {

			p = p->next[i];

		}
		update[i] = p;
	}

	p = p->next[0];

	if (p!=tail && erase_key == p->data->first) {

		for (size_t i = 0; i < update.size(); i++) { //note

			if (update[i]->next[i] == p) {

				update[i]->next[i] = p->next[i];

				if (i == 0) {
					p->next[i]->prev = update[i];
				}
			}
		}

		delete p;
		map_size--;
	} else {
		//cout << "no such element exists!" << endl;
		throw std::out_of_range(
				"Specified iterator position is not in the Map!");
	}

}

template<typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::erase(const Key_T &erase_key) {

	SkipNode<Key_T, Mapped_T> *p = head;

	// update vector
	vector<SkipNode<Key_T, Mapped_T>*> update(head->next);

	int currentMaximum = get_current_max_level();

	//start from head at the current max level
	unsigned int i;
	for (i = currentMaximum; i-- > 0;) {
		while (p->next[i] != tail && p->next[i]->data->first < erase_key) {

			p = p->next[i];

		}
		update[i] = p;
	}

	p = p->next[0];

	if (p!=tail && erase_key == p->data->first) {

		for (size_t i = 0; i < update.size(); i++) {
			if (update[i]->next[i] == p) {
				update[i]->next[i] = p->next[i];

				if (i == 0) {
					p->next[i]->prev = update[i];
				}

			}

		}
		delete p;
		map_size--;
	} else {
		//cout << "no such element exists!" << endl;
		throw std::out_of_range("Specified key is not in the Map!");
	}

}

template<typename Key_T, typename Mapped_T>
void Map<Key_T, Mapped_T>::clear() {

	SkipNode<Key_T, Mapped_T> *p = head;
	SkipNode<Key_T, Mapped_T> *trail_p;

	while (p->next[0] != nullptr) {
		trail_p = p;
		p = p->next[0];
		delete trail_p;
	}

	delete tail;

	tail = NULL;
	head = NULL;

	map_size = 0;

	tail = new SkipNode<Key_T, Mapped_T>();
	tail->next[0] = nullptr;

	head = new SkipNode<Key_T, Mapped_T>();
	for (int i = skip_list_max_level - 1; i >= 0; i--) {
		head->next[i] = tail;

	}
	tail->prev = head;
}

// iterator inner class member functions

template<typename Key_T, typename Mapped_T>
SkipNode<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::Iterator::get_current() const {
	return current;
}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Iterator::Iterator(SkipNode<Key_T, Mapped_T> *skip_node) {

	current = skip_node;
}

//template<typename Key_T, typename Mapped_T>
//Map<Key_T, Mapped_T>::Iterator::Iterator(
//		const Map<Key_T, Mapped_T>::Iterator &iter) {
//
//	current = iter.get_current();
//}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::Iterator::~Iterator() {
	current = nullptr;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator=(
		const Iterator &iter) {

	current = iter.get_current();
	return *this;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator++() {

	if (current == NULL) {
		return *this;
	}
	current = current->next[0];
	return *this;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator++(
		int) {

	Map<Key_T, Mapped_T>::Iterator iter = *this;
	if (current == NULL) {
		return iter;
	}
	current = current->next[0];
	return iter;

}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator& Map<Key_T, Mapped_T>::Iterator::operator--() {

	if (current == NULL) {
		return *this;
	}
	current = current->prev;
	return *this;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::Iterator::operator--(
		int) {

	Map<Key_T, Mapped_T>::Iterator iter = *this;
	if (current == NULL) {
		return iter;
	}
	current = current->prev;
	return iter;

}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType& Map<Key_T, Mapped_T>::Iterator::operator*() const {
	return *current->data;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::Iterator::operator->() const {
	return current->data;
}

// ConstIterator inner class member functions

template<typename Key_T, typename Mapped_T>
SkipNode<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::ConstIterator::get_current() const {
	return current;
}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(
		SkipNode<Key_T, Mapped_T> *skip_node) {
	current = skip_node;
}

//template<typename Key_T, typename Mapped_T>
//Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(
//		const Map<Key_T, Mapped_T>::ConstIterator &const_iter) {
//
//	current = const_iter.get_current();
//}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator::ConstIterator(
		const Map<Key_T, Mapped_T>::Iterator &iter) {
	current = iter.get_current();
}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ConstIterator::~ConstIterator() {
	current = nullptr;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator& Map<Key_T, Mapped_T>::ConstIterator::operator=(
		const Map<Key_T, Mapped_T>::ConstIterator &const_iter) {

	current = const_iter.get_current();
	return *this;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator& Map<Key_T, Mapped_T>::ConstIterator::operator++() {

	if (current == NULL) {
		return *this;
	}

	current = current->next[0];
	return *this;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator++(
		int) {

	Map<Key_T, Mapped_T>::ConstIterator const_iter = *this;
	if (current == NULL) {
		return const_iter;
	}
	current = current->next[0];
	return const_iter;

}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator& Map<Key_T, Mapped_T>::ConstIterator::operator--() {

	if (current == NULL) {
		return *this;
	}
	current = current->prev;
	return *this;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ConstIterator Map<Key_T, Mapped_T>::ConstIterator::operator--(
		int) {

	Map<Key_T, Mapped_T>::ConstIterator const_iter = *this;
	if (current == NULL) {
		return const_iter;
	}
	current = current->prev;
	return const_iter;
}

template<typename Key_T, typename Mapped_T>
const typename Map<Key_T, Mapped_T>::ValueType& Map<Key_T, Mapped_T>::ConstIterator::operator*() const {
	return *current->data;

}

template<typename Key_T, typename Mapped_T>
const typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::ConstIterator::operator->() const {
	return current->data;
}

// ReverseIterator inner class member functions

template<typename Key_T, typename Mapped_T>
SkipNode<Key_T, Mapped_T>* Map<Key_T, Mapped_T>::ReverseIterator::get_current() const {
	return current;
}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ReverseIterator::ReverseIterator(
		SkipNode<Key_T, Mapped_T> *skip_node) {
	current = skip_node;
}

//template<typename Key_T, typename Mapped_T>
//Map<Key_T, Mapped_T>::ReverseIterator::ReverseIterator(
//		const Map<Key_T, Mapped_T>::ReverseIterator &rev_iter) {
//	current = rev_iter.get_current();
//}

template<typename Key_T, typename Mapped_T>
Map<Key_T, Mapped_T>::ReverseIterator::~ReverseIterator() {
	current = nullptr;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator=(
		const Map<Key_T, Mapped_T>::ReverseIterator &rev_iter) {

	current = rev_iter.get_current();
	return *this;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator++() {

	if (current == NULL) {
		return *this;
	}
	current = current->prev;
	return *this;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator++(
		int) {

	Map<Key_T, Mapped_T>::ReverseIterator rev_iter = *this;
	if (current == NULL) {
		return rev_iter;
	}
	current = current->prev;
	return rev_iter;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator& Map<Key_T, Mapped_T>::ReverseIterator::operator--() {

	if (current == NULL) {
		return *this;
	}
	current = current->next[0];
	return *this;

}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::ReverseIterator::operator--(
		int) {

	Map<Key_T, Mapped_T>::ReverseIterator rev_iter = *this;
	if (current == NULL) {
		return rev_iter;
	}
	current = current->prev;
	return rev_iter;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType& Map<Key_T, Mapped_T>::ReverseIterator::operator*() const {

	return *current->data;
}

template<typename Key_T, typename Mapped_T>
typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::ReverseIterator::operator->() const {

	return current->data;
}

// Comparison

template<typename Key_T, typename Mapped_T>
bool operator==(const Map<Key_T, Mapped_T> &map1,
		const Map<Key_T, Mapped_T> &map2) {

	if (map1.size() != map2.size()) {
		return false;
	}

	auto iter1 = map1.begin();
	auto iter2 = map2.begin();

	while (iter1 != map1.end() && iter2 != map2.end()) {
		if (*iter1 != *iter2) {
			return false;
		}
		++iter1;
		++iter2;
	}
	return true;
}

template<typename Key_T, typename Mapped_T>
bool operator!=(const Map<Key_T, Mapped_T> &map1,
		const Map<Key_T, Mapped_T> &map2) {

	return !(map1 == map2);
}

template<typename Key_T, typename Mapped_T>
bool operator<(const Map<Key_T, Mapped_T> &map1,
		const Map<Key_T, Mapped_T> &map2) {

	size_t map1_size = map1.size();
	size_t map2_size = map2.size();

	// first compare sizes,
	if (map1_size > map2_size) {
		return false;
	}

	// if map1 is shorter than map2, then compare lexicographically. when you encounter the first element that is greater in map2, return false
	if (map1_size < map2_size) {

		auto iter1 = map1.begin();
		auto iter2 = map2.begin();

		while (iter1 != map1.end()) {
			if ((*iter2).first < (*iter1).first) {
				return false;
			}
			++iter1;
			++iter2;
		}
		return true;
	}

	// if map1 is shorter than map2, then see if all the corresponding position elements are equal
	if (map1_size < map2_size) {

		auto iter1 = map1.begin();
		auto iter2 = map2.begin();
		while (iter1 != map1.end()) {

			if (!((*iter1).first == (*iter2).first)) {
				return false;
			}

			++iter1;
			++iter2;
		}
		return true;
	}

	// If map1 is equal to map in size, check that all corresponsing position elements in map1 are less than map2
	if (map1_size == map2_size) {

		auto iter1 = map1.begin();
		auto iter2 = map2.begin();

		while (iter1 != map1.end()) {

			if (((*iter2).first < (*iter1).first)
					|| ((*iter1).first == (*iter2).first)) {
				return false;
			}

			++iter1;
			++iter2;

		}
		return true;
	}

	return false;
}

} // end namespase cs540

#endif /* MAP_HPP_ */
