using System;
using _253502_Lishyk_Lab1.Interfaces;
using System.Numerics;
//using GenericMath;

namespace _253502_Lishyk_Lab1
{
    namespace Math
    {
        public class GenericOperator<T> : IGenericOperator<T>
        {
            public T Zero //возвращает нулевое значение
            {
                get
                {
                    if (typeof(T) == typeof(int))
                    {
                        return (T)(object)0;
                    }
                    else if (typeof(T) == typeof(double))
                    {
                        return (T)(object)0.0;
                    }
                    else
                    {
                        throw new NotSupportedException($"Тип {typeof(T)} не поддерживается.");
                    }
                }
            }

            public T One //возвращ 1 или 1.0
            {
                get
                {
                    if (typeof(T) == typeof(int))
                    {
                        return (T)(object)1;
                    }
                    else if (typeof(T) == typeof(double))
                    {
                        return (T)(object)1.0;
                    }

                    else
                    {
                        throw new NotSupportedException($"Тип {typeof(T)} не поддерживается.");
                    }
                }
            }

            public T Add(T left, T right)
            {
                if (typeof(T) == typeof(int))
                {
                    return (T)(object)(Convert.ToInt32(left) + Convert.ToInt32(right));
                }
                else if (typeof(T) == typeof(double))
                {
                    return (T)(object)(Convert.ToDouble(left) + Convert.ToDouble(right));
                }
                else
                {
                    throw new NotSupportedException($"Тип {typeof(T)} не поддерживается.");
                }
            }

            public T Subtract(T left, T right)
            {
                if (typeof(T) == typeof(int))
                {
                    return (T)(object)(Convert.ToInt32(left) - Convert.ToInt32(right));
                }
                else if (typeof(T) == typeof(double))
                {
                    return (T)(object)(Convert.ToDouble(left) - Convert.ToDouble(right));
                }
                else
                {
                    throw new NotSupportedException($"Тип {typeof(T)} не поддерживается.");
                }
            }

            public T Multiply(T left, T right)
            {
                if (typeof(T) == typeof(int))
                {
                    return (T)(object)(Convert.ToInt32(left) * Convert.ToInt32(right));
                }
                else if (typeof(T) == typeof(double))
                {
                    return (T)(object)(Convert.ToDouble(left) * Convert.ToDouble(right));
                }
                else
                {
                    throw new NotSupportedException($"Тип {typeof(T)} не поддерживается.");
                }
            }

            public T Divide(T left, T right)
            {
                if (typeof(T) == typeof(int))
                {
                    return (T)(object)(Convert.ToInt32(left) / Convert.ToInt32(right));
                }
                else if (typeof(T) == typeof(double))
                {
                    return (T)(object)(Convert.ToDouble(left) / Convert.ToDouble(right));
                }
                else
                {
                    throw new NotSupportedException($"Тип {typeof(T)} не поддерживается.");
                }
            }

            public T FromInt(int value)
            {
                return (T)(object)value;
            }

            public T FromDouble(double value)
            {
                return (T)(object)value;
            }

            public double ToDouble(T value)
            {
                return Convert.ToDouble(value);
            }

            public int ToInt(T value)
            {
                return Convert.ToInt32(value);
            }
        }
    }
}
