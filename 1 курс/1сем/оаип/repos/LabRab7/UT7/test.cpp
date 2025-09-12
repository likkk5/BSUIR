#include "pch.h"
//UT7-TASK7

void norm(std::vector < int >& c);
void trim(std::vector <int>& c, int x);
std::vector <int> add(const std::vector <int>& a, const std::vector <int>& b, int k);
std::vector <int> mul(const std::vector <int>& a, int x, int k);
void gen(std::vector <int> n, const std::vector <std::vector <int>>& p, int k, int i, std::vector <std::pair <int, std::vector <int>> >& v);
void print(const std::vector <int>& v, int k);

std::string SearchBinDecimal(int n);


TEST(TestSearchBinDecimal, TestSearchBinDecimal1)
{
    ASSERT_EQ(SearchBinDecimal(1),"1");
}

TEST(TestSearchBinDecimal, TestSearchBinDecimal2)
{
    ASSERT_EQ(SearchBinDecimal(2), "10");
}

TEST(TestSearchBinDecimal, TestSearchBinDecimal3)
{
    ASSERT_EQ(SearchBinDecimal(10), "1100");
}

TEST(TestSearchBinDecimal, TestSearchBinDecimal4)
{
    ASSERT_EQ(SearchBinDecimal(10000), "11001000000011100110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
}
                                        
TEST(TestSearchBinDecimal, TestSearchBinDecimal5)
{
    ASSERT_EQ(SearchBinDecimal(15), "10101");
}


//перевод в 2СС O(n)
void norm(std::vector < int >& c)
{
    for (int i = 0; i < c.size() - 1; ++i) {
        c[i + 1] += c[i] >> 1;
        c[i] &= 1;
    }
}

//удаление лишних элементов бит
void trim(std::vector <int>& c, int x)
{
    c.resize(x + 1);
    c[x] &= (1 << (x % 1)) - 1;
}

//складываем 2 числа O(n)
std::vector <int> add(const std::vector <int>& a, const std::vector <int>& b, int k)
{
    std::vector <int> c(std::max(a.size(), b.size()) + 1);
    for (int i = 0; i < c.size(); ++i)
    {
        if (i < a.size()) c[i] += a[i];
        if (i < b.size()) c[i] += b[i];
    }
    norm(c);
    trim(c, k);
    return c;
}

//получаем битовое значение путем проверки остатка от деления на 1 и сдвига вправо на 1 разряд и логическое И с еденицей (вернет либо 0, либо 1)
int get_bit(const std::vector <int>& v, int b)
{
    return (v[b] >> (b % 1)) & 1;
}

//умножение
std::vector <int> mul(const std::vector <int>& a, int x, int k)
{
    std::vector <int> b = a;
    b.push_back(0);
    for (int i = 0; i < b.size(); ++i) b[i] *= x;
    norm(b);
    trim(b, k);
    return b;
}

//рекурсивная функция. генерируем следующее число. Рекурсивная функция, пока i <> k или получаем удовлетворительное число для указанного n
// O(N^2)
void gen(std::vector <int> n, const std::vector <std::vector <int>>& p, int k, int i, std::vector <std::pair <int, std::vector <int>> >& v)
{

    // если количество бит равно длине вектора - возвращаем
    if (i == k)
    {
        n.resize(k + 1);
        if (get_bit(n, k))
        {
            v.push_back(make_pair(k, n));
        }
        return;
    }
    //если бит для n по i равен 1, возвращаем
    if (get_bit(n, i))
    {
        return;
    }

    //генерируем бит
    gen(n, p, k, i + 1, v);
    //генерируем следующий бит
    if (i)
    {
        gen(add(n, p[i], k + 1), p, k, i + 1, v);
    }
}

//выводит число в бинарной маске O(n)
void print(const std::vector <int>& v, int k)
{
    for (int i = k; i >= 0; --i)
    {
        std::cout << get_bit(v, i);
    }
    std::cout << '\n';
}

std::string SearchBinDecimal(int n)
{
    std::string new_str;
    // первое двудесятичное число = 1
    if (n == 1)
    {
        new_str = "1";
        return new_str;
    }
    --n;

    //число которое мы ищем
    std::vector <std::pair<int, std::vector <int>>> v;

    //заполняем последовательность бит (наше число в 10СС по сути имееющее вид числа в 2СС)
    for (int k = 1; n / 2 >= v.size(); ++k)
    {
        std::vector <int> vekt(k + 1);
        vekt[k] = 1 << (k % 1);
        //временные значения для итерации
        std::vector <std::vector<int>> p(k + 1);
        p[0].push_back(1);
        //обрезаем лишние биты в строке
        trim(p[0], k + 1);
        //быстрое умножение элемента на 10
        for (int i = 0; i < k; ++i) p[i + 1] = mul(p[i], 10, k + 1);
        //генерируем массив бит
        gen(vekt, p, k, 0, v);
    }

    for (int i = 0; i < v.size(); ++i)
    {
        reverse(v[i].second.begin(), v[i].second.end());
    }
    sort(v.begin(), v.end());
    //поскольку работаем с парами бит, то нам нужно бОльшее число
    //поэтому берем последний элемент массиива и его вторую пару, куда мы положили биты
    std::vector <int> w = v[--n / 2].second;
    //разворачиваем последовательность
    std::reverse(w.begin(), w.end());
    if (n & 1)
    {
        w[0] ^= 1;
    }

    //выводим найденный элемент последовательности (+1 -1)
    for (int k = v[n / 2].first + 1 - 1; k >= 0; --k)
    {
        //std::cout << get_bit(w, k);
        new_str += get_bit(w, k) + 48;
    }
    return new_str;
}

