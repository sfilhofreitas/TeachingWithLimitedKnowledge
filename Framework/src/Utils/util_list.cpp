#include "util_list.h"

int UtilList::getSize() const{
    return size;
}

int UtilList::getHeadValue() const{
    return this->head->data;
}

UtilList::UtilList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

UtilList::~UtilList(){
    this->eraseAll();
}

void UtilList::push_back(int data){
    if (!this->head){
        this->head = new Node;
        this->head->data = data;
        this->head->next = nullptr;
        this->head->prev = nullptr;
        this->tail = this->head;
    }else{
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = this->tail;
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->size ++;
}

void UtilList::push_back(Node *node, int data){
    if (!this->head){
        this->head = node;
        this->head->data = data;
        this->head->next = nullptr;
        this->head->prev = nullptr;
        this->tail = this->head;
    }else{
        node->data = data;
        node->next = nullptr;
        node->prev = this->tail;
        this->tail->next = node;
        this->tail = node;
    }
    this->size ++;
}

void UtilList::erase(Node *node){
    if(this->size == 1){
        this->head = nullptr;
        this->tail = nullptr;
        delete node;
    }else{
        if(!node->next){//it is the tail
            this->tail = node->prev;
            this->tail->next = nullptr;
            node->prev = nullptr;
            delete node;
        }else if(!node->prev){ //it is the head
            this->head = node->next;
            this->head->prev = nullptr;
            node->next = nullptr;
            delete node;
        }else{
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->next = nullptr;
            node->prev = nullptr;
            delete node;
        }
    }

   this->size --;
}

void UtilList::eraseAll(){
    while(this->head){
        if(this->head == this->tail){
            Node* node = this->head;
            this->head = nullptr;
            this->tail = nullptr;
            delete node;
        }else{
            Node* node = this->head;
            this->head = this->head->next;
            this->head->prev = nullptr;
            node->next = nullptr;
            delete node;
        }
    }
    this->size = 0;

}

void UtilList::print_list(){
    Node* next = this->head;
    while(next){
        cout << next->data<<" ";
        next = next->next;
    }
    cout<<"\n";

}
