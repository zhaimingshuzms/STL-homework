//
// Created by Administrator on 2021/3/1.
//

#ifndef LIST_LIST_HPP
#define LIST_LIST_HPP
#include <cstdio>
#include <iostream>
namespace sjtu {
    template<class T>
    class list {
        struct node {
            T *value;
            node *ne;
            node *pre;

            node(const T &v) {
                value = new T(v);
                ne = nullptr;
                pre = nullptr;
            }
        };

        node *_head=nullptr;
        node *_tail=nullptr;
        size_t _size=0;
    public:
        class iterator{
            node *pos;
        public:
            iterator(node * const & p):pos(p){
            }
            iterator & operator ++(){
                pos=pos->ne;
                return *this;
            }
            const iterator operator ++(int){
                node *ret=pos;
                pos=pos->ne;
                return ret;
            }
            iterator operator +(const size_t & u){
                node *tmp=pos;
                for (size_t i=0; i<u; ++i) tmp=tmp->ne;
                return tmp;
            }
            iterator operator -(const size_t &u){
                node *tmp=pos;
                for (size_t i=0; i<u; ++i) tmp=tmp->pre;
                return tmp;
            }
            iterator operator --(){
                pos=pos->pre;
                return *this;
            }
            const iterator operator --(int){
                node *ret=pos;
                pos=pos->pre;
                return pos;
            }
            T& operator *(){
                return *(pos->value);
            }
            node * operator ->(){
                return pos;
            }
            bool available(){
                return pos!=nullptr;
            }
        };
        void unite(node *p, node *q) {
            node *tmp = p->ne;
            p->ne = q;
            q->ne = tmp;

            tmp = q->pre;
            q->pre = p;
            p->pre = tmp;
        }

        void push_back(const T &v) {
            if (_size++ == 0) {
                _head = _tail = new node(v);
                return;
            }
            node *tmp = new node(v);
            unite(_tail, tmp);
            _tail = tmp;
        }

        void push_front(const T &v) {
            if (_size++ == 0) {
                _head = _tail = new node(v);
                return;
            }
            node *tmp = new node(v);
            unite(tmp, _head);
            _head = tmp;
        }
        const iterator head(){
            return _head;
        }
        const iterator tail(){
            return iterator(_tail);
        }
        bool empty() {
            return _size==0;
        }
        size_t size(){
            return _size;
        }
    };
}

#endif //LIST_LIST_HPP
