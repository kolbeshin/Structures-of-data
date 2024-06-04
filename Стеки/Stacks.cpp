// шаблон класса Stack
template<class T> class Stack {
    private:
        List<T> *s;
    public:
        Stack(void);
        ~Stack(void);
        void push(T v);
        T pop(void);
        bool empty(void);
        int size(void);
        T top(void);
        T nextToTop(void);
        T bottom(void);
};

// конструктор создает объект List и приписывает его элементу данных s
template<class T> Stack<T>::Stack(void):
{
	s(new List<T>);
}

// удаляет объект List 
template<class T> Stack<T>::~Stack(void):
{
	delete s;
}

// проталкивает элемент v в текущий стек
template<class T> void Stack<T>::push(T v):
{
	s->prepend(v);
}

// выбирает самый верхний элемент из текущего стека и возвращает его 
template<class T> T Stack<T>::pop(void):
{
	s -> first();
	return s -> remove();
}

// если стек пустой - возвращет TRUE
template<class T> bool Stack<T>::empty(void)
{
	return (s -> length() == 0);
}

// число элементов в текущем стеке
template<class T> int Stack<T>::size(void)
{
	return s -> length();
}

// возвращает самый верхний элемент стека (не меняет состояние стека, ничто не заносится и не выбирается)
template<class T> T Stack::top(void)
{
	return s->first();
}

// возвращает элемент непосредственно под верхним в стеке (не меняет состояние стека, ничто не заносится и не выбирается)
template<class T> T Stack::nextToTop(void)
{
	s ->first();
	return s->next();
}

// возвращет самый нижний элемент (не меняет состояние стека, ничто не заносится и не выбирается)
template<class T> T Stack::bottom(void)
{
	return s->last();
}

// пример использования
void reverse(char *s[], int n)
{
	stack<char*> s;
	for (int i = 0; i < n; i++)
		s.push(a[i]);
	for (i = 0; i<n; i++)
		a[i] = s.pop();
}
