// Определение класса Node
class Node {
    constructor() {
        this._next = null;
        this._prev = null;
    }

    insert(node) {
        node._next = this._next;
        node._prev = this;
        if (this._next) {
            this._next._prev = node;
        }
        this._next = node;
    }

    remove() {
        if (this._prev) {
            this._prev._next = this._next;
        }
        if (this._next) {
            this._next._prev = this._prev;
        }
    }

    next() {
        return this._next;
    }

    prev() {
        return this._prev;
    }
}

// Определение класса TreeNode
class TreeNode {
    constructor(val) {
        this.val = val;
        this._lchild = null;
        this._rchild = null;
    }

    lchild() {
        return this._lchild;
    }

    rchild() {
        return this._rchild;
    }
}

// Определение класса BraidedNode, наследующего Node и TreeNode
class BraidedNode extends Node {
    constructor(val) {
        super();
        this.val = val;
        this._lchild = null;
        this._rchild = null;
    }

    lchild() {
        return this._lchild;
    }

    rchild() {
        return this._rchild;
    }

    next() {
        return super.next();
    }

    prev() {
        return super.prev();
    }
}

// Определение класса BraidedSearchTree
class BraidedSearchTree {
    constructor(cmp) {
        this.root = new BraidedNode(null);
        this.win = this.root;
        this.cmp = cmp;
    }

    // Симметричный обход дерева
    inorder(visit) {
        let n = this.root.next();
        while (n !== this.root && n !== null) {
            if (n.val !== null) {
                visit(n.val);
            }
            n = n.next();
        }
    }

    // Вставка элемента
    insert(val) {
        let result = 1;
        let p = this.root;
        let n = this.root.rchild();
        while (n) {
            p = n;
            result = this.cmp(val, p.val);
            if (result < 0) {
                n = p.lchild();
            } else if (result > 0) {
                n = p.rchild();
            } else {
                return null;
            }
        }
        this.win = new BraidedNode(val);
        if (result < 0) {
            p._lchild = this.win;
            if (p.prev()) {
                p.prev().insert(this.win);
            }
        } else {
            p._rchild = this.win;
            p.insert(this.win);
        }
        return val;
    }

    // Удаление элемента
    remove() {
        if (this.win !== this.root) {
            this._remove(this.win.val, this.root._rchild);
        }
    }

    // Вспомогательный метод удаления
    _remove(val, n) {
        if (!n) return;
        let result = this.cmp(val, n.val);
        if (result < 0) {
            this._remove(val, n._lchild);
        } else if (result > 0) {
            this._remove(val, n._rchild);
        } else {
            if (n._lchild === null) {
                let old = n;
                if (this.win === old) {
                    this.win = old.prev();
                }
                n = old.rchild();
                old.remove();
            } else if (n._rchild === null) {
                let old = n;
                if (this.win === old) {
                    this.win = old.prev();
                }
                n = old.lchild();
                old.remove();
            } else {
                let m = n.next();
                if (m) {
                    n.val = m.val;
                    this._remove(m.val, n._rchild);
                }
            }
        }
    }

    // Удаление минимального элемента
    removeMin() {
        let minNode = this.root.next();
        if (minNode) {
            let val = minNode.val;
            if (this.root !== minNode) {
                this._remove(val, this.root._rchild);
            }
            return val;
        }
        return null;
    }

    // Поиск элемента
    find(val) {
        let n = this.root.rchild();
        while (n) {
            let result = this.cmp(val, n.val);
            if (result < 0) {
                n = n.lchild();
            } else if (result > 0) {
                n = n.rchild();
            } else {
                this.win = n;
                return n.val;
            }
        }
        return null;
    }

    // Поиск минимального элемента
    findMin() {
        this.win = this.root.next();
        return this.win ? this.win.val : null;
    }

    // Проверка, пустое ли дерево
    isEmpty() {
        return this.root === this.root.next();
    }

    // Проверка, является ли текущий узел первым
    isFirst() {
        return this.win === this.root.next() && this.root !== this.root.next();
    }

    // Проверка, является ли текущий узел последним
    isLast() {
        return this.win === this.root.prev() && this.root !== this.root.next();
    }

    // Переход к следующему элементу
    next() {
        if (this.win && this.win.next() !== null) {
            this.win = this.win.next();
            return this.win.val;
        }
        return null;
    }

    // Переход к предыдущему элементу
    prev() {
        if (this.win && this.win.prev() !== null) {
            this.win = this.win.prev();
            return this.win.val;
        }
        return null;
    }

    // Возвращает значение текущего узла
    val() {
        return this.win ? this.win.val : null;
    }
}

// Пример использования классов BraidedNode и BraidedSearchTree

// Функция сравнения для чисел
function compareNumbers(a, b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// Функция для вывода значения узла
function printNode(val) {
    console.log(val);
}

// Тестовая функция
function testBraidedSearchTree() {
    // Создаем дерево поиска с функцией сравнения чисел
    let tree = new BraidedSearchTree(compareNumbers);

    // Вставляем элементы
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);
    tree.insert(30);

    console.log("Inorder traversal:");
    // Симметричный обход дерева
    tree.inorder(printNode);

    console.log("Find 15:");
    // Поиск элемента
    console.log(tree.find(15)); // 15

    console.log("Find Min:");
    // Нахождение минимального элемента
    console.log(tree.findMin()); // 5

    console.log("Is tree empty?");
    // Проверка, пустое ли дерево
    console.log(tree.isEmpty()); // false

    console.log("Next element:");
    // Переход к следующему элементу
    console.log(tree.next()); // 10

    console.log("Prev element:");
    // Переход к предыдущему элементу
    console.log(tree.prev()); // 5

    console.log("Remove 10:");
    // Удаление элемента 10
    tree.find(10);
    tree.remove();

    console.log("Inorder traversal after removal:");
    // Симметричный обход дерева после удаления
    tree.inorder(printNode);

    console.log("Remove Min:");
    // Удаление минимального элемента
    tree.removeMin();

    console.log("Inorder traversal after removing min:");
    // Симметричный обход дерева после удаления минимального элемента
    tree.inorder(printNode);
}

// Запуск тестовой функции
testBraidedSearchTree();

