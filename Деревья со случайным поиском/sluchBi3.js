// Класс узла дерева со случайным приоритетом
class RandomizedNode {
    constructor(val, seed = -1) {
        this.val = val;
        this._parent = null;
        this._lchild = null;
        this._rchild = null;
        this._next = null;
        this._prev = null;
        this._priority = this.generatePriority(seed); // Присваивает новому узлу случайное значение приоритета
    }

    generatePriority(seed) {
        if (seed !== -1) {
            Math.seedrandom(seed); // Инициализация генератора случайных чисел
        }
        return Math.random(); // Генерация случайного приоритета
    }

    // Выполняет правую ротацию для текущего узла
    rotateRight() {
        const y = this;
        const x = y.lchild();
        const p = y.parent();
        y._lchild = x.rchild();
        if (y.lchild() !== null) y.lchild()._parent = y;
        if (p.rchild() === y) p._rchild = x;
        else p._lchild = x;
        x._parent = p;
        x._rchild = y;
        y._parent = x;
    }

    // Выполняет левую ротацию для текущего узла
    rotateLeft() {
        const x = this;
        const y = x.rchild();
        const p = x.parent();
        x._rchild = y.lchild();
        if (x.rchild() !== null) x.rchild()._parent = x;
        if (p.lchild() === x) p._lchild = y;
        else p._rchild = y;
        y._parent = p;
        y._lchild = x;
        x._parent = y;
    }

    // Переносит текущий узел вверх по направлению к корню
    bubbleUp() {
        let p = this.parent();
        if (this.priority() < p.priority()) {
            if (p.lchild() === this) p.rotateRight();
            else p.rotateLeft();
            this.bubbleUp();
        }
    }

    // Переносит текущий узел вниз по направлению к внешним узлам
    bubbleDown() {
        const lcPriority = this.lchild() ? this.lchild().priority() : 2.0;
        const rcPriority = this.rchild() ? this.rchild().priority() : 2.0;
        const minPriority = Math.min(lcPriority, rcPriority);

        if (this.priority() <= minPriority) return;

        if (lcPriority < rcPriority) this.rotateRight();
        else this.rotateLeft();

        this.bubbleDown();
    }

    // Определяет правого потомка текущего узла
    rchild() {
        return this._rchild;
    }

    // Определяет левого потомка текущего узла
    lchild() {
        return this._lchild;
    }

    // Определяет следующий узел относительно текущего
    next() {
        return this._next;
    }

    // Определяет предыдущий узел относительно текущего
    prev() {
        return this._prev;
    }

    // Определяет узел-предок текущего узла
    parent() {
        return this._parent;
    }

    // Возвращает приоритет текущего узла
    priority() {
        return this._priority;
    }
}

// Класс дерева со случайным поиском
class RandomizedSearchTree {
    constructor(cmp, seed = -1) {
        this.cmp = cmp;
        this.win = this.root = new RandomizedNode(null, seed);
        this.root._priority = -1.0;
        this.root._next = this.root;
        this.root._prev = this.root;
    }

    // Переходит к следующему узлу в дереве
    next() {
        this.win = this.win.next();
        return this.win.val;
    }

    // Переходит к предыдущему узлу в дереве
    prev() {
        this.win = this.win.prev();
        return this.win.val;
    }

    // Возвращает значение текущего узла
    val() {
        return this.win.val;
    }

    // Обход дерева в порядке возрастания
    inorder(visit) {
        let n = this.root.next();
        while (n !== this.root) {
            visit(n.val);
            n = n.next();
        }
    }

    // Проверяет, является ли текущий узел первым в дереве
    isFirst() {
        return this.win === this.root.next() && this.root !== this.root.next();
    }

    // Проверяет, является ли текущий узел последним в дереве
    isLast() {
        return this.win === this.root.prev() && this.root !== this.root.next();
    }

    // Проверяет, является ли текущий узел головным
    isHead() {
        return this.win === this.root;
    }

    // Проверяет, пусто ли дерево
    isEmpty() {
        return this.root === this.root.next();
    }

    // Находит элемент в дереве
    find(val) {
        let n = this.root.rchild();
        while (n) {
            const result = this.cmp(val, n.val);
            if (result < 0) n = n.lchild();
            else if (result > 0) n = n.rchild();
            else {
                this.win = n;
                return n.val;
            }
        }
        return null;
    }

    // Находит минимальный элемент в дереве
    findMin() {
        this.win = this.root.next();
        return this.win.val;
    }

    // Возвращается наибольший элемент в дереве, который не больше, чем значение val
    locate(val) {
        let b = this.root;
        let n = this.root.rchild();
        while (n) {
            const result = this.cmp(val, n.val);
            if (result < 0) n = n.lchild();
            else if (result > 0) {
                b = n;
                n = n.rchild();
            } else {
                this.win = n;
                return this.win.val;
            }
        }
        this.win = b;
        return this.win.val;
    }

    // Включает элемент в текущее дерево случайного поиска и перемещает окно на этот элемент
    insert(val) {
        // Этап 1: Найдем внешний узел
        let result = 1;
        let p = this.root;
        let n = this.root.rchild();
        while (n) {
            p = n;
            result = this.cmp(val, p.val);
            if (result < 0) n = p.lchild();
            else if (result > 0) n = p.rchild();
            else return null;
        }
        this.win = new RandomizedNode(val);
        this.win._parent = p;
        if (result < 0) {
            p._lchild = this.win;
            this.win._next = p;
            this.win._prev = p._prev;
            if (p._prev) p._prev._next = this.win;
            p._prev = this.win;
        } else {
            p._rchild = this.win;
            this.win._next = p._next;
            this.win._prev = p;
            if (p._next) p._next._prev = this.win;
            p._next = this.win;
        }

        // Этап 2: Поднимаем его по дереву по направлению к корню в соответствии с его приоритетом
        this.win.bubbleUp();
        return val;
    }
}

// Пример функции сравнения
function compare(a, b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// Пример использования
const tree = new RandomizedSearchTree(compare);
tree.insert(5);
tree.insert(3);
tree.insert(7);
tree.insert(1);
tree.insert(4);
tree.insert(6);
tree.insert(8);

tree.inorder(console.log); // выводит элементы дерева в порядке возрастания
console.log('Минимальный элемент:', tree.findMin()); // выводит минимальный элемент
console.log('Элемент 4 найден:', tree.find(4)); // выводит 4
console.log('Элемент 10 найден:', tree.find(10)); // выводит null, так как элемента 10 в дереве нет

