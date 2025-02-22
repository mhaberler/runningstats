#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <vector>
#include <iterator>

template<typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(size_t capacity) 
        : buffer(capacity), maxSize(capacity), head(0), tail(0), full(false) {}

    void push(const T& item) {
        buffer[head] = item;
        head = (head + 1) % maxSize;
        if (full) {
            tail = (tail + 1) % maxSize;  // Move tail when overwriting
        } else if (head == tail) {
            full = true;  // Mark as full when head catches up to tail
        }
    }

    bool pop(T& output) {
        if (empty()) {
            return false;
        }
        output = buffer[tail];
        tail = (tail + 1) % maxSize;
        full = false;
        return true;
    }

    bool empty() const { return (!full && (head == tail)); }
    bool isFull() const { return full; }
    size_t size() const {
        if (full) return maxSize;
        if (head >= tail) return head - tail;
        return maxSize + head - tail;
    }
    size_t capacity() const { return maxSize; }
    void clear() { head = tail = 0; full = false; }

    // Iterator support
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(CircularBuffer* cb, size_t pos, bool isEnd) 
            : buffer(cb), position(pos), isEnd(isEnd) {}

        T& operator*() { return buffer->buffer[position]; }
        T* operator->() { return &(buffer->buffer[position]); }
        Iterator& operator++() {
            position = (position + 1) % buffer->maxSize;
            if (position == buffer->head) isEnd = true;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const Iterator& other) const {
            return buffer == other.buffer && 
                   position == other.position && 
                   isEnd == other.isEnd;
        }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

    private:
        CircularBuffer* buffer;
        size_t position;
        bool isEnd;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const CircularBuffer* cb, size_t pos, bool isEnd) 
            : buffer(cb), position(pos), isEnd(isEnd) {}

        const T& operator*() const { return buffer->buffer[position]; }
        const T* operator->() const { return &(buffer->buffer[position]); }
        ConstIterator& operator++() {
            position = (position + 1) % buffer->maxSize;
            if (position == buffer->head) isEnd = true;
            return *this;
        }
        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const ConstIterator& other) const {
            return buffer == other.buffer && 
                   position == other.position && 
                   isEnd == other.isEnd;
        }
        bool operator!=(const ConstIterator& other) const { return !(*this == other); }

    private:
        const CircularBuffer* buffer;
        size_t position;
        bool isEnd;
    };

    Iterator begin() { return Iterator(this, tail, empty()); }
    Iterator end() { return Iterator(this, head, true); }
    ConstIterator begin() const { return ConstIterator(this, tail, empty()); }
    ConstIterator end() const { return ConstIterator(this, head, true); }
    ConstIterator cbegin() const { return ConstIterator(this, tail, empty()); }
    ConstIterator cend() const { return ConstIterator(this, head, true); }

private:
    std::vector<T> buffer;
    size_t maxSize;
    size_t head;
    size_t tail;
    bool full;
};

#endif // CIRCULAR_BUFFER_H