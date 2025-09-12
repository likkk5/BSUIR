#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector < int > vi;

int B = 1;
const int fm = (1 << B) - 1; // максимальный инт

void norm(std::vector < int >& c) {
    for (int i = 0; i < c.size() - 1; ++i) {
        // добавляем следущему числу двойной сдвиг вправо
        c[i + 1] += c[i] >> B;
        //логическое И для текущего числа в ячейке
        c[i] &= fm;
    }
}

//обрезаем x символов
void trim(vi& c, int x) {  // что такое vi?
    c.resize(x / B + 1);
    c[x / B] &= (1 << (x % B)) - 1;
}

//складываем 2 числа
vi add(const vi& a, const vi& b, int k) {
    vi c(std::max(a.size(), b.size()) + 1);
    for (int i = 0; i < c.size(); ++i) {
        if (i < a.size()) c[i] += a[i];
        if (i < b.size()) c[i] += b[i];
    }
    norm(c);
    trim(c, k);
    return c;
}

//получаем побитовую маску по математическому условию из https://oeis.org/A038102
int get_bit(const vi& v, int b) {
    return (v[b / B] >> (b % B)) & 1;
}

//умножение
std::vector <int> mul(const vi& a, int x, int k) {
    std::vector <int> b = a;
    b.push_back(0);
    for (int i = 0; i < b.size(); ++i) b[i] *= x;
    norm(b);
    trim(b, k);
    return b;
}

//генерируем следующее число. Рекурсивная функция, пока i <> k или получаем удовлетворительное число для указанного n
void gen(std::vector <int> n, const std::vector <std::vector <int>>& p, int k, int i, std::vector <std::pair <int, std::vector <int>> >& v) {

    if (i == k) {
        n.resize(k + 1);
        if (get_bit(n, k)) v.push_back(make_pair(k, n));
        return;
    }
    if (get_bit(n, i)) return;

    gen(n, p, k, i + 1, v);
    if (i) gen(add(n, p[i], k + 1), p, k, i + 1, v);
}

//выводит число в бинарной маске
void print(const vi& v, int k) {
    for (int i = k; i >= 0; --i) std::cerr << get_bit(v, i);
    std::cerr << '\n';
}

int main() {
    int n;
    std::cin >> n;

    std::cout << "B = " << B << "\n";
    std::cout << "fm = " << fm << "\n";
    std::cout << "n / 2 = " << (n / 2) << "\n";

    // первое двудесятичное число = 1
    if (n == 1) {
        std::cout << "1\n";
        return 0;
    }
    
    --n;
    
    std::vector <std::pair<int, std::vector <int>>> v; // объявлен вектор состоящий из пары векторов типа int

    //заполняем последовательность бит (наше число в 10СС по сути имееющее вид числа в 2СС)
    for (int k = 1; v.size() <= n / 2; ++k) {
        std::vector <int> vekt(k / B + 1); // объявляем переменную vekt типа Вектор, каждый элемент которого типа int??? Размер вектора - (k / B + 1)
        
        vekt[k / B] = 1 << (k % B); // каждому элементу (т.к. B=1 всегда) присваиваем (2 в степени k) (т.к. k % 1 = k; 1 << k - это умножение на 2 в степени k )
        std::cout << "   k / B = " << (k / B) << "   v.size() = " << (v.size());
        std::cout << "   vekt[k / B] = ";
        for (int i = 0; i < vekt.size();i++)
        {
            std::cout << vekt[i];
        }
        std::cout << '\n';

        std::vector <std::vector<int>> p(k + 1); // // объявляем переменную p типа Вектор, каждый элемент которого типа int??? Размер вектора - (k + 1)
 
        p[0].push_back(1); // 0 - му элементу вектора p добавляем в конец единицу?
        trim(p[0], k + 1); //??? зачем обрезаем в векторе р (k + 1) символ (почему не использовали pop_back?) если обрезаем, зачем добавляли 1 строкой выше
        
        for (int i = 0; i < k; ++i) p[i + 1] = mul(p[i], 10, k + 1);
        gen(vekt, p, k, 0, v);
    }

    for (int i = 0; i < v.size(); ++i) reverse(v[i].second.begin(), v[i].second.end()); // в каждом i-ом элементе вектора во второй части переворачиваем элемент
    sort(v.begin(), v.end()); // ??? зачем сортируем
    
    //поскольку работаем с парами бит, то нам нужно большее число
    std::vector <int> w = v[--n / 2].second;// объявляем вектор w, который равен  ....... во второй части вектора v
    std::reverse(w.begin(), w.end()); // переворачиваем вектор
    if (n & 1) w[0] ^= 1; // и если n - нечетное, то 0-му элементу вектора w присваиваем 1

    //выводим найденный элемент последовательности
    for (int k = v[n / 2].first + 1 - 1; k >= 0; --k) std::cout << get_bit(w, k); // побитово печатаем вектор w??? // v[n / 2].first + 1 - 1 - зачем +-1? в первой части вектора в элементе n/2 что лежит? количество символов нашего искомого двудесятичного числа
    
    std::cout << '\n';
    return 0;
}