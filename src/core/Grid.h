#pragma once
#include <cstddef>

template <typename T>
class Grid {
public:
    Grid(std::size_t width, 
         std::size_t height, 
         const T& initialValue = T{});
    ~Grid();

    Grid(const Grid& other);
    Grid& operator=(const Grid& other);

    Grid(Grid&& other) noexcept;
    Grid& operator=(Grid&& other) noexcept;

    std::size_t width() const noexcept;
    std::size_t height() const noexcept;

    T& at(std::size_t x, std::size_t y);
    const T& at(std::size_t x, std::size_t y) const;

    void fill(const T& value);

private:
    std::size_t width_ = 0;
    std::size_t height_ = 0;
    T* data_ = nullptr;
};