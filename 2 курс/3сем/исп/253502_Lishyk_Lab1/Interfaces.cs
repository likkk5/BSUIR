namespace _253502_Lishyk_Lab1
{
    namespace Interfaces
    {
        public interface ICommunalServiceSystem<T>
        {
            // Индексатор коллекции
            T this[int index] { get; set; }

            // Метод, устанавливающий курсор в начало коллекции
            void Reset();

            // Метод, перемещающий курсор на следующий элемент коллекции
            void Next();

            // Метод, возвращающий элемент текущего положения курсора
            T Current();

            // Свойство, возвращающее количество элементов в коллекции
            int Count { get; }

            // Метод, добавляющий объект item в конец коллекции
            void Add(T item);

            // Метод, удаляющий объект item из коллекции
            void Remove(T item);

            // Метод, удаляющий элемент текущего положения курсора
            T RemoveCurrent();
        }
        public interface IGenericOperator<T>
        {
            T Zero { get; }
            T One { get; }

            T Add(T left, T right);
            T Subtract(T left, T right);
            T Multiply(T left, T right);
            T Divide(T left, T right);

            T FromInt(int value);
            T FromDouble(double value);

            double ToDouble(T value);
            int ToInt(T value);
        }
        public interface IEnumerable<T>
        {
            IEnumerator<T> GetEnumerator();
        }
    }

}
