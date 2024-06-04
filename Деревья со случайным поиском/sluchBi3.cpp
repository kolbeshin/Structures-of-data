// Деревья со случайным поиском 
template<class T>
class RandomizeNode : public BraideNide<T> {

	protected:
		RandomizeNode *_parent;
		double _priority; 
		void rotateRight(void)
		void rotateLeft(void);
		voidbubbleUp(void);
		void bubbleDown(void);
	public:
		RandomizeNode (T v, int seed = -1);
		RandomizeNode *lchild(void);
		RandomizeNode *rchild(void);
		RandomizeNode *next(void);
		RandomizeNode *prev(void);
		RandomizeNode *parent(void); // указывает на узел-предок текущего узла
		double pririty(void); // приоритет текущего узла
		friend class RandomizedSearchTree<T>;
};



// конструктор присваивает новому узлу RandomizedNode случайное значение приоритета
template<class T>
RandoizedNode<T>::RandomizedNode(T v, int seed): BraidedNode<T>(v)

{
	if (seed != -1) srand(seed);
	_priority = (rand() % 32767) / 32767.0;
	_parent = NULL;
}

// выполняет правую ротацию для текущего узла, который играет роль узла y
template<class T> void RandomizedNode<T>::rotateRight(void)
{
	RandomizeNode<T> *y = this;
	RandomizeNode<T> *x = y->lchild();
	RandomizeNode<T> *p = y->parent()
	y -> _lchild = x -> rchild();
	if (y -> lchild() != NULL)
		y ->lchild() -> _parent = y;
	if (p -> rchild() == y)
		p ->_rchild = x;
	else
		p ->_lchild = x;
	x -> _parent = p;
	x -> _rchild = y;
	y -> _parent = x;
}


// левая ротация
template<class T> void RandomizedNode<T>::rotateLeft(void)
{
	RandomizedNode<T> *x = this;
	RandomizedNode<T> *y = x ->rchild();
	RandomizedNode<T> *p = x->parent();
	x -> _rchild = y -> lchild();
	if (x ->rchild() != NULL)
		x -> _rchild() -> parent = x;
	if (p->lchild() == x)
		p->_lchild = y;
	else
		p ->_rchild = y;
	y ->_parent = p;
	y ->_lchild = x;
	x ->_parent = y;
}

// переносит текущий узел вверх по направлению к корню путем многократных ротаций до тех пор,
// пока приоритет текущего узла не станет больше или равным, чем у его предка
// применяется в тех случаях когда элемент в дереве случайного поиска располагается ниже, 
// чем это следует в соответствии со значением его приоритета
template<class T> void RandomizedNode<T>::bubbleUp(void)
{
	RandomizedNode<T> *p = parent();
	if (priority() < p -> pririty()) {
		if (p ->lchild() == this)
			p ->rotateRight();
		else
			p -> rotateLeft();
		bubbleUp();
	}
}
	
// переносит вниз по направлению к внешним узлам  дерева
// применяется в тех случаях когда элемент в дереве случайного поиска располагается выше, 
// чем это следует в соответствии со значением его приоритета
template<class T> void RandomizedNode<T>::bubbleDown(void)
{
	float lcPriority = lchild() ? lchild() -> pririty():2.0;
	float rcPriority = rchild() ? rchild() -> priority() : 2.0;
	float minPriority = (lcPriority < rcPriority) ? lcPririty : rcPriority;
	
	if (prority() <= minPriority)
		return;
	if (lcPriority < rcPriority)
		rotateRight();
	else
		rotateLeft();
	bubbleDown();
	
}

// rchild, lchild, next, prev, parent - определяют  связи текущего узла с его правым и левым потомками, 
// с последующим и предшествующим узлами и с предком соответственно
template<class T>
RandomizedNode<T> *RandomizedNode<T>::rchild(void)
{
	return (RandomizedNode<T>*) _rchild;
}

template<class T>
RandomizedNode<T> *RandomizedNode<T>::lchild(void)
{
	return (RandomizedNode<T>*) _lchild;
}

template<class T>
RandomizedNode<T> *RandomizedNode<T>::next(void)
{
	return (RandomizedNode<T>*) _next;
}

template<class T>
RandomizedNode<T> *RandomizedNode<T>::prev(void)
{
	return (RandomizedNode<T>*) _prev;
}

template<class T>
RandomizedNode<T> *RandomizedNode<T>::parent(void)
{
	return (RandomizedNode<T>*) _parent;
}

// возвращает приоритет текущего узла
template<class T>
double RandomizedNode<T>::priority(void)
{
	return _priority;
}


template<class T> class RandomizedSearchTree {
	private:
		RandomizedNode<T> * root; // головной узел
		RandomizedNode<T> *win; // окно
		int (*cmp) (T,T); // функция сравнения
		void _remove(RandomizedNode<T>*);
	public:
		RandomizedSearchTree(int(*) (T, T), int = unt = -1);
		~RandomizedSearchTree(void);
		T next(void);
		T prev(void);
		void inorder(void(*) (T) );
		T val (void);
		bool isFirst(void);
		bool isLast(void);
		bool isHead(void);
		bool isEmpty(void);
		T find(T);
		T findMin(void);
		T locate(T);
		T insert(T);
		void remove(void);
		T remove(T);
		T removeMin(void);
};

// инциализирует новое дерево случайного поиска, представляемое изолированным головным  узлом с минимальным приоритетом, равным -1,0
template<class T>
RandomizedSearchTree<T>::RandomizedSearchTree(int(*c) (T,T), int seed): cmp(c)
{
	win = root = new RandomizedNode<T> (NULL, seed);
	root -> _priority = -1.0;
}

удаляет дерево поиска
template<class T>
RandomizedSearchTree<T>::~RandomizedSearchTree(void)
{
	delete root;
}

// next, prev, val, inorder, isFirst, isLast, isHead, isEmpty - определяются подобно их аналогам в классе BraidedSearchTree
template<class T> T RandomizedSearchTree<T>::next(void) 
{
	win = win->next();
	return win ->val;
}

template<class T> T RandomizedSearchTree<T>::prev(void)
{
	win = win->prev();
	return win->val;
}

template<class T> T RandomizedSearchTree<T>::val(void)
{
	return win->val;
}

template<class T>
void RandomizedSearchTree<T>::inorder(void(*visit) (T))
{
	RandomizedNode<T> *n = root ->next();
	while (n != root) {
		(*visit) (n -> val);
		n = n->next();
	}
}

template<class T>
bool RandomizedSearchTree<T>::isFirst(void)
{
	return (win == root -> next()) && (root != root -> next());
}

template<class T>
bool RandomizedSearchTree<T>::isLast(void)
{
	return (win == root -> prev() ) && (root != root->next());
}

template<class T>
bool RandomizedSearchTree<T>::isHead(void)
{
	return (win == root);
}

template<class T>
bool RandomizedSearchTree<T>::isEmpty(void)
{
	return (root == root -> next());
}

// find, findMin - подобно их аналогам в классе BraidedSearchTree
template<class T> T RandomizedSearchTree<T>::find(T val)
{
	RandomizedNode<T> *n = root->rchild();
	while (n) {
		int result = (*cmp) (val, n -> val);
		if (result < 0)
			n = n -> lchild();
		else if (result > 0)
			n = n -> rchild();
		else{
			win = n;
			return n ->val;
		}
	}
	return NULL;
}

template<class T> T RandomizedSearchTree<T>::findMin(void)
{
 	win = root ->next();
	return win->val;
}

// возвращается наибольший элемент в дереве, который не больше, чем значение val
template<class T> T RandomizedSearchTree<T>::locate(T val)
{
	RandomizedNode<T> *b = root;
	RandomizedNode<T> *n = root ->rchild();
	while (n) {
		int result = (*cmp) (val, n -> val);
		if (result < 0)
			n = n -> lchild();
		else if (result > 0) {
			b = n
			n = n -> rchild();
		}else {
			win = n;
			return win->val;
		}
	}
	win = b;
	return win->val;
}

// Включение элементов
// заносит элемент val в текущее дерево случайного поиска и затем перемещает окно на этот элемент и возвращает указатель на этот элемент
template<class T> T RandomizedSearchTree<T>::insert(T val)
{
    // этап 1
    // найдем внешний узел
    int result = 1;
    RandomizedNode<T> *p = root;
    RandomizedNode<T> *n = root ->rchild();
    while (n) {
        p = n;
        result = (*cmp) (val, p->val);
        if (result < 0)
            n = p ->lchild();
        else if (result > 0)
            n = p -> rchild();
        else
            return NULL;
        }
        win = new RandomizedNode<T>(val);
        win ->_parent = p;
        if (result < 0) {
            p ->_lchild = win;
            p ->prev()->Node::insert(win);
        }
        else {
            p -> _rchild = win;
            p ->Node::insert(win);
        }
        // этап 2
        // поднимаем его по дереву по направлению к корню в соотвтествии с его приоритетом
        win -> bubbleUp();
        return val;
}

// Удаление элементов
// удаляет элемент в окне и затем перемещает окно в предшествующую позицию
template<class T> void RandomizedSearchTree<T>::remove(void)
{
	if (win != root)
		_remove(win);
}

// удаляет наименьший элемент и возвращает и возвращает его 
template<class T> T RandomizedSearchTree<T>::removeMin(void)
{
	T val = root->next()->val;
	if (root != root ->next())
		_remove(root->next());
	return val;
}

// функция _remove увеличивает приоритет узла n до 1.5 и затем опускает его вниз до тех пор, пока он не станет внешним узлом
template<class T> void
RandomizedSearchTree<T>::_remove(RandomizedNode<T> *n)
{
	n -> _pririty = 1. 5;
	n -> bubbleDown();
	RandomizedNode<T> *p = n ->parent();
	if (p->lchild() == n)
		p ->_lchild = NULL;
	else
		p -> _rchild = NULL;
	if (win == n)
		win = n -> prev();
	n->Node::remove();
	delete n;
}

// для удобства вводим вторую функцию remove, которая при передаче ей элемента, удаляет его из дерева случайного поиска
template<class T> T RandomizedSearchTree<T>::remove(T val)
{
	T v = find(val);
	if (v) {
		remove();
		return v;
	}
	return NULL;
}
