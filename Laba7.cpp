#include <iostream>
#include <cstdint>

bool isPalindrome(char* word, int32_t len) {
    if (len <= 0) return false;
    for (int32_t i = 0; i < len / 2; ++i) {
        if (*(word + i) != *(word + len - 1 - i)) {
            return false;
        }
    }
    return true;
}

bool isSeparator(char c, char* seps) {
    for (int32_t i = 0; *(seps + i) != '\0'; ++i) {
        if (c == *(seps + i)) return true;
    }
    return false;
}

void addWord(char* dest, char* src, int32_t len, bool addSemicolon) {
    int32_t dIdx = 0;
    for (dIdx = 0; *(dest + dIdx) != '\0'; ++dIdx);

    if (addSemicolon) {
        *(dest + dIdx) = ';';
        dIdx++;
    }

    for (int32_t i = 0; i < len; ++i) {
        *(dest + dIdx + i) = *(src + i);
    }
    *(dest + dIdx + len) = '\0';
}

int main() {
    setlocale(LC_ALL, "");
    char* str = new char[301];
    char* seps = new char[100];
    char* result = new char[601];
    *(result) = '\0'; 

    std::cout << "Введите строку: ";
    std::cin.getline(str, 301);
    std::cout << "Введите разделители: ";
    std::cin.getline(seps, 100);

    int32_t maxPalLen = 0;
    int32_t strLen = 0;
    for (strLen = 0; *(str + strLen) != '\0'; ++strLen);

    for (int32_t i = 0; i < strLen; ++i) {
        if (isSeparator(*(str + i), seps)) {
            continue;
        }

        int32_t startIdx = i;
        for (i = i; i < strLen && !isSeparator(*(str + i), seps); ++i);
        int32_t currentLen = i - startIdx;

        if (isPalindrome(str + startIdx, currentLen)) {
            if (currentLen > maxPalLen) {
                maxPalLen = currentLen;
            }
        }
    }

    if (maxPalLen == 0) {
        throw "Ошибка: подходящие слова-палиндромы не найдены.\n";
        return 1;
    }
    else {
        bool firstFound = false;
        for (int32_t i = 0; i < strLen; i++) {
            if (isSeparator(*(str + i), seps)) {
                continue;
            }

            int32_t startIdx = i;
            for (; i < strLen && !isSeparator(*(str + i), seps); ++i);
            int32_t currentLen = i - startIdx;

            if (currentLen == maxPalLen && isPalindrome(str + startIdx, currentLen)) {
                addWord(result, str + startIdx, currentLen, firstFound);
                firstFound = true;
            }
        }
        std::cout << "Результат: " << result << std::endl;
    }

    delete[] str;
    delete[] seps;
    delete[] result;

    return 0;
}