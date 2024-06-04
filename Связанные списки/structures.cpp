#include <iostream>

class Node {
protected:
    Node *_next; // связь к последующему узлу
    Node *_prev; // связь к предшествующему узлу
public:
    Node (void); 
    virtual ~Node (void);
    Node *next(void);
    Node *prev(void);
    Node *insert(Node*);
    Node *remove(void);
    void splice(Node*);
};

// конструктор, формирует новый узел, который имеет двойную ссылку на себя
Node::Node(void)
{
    _next(this), _prev(this);
}

// деконструктор отвечает за удаление объекта
Node::~Node(void)
{
}

// компонентные функции next и prev используются для перемещения из этого узла к последователю или предшественнику 
Node *Node::next(void)
{
    return _next;
}

Node *Node::prev(void)
{
    return _prev;
}

// Включение узла в связный список

Node *Node::insert(Node *b)
{
    Node *c = _next;
    b -> _next = c;
    b -> _prev = this;
    _next = b;
    c -> _prev = b;
    return b;
}

// Удаление узла из списка

Node *Node::remove(void)
{
    _prev->_next = _next;
    _next-> _prev=_prev;
    _next = _prev = this;
    return this;
}

// Слияние/разъединение 2 узлов 
void Node::splice (Node *b)
{
    Node *a = this;
    Node *an = a -> _next; // устанавливаем ссылку из a на b->_next (на последователя узла b)
    Node *bn = b -> _next; // устанавливаем ссылку из b на a->_next (на последователя узла a)
    a ->_next = bn; // для новго последователя узла a устанавливаем обратную ссылку на a
    b ->_next = an; // для новго последователя узла b устанавливаем обратную ссылку на b
    an->_prev = b;
    bn ->_prev = a;
}




int main()
{



}