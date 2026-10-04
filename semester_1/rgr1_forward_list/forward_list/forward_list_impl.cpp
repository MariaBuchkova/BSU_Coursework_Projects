#include "forward_list_impl.h"

void ForwardList::PushBack(int32_t value) {
    Node* new_node = new Node(value);
    if (begin_ == nullptr) {
        begin_ = new_node;
    } else {
        Node* end = begin_;
        while (end->next_ != nullptr) {
            end = end->next_;
        }
        end->next_ = new_node;
    }
    ++size_;
}


ForwardList::ForwardList(){}
ForwardList::ForwardList(const ForwardList& other){
    Node* buf = other.begin_;
    while (buf != nullptr) {
        PushBack(buf->value_);
        buf = buf->next_;
    }
}
ForwardList::ForwardList(size_t count, int32_t value) : size_(0) {
    for (size_t i = 0; i < count; ++i) {
        PushBack(value);
    }
}
ForwardList::ForwardList(std::initializer_list<int32_t> list) {
    for (int32_t x : list) {
        PushBack(x);
    }
}
ForwardList::~ForwardList() { 
    Clear();
}
ForwardList& ForwardList::operator=(const ForwardList& other) {
    if (this != &other) {
        Clear();
        Node* buf = other.begin_;
        while (buf != nullptr) {
            PushBack(buf->value_);
            buf = buf->next_;
        }
    }
    return *this;
}


void ForwardList::PushFront(int32_t value) {
    Node* p = new Node(value);
    p->next_ = begin_;
    begin_ = p;
    ++size_;
}
void ForwardList::PopFront() {
    if (begin_ == nullptr) {
        throw "Error, list is empty";
    }
    Node* buf = begin_;
    begin_ = begin_->next_;
    delete buf;
    --size_;
}
int32_t ForwardList::Front() const {
    if (begin_ == nullptr) {
        throw "Error, list is empty";
    }
    return begin_->value_;
}

void ForwardList::Clear() {
    while (begin_ != nullptr) {
        PopFront();
    }
}

size_t ForwardList::Size() const {
    return size_;
}

void ForwardList::Print(std::ostream& out) {
    if (begin_ != nullptr) {
        Node* buf = begin_;
        out << buf->value_;
        buf = buf->next_;
        while (buf != nullptr) {
            out << ' ' << buf->value_;
            buf = buf->next_;
        }
    }
}

bool ForwardList::FindByValue(int32_t value) {
    Node* buf = begin_;
    while (buf != nullptr) {
        if (buf->value_ == value) {
            return true;
        }
        buf = buf->next_;
    }
    return false;
}
void ForwardList::Remove(int32_t value) {
    
    while (begin_ != nullptr && begin_->value_ == value) {
        Node* temp = begin_;
        begin_ = begin_->next_;
        delete temp;
        --size_;
    }

    if (begin_ == nullptr)
        return;

    Node* curr = begin_;
    while (curr->next_ != nullptr) {
        if (curr->next_->value_ == value) {
            Node* temp = curr->next_;
            curr->next_ = temp->next_;
            delete temp;     
            --size_;
        } else {
            curr = curr->next_;
        }
    }
}
