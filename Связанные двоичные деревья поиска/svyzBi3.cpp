// Узлы связанного дерева поиска  являются  объектами класса BraideNode
// Шаблон класса строится на основе TreeNode и Node
template<class T>
class BraideNode : public Node, public TreeNode<T>{
	public:
		BraideNode (T);
		BraideNode<T> *rchild(void);
		BraideNode<T> *lchild(void);
		BraideNode<T> *next(void)
		BraideNode<T> *prev(void)
		friend class BraideSearchTree<T>;
};

// Конструктор инициализирует базовый класс TreeNode
template<class T> BraideNode<T>::BraideNode(T val): 
    TreeNode<T> (val)
{
}

// компоненты функции rchild, lchild, next, prev устанавливают 4 ссылки для текущего узла
//  - первые два для дерева, другие для ленты
template<class T>
BraideNode<T> *BraideNode<T>::rchild(void)
{
	return (BraideNode<T> *)_rchild;
}

template<class T>
BraideNode<T> *BraideNode<T>::lchild(void)
{
	return (BraideNode<T> *) _lchild;
}


template<class T>
BraideNode<T> *BraideNode<T>::next(void)
{
	return (BraideNode<T> *)_next;
}

template<class T>
BraideNode<T> *BraideNode<T> :: prev(void)
{
	return (BraideNode<T> *)_prev;
}

// Класс BraideSearchTree
template<class T> class BraideSearchTree{
	private:
		BraideNode<T> *root; // головной узел
		BraideNode<T> *win; // текущее окно
		int (*cmp) (T, T); // функция сравнения
		void _remove(T, TreeNode<T> * &);
	public:
		BraideSearchTree(int(*) (T, T));
		~BraideSearchTree(void);
		T next (void);
		T prev(void);
		void inorder(void(*) (T));
		T val(void);
		bool isFirst(void);
		bool isLast(void);
		bool isHead(void);
		bool isEmpty(void);
		T find(T);
		T findMin(void);
		T insert(T);
		void remove(void);
		T removeMin(void);
};

// конструктор инициализирует элементы данных cmp для функции сравнения и 
// root для пустого дерева, представленного в виде изолированного  головного узла
template<class T>
BraideSearchTree<T>::BraideSearchTree(int(*c) (T,T)) : cmp(c)
{
	win = root = new BraideNode<T>(NULL);
}

// деструктор удаляет дерево целиком, обращаясь к деструктору головного узла
template<class T>
BraideNode<T>::~BraideSearchTree(void)
{
	delete root;
}

// использование ленты
// перемещают окно на следующую или на предыдущую позиции
template<class T> T BraideSearchTree<T>::next(void)
{
	win = win->next();
	return win->val;
}

template<class T> T BraideSearchTree<T>::prev(void)
{
	win = win ->prev();
	return win->val;
}

// возвращает ссылку на элемент внутри окна
template<class T> T BraideSearchTree<T>::val(void)
{
	return win->val;
}

// симметричный обход с первой по последнюю позицию, применяя функцию visit
template<class T>
void BraideSearch Tree<T>::inorder(void(*visit) (T) )
{
	BraideNode<T> *n = root ->next();
	while (n != root){
		(*visit) (n ->val);
		n = n -> next();
	}
}

// isFirst, isLast, isHead - возвращают TRUE, если окно в первой, последней или головной позиции
template<class T> bool BraideSearchTree<T>::isFirst(void)
{
	return (win == root -> next() ) && (root != root -> next());
}

template<class T> bool BraideSearchTree<T>::isLast(void)
{
	return (win == root -> prev() ) && (root != root -> next());
}

template<class T> bool BraideSearchTree<T>::isHead(void)
{
	return (win == root);
}

возвращает TRUE если текущее дерево пусто
template<class T> bool BraideSearchTree<T>::isEmpty()
{
	return (root == root -> next());
}


// Поиск
// отличие от SearchTree::find в том, что поиск с root -> rchild(), фактического корня
template<class T> T BraideSearchTree<T>::find(T val)
{
	BraideNode<T> *n = root -> rchild();
	while (n) {
		int result = (*cmp) (val, n ->val);
		if (result < 0)
			n = n ->lchild(); 
		else if (result > 0)
			n = n -> rchild();
		else {
			win = n;
			return n -> val;
		}
	}
	return NULL;
}

// наименьший элемент в связанном дереве поиска располагается  в первой позиции ленты, 
// функция findMin перемещает окно на этот элемент и возвращает указатель
template<class T> T BraideSearchTree<T>::findMin(void)
{
	win = root->next();
	return win -> val;
}

// Включение элементов 
// реализация совпадает с SearchTree::insert, за исключением дополнительного включения нового узла в ленту. 
// нет проверки включения в пустое дерево, посколько головной узел присутсвует всегда
template<class T> T BraideSearchTree<T>::insert(T val)
{
	int result = l;
	BraideNode<T> *p = root;
	BraideNode<T> *n = root -> rchild();
	while (n) {
		p = n;
		result = (*cmp) (val, p -> val);
		if (result < 0)
			n = p->lchild(0);
		else if (result > 0)
			n = p ->rchild()t
		else
			return NULL;
	}
	
	win = new BraideNode<T>(val);
	if (result < 0) {
		p ->_lchild = win;
		p->prev() -> Node::insert(win);
	}
	else {
		p -> _rchild = win;
		p -> Node::insert(win);
	}
	return val;
}

// Удаление элементов 
// удаляет элемент, находящийся в окне и перемещает окно в предыдущую позицию
template<class T> void BraideSearchTree<T>::remove(void)
{
	if (win != root)
		_remove(win->val, root ->_rchild);
}

// в отличии от аналогичной функции в SearchTree здесь надо удалить элемент из ленты
template<class T> 
void BraideSearchTree<T>::_remove(T val, TreeNode<T>* &n)
{

	int result = (*cmp) (val, n->val);
	if (result < 0)
		_remove(val, n -> _lchild);
	else if (result > 0);
		_remove(val, n -> _rchild);
	else {
		if (n ->_lchild == NULL) {
			BraideNode<T> *old = (BraideNode<T>*)n;
			if (win == old)
				win = old->prev();
			n = old->rchild();
			old ->Node::remove();
			delete old;
		}
		else if (n -> _rchild == NULL) {
			BraidedNode<T> *old = (BraidedNode<T>*)n;
			if (win == old)
				win = old->prev();
			n = old->lchild();
			old->Node::remove();
			delete old;
		}
		else {
			BraideNode<T> *m = ((BraidedNode<T>*)n)->next();
			n - > val = m -> val;
			_remove(m->val, s->_rchild);
		}
	}
}

// удаляет из дерева наименьший элемент и возвращет указаетль на него
template<class T> T BraidedSearchTree<T>::removeMin(void)
{
	T val = root -> next()->val;
	if (root != root ->next())
	_remove(val, root ->_rchild);
	return val;
}
