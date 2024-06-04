class Node {
    constructor(id) {
        this._id = id; // Добавим идентификатор узла для удобства
        this._next = this;
        this._prev = this;
    }

    // Возвращает следующий узел
    next() {
        return this._next;
    }

    // Возвращает предыдущий узел
    prev() {
        return this._prev;
    }

    // Включает узел в связный список
    insert(b) {
        let c = this._next;
        b._next = c;
        b._prev = this;
        this._next = b;
        c._prev = b;
        return b;
    }

    // Удаляет узел из списка
    remove() {
        this._prev._next = this._next;
        this._next._prev = this._prev;
        this._next = this._prev = this;
        return this;
    }

    // Слияние/разъединение двух узлов
    splice(b) {
        let a = this;
        let an = a._next;
        let bn = b._next;
        a._next = bn;
        b._next = an;
        an._prev = b;
        bn._prev = a;
    }
    
    toString() {
        return `Node(${this._id})`;
    }
}

// Пример использования:
const main = () => {
    let node1 = new Node(1);
    let node2 = new Node(2);
    let node3 = new Node(3);

    console.log("Inserting nodes:");
    node1.insert(node2);
    node2.insert(node3);
    console.log(`node1.next() -> ${node1.next()}`); // Node(2)
    console.log(`node2.next() -> ${node2.next()}`); // Node(3)

    console.log("Removing node2:");
    node2.remove();
    console.log(`node1.next() -> ${node1.next()}`); // Node(3)
    console.log(`node3.prev() -> ${node3.prev()}`); // Node(1)

    console.log("Splicing nodes:");
    node1.splice(node3);
    console.log(`node1.next() -> ${node1.next()}`); // Node(3)
    console.log(`node3.prev() -> ${node3.prev()}`); // Node(1)
};

main();
