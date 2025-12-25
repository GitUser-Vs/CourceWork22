#pragma once
#include <string>
#include <iostream>
#include <memory> // Для клонирования

class LibraryItem {
protected:
    int m_itemId;
    std::string m_title;
    int m_totalQuantity;

public:
    LibraryItem() : m_itemId(0), m_title("Unknown Item"), m_totalQuantity(0) {};
    LibraryItem(int itemId, const std::string& title, int quantity);

    // Виртуальный деструктор
    virtual ~LibraryItem() = default;

    // Виртуальная функция для отображения информации
    virtual void displayInfo() const = 0;

    virtual int getQuantity() const;

    // Функция для клонирования
    virtual LibraryItem* clone() const = 0; // Чистая виртуальная функция клонирования

    LibraryItem(const LibraryItem& other) = delete;
    LibraryItem& operator=(const LibraryItem& other) = delete;

    // Геттеры
    int getItemId() const { return m_itemId; }
    const std::string& getTitle() const { return m_title; }
};