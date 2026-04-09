#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<std::vector<unsigned int>> generateGrayCode(unsigned int n, unsigned int base) {
    if (n == 0) {
        return {{}};
    }

    if (n == 1) {
        std::vector<std::vector<unsigned int>> result;
        result.reserve(base);
        for (unsigned int digit = 0; digit < base; ++digit) {
            result.push_back({digit});
        }
        return result;
    }

    auto shorter = generateGrayCode(n - 1, base);
    std::vector<std::vector<unsigned int>> result;
    result.reserve(shorter.size() * base);

    for (unsigned int digit = 0; digit < base; ++digit) {
        if (digit % 2 == 0) {
            for (const auto& suffix : shorter) {
                std::vector<unsigned int> code;
                code.reserve(n);
                code.push_back(digit);
                code.insert(code.end(), suffix.begin(), suffix.end());
                result.push_back(std::move(code));
            }
        } else {
            for (auto it = shorter.rbegin(); it != shorter.rend(); ++it) {
                std::vector<unsigned int> code;
                code.reserve(n);
                code.push_back(digit);
                code.insert(code.end(), it->begin(), it->end());
                result.push_back(std::move(code));
            }
        }
    }

    return result;
}

int main() {
    unsigned int n, base, x;
    if (!(std::cin >> n >> base >> x)) {
        std::cerr << "Fehler: Bitte drei ganze Zahlen eingeben: N B X\n";
        return 1;
    }

    if (n == 0) {
        std::cerr << "Fehler: N muss groesser als 0 sein.\n";
        return 1;
    }

    if (base < 2) {
        std::cerr << "Fehler: Basis B muss mindestens 2 sein.\n";
        return 1;
    }

    unsigned long long total = 1;
    for (unsigned int i = 0; i < n; ++i) {
        if (total > ULLONG_MAX / base) {
            std::cerr << "Fehler: Die Anzahl der Graycodes ist zu gross.\n";
            return 1;
        }
        total *= base;
    }

    if (x >= total) {
        std::cerr << "Warnung: X liegt ausserhalb des Bereichs. Ausgabe wird auf " << (total - 1) << " begrenzt.\n";
        x = static_cast<unsigned int>(total - 1);
    }

    auto grayCodes = generateGrayCode(n, base);
    for (unsigned int index = 0; index <= x; ++index) {
        const auto& code = grayCodes[index];
        for (unsigned int j = 0; j < code.size(); ++j) {
            std::cout << code[j];
            if (j + 1 < code.size()) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}
