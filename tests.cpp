#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> naiveSearch(const string& text, const string& pattern);
vector<int> KMPSearch(const string& text, const string& pattern);
vector<int> BoyerMooreSearch(const string& text, const string& pattern);
bool equalResults(const vector<int>& a, const vector<int>& b);

// ЮНІТ-ТЕСТИ
void runTests() {
    cout << "Запуск юнiт-тестiв\n";

    {
        string text = "ABABDABACDABABCABAB";
        string pattern = "ABAB";
        auto n1 = naiveSearch(text, pattern);
        auto k1 = KMPSearch(text, pattern);
        auto b1 = BoyerMooreSearch(text, pattern);
        assert(equalResults(n1, k1));
        assert(equalResults(k1, b1));
        cout << "[OK] Test 1: стандартний приклад\n";
    }

    {
        string text = "0000000000";
        string pattern = "000";
        auto n2 = naiveSearch(text, pattern);
        auto k2 = KMPSearch(text, pattern);
        auto b2 = BoyerMooreSearch(text, pattern);
        assert(equalResults(n2, k2));
        assert(equalResults(k2, b2));
        cout << "[OK] Test 2: повторюванi символи\n";
    }

    {
        string text = "ABCDE";
        string pattern = "XYZ";
        auto n3 = naiveSearch(text, pattern);
        auto k3 = KMPSearch(text, pattern);
        auto b3 = BoyerMooreSearch(text, pattern);
        assert(n3.empty() && k3.empty() && b3.empty());
        cout << "[OK] Test 3: зразок не знайдено\n";
    }

    {
        string text = "";
        string pattern = "A";
        auto n4 = naiveSearch(text, pattern);
        auto k4 = KMPSearch(text, pattern);
        auto b4 = BoyerMooreSearch(text, pattern);
        assert(n4.empty() && k4.empty() && b4.empty());
        cout << "[OK] Test 4: порожнiй текст\n";
    }

    cout << "Усi тести пройдено успiшно!\n\n";
}

int main() {
    setlocale(0, "");
    runTests();
}