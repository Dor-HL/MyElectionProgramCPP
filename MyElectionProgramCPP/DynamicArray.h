#pragma once
//this specific header file was given to us by our proffesor us an incomplete file and we had to complete it
#include <iostream>
using namespace std;

namespace elections
{
	template <class T>
	class DynamicArray
	{
	public:
		DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}


		DynamicArray(const DynamicArray& other) : _arr(nullptr) 
		{
			*this = other;
		}
		~DynamicArray() {
			delete[] _arr;
		}

		const DynamicArray& operator=(const DynamicArray& other)
		{
			if (this != &other) {
				_logicalSize = other._logicalSize;
				_physicalSize = other._physicalSize;
				delete[] _arr;
				_arr = new T[_physicalSize];
				for (int i = 0; i < _logicalSize; i++)
					*(_arr+i) = other._arr[i];
			}
			return *this;
		}

		const T& operator[](int i) const
		{
			try
			{
				if (i > (_physicalSize - 1))
				{
					throw "OUT OF ARRAY, CANNOT ACCES THIS MEMEORY";
				}
			}
			catch(const char* statement)
			{
				cout << statement << endl;
				exit(5);
			}
			return _arr[i];
		}

		T& operator[](int i) 
		{
			return _arr[i];
		}

		void push_back(const T& value)
		{
			if (_logicalSize == _physicalSize)
				resize();
			_arr[_logicalSize++] = value;
		}

		const T& front()    const { return _arr[0]; }
		int      size()     const { return _logicalSize; }
		int      capacity() const { return _physicalSize; }
		bool     empty()    const { return _logicalSize == 0; }
		void     clear() { _logicalSize = 0; }

		void setSize(int _size)
		{
			while(_size >= _physicalSize)
			{
				resize();
			}
			_logicalSize = _size;
		}

		template <class T>
		void mySwap(T& a, T& b)
		{
			T temp = a;
			a = b;
			b = temp;
		}

	



		void resize()
		{
			_physicalSize *= 2;
			T* temp = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				temp[i] = _arr[i];

			delete[] _arr;
			_arr = temp;
		}
		// example iterator implementation:
		// (causes code duplication)
		class iterator
		{
		private:
			DynamicArray* _da;
			int				_i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			// other options exist, e.g., std::forward_iterator_tag
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
			iterator(const iterator& other) : _da(other._da), _i(other._i) {}


		
			
				
			// const_iterator should also be constructible from regular iterator
			friend class const_iterator;

			const iterator& operator=(const iterator& other)
			{
				_da = other._da;
				_i = other._i;
				return *this;
			}
		
	

			// comparison with another iterator
			bool operator==(const iterator& other) const
			{
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const iterator& other) const
			{
				return !(*this == other);
			}

			// smart-pointer iterator methods
			T& operator*()
			{
				return _da->_arr[_i];
			}
			T* operator->()
			{
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			iterator& operator++()
			{
				++_i;
				return *this;
			}
			iterator operator++(int)
			{
				iterator temp(*this);
				++_i;
				return temp;
			}
			iterator& operator--()
			{
				--_i;
				return *this;
			}
			iterator operator--(int)
			{
				iterator temp(*this);
				--_i;
				return temp;
			}
		};




		// and here we duplicate the 'iterator' class to 'const_iterator' 
		class const_iterator
		{
		private:
			const DynamicArray* _da;
			int				_i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			// other options exist, e.g., std::forward_iterator_tag
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			const_iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
			const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}

	

			const_iterator& operator=(const iterator& other)
			{
				_da = other._da;
				_i = other._i;
				return *this;
			}
		

			// comparison with another iterator
			bool operator==(const const_iterator& other) const
			{
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const const_iterator& other) const
			{
				return !(*this == other);
			}

			// smart-pointer iterator methods
			const T& operator*()
			{
				return _da->_arr[_i];
			}
			const T* operator->()
			{
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			const_iterator& operator++()
			{
				++_i;
				return *this;
			}
			const_iterator operator++(int)
			{
				iterator temp(*this);
				++_i;
				return temp;
			}
			const_iterator& operator--()
			{
				--_i;
				return *this;
			}
			const_iterator operator--(int)
			{
				iterator temp(*this);
				--_i;
				return temp;
			}
		};

		// should return iterator to new element
		void insert(const iterator& pos, const T& val)
		{
			if (_logicalSize == _physicalSize)
				resize();

			iterator itrEnd = end();
			iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
			while (itrCurrent != pos)
			{
				*itrCurrent = *itrPrev;
				itrCurrent = itrPrev--;
			}

			iterator p = pos;
			*p = val;
			++_logicalSize;
		}

		// returns iterator to first element after deleted element/s
		iterator erase(const iterator& iter)
		{
			iterator it;
			T* _newda;
			for (it = begin(); it != end(); it++)
			{
				if (it != iter)
				{
					_newda.push_back(*it);
				}
			}
			_arr.clear();
			_arr = _newda;

		}
		iterator erase(const iterator& first, const iterator& last)
		{
			iterator it;
			T* _newda;
			for (it = begin(); it != end(); it++)
			{
				if (it = first)
				{
					while (it != last)
					{
						it++;
					}
				}
				_newda.push_back(*it);
			}
			_arr.clear();
			_arr = _newda;
		}

		iterator begin()
		{
			return iterator(*this, 0);
		}
		iterator end()
		{
			return iterator(*this, _logicalSize);
		}
		const iterator cbegin()
		{
			return iterator(*this, 0);
		}
		const iterator cend()
		{
			return iterator(*this, _logicalSize);
		}

		iterator rbegin()
		{
			return iterator(*this, _logicalSize);
		}
		iterator rend()
		{
			return iterator(*this, 0);
		}

		const_iterator begin() const 
		{
			return const_iterator(*this, 0);
		}
		const_iterator end() const 
		{
			return const_iterator(*this, _logicalSize);
		}
		const_iterator rbegin()const
		{
			return const_iterator(*this, _logicalSize);
		}
		const_iterator rend()const
		{
			return const_iterator(*this, 0);
		}

		void print() const
		{
			for (int i = 0; i < _logicalSize; i++)
				cout << _arr[i] << " ";
			cout << endl;
		}

	private:
		

		T* _arr;
		int _logicalSize;
		int _physicalSize;
	};

	

}


