// Определение класса TreeNode
class TreeNode {
    // Конструктор класса
    constructor(value) {
        this.val = value; // Значение узла
        this.leftChild = null; // Связь текущего узла с левым потомком
        this.rightChild = null; // Связь текущего узла с правым потомком
    }
}

// Определение класса SearchTree
class SearchTree {
    // Конструктор класса
    constructor(compareFunc) {
        this.root = null; // Указатель на корень двоичного дерева
        this.compare = compareFunc; // Функция сравнения для элементов данных
    }

    // Проверка, пустое ли дерево
    isEmpty() {
        return this.root === null;
    }

    // Поиск элемента в дереве поиска
    find(value) {
        let node = this.root;
        while (node) {
            const result = this.compare(value, node.val);
            if (result < 0) {
                node = node.leftChild;
            } else if (result > 0) {
                node = node.rightChild;
            } else {
                return node.val;
            }
        }
        return null;
    }

    // Поиск минимального элемента в дереве
    findMin(node) {
        if (!node) return null;
        while (node.leftChild) {
            node = node.leftChild;
        }
        return node;
    }

    // Получение значения минимального элемента в дереве
    findMinValue() {
        const minNode = this.findMin(this.root);
        return minNode ? minNode.val : null;
    }

    // Симметричный обход дерева
    inorderTraversal(visit) {
        this._inorder(this.root, visit);
    }

    // Вспомогательная функция для симметричного обхода
    _inorder(node, visit) {
        if (node) {
            this._inorder(node.leftChild, visit);
            visit(node.val);
            this._inorder(node.rightChild, visit);
        }
    }

    // Вставка элемента в дерево
    insert(value) {
        if (this.root === null) {
            this.root = new TreeNode(value);
            return;
        } else {
            let current = this.root;
            let parent;
            let result;
            while (current) {
                parent = current;
                result = this.compare(value, parent.val);
                if (result < 0) {
                    current = parent.leftChild;
                } else if (result > 0) {
                    current = parent.rightChild;
                } else {
                    return;
                }
            }
            if (result < 0) {
                parent.leftChild = new TreeNode(value);
            } else {
                parent.rightChild = new TreeNode(value);
            }
        }
    }

    // Удаление элемента из дерева
    remove(value) {
        this.root = this._remove(value, this.root);
    }

    // Вспомогательная функция для удаления элемента из дерева
    _remove(value, node) {
        if (!node) {
            return null;
        }
        const result = this.compare(value, node.val);
        if (result < 0) {
            node.leftChild = this._remove(value, node.leftChild);
        } else if (result > 0) {
            node.rightChild = this._remove(value, node.rightChild);
        } else {
            if (!node.leftChild) {
                return node.rightChild;
            } else if (!node.rightChild) {
                return node.leftChild;
            } else {
                const minRightNode = this.findMin(node.rightChild);
                node.val = minRightNode.val;
                node.rightChild = this._remove(minRightNode.val, node.rightChild);
            }
        }
        return node;
    }

    // Удаление минимального элемента из дерева
    removeMin() {
        const minValue = this.findMinValue();
        this.remove(minValue);
        return minValue;
    }
}

// Древовидная сортировка (занесение всех элементов в дерево поиска и затем интерактивное
// удаление наименьшего элемента до тех пор, пока не будут удалены все элементы)
function heapSort(arr, compareFunc) {
    const tree = new SearchTree(compareFunc); // Создание экземпляра дерева поиска
    // Вставка всех элементов массива в дерево поиска
    for (let i = 0; i < arr.length; i++) {
        tree.insert(arr[i]);
    }
    // Извлечение элементов из дерева поиска и замена значений в исходном массиве
    for (let i = 0; i < arr.length; i++) {
        arr[i] = tree.removeMin();
    }
}

// Пример использования
const array = [5, 3, 7, 2, 4, 6, 8];
const compareFunc = (a, b) => a - b; // Функция сравнения для чисел
heapSort(array, compareFunc);
console.log("Sorted array:", array); // Вывод отсортированного массива
