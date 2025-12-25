#pragma once
#include <vector>
#include <numeric>
#include <type_traits> // Для static_assert

// Шаблонная функция с ограничением типов
template <typename T>
double calculateAverage(const std::vector<T>& data) {

    static_assert(std::is_arithmetic<T>::value, "calculateAverage expects numeric types (int, double, float, etc.).");

    if (data.empty()) {
        return 0.0;
    }

    T sum = std::accumulate(data.begin(), data.end(), T{ 0 });

    return static_cast<double>(sum) / data.size();
}
