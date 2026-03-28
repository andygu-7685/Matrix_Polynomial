#ifndef LIST_SORTED_H
#define LIST_SORTED_H
#include "../../includes/linked_list_functions/linked_list_functions.h"
#include <iostream>
using namespace std;

template <class T>
class List {
public:

    class Iterator {
    public:
        friend class List; // give access to List to access _ptr

        Iterator() { _ptr = NULL; } // default ctor

        Iterator(node<T>* p) { _ptr = p; } // Point Iterator to where p is pointing to

        T& operator*() { return _ptr->_item; } // dereference operator

        T* operator->() { return &_ptr->_item; } // member access operator

        bool is_null() { return _ptr == nullptr; } // true if _ptr is NULL
        node<T>* get_ptr() { return _ptr; } 

        friend bool operator!=(const Iterator& left, const Iterator& right) { return left._ptr != right._ptr; } // true if left != right
        friend bool operator==(const Iterator& left, const Iterator& right) { return left._ptr == right._ptr; } // true if left == right

        Iterator& operator++() { // member operator:  ++it; or  ++it = new_value
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused) { // friend operator: it++
            Iterator temp = it;
            ++it;
            return temp;
        }

        Iterator& operator--() { // member operator:  ++it; or  ++it = new_value
            _ptr = _ptr->_prev;
            return *this;
        }

        friend Iterator operator--(Iterator& it, int unused) { // friend operator: it++
            Iterator temp = it;
            --it;
            return temp;
        }

    private:
        node<T>* _ptr; // pointer being encapsulated
    };

    List(bool order = true, bool unique = false) // CTOR: default args
    {
        _head_ptr = nullptr;
        _order = order;
        _unique = unique;
        _size = 0;
    }

    // BIG 3:
    ~List() {
        _clear_list(_head_ptr);
        _size = 0;
    }

    void clear() {
        _clear_list(_head_ptr);
        _size = 0;
    }

    List(const List<T>& copyThis) {
        _head_ptr = nullptr;
        _copy_list(_head_ptr, copyThis._head_ptr);
        _size = copyThis._size;
        _order = copyThis._order;
        _unique = copyThis._unique;
    }

    List& operator=(const List& RHS) {
        if (this != &RHS) { // Self-assignment check
            _clear_list(_head_ptr);
            _head_ptr = _copy_list(RHS._head_ptr);
            _order = RHS._order;
            _unique = RHS._unique;
            _size = RHS._size;
        }
        return *this;
    }

    Iterator insert(const T& i) { // Insert i
        _size++;
        return _insert_sorted(_head_ptr, i, _order);
    }

    Iterator insert_and_add(const T& i) { // Insert i
        node<T>* found = _search_list(_head_ptr, i);
        if (_unique && found) { // Unique mode and item already exists
            found->_item += i;
            return found;
        }
        else {
            _size++;
            return _insert_sorted(_head_ptr, i, _order);
        }
    }

    T Delete(List<T>::Iterator iMarker) { // delete node at marker
        T deleted_value = _delete_node(_head_ptr, iMarker._ptr);
        _size--;
        return deleted_value;
    }

    void Print() const {
        _print_list(_head_ptr);
    }

    Iterator search(const T& key) const { // return Iterator to node [key]
        return _search_list(_head_ptr, key);
    }

    Iterator prev(Iterator iMarker) { // previous node: marker
        return _previous_node(_head_ptr, iMarker._ptr);
    }

    const T& operator[](int index) const { // const version of the operator [ ]
        return _at(_head_ptr, index);
    }

    T& operator[](int index) {
        return _at(_head_ptr, index);
    }

    Iterator begin() const {
        return _head_ptr;
    }

    Iterator end() const {
        return nullptr;
    }

    Iterator last_node() const {
        return _last_node(_head_ptr);
    }

    bool empty() const { return _head_ptr == nullptr; }

    template <class U>
    friend ostream& operator<<(ostream& outs, const List<U>& l);

    int size() const { return _size; }

private:
    node<T>* _head_ptr;
    bool _order;
    bool _unique;
    int _size;
};

template <class U>
ostream& operator<<(ostream& outs, const List<U>& l) {
    _print_list(l._head_ptr);
    return outs;
}

#endif
