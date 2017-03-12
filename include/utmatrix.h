// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>// шаблонный класс
class TVector // объявили класс элементы которого -  твектор
{
protected:
	ValType *pVector; //указатель на тип
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0); // конструктор
	TVector(const TVector &v);                // конструктор копирования 
	~TVector();  // деструктор

	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента

	ValType& operator[](int pos);             // доступ перегрузка
	bool operator==(const TVector &v) const;  // сравнение перегрузка
	bool operator!=(const TVector &v) const;  // сравнение перегрузка
	TVector& operator=(const TVector &v);     // присваивание перегрузка

											  // скалярные операции
	TVector  operator+(const ValType &val);   // прибавить скаляр перегрузка
	TVector  operator-(const ValType &val);   // вычесть скаляр перегрузка
	TVector  operator*(const ValType &val);   // умножить на скаляр перегрузка

											  // векторные операции
	TVector  operator+(const TVector &v);     // сложение перегрузка
	TVector  operator-(const TVector &v);     // вычитание перегрузка
	ValType  operator*(const TVector &v);     // скалярное произведение перегрузка

											  // ввод-вывод
	
	friend istream& operator>>(istream &in, TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	/*
    в чикле вводится вектор поэлементно
	*/
	friend ostream& operator<<(ostream &out, const TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
	/*
	в чикле выводится вектор поэлементно
	*/


};

// реализация методов класса вектор:


template <class ValType>
TVector<ValType>::TVector(int s, int si) // конструктор
{
	if ((s < 1) || (s > MAX_VECTOR_SIZE)) 
		throw (s); // исключение
	if ((si < 0) || (si >= MAX_VECTOR_SIZE))
		throw(si); // исключение
	Size = s;
	StartIndex = si;
	pVector = new ValType[Size];
	/*
	передаем старт индекс и размер, проверям правильность и создаем объект
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
	/*
	Аргументы Size и StartIndex из protected секции класса инициализируются полученными от объекта значениями  
	v.Size; и v.StartIndex; соответственно. Затем выделяется Size ячеек ValType памяти, и значения копируются поэлементно в цикле
	*/

} /*-------------------------------------------------------------------------*/

template <class ValType>// деструктор
TVector<ValType>::~TVector()
{
	delete[]pVector;
	pVector = NULL;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ  
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos - StartIndex >= 0) && (pos - StartIndex < Size))
		return pVector[pos - StartIndex];
	else throw(pos);
	// возвращаем элемент вектора с номером (pos - StartIndex)
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size) return false;
	if (StartIndex != v.StartIndex) return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != v.pVector[i]) return false;
	return true;
	/*
	если длин разные - возврат 0, иначе если разные стартовые индексы - возврат 9.
	в противном случае сравниваем два вектора поэлементно, нашли разные - возврат 0
	иначе одинаковые - возврат 1
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	if (v == *this) return false;
	else return true;
    /*
	отрицание выше
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (*this != v)// сравниваем указатели 
	{
		if (Size != v.Size)
		{
			delete[] pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.Size;
		StartIndex = v.StartIndex;
		for (int i = 0; i < Size; i++)
			pVector[i] = v.pVector[i];
	}
	return *this;

	/*
	В случае неравенства информации, лежащей в ячейке памяти pVector и v.pVector и значений Size и v.Size, метод инициализирует 
	Size и StartIndex значениями объекта v.Size и v.StartIndex соответственно. Затем память, на которую
	указывает указатель pVector, освобождаются. После чего выделяется Size ячеек ValType памяти и указатель pVector указывает
	на нее. Затем вектор копируется в память, на которую указывает pMem.
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector tmp(Size, StartIndex);//Создаем объект Класса ТВЕКТОР. имя тмп
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] = pVector[i] + val;
	return tmp;
	/*
	в метод передается скаляр val типа ВалТап 
	возвращаем вектор тмп.  в тмп поэлеметно копируются значения старого вектора плюс val
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] = pVector[i] - val;
	return tmp;
	/*
	как сверху, только с -
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] = val*pVector[i];
	return tmp;
	/*
	как сверху, только с *
	*/

} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size != v.Size)
	{
		throw(v);  // исключение
	}
	TVector tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] = pVector[i] + v.pVector[i];
	return tmp;
} /*-------------------------------------------------------------------------*/
/*
передается векттор v
если они равных размеров, то они поэлементно складываются в вектор тмп. тмп возвращается
*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size != v.Size)
	{
		throw(v); // исключение
	}
	TVector tmp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] = pVector[i] - v.pVector[i];
	return tmp;
	/*
	как сверху, только с -
	*/

} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size != v.Size) {
		throw(v);
	}
	int tmp = 0;
	for (int i = 0; i < Size; i++)
		tmp = tmp + v.pVector[i] * pVector[i];
	return tmp;

	/*
	передается векттор v
	если они равных размеров, то они поэлементно умножаются в вектор тмп. тмп возвращается
	*/
} /*-------------------------------------------------------------------------*/







//Верхнетреугольная матрица
//матрица, как вектор векторных элементов (шаблоны) 4 подход

template <class ValType> //шаблонный класс типа валтап
class TMatrix : public TVector<TVector<ValType> >  // список инициализации: создается вектор элементы которого вектоы типа валтайп. как у Гергеля
{
public:
	TMatrix(int s = 10); 
	TMatrix(const TMatrix &mt);                    // констуктор копирование
	TMatrix(const TVector<TVector<ValType> > &mt); // констуктор преобразование типа
	bool operator==(const TMatrix &mt) const;      // сравнение
	bool operator!=(const TMatrix &mt) const;      // сравнение
	TMatrix& operator= (const TMatrix &mt);        // присваивание
	TMatrix  operator+ (const TMatrix &mt);        // сложение
	TMatrix  operator- (const TMatrix &mt);        // вычитание

												   // ввод / вывод
	friend istream& operator>>(istream &in, TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	/*
	матрица - вектор векторов
	вводим вектор векторов поэлементно, а операцию ввода векторов перегрузили выше
	*/
	friend ostream & operator<<(ostream &out, const TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
		/*
		матрица - вектор векторов
		выводим вектор векторов поэлементно, а операцию вывода векторов перегрузили выше
		*/
	}
};




template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s) // вектор векторов в которх валтайп
{
	if (s > MAX_MATRIX_SIZE) throw (s);
	for (int i = 0; i < s; i++)
		pVector[i] = TVector<ValType>(s - i, i);//вызывается конструктор класса твектор. указатели указывают на нужные векутора
	/*
	выше был создан вектор векторов размера s
	в 1 ячейку вектора векторов кладется вектор элементов типа валтайп длиной s, стариндекс 0
	в 2 ячейку вектора векторов кладется вектор элементов типа валтайп длиной s-1, стариндекс 1
	и тд до размера вектора веккторов
	*/
} /*-------------------------------------------------------------------------*/


template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :
	TVector<TVector<ValType> >(mt) {}// выше есть 
/*
Метод вызывает конструктор копирования  класса TVector:
*/


template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) :
	TVector<TVector<ValType> >(mt) {}// выше есть 
/*
Метод вызывает конструктор копирования класса TVector:
*/


template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (Size != mt.Size) return false;
	for (int i = 0; i < Size; i++)
	{
		if (pVector[i] != mt.pVector[i]) return false;// сравниваем два вектора, а их сравнивать можем тк перегружено выше
	}
	return true;
	/*
	если длины матриц разные - разные матрицы
	матрицы сравниваются повекторно.
	сравниваем два вектора, а их сравнивать можем тк перегружено выше
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	if (*this == mt) return false; // отрицание выше 
	else return true;
	/*
	отрицание выше
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (*this != mt)
	{
		if (Size != mt.Size)
		{
			delete[]pVector;
			pVector = new TVector<ValType>[mt.Size];
		}
		Size = mt.Size;
		StartIndex = mt.StartIndex;
		for (int i = 0; i < Size; i++)
			pVector[i] = mt.pVector[i]; // вектора присваивать можем тк перегружено выше
	}
	return *this;
	/*
	если размеры матриц не равны - выделяеися новый вектор векторов, длиной mt.Size]
	Метод инициализирует переменные Size и StartIndex значениями mt.Size и 
	mt.StartIndex соответственно. Марицы копируюся с помощью присваивания соответстующих векторов
	вектора присваивать можем тк перегружено выше
	После чего метод возвращает полученное матрицу.
	*/
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	TMatrix<int> tmp = TVector<TVector<ValType> >::operator+(mt);
	return tmp;
} /*-------------------------------------------------------------------------*/
/*
матрицы складываются повекторно, сложение векторов перегружено выше
*/
template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	TMatrix<int> tmp = TVector<TVector<ValType> >::operator-(mt);
	return tmp;
	/*
	матрицы вычитаются повекторно, вычитание векторов перегружено выше
	*/

} /*-------------------------------------------------------------------------*/

  // TVector О3 Л2 П4 С6
  // TMatrix О2 Л2 П3 С3
#endif
