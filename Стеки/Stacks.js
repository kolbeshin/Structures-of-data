class Stack {
    constructor() {
        this.s = new List(); // создает объект List и приписывает его элементу данных s
    }

    // проталкивает элемент v в текущий стек
    push(v) {
        this.s.prepend(v);
    }

    // выбирает самый верхний элемент из текущего стека и возвращает его
    pop() {
        this.s.first();
        return this.s.remove();
    }

    // если стек пустой - возвращет TRUE
    empty() {
        return (this.s.length() === 0);
    }

    // число элементов в текущем стеке
    size() {
        return this.s.length();
    }

    // возвращает самый верхний элемент стека (не меняет состояние стека, ничто не заносится и не выбирается)
    top() {
        return this.s.first();
    }

    // возвращает элемент непосредственно под верхним в стеке (не меняет состояние стека, ничто не заносится и не выбирается)
    nextToTop() {
        this.s.first();
        return this.s.next();
    }

    // возвращет самый нижний элемент (не меняет состояние стека, ничто не заносится и не выбирается)
    bottom() {
        return this.s.last();
    }
}


// шаблон класса ListNode
class ListNode {
    constructor(val) {
        this._val = val; // значение узла
        this._next = this; // связь к последующему узлу
        this._prev = this; // связь к предшествующему узлу
    }

    next() {
        return this._next; // перемещение к последующему узлу
    }

    prev() {
        return this._prev; // перемещение к предшествующему узлу
    }

    insert(node) {
        // включение узла в связанный список
        let c = this._next;
        node._next = c;
        node._prev = this;
        this._next = node;
        c._prev = node;
        return node;
    }

    remove() {
        // удаление узла из списка
        this._prev._next = this._next;
        this._next._prev = this._prev;
        this._next = this._prev = this;
        return this;
    }

    splice(node) {
        // слияние/разъединение двух узлов
        let an = this._next;
        let bn = node._next;
        this._next = bn;
        node._next = an;
        an._prev = node;
        bn._prev = this;
    }

    toString() {
        return `ListNode(${this._val})`; // для удобства вывода
    }
}


class List {
    constructor() {
        // конструктор создает и инициализирует пустой список, представленный одним головным узлом, со ссылками на себя
        this._length = 0;
        this.header = new ListNode(null);
        this.win = this.header;
    }

    // заносит новый элемент после окна и возвращает указатель на новый элемент
    insert(val) {
        let newNode = new ListNode(val);
        this.win.insert(newNode);
        this._length++;
        return val;
    }

    // prepend вставляет новый элемент в начало списка и возвращает указатель на новый элемент
    prepend(val) {
        let newNode = new ListNode(val);
        this.header.insert(newNode);
        this._length++;
        return val;
    }

    // append вставляет новый элемент в конец списка и возвращает указатель на новый элемент
    append(val) {
        let newNode = new ListNode(val);
        this.header.prev().insert(newNode);
        this._length++;
        return val;
    }

    // добавление списка l в конец текущего списка
    appendList(list) {
        let a = this.header.prev();
        a.splice(list.header);
        this._length += list._length;
        list.header.remove();
        list._length = 0;
        list.win = list.header;
        return this;
    }

    // удаляет элемент в окне, перемещает окно в предыдущую позицию и возвращает указатель на только что удаленный элемент
    remove() {
        if (this.win === this.header) {
            return null;
        }
        let val = this.win._val;
        this.win = this.win.prev();
        this.win.next().remove();
        this._length--;
        return val;
    }

    // замена элемента, находящегося в текущем окне, на элемент v
    setVal(val) {
        if (this.win !== this.header) {
            this.win._val = val;
        }
    }

    // возвращает элемент в окне, либо null, если окно в головной позиции
    getVal() {
        return this.win._val;
    }

    // перемещает окно в следующую позицию и возвращает указатель на элемент в новой позиции окна
    next() {
        this.win = this.win.next();
        return this.win._val;
    }

    // перемещает окно в предыдущую позицию и возвращает указатель на элемент в новой позиции окна
    prev() {
        this.win = this.win.prev();
        return this.win._val;
    }

    // переносит окно в первую позицию и возвращает указатель на элемент в новой позиции окна
    first() {
        this.win = this.header.next();
        return this.win._val;
    }

    // переносит окно в последнюю позицию и возвращает указатель на элемент в новой позиции окна
    last() {
        this.win = this.header.prev();
        return this.win._val;
    }

    // возвращает длину списка
    length() {
        return this._length;
    }

    // возвращает true, если окно находится в первой позиции
    isFirst() {
        return (this.win === this.header.next() && this._length > 0);
    }

    // возвращает true, если окно находится в последней позиции
    isLast() {
        return (this.win === this.header.prev() && this._length > 0);
    }

    // возвращает true, если окно находится в головной позиции
    isHead() {
        return (this.win === this.header);
    }
}
// пример использования
function reverse(arr) {
    let stack = new Stack();
    for (let i = 0; i < arr.length; i++) {
        stack.push(arr[i]);
    }
    for (let i = 0; i < arr.length; i++) {
        arr[i] = stack.pop();
    }
}

const main = () => {
    let arr = ['a', 'b', 'c', 'd', 'e'];
    console.log("Original array:", arr);
    
    reverse(arr);
    
    console.log("Reversed array:", arr); // ['e', 'd', 'c', 'b', 'a']
    
    // Пример работы со стеком
    let stack = new Stack();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    console.log("Top element:", stack.top()); // 3
    console.log("Next to top element:", stack.nextToTop()); // 2
    console.log("Bottom element:", stack.bottom()); // 1
    console.log("Popped element:", stack.pop()); // 3
    console.log("Stack size after pop:", stack.size()); // 2
};

main();
