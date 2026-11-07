#pragma once

#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
class Grid {
public:
    Grid(std::size_t width, 
         std::size_t height, 
         const T& initialValue = T{})
        : width_(width), height_(height)
    {
        if (width == 0 || height == 0) {
            throw std::invalid_argument(
                "Grid dimensions must be greater than zero"
            );
        }

        if (width > std::numeric_limits<std::size_t>::max() / height) {
            throw std::length_error("Grid dimensions are too large");
        }

        const std::size_t count = width_ * height_;

        // Temporary ownership prevents leaks if initialization throws.
        std::unique_ptr<T[]> temporary(new T[count]{});
        std::fill_n(temporary.get(), count, initialValue);

        // Transfer ownership to this Grid.
        data_ = temporary.release();
    }

    ~Grid() {
        delete[] data_;
    }

    Grid(const Grid& other)
        : width_(other.width_), height_(other.height_)
    {
        const std::size_t count = width_ * height_;

        if (count > 0) {
            std::unique_ptr<T[]> temporary(new T[count]{});
            std::copy_n(other.data_, count, temporary.get());
            data_ = temporary.release();
        }
    }

    // Copy assignment: copy first, then replace our contents.
    Grid& operator=(const Grid& other) {
        if (this != &other) {
            Grid temporary(other);
            swap(temporary);
        }

        return *this;
    }

    // Move constructor: take ownership and leave other empty.
    Grid(Grid&& other) noexcept {
        swap(other);
    }

    // Move assignment: take ownership and release old contents.
    Grid& operator=(Grid&& other) noexcept {
        if (this != &other) {
            Grid temporary(std::move(other));
            swap(temporary);
        }

        return *this;
    }

    std::size_t width() const noexcept {
        return width_;
    }

    std::size_t height() const noexcept {
        return height_;
    }

    // Mutable access: allows grid.at(x, y) = value.
    T& at(std::size_t x, std::size_t y) {
        checkBounds(x, y);
        return data_[y * width_ + x];
    }

    // Read-only access for const grids.
    const T& at(std::size_t x, std::size_t y) const {
        checkBounds(x, y);
        return data_[y * width_ + x];
    }

    void fill(const T& value) {
        const std::size_t count = width_ * height_;

        if (count > 0) {
            std::fill_n(data_, count, value);
        }
    }

private:
    std::size_t width_ = 0;
    std::size_t height_ = 0;
    T* data_ = nullptr;

    void checkBounds(std::size_t x, std::size_t y) const {
        if (x >= width_ || y >= height_) {
            throw std::out_of_range("Grid coordinates are out of bounds.");
        }
    }

    // Exchange ownership and dimensions without copying any cells.
    void swap(Grid& other) noexcept {
        std::swap(width_, other.width_);
        std::swap(height_, other.height_);
        std::swap(data_, other.data_);
    }
};