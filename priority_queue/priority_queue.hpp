#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
    template<class T>
    struct container{
        int count,_size;
        T *head;
        container(){
            count=0;
            _size=4;
            head=new T[_size]();
        }
        T& operator [](size_t x){
            return head[x];
        }
        void myalloc(){
            T * tmp=new T[_size*2]();
            for (int i=0; i<count; ++i) tmp[i]=head[i];
            _size*=2;
            delete []head;
            head=tmp;
        }
        void push_back(const T &x){
            if (count==_size) myalloc();
            head[count++]=x;
        }
        T& back(){
            return head[count-1];
        }
        ~container(){
            delete []head;
        }
        size_t size() const{
            return count;
        }
    };
    template<typename T, class Compare = std::less<T>>
    class priority_queue {
        struct node{
            T value;
            container<node*> sonlist;
            node (const T &v):value(v){
            }
            node* merge(node *other){
                if (Compare()(value,other->value)){
                    other->sonlist.push_back(this);
                    return other;
                }
                else{
                    sonlist.push_back(other);
                    return this;
                }
            }
        };
        node* root;
        size_t _size;
    public:
        /**
         * TODO constructors
         */
        void print_tree(int dep,node* x){
            std::cerr<<x->value<<" "<<dep<<std::endl;
            for (int i=0; i<x->sonlist.size(); ++i) print_tree(dep+1,x->sonlist[i]);
        }
        void print(){
            std::cerr<<"print"<<std::endl;
            print_tree(1,root);
        }
        priority_queue() {
            root=nullptr;
            _size=0;
        }
        //digui construct
        void construct(node *& p, node * const q){
            if (p) delete p;
            p=new node(q->value);
            for (int i=0; i<q->sonlist.size(); ++i){
                p->sonlist.push_back(new node(q->value));
                construct(p->sonlist.back(),q->sonlist[i]);
            }
        }
        priority_queue(const priority_queue &other) {
            //need to be done
            _size=other._size;
            root=nullptr;
            if (other.root!=nullptr) construct(root,other.root);
        }
        /**
         * TODO deconstructor
         */
        void Free(node *p){
            for (int i=0; i<p->sonlist.size(); ++i) Free(p->sonlist[i]);
            delete p;
        }
        ~priority_queue() {
            if (root!=nullptr) Free(root);
        }
        /**
         * TODO Assignment operator
         */
        priority_queue &operator=(const priority_queue &other) {
            //need to be done
            if (&other==this) return *this;

            if (root!=nullptr) Free(root);
            _size=other._size;
            root=nullptr;
            if (other.root!=nullptr) construct(root,other.root);

            return *this;
        }
        /**
         * get the top of the queue.
         * @return a reference of the top element.
         * throw container_is_empty if empty() returns true;
         */
        const T & top() const {
            if (empty()) throw container_is_empty();
            return root->value;
        }
        /**
         * TODO
         * push new element to the priority queue.
         */
        void push(const T &e) {
            if (root==nullptr){
                _size=1;
                root=new node(e);
                return;
            }
            priority_queue *tmp=new priority_queue();
            tmp->push(e);
            merge(*tmp);
            tmp->root=nullptr;
            delete tmp;
        }
        /**
         * TODO
         * delete the top element.
         * throw container_is_empty if empty() returns true;
         */
        void pop() {
//            std::cerr<<"pop"<<_size<<" "<<root->sonlist.size()<<std::endl;
            if (empty()) throw container_is_empty();
            --_size;
            if (root->sonlist.size()==0){
                delete root;
                root=nullptr;
                return;
            }
            node * * q=new node *[root->sonlist.size()*2];
            int l=0,r=0;
            for (int i=0; i<root->sonlist.size(); ++i) q[r++]=root->sonlist[i];
            while (l<r){
                if (l+1==r) break;
//                std::cerr<<"l:"<<l<<" "<<"r:"<<r<<" "<<q[l]<<" "<<q[l+1]<<" "<<(q[l]->value)<<" "<<(q[l+1]->value)<<std::endl;
                q[r++]=(q[l]->merge(q[l+1]));
                l+=2;
                //std::cerr<<"mergeroot"<<r<<" "<<q[l]<<" "<<q[r-1]<<std::endl;
            }
            delete root;
            root=q[l];
            delete []q;
        }
        /**
         * return the number of the elements.
         */
        size_t size() const {
            return _size;
        }
        /**
         * check if the container has at least an element.
         * @return true if it is empty, false if it has at least an element.
         */
        bool empty() const {
            return size()==0;
        }
        /**
         * return a merged priority_queue with at least O(logn) complexity.
         */
        void merge(priority_queue &other) {
            //assert non-empty
            root=root->merge(other.root);
            _size+=other._size;

            other._size=0;
            other.root=nullptr;
        }
    };

}

#endif