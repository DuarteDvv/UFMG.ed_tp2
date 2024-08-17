#ifndef LIST
#define LIST

#include <iostream> 

#define MAXTAM 1000 

template<typename T>
class Container {

protected:
    int size;
    
public:
    Container(): size(0) {}
    int getSize() const { return size; } 
    bool empty() const { return size == 0; } 

    virtual T getObject(int pos) const = 0;
    virtual T removeBegin() = 0;
    virtual T removeEnd() = 0;
    virtual T removePos(int pos) = 0;
    virtual void setObject(T object, int pos) = 0;
    virtual void insertBegin(T object) = 0;
    virtual void insertEnd(T object) = 0;
    virtual void insertPos(T object, int pos) = 0;
    virtual void clear() = 0;
    
};

/////////////////////////////////////////////////////////

template<typename T>
class ArrayList : public Container<T> { 

private:
    T objects[MAXTAM];

public:
    //O(1)
    ArrayList(): Container<T>() {} 
    T getObject(int pos) const override;
    T removeBegin() override;
    T removeEnd() override;
    T removePos(int pos) override;
    void setObject(T item, int pos) override;
    void insertBegin(T object) override;
    void insertEnd(T object) override;
    void insertPos(T object, int pos) override;
    void clear() override;
};



//O(1)
template<typename T>
T ArrayList<T>::getObject(int pos) const {
    if(pos >= this->size || pos < 0) throw "ERROR: Invalid Position"; 
    return objects[pos];
}

//O(n)
template<typename T>
T ArrayList<T>::removeBegin() {
    if (this->size == 0) throw "ERROR: Empty";
    T aux = objects[0];
    for(int i = 0; i < this->size - 1; i++) objects[i] = objects[i+1]; 
    this->size--;
    return aux;
}

//O(1)
template<typename T>
T ArrayList<T>::removeEnd() {
    if (this->size == 0) throw "ERROR: Empty";
    T aux = objects[this->size - 1]; 
    this->size--;
    return aux;
}

//O(1) O(n)
template<typename T>
T ArrayList<T>::removePos(int pos) {
    if (this->size == 0) throw "ERROR: Empty";
    if(pos >= this->size || pos < 0) throw "ERROR: Invalid Position";
    T aux = objects[pos];
    for(int i = pos; i < this->size - 1; i++) objects[i] = objects[i+1]; 
    this->size--;
    return aux;
}

//O(1)
template<typename T>
void ArrayList<T>::setObject(T obj, int pos) {
    if(pos >= this->size || pos < 0) throw "ERROR: Invalid Position";
    objects[pos] = obj;
}

//O(n)
template<typename T>
void ArrayList<T>::insertBegin(T obj) {
    if (this->size == MAXTAM) throw "ERROR: Already full";
    this->size++;
    for(int i = this->size - 1; i > 0; i-- ) objects[i] = objects[i-1];
    objects[0] = obj;
}

//O(1)
template<typename T>
void ArrayList<T>::insertEnd(T obj) {
    if (this->size == MAXTAM) throw "ERROR: Already full";
    objects[this->size++] = obj; 
}

// Best: O(n) Worst: O(1)
template<typename T>
void ArrayList<T>::insertPos(T obj, int pos) {
    if (this->size == MAXTAM) throw "ERROR: Already full";
    if (pos > this->size || pos < 0) throw "ERROR: Invalid Position";
    for(int i = this->size++; i > pos; i-- ) objects[i] = objects[i-1];
    objects[pos] = obj;
    
}

//O(1)
template<typename T>
void ArrayList<T>::clear() {
    this->size = 0;

}

////////////////////////////////////////////

template<typename T> 
class LinkedList : public Container<T>
{
    private:
        Cell<T>* head;
        Cell<T>* tail;

        //O(n) O(1)
        Cell<T>* putPosition(int pos) const {
            if(pos > this->size || pos < 0) throw "ERROR: Invalid Position";

            Cell<T>* aux = head;
            for(int i = 0; i < pos; i++) aux = aux->next;

            return aux;
        };

    public:

        LinkedList(): Container<T>() , head(new Cell<T>()), tail(head) {};
        //O(n)
        ~LinkedList(){ 
            Cell<T>* aux;
            while(head != nullptr){
                aux = head;
                head = head->next;
                delete aux;
            }
            head = nullptr;
            tail = nullptr;
        };

        T getObject(int pos) const override;
        T removeBegin() override;
        T removeEnd() override;
        T removePos(int pos) override;
        void setObject(T item, int pos) override;
        void insertBegin(T object) override;
        void insertEnd(T object) override;
        void insertPos(T object, int pos) override;
        void clear() override;

};



//O(1) O(n)
template<typename T>
T LinkedList<T>::getObject(int pos) const {

    return putPosition(pos + 1)->object; 
}

//O(1)
template<typename T>
T LinkedList<T>::removeBegin() {
    if (this->size == 0) throw "ERROR: Empty";

    Cell<T>* p = head->next;
    head->next = p->next;
    this->size--; 
    if (head->next == nullptr) tail = head;

    T aux = p->object;
    delete p;

    return aux;
}


// O(n)
template<typename T>
T LinkedList<T>::removeEnd() {
    if (this->size == 0) throw "ERROR: Empty";

    
    Cell<T>* p = putPosition(this->size - 1); 
    T aux = tail->object;
    delete tail;
    tail = p;
    tail->next = nullptr; 
    this->size--;

    return aux;
}

//O(1) O(n)
template<typename T>
T LinkedList<T>::removePos(int pos) {
    if (this->size == 0) throw "ERROR: Empty";

    T aux;
    Cell<T>* q;
    Cell<T>* p = putPosition(pos);
    q = p->next;
    p->next = q->next;
    this->size--;
    aux = q->object;
    delete q;
    if(p->next == nullptr) tail = p;
    return aux;
    
}

//O(1) O(n)
template<typename T>
void LinkedList<T>::setObject(T obj, int pos) {
    
    putPosition(pos + 1)->object = obj; 
}

//O(1)
template<typename T>
void LinkedList<T>::insertBegin(T obj) {
    Cell<T>* newCell = new Cell<T>();
    newCell->object = obj;
    newCell->next = head->next; 
    head->next = newCell; 
    this->size++;

    if (newCell->next == nullptr) tail = newCell;
}

//O(1)
template<typename T>
void LinkedList<T>::insertEnd(T obj) {
    Cell<T>* newCell = new Cell<T>();
    newCell->object = obj;
    tail->next = newCell;
    tail = newCell;
    this->size++;
   
}

//O(1) O(n)
template<typename T>
void LinkedList<T>::insertPos(T obj, int pos) {
    if (pos < 0 || pos > this->size) throw "ERROR: Invalid Position"; 

    Cell<T>* p = putPosition(pos);
    Cell<T>* newCell = new Cell<T>();
    newCell->object = obj;
    newCell->next = p->next;
    p->next = newCell;
    this->size++;

    if (newCell->next == nullptr) tail = newCell; 
}

//O(1)
template<typename T>
void LinkedList<T>::clear() {
    Cell<T>* p = head->next;
    while(p != nullptr){
        head->next = p->next;
        delete p;
        p = head->next;

    }
    tail = head;
    this->size = 0;
}

///////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList : public Container<T> {
private:
    struct DoublyCell {
        T data;
        DoublyCell* next;
        DoublyCell* prev;
        DoublyCell(const T& newData, DoublyCell* newNext = nullptr, DoublyCell* newPrev = nullptr)
            : data(newData), next(newNext), prev(newPrev) {}
    };

    DoublyCell* head;
    DoublyCell* tail;

    //O(n/2) O(1)
    DoublyCell* getDoublyCell(int pos) const{
        if (pos < 0 || pos >= this->size) throw "ERROR: Invalid Position";

        if (pos < this->size / 2) {
            DoublyCell* current = head->next;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            return current;
        } else {
            DoublyCell* current = tail;
            for (int i = this->size - 1; i > pos; --i) {
                current = current->prev;
            }
            return current;
        }
    };

public:
    DoublyLinkedList() : Container<T>(), head(new DoublyCell(T())), tail(head) {}

    ~DoublyLinkedList(){
        DoublyCell* current = head;
        while (current != nullptr) {
            DoublyCell* next = current->next;
            delete current;
            current = next;
        }
    };  

    T getObject(int pos) const override;
    T removeBegin() override;
    T removeEnd() override;
    T removePos(int pos) override;
    void setObject(T item, int pos) override;
    void insertBegin(T object) override;
    void insertEnd(T object) override;
    void insertPos(T object, int pos) override;
    void clear() override;
};



//O(1) O(n/2)
template<typename T>
T DoublyLinkedList<T>::getObject(int pos) const {
    DoublyCell* Cell = getDoublyCell(pos);
    return Cell->data;
}

//O(1)
template<typename T>
T DoublyLinkedList<T>::removeBegin() {
    if (this->size == 0) throw "ERROR: Empty";

    DoublyCell* toDelete = head->next;
    T data = toDelete->data;
    head->next = toDelete->next;
    if (toDelete->next != nullptr) {
        toDelete->next->prev = head;
    } else {
        tail = head;
    }
    delete toDelete;
    this->size--;
    return data;
}

//O(1)
template<typename T>
T DoublyLinkedList<T>::removeEnd() {
    if (this->size == 0) throw "ERROR: Empty";
    DoublyCell* toDelete = tail;
    T data = toDelete->data;
    tail = toDelete->prev;
    tail->next = nullptr;
    delete toDelete;
    this->size--;
    return data;
}

//O(n/2) O(1)
template<typename T>
T DoublyLinkedList<T>::removePos(int pos) {
    if (this->size == 0) throw "ERROR: Empty";

    DoublyCell* toDelete = getDoublyCell(pos);
    T data = toDelete->data;
    toDelete->prev->next = toDelete->next;
    if (toDelete->next != nullptr) {
        toDelete->next->prev = toDelete->prev;
    } else {
        tail = toDelete->prev;
    }
    delete toDelete;
    this->size--;
    return data;
}

//O(n/2) O(1)
template<typename T>
void DoublyLinkedList<T>::setObject(T item, int pos) {
    DoublyCell* DoublyCell = getDoublyCell(pos);
    DoublyCell->data = item;
}

//O(1)
template<typename T>
void DoublyLinkedList<T>::insertBegin(T object) {
    DoublyCell* newDoublyCell = new DoublyCell(object, head->next, head);
    if (head->next != nullptr) {
        head->next->prev = newDoublyCell;
    } else {
        tail = newDoublyCell;
    }
    head->next = newDoublyCell;
    this->size++;
}

//O(1)
template<typename T>
void DoublyLinkedList<T>::insertEnd(T object) {
    DoublyCell* newDoublyCell = new DoublyCell(object, nullptr, tail);
    tail->next = newDoublyCell;
    tail = newDoublyCell;
    this->size++;
}

//O(n/2) O(1)
template<typename T>
void DoublyLinkedList<T>::insertPos(T object, int pos) {
    if (pos < 0 || pos > this->size) throw "ERROR: Invalid Position";
    if (pos == this->size) {
        insertEnd(object);
        return;
    }
    DoublyCell* nextDoublyCell = getDoublyCell(pos);
    DoublyCell* prevDoublyCell = nextDoublyCell->prev;
    DoublyCell* newDoublyCell = new DoublyCell(object, nextDoublyCell, prevDoublyCell);
    nextDoublyCell->prev = newDoublyCell;
    if (prevDoublyCell != nullptr) {
        prevDoublyCell->next = newDoublyCell;
    } else {
        head->next = newDoublyCell;
    }
    this->size++;
}

//O(n)
template<typename T>
void DoublyLinkedList<T>::clear() {
    DoublyCell* current = head->next;
    while (current != nullptr) {
        DoublyCell* next = current->next;
        delete current;
        current = next;
    }
    tail = head;
    head->next = nullptr; 
    this->size = 0;
}

////////////////////////////////////////////////////

template<typename T>
class SortedLinkedList : public Container<T> {
    private:
        Cell<T>* head;
        Cell<T>* tail;

        //O(n) O(1)
        Cell<T>* putPosition(int pos) const {
            if(pos > this->size || pos < 0) throw "ERROR: Invalid Position";

            Cell<T>* aux = head;
            for(int i = 0; i < pos; i++) aux = aux->next;

            return aux;
        };

    public:

        SortedLinkedList(): Container<T>() , head(new Cell<T>()), tail(head) {};
        //O(n)
        ~SortedLinkedList(){ 
            Cell<T>* aux;
            while(head != nullptr){
                aux = head;
                head = head->next;
                delete aux;
            }
            head = nullptr;
            tail = nullptr;
        };

        T getObject(int pos) const override;
        T removeBegin() override;
        T removeEnd() override;
        T removePos(int pos) override;
        void insert(T object);
        void clear() override;

        //Not used
        void setObject(T item, int pos) override {};
        void insertBegin(T object) override {};
        void insertEnd(T object) override {};
        void insertPos(T object, int pos) override {};

};



//O(1) O(n)
template<typename T>
T SortedLinkedList<T>::getObject(int pos) const {

    return putPosition(pos + 1)->object; 
}

//O(1)
template<typename T>
T SortedLinkedList<T>::removeBegin() {
    if (this->size == 0) throw "ERROR: Empty";

    Cell<T>* p = head->next;
    head->next = p->next;
    this->size--; 
    if (head->next == nullptr) tail = head;

    T aux = p->object;
    delete p;

    return aux;
}


// O(n)
template<typename T>
T SortedLinkedList<T>::removeEnd() {
    if (this->size == 0) throw "ERROR: Empty";

    
    Cell<T>* p = putPosition(this->size - 1); 
    T aux = tail->object;
    delete tail;
    tail = p;
    tail->next = nullptr; 
    this->size--;

    return aux;
}

//O(1) O(n)
template<typename T>
T SortedLinkedList<T>::removePos(int pos) {
    if (this->size == 0) throw "ERROR: Empty";

    T aux;
    Cell<T>* q;
    Cell<T>* p = putPosition(pos);
    q = p->next;
    p->next = q->next;
    this->size--;
    aux = q->object;
    delete q;
    if(p->next == nullptr) tail = p;
    return aux;
    
}

//O(1) O(n)
template<typename T>
void SortedLinkedList<T>::insert(T obj) {
    Cell<T>* newCell = new Cell<T>();
    newCell->object = obj; 

    if (this->size == 0) {
        head->next = newCell;
        tail = newCell;
    } else {
        Cell<T>* current = head->next;
        Cell<T>* previous = head;
               
        while (current != nullptr && obj > current->object) {
            previous = current;
            current = current->next;
        }
         
        newCell->next = current;
        previous->next = newCell;
    }

    this->size++; 
}


//O(1)
template<typename T>
void SortedLinkedList<T>::clear() {
    Cell<T>* p = head->next;
    while(p != nullptr){
        head->next = p->next;
        delete p;
        p = head->next;

    }
    tail = head;
    this->size = 0;
}

/////////////////////////////////////////////////////////////////

template<typename T>
class Vector : public Container<T> {
private:
    T* objects;
    int capacity;

    void resize(int newCapacity);

public:
    Vector() : Container<T>(), objects(nullptr), capacity(0) {}
    ~Vector() {
        delete[] objects;
    }

    T getObject(int pos) const override;
    T removeBegin() override;
    T removeEnd() override;
    T removePos(int pos) override;
    void setObject(T item, int pos) override;
    void insertBegin(T object) override;
    void insertEnd(T object) override;
    void insertPos(T object, int pos) override;
    void clear() override;
};



//O(1)
template<typename T>
T Vector<T>::getObject(int pos) const {
    if (pos < 0 || pos >= this->size) throw "ERROR: Invalid Position";
    return objects[pos];
}

//O(1)
template<typename T>
T Vector<T>::removeBegin() {
    if (this->size == 0) throw "ERROR: Empty";
    T aux = objects[0];
    for (int i = 0; i < this->size - 1; i++) objects[i] = objects[i + 1];
    this->size--;
    return aux;
}

//O(1)
template<typename T>
T Vector<T>::removeEnd() {
    if (this->size == 0) throw "ERROR: Empty";
    T aux = objects[this->size - 1];
    this->size--;
    return aux;
}

//O(1)
template<typename T>
T Vector<T>::removePos(int pos) {
    if (this->size == 0) throw "ERROR: Empty";
    if (pos < 0 || pos >= this->size) throw "ERROR: Invalid Position";
    T aux = objects[pos];
    for (int i = pos; i < this->size - 1; i++) objects[i] = objects[i + 1];
    this->size--;
    return aux;
}

//O(1)
template<typename T>
void Vector<T>::setObject(T obj, int pos) {
    if (pos < 0 || pos >= this->size) throw "ERROR: Invalid Position";
    objects[pos] = obj;
}

//O(n)
template<typename T>
void Vector<T>::insertBegin(T obj) {
    if (this->size == capacity) {
        resize((capacity == 0) ? 1 : capacity * 2);
    }
    this->size++;
    for (int i = this->size - 1; i > 0; i--) objects[i] = objects[i - 1];
    objects[0] = obj;
}

//O(n)
template<typename T>
void Vector<T>::insertEnd(T obj) {
    if (this->size == capacity) {
        resize((capacity == 0) ? 1 : capacity * 2);
    }
    objects[this->size++] = obj;
}

//O(n)
template<typename T>
void Vector<T>::insertPos(T obj, int pos) {
    if (pos < 0 || pos > this->size) throw "ERROR: Invalid Position";
    if (this->size == capacity) {
        resize((capacity == 0) ? 1 : capacity * 2);
    }
    for (int i = this->size++; i > pos; i--) objects[i] = objects[i - 1];
    objects[pos] = obj;
}

//O(1)
template<typename T>
void Vector<T>::clear() {
    this->size = 0;
    this->capacity = 0;
    delete[] this->objects;
    this->objects = nullptr;
}

//O(n)
template<typename T>
void Vector<T>::resize(int newCapacity) {
    T* newObjects = new T[newCapacity];
    for (int i = 0; i < this->size; ++i) {
        newObjects[i] = this->objects[i];
    }
    delete[] this->objects;
    this->objects = newObjects;
    this->capacity = newCapacity;
}



#endif 
