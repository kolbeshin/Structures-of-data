// шаблон класса ListNode
template<class T> class ListNode : public Node {
	public:
    T _val;
	ListNode(T val);
	friend class List<T>;
};

// конструктор ListNode
template<class T> ListNode::ListNode(T val) :
	_val(val)
{
}

// шаблон класса List
template<class T> class List{
	private:
		ListNode<T> *header;
		ListNode<T> *win;
		int _lenght;
	public:
		List (void);
		~List(void);
		T insert(T);
		T append(T);
		List *append(List *);
		T prepend(T);
		T remove(void);
		void val(T);
		T val (void);
		T next (void);
		T prev (void);
		T first (void);
		T last (void);
		int length (void);
		bool isFirst (void);
		bool isLast(void);
		bool isHead (void);
};

// конструктор создает и инициализирует пустой список, представленный одним  головным узлом, со ссылками на себя
template<class T> List<T>::List(void) :
	_length(0)
{
	header = new ListNode<T> (Null);
	win = header;
}

// разрушает узлы связанного списка (не разрушает сами элементы данных)
template<class T> List<T>::~List(void)
{
	while (length() > 0) {
		first();
		remove();
	}
	delete header;
}

// заносит новыый элемент после окна и возвращает указатель на новый элемент
template<class T> T List<T>::insert(T val)
{
	win ->insert(new ListNode<T>(val));
	++ _length;
	return val;
	
}

// prepend и append вставляют новый элемент в начало или конец списка 
// соответсвенно и возращают указатель на новый элемент
template<class T> T List<T>::prepend(T val)
{
	header -> insert(new ListNode<T> (val));
	++_length;
	return val;
}


template<class T> T List<T>::append(T val)
{
	header ->prev() -> insert (new ListNode<T> (val));
	++_length;
	return val;
}

// вторая версия  функции append - добавление списка 1 в конец  
// текущего списка, первый элемент списка 1 помещается после последнего
// элемента текущего списка. В процессе выполнения список 1 - пустой.
template<class T> List<T>* List<T>::append(List<T> *l)
{
	ListNode<T> *a = (ListNode<T>*) header -> prev();
	a -> splice (l->header);
	_length += 1; 1-> _length;
	l ->header->remove();
	l->_length = 0;
	l->win = header;
	return this;
}

// удаляет элемент в окне, перемещает окно в предыдущую позицию и возвращает 
// указатель на только что удаленный элемент.
// ПРИМЕЧАНИЕ! если окно находится  в головной позиции, то таких действий не производится
template<class T> T List<T>::remove(void)
{
	if (win == header)
		return NULL;
	void *val = win ->_val;
	win = (ListNode<T>*)win->prev();
	delete (listNode<T>*)win->next()->remove();
	--_length;
	return val;

}

// замена элемента, находящегося  в текущем окне, на элемент v
// елси в голове, то дейстие не производится
void List<T>::val (T v)
{
	if (win != header)
		win -> _val = v;
}

// если val без аргументов, то возвращется элемент в окне, либо NULL, если окно в головной позиции
template<class T> T List<T>::val(void)
{
	return win->_val;
}

// next и prev перемещают окно в следующую или предыдущую позиции
// каждая из них возвращает указатель на элемент, расположенный в новой позиции окна
template<class T> T List<T>::next(void)
{
	win = (ListNode<T>*) win->next();
	return win->_val;
}

template<class T> T List<T>::prev(void)
{
	win = (ListNode<T>*) win->prev();
	return win->_val;
}

// переносят окно в первую и последнюю позицию соотвественно
template<class T> T List<T>::first(void)
{
	win = (ListNode<T>*) header->next();
	return win->_val;
}

template<class T> T List<T>::last(void)
{
	win = (ListNode<T>*) header->prev();
	return win->_val;
}

// значение длины списка
template<class T> int List<T>::length(void)
{
	return _length;
}

// isFirst, isLast, isHead возвращают TRUE только в случае выполнения условий,
// что окно находится либо в первой, либо последней, либо головной позиции соответсвенно
template<class T> bool List<T>::isFirst(void)
{
	return ((win ==header ->next()) && (_legth > 0));
}


template<class T> bool List<T>::isLast(void)
{
	return ((win ==header ->()) prev&& (_legth > 0));
}


template<class T> bool List<T>::isHead(void)
{
	return (win == header);
}


// Примеры списков 

// функция загружает n элементов массива a в список и возвращает указатель на этот список
template<class T> List<T> *arrayToList(T a[], int n)
{
	List<T> *s = new List<T>;
	for (int i = 0; i < n; i++)
		s ->append(a[i]);
	return s;
}

// функция возвращает наименьший элемент в списке s
template<class T> T leastItem(List<T> &s, int(*cmp) (T,T))
{
	int i;
	if (s.length() == 0)
		return NULL;
	T v = s.first();
	for (s.next(); !s.isHead(); s.next())
		if (cmp(s.val(), v) < 0)
			v = s.val();
	return v;
}
