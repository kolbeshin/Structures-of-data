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

// шаблон класса List
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

// функция загружает n элементов массива в список и возвращает указатель на этот список
function arrayToList(arr) {
    let list = new List();
    for (let val of arr) {
        list.append(val);
    }
    return list;
}

// функция возвращает наименьший элемент в списке s
function leastItem(list, cmp) {
    if (list.length() === 0) {
        return null;
    }
    let v = list.first();
    for (list.next(); !list.isHead(); list.next()) {
        if (cmp(list.getVal(), v) < 0) {
            v = list.getVal();
        }
    }
    return v;
}

const main = () => {
    let list = new List();
    list.append(10);
    list.append(20);
    list.prepend(5);

    console.log("First element:", list.first()); // 5
    console.log("Last element:", list.last()); // 20

    let arr = [3, 1, 4, 1, 5];
    let newList = arrayToList(arr);
    console.log("First element of new list:", newList.first()); // 3

    let least = leastItem(newList, (a, b) => a - b);
    console.log("Least item in the new list:", least); // 1
};

main();
