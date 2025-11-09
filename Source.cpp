#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <cassert>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace chrono;

// Наївний алгоритм
vector<int> naiveSearch(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.size(), m = pattern.size();
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
            j++;
        if (j == m)
            positions.push_back(i);
    }
    return positions;
}

// Алгоритм КМП 
vector<int> computeLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }
    return lps;
}

vector<int> KMPSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.size(), m = pattern.size();
    vector<int> lps = computeLPS(pattern);
    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++; j++;
        }
        if (j == m) {
            result.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return result;
}

// Алгоритм Боєра–Мура
const int ALPHABET_SIZE = 256;

vector<int> badCharTable(const string& pattern) {
    vector<int> badChar(ALPHABET_SIZE, -1);
    for (int i = 0; i < pattern.size(); i++)
        badChar[(unsigned char)pattern[i]] = i;
    return badChar;
}

vector<int> BoyerMooreSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.size(), m = pattern.size();
    vector<int> badChar = badCharTable(pattern);
    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j])
            j--;
        if (j < 0) {
            result.push_back(s);
            s += (s + m < n) ? m - badChar[(unsigned char)text[s + m]] : 1;
        }
        else {
            s += max(1, j - badChar[(unsigned char)text[s + j]]);
        }
    }
    return result;
}

// Допоміжні функції
bool equalResults(const vector<int>& a, const vector<int>& b) {
    return a == b;
}

string joinVector(const vector<int>& v) {
    string res;
    for (int i : v) res += to_string(i) + " ";
    return res;
}

// Функція для випадкових рядків
string randomBinaryString(int length) {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 1);
    string s;
    s.reserve(length);
    for (int i = 0; i < length; i++) s += (dis(gen) ? '1' : '0');
    return s;
}

int main() {
    setlocale(0, "");

    cout << "Тест ефективностi алгоритмiв\n";
    int textLen = 50000;
    int patternLen = 10;
    string text = randomBinaryString(textLen);
    string pattern = randomBinaryString(patternLen);

    auto start = high_resolution_clock::now();
    naiveSearch(text, pattern);
    auto end = high_resolution_clock::now();
    cout << "Наївний: " << duration_cast<milliseconds>(end - start).count() << " мс\n";

    start = high_resolution_clock::now();
    KMPSearch(text, pattern);
    end = high_resolution_clock::now();
    cout << "КМП: " << duration_cast<milliseconds>(end - start).count() << " мс\n";

    start = high_resolution_clock::now();
    BoyerMooreSearch(text, pattern);
    end = high_resolution_clock::now();
    cout << "Боєра-Мура: " << duration_cast<milliseconds>(end - start).count() << " мс\n";
}
