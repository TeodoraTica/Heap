#ifndef HEAP_H
#define HEAP_H

#include<stdexcept>

using namespace std;

template <class T>
class isLessThan{
	
public:
	bool operator () (const T& node1, const T& node2)
	{
		return node1 < node2;
	}
};

template <class T>
class isGreaterThan{
	
public:
	bool operator () (const T& node1, const T& node2)
	{
		return node1 > node2;
	}
};

template<class T, class Comp>
class Heap {

private:

    T *heap;
    int capacity;
    int size;
    Comp compare;

    int getParent(int index)
    {
        return (index-1)/2;
    }

    int getLeftSon(int index)
    {
        return 2*index+1;
    }

    int getRightSon(int index)
    {
        return 2*index+2;
    }

    void resize(int newCapacity)
    {
        T *newHeap = new T[newCapacity];
        int i;
        for (i = 0; i < capacity; ++i)
        {
            newHeap[i] = heap[i];
        }

        delete[] heap;

        heap = newHeap;
        capacity = newCapacity;
    }

    void pushUp()
    {
        int index = size - 1, parent;
        T aux;

        parent = getParent(index);
        while (index != 0 && !compare(heap[parent], heap[index])) //Nu am ajuns in varf si proprietatea heap-ului nu e indeplinita
        {
            aux = heap[parent];
            heap[parent] = heap[index];
            heap[index] = aux;

            index = parent;
            parent = getParent(index);
        }
    }


    void pushDown()
    {
        int index = 0, leftSon, rightSon;
        T aux;

        while (1)
        {
            leftSon = getLeftSon(index);
            rightSon = getRightSon(index);

            if(leftSon >= size)//Nu exista niciun fiu, deci proprietatea heapului este indeplinita
            {
                break;
            }
            else //Exista fiu stang
            {
                if(rightSon >= size) //Nu exista fiu drept
                {
                    if(!compare(heap[index], heap[leftSon])) //Exista fiu stang si prorprietatea heapului nu este indeplinita
                    {
                        aux = heap[index];
                        heap[index] = heap[leftSon];
                        heap[leftSon] = aux;

                        index = leftSon;
                    }
                    else  //Proprietatea heapului este indeplinita
                    {
                        break;
                    }
                }
                else //Exista ambii fii
                {
                    if(compare(heap[index], heap[leftSon]) && compare(heap[index], heap[rightSon])) //Proprietatea heapului este indeplinita
                    {
                        break;
                    }

                    //Daca proprietatea heapului nu este indeplinita, se muta in sus fiul cel mai mic (pentru minHeap) sau cel mai mare (pentru maxHeap)
                    if(compare(heap[leftSon], heap[rightSon]))
                    {
                        aux = heap[index];
                        heap[index] = heap[leftSon];
                        heap[leftSon] = aux;

                        index = leftSon;
                    }
                    else
                    {
                        aux = heap[index];
                        heap[index] = heap[rightSon];
                        heap[rightSon] = aux;

                        index = rightSon;
                    }

                }
            }
        }
    }


public:

	Heap()
	{
		capacity = 1;
		size = 0;

		heap = new T[capacity];
	}

	Heap(int capacity)
	{
		size = 0;
		this->capacity = capacity;

		heap = new T[this->capacity];
	}

	~Heap()
	{
		delete[] heap;
	}

	void insert(const T& elem)
	{
        if (size == capacity)
        {
            resize(capacity * 2);
        }

        heap[size++] = elem;

        pushUp();
    }

    T front() // Returneaza elementul din varful heap-ului dar NU il sterge
    {
        if (size == 0)
        {
            throw runtime_error("front() called on empty heap.");
        }

        return heap[0];
    }

    T pop() // Returneaza elementul din varful heap-ului si il sterge din heap
    {
        if (size == 0)
        {
           throw std::runtime_error("pop() called on empty heap.");
        }

        T top = heap[0];

        if (size == 1)
        {
            size--;
        }
        else
        {
            T aux;

            aux = heap[0];
            heap[0] = heap[size - 1];
            heap[size - 1] = aux;

            size--;

            pushDown();
        }

        return top;
    }

};

#endif // HEAP_H
