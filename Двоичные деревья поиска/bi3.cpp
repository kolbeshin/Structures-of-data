template<class T> class TreeNode{
	protected:
		TreeNode *_lchild; // связь текущего узла с левым потомком
		TreeNode *_rchild; // связь текущего узла с правым потомком
		T val;
	public:
        TreeNode(T);
        virtual ~TreeNode(void);
        friend class SearchTree<T>;
        friend class BraideSearchTree<T>;
};

// конструктор формирует двоичное дерево единичного размера 
// (единственный внутренний узел имеет два пустых потомка, каждое из которых NULL)
template<class T> TreeNode<T>::TreeNode(T v) :
	val(v), _lchild(NULL), _rchild(NULL)
{
}

// деструктор рекурсивно удаляет оба потомка текущего узла (если они существуют) перед уничтожением самого текущего узла
template<class T> TreeNode<T>::~TreeNode(void)
{
	if (_lchild) delete _lchild;
	if (_rchild) delete _rchild;
}

// дерево поиска

template<class T> class SearchTree {
	private:
		TreeNode *root; // указывает на корень двоичного дерева
		int (*) (T, T) cmp; // элемент данных, который указывает на функцию сравнения
		TreeNode<T> * findMin(TreeNode<T> *);
		void _remove(T, TreeNode<T> * s);
		void _inorder(TreeNode<T> *, void (*) (T));
	public:
		SearchTree (int(*) (T, T) );
		~SearchTree (void);
		int isEmpty(void);
		T find(T);
		T findMin(void);
		void inornder(void(*) (T));
        void insert(T)
		void remove(T);
		T removeMin(void);
};

// инициализирует элементы данных cmp для функций сравнения и root для пустого дерева поиска
<template<class T> SearchTree<T>::SearchTree(int(*c) (T,T)):
	cmp(c), root(NULL)
{
}

// Дерево поиска пусто только, если в элементе данных root содержится NULL вместо разрешенного указателя:
template<class T> int SearchTree<T>::isEmpty(void)
{
	return (root == NULL);
}

// Деструктор удаляет все дерево путем обращения к деструктору корня:
template<class T> SearchTree<T>::~SearchTree(void)
{
	if(root) delete root;
}

// функция возвращает обнаруженный ею указтель на элемент 
<template<class T> T SearchTree::find(T val)
{
	TreeNode *n = root;
	while (n) {
		int result = (*cmp) (val, n -> val);
		if(result < 0)
			n = n->_lchild;
		else if (result > 0)
			n = n -> _rchild;
		else
			return n ->val;
	}
	return NULL;
}

// возвращает наименьший элемент в данном дереве
template<class T> T SearchTree<T>::findMin(void)
{
	TreeNode<T> *n = findMin(root);
	return (n ? n -> val: NULL);
}

// алгоритм поиска начиная с n
template<class T>
TreeNode<T> *SearchTree<T>::_findMin(TreeNode<T> *n)
{
if (n == NULL)
	return NULL;
while (n -> lchild)
	n = n->_lchild;
return n;
}
//для нахождения наибольшего надо сравнивать с правым потомком


// Симетричный обход
// сама функция обращается к собственной функции, которая выполняет симметричный 
// обход от узла n и применяет функцию visit к каждому достигнутому узлу
template<class T> void SearchTree::inorder(void(*visit) (T)){
	_inorder (root, visit);
}

template<class T>
void SearchTree::inorder(TreeNode<T> *n, void(*visit) (T))
{
	if(n) {
		_inorder(n->_lchild, visit);
		(*visit) (n->val);
		_inorder(n->rchild, visit);
	}
}

// Включение элементов
template<Class T> void SearchTree<T>::insert(T val)
{
	if (root == NULL) {
		root = new TreeNode<T>(val);
		return;
	}
	else {
		int result;
		TreeNode<T> *p, *n = root;
		while (n) {
			p = n;
			result = (*cmp) (val, p -> val);
			if (result < 0)
				n = p ->_lchild;
			else if (result > 0)
				n = p ->_lchild;
			else
				return;
		}
		if (result < 0 )
			p -> _lchild = new TreeNode<T>(val);
		else 
			p ->_child = new TreeNode<T>(val);
	}
}

// Удаление элементов 
template<class T> void SearchTree<T>::remove(T val)
{
	_remove(val, root);
}


template<class T>
void SearchTree<T>::_remove(T val, TreeNode<T> *&n)
{
	if (n == NULL)
		return ;
	int result = (*cmp) (val, n ->val);
	if (result < 0)
		_remove(val, n ->_lchild);
		
	else if (result > 0)
		_remove(val, n ->_rchild);
	
	else {
        // узел n имеет пустой левый потомок (в этом случае ссылка на n заменяется  на ссылку на правого потомка n)
		if(n ->_lchild == NULL) {
			TreeNode<T> *old = n;
			n = old -> rchild;
			delete old;
		}
		// узел n имеет пустой правый потомок (в этом случае ссылка вниз на n заменяется  на ссылку на левого потомка n)
		else if(n->_rchild == NULL) {
			TreeNode<T> *old = n;
			n = old->lchild;
			delete old;
		}
        // узел n имеет два непустых потомка (найдем последователя для n (назовем его m), скопируем данных, 
        // хранящиеся в m, в узел n и затем рекурсивно удалим узел m из дерева поиска)
		else {
		TreeNode<T> *m= findMin(n->_rchild);
		n ->val = m->val;
		_remove(n->val, n->_rchild);
		}
	}
}

// удаляет из дерева поиска наименьший элемент и возвращает его
template<class T> T SearchTree<T>::removeMin(void)
{
	T v = findMin();
	remove(v);
	return v;
}

// древовидная сортировка (занесение всех элементов в дерево поиска и затем интерактивном 
// удалении наименьшего элемента до тех пор, пока не будут удалены все элементы)
template<class T> void heapSort(T s(), int int n, int(*cmp) (T, T))
{
	SearchTree<T> t(cmp);
	for (int i = 0; i < n; i++)
		t.insert(s[i]);
	for (i = 0; i <n; i++)
		s[i] = t.removeMin();
		
}
