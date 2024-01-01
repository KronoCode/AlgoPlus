#ifdef __cplusplus
#include "../../plotting/iterator/list_iterator.cc"
#include <iostream>
#endif

template <typename T> class linked_list {
public:
  explicit linked_list() : root(std::make_shared<link<T>>()), tail(nullptr) {}

  bool empty() { return tail == nullptr; }

  Iterator<T> begin() { return Iterator<T>(root); }

  Iterator<T> end() { return Iterator<T>(nullptr); }

  void push_back(T key) {
    if (empty()) {
      root->succ() = std::make_shared<link<T>>(key);
      tail = root->succ();
    } else {
      tail->succ() = std::make_shared<link<T>>(key);
      tail = tail->succ();
    }
  }

  void push_front(T key) {
    if (empty()) {
      root->succ() = std::make_shared<link<T>>(key);
      tail = root->succ();
    } else {
      std::shared_ptr<link<T>> p = std::make_shared<link<T>>(key);
      p->succ() = root->succ();
      root->succ() = p;
    }
  }

  void erase(T key) {
    if (empty()) {
      std::cout << "List is Empty!";
      return;
    }
    std::shared_ptr<link<T>> t = root;
    std::shared_ptr<link<T>> to_be_removed = nullptr;
    while (t != tail && t->succ()->val() != key) {
      t = t->succ();
    }
    if (t == tail) {
      std::cout << "Element not found\n";
      return;
    }
    to_be_removed = t->succ();
    t->succ() = t->succ()->succ();
    to_be_removed.reset();
    if (t->succ() == nullptr) {
      tail = t;
    }
    if (root == tail) {
      tail = nullptr;
    }
  }

  std::shared_ptr<link<T>> search(T key) {
    try {
      if (empty()) {
        throw std::invalid_argument("List is empty");
      } else {
        std::shared_ptr<link<T>> t = root;
        while (t != tail && t->succ()->val() != key) {
          t = t->succ();
        }
        if (t == tail) {
          std::cout << "Element:" << key << " not found\n";
          return nullptr;
        }
        std::cout << "Element:" << key << " was found\n";
        return t->succ();
      }
    } catch (std::invalid_argument &e) {
      std::cerr << e.what() << '\n';
      return nullptr;
    }
  }

  friend constexpr std::ostream &operator<<(std::ostream &out,
                                            linked_list<T> &l1);
  friend constexpr linked_list &operator+(const linked_list<link<T>> &l1,
                                          const linked_list<link<T>> &l2);

private:
  std::shared_ptr<link<T>> root;
  std::shared_ptr<link<T>> tail;
};
