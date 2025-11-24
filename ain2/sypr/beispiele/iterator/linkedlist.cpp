#include <iostream>
#include <memory>

template <typename T> class LinkedList
{
private:
  struct Node
  {
    T data;
    std::unique_ptr<Node> next;

    Node(const T &value) : data(value), next(nullptr) {}
  };

  std::unique_ptr<Node> head_;
  size_t size_;

public:
  LinkedList() : head_(nullptr), size_(0) {}

  void push_front(const T &value)
  {
    auto new_node = std::make_unique<Node>(value);
    new_node->next = std::move(head_);
    head_ = std::move(new_node);
    ++size_;
  }

  size_t size() const { return size_; }

  // Iterator for linked list
  class Iterator
  {
  private:
    Node *current_;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    explicit Iterator(Node *node) : current_(node) {}

    reference operator*() const { return current_->data; }
    pointer operator->() const { return &current_->data; }

    Iterator &operator++()
    {
      current_ = current_->next.get();
      return *this;
    }

    Iterator operator++(int)
    {
      Iterator tmp = *this;
      current_ = current_->next.get();
      return tmp;
    }

    bool operator==(const Iterator &other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const Iterator &other) const
    {
      return current_ != other.current_;
    }
  };

  Iterator begin() { return Iterator(head_.get()); }
  Iterator end() { return Iterator(nullptr); }
};

int main()
{
  LinkedList<int> list;
  list.push_front(30);
  list.push_front(20);
  list.push_front(10);

  std::cout << "Linked list contents:\n";
  for (const auto &value : list)
  {
    std::cout << value << ' ';
  }
  std::cout << '\n';
  // Output: 10 20 30
}
