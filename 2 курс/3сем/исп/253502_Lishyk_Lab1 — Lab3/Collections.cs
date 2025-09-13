using System.Collections;
using System.Collections.Generic;
using _253502_Lishyk_Lab1.Interfaces;

namespace _253502_Lishyk_Lab1
{
    public class MyCustomCollection<T> : ICommunalServiceSystem<T>, System.Collections.Generic.IEnumerable<T>
    {
        private class Node
        {
            public T Data { get; set; }
            public Node Next { get; set; }

            public Node(T data)
            {
                Data = data;
                Next = null;
            }
        }

        private Node head; // голова списка
        private Node current; // текущий элемент 
        private int count; // количество элементов в коллекции

        public MyCustomCollection()
        {
            head = null;
            current = null;
            count = 0;
        }

        public T this[int index]
        {
            get
            {
                if (index < 0 || index >= count)
                    throw new IndexOutOfRangeException("Индекс находится вне диапазона коллекции");

                Node currentNode = head;
                for (int i = 0; i < index; i++)
                {
                    currentNode = currentNode.Next;
                }
                return currentNode.Data;
            }
            set
            {
                if (index < 0 || index >= count)
                    throw new IndexOutOfRangeException("Индекс находится вне диапазона коллекции");

                Node currentNode = head;
                for (int i = 0; i < index; i++)
                {
                    currentNode = currentNode.Next;
                }
                currentNode.Data = value;
            }
        }

        public void Reset()
        {
            current = head;
        }

        public void Next()
        {
            if (current != null)
            {
                current = current.Next;
            }
        }

        public T Current()
        {
            if (current == null)
                throw new InvalidOperationException("Курсор находится вне коллекции");

            return current.Data;
        }

        public int Count
        {
            get { return count; }
        }

        public void Add(T item)
        {
            Node newNode = new Node(item);
            if (head == null)
            {
                head = newNode;
                current = newNode;
            }
            else
            {
                current.Next = newNode;
                current = newNode;
            }
            count++;
        }

        public void Remove(T item)
        {
            Node currentNode = head;
            Node previousNode = null;

            while (currentNode != null)
            {
                if (EqualityComparer<T>.Default.Equals(currentNode.Data, item))
                {
                    if (previousNode == null)
                    {
                        head = currentNode.Next;
                    }
                    else
                    {
                        previousNode.Next = currentNode.Next;
                    }
                    count--;
                    return;
                }

                previousNode = currentNode;
                currentNode = currentNode.Next;
            }
        }

        public T RemoveCurrent()
        {
            if (current == null)
                throw new InvalidOperationException("Курсор находится вне коллекции");

            T removedItem = current.Data;

            Node currentNode = head;
            Node previousNode = null;

            while (currentNode != null)
            {
                if (EqualityComparer<T>.Default.Equals(currentNode.Data, removedItem))
                {
                    if (previousNode == null)
                    {
                        head = currentNode.Next;
                    }
                    else
                    {
                        previousNode.Next = currentNode.Next;
                    }
                    count--;
                    current = currentNode.Next; // Перемещаем курсор на следующий элемент
                    return removedItem;
                }

                previousNode = currentNode;
                currentNode = currentNode.Next;
            }

            return removedItem;
        }
        public T FirstOrDefault(Func<T, bool> predicate)
        {
            Node currentNode = head;
            while (currentNode != null)
            {
                if (predicate(currentNode.Data))
                {
                    return currentNode.Data;
                }
                currentNode = currentNode.Next;
            }
            return default(T); // Возвращайте значение по умолчанию, если элемент не найден
        }
        public IEnumerator<T> GetEnumerator()
        {
            return GetEnumerable().GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        private System.Collections.Generic.IEnumerable<T> GetEnumerable()
        {
            Node currentNode = head;
            while (currentNode != null)
            {
                yield return currentNode.Data;//для итератора. возвращ элементы коллекции в виде перечисления
                currentNode = currentNode.Next;
            }
        }

    }

}
