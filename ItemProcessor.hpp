#pragma once
#include "LibraryItem.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

// Шаблонный класс ItemProcessor<T>
template <typename T>
class ItemProcessor {
    static_assert(std::is_base_of<LibraryItem, T>::value, "T must derive from LibraryItem.");

private:
    std::vector<std::unique_ptr<T>> m_items;

public:
    ItemProcessor() = default;
    ~ItemProcessor() = default;

    // Нешаблонный метод: Добавление элемента
    void addItem(std::unique_ptr<T> item) {
        m_items.push_back(std::move(item));
    }

    // Шаблонный метод: Поиск по ID
    template <typename U>
    T* findItemById(int id) {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [id](const std::unique_ptr<T>& item) {
                return item->getItemId() == id;
            });

        if (it != m_items.end()) {
            return it->get();
        }
        return nullptr;
    }

    // Нешаблонный метод (использует виртуальный метод displayInfo())
    void printAll() const {
        std::cout << "\n--- Processor Contents (" << typeid(T).name() << ") ---\n";
        for (const auto& item : m_items) {
            item->displayInfo(); // Полиморфный вызов
            std::cout << "\n";
        }
    }
};