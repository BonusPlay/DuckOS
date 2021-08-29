#pragma once

namespace dstd
{

template<class K, class T>
class Map
{
public:
    Map() = default;
    Map(const Map&);
    Map(Map&&);
    Map& operator=(const Map&);
    Map& operator=(Map&&);
    ~Map();

    T& operator[](K&&);

    void clear();

    struct Node
    {
        K key_;
        T val_;
        Node* next_;
    };

private:
    Node* head_ = nullptr;
};

template<class K, class T>
Map<K,T>::Map(const Map<K,T>& other)
{
    this->clear();

    const auto visit_node = [=](const auto& self, Node* this_node, Node* other_node)
    {
        this_node->key_ = other_node->key_;
        this_node->val_ = other_node->val_;

        if (other_node->next_)
        {
            this_node->next_ = new Node;
            self(self, this_node->next_, other_node->next_);
        }
    };

    if (other.head_)
        visit_node(visit_node, this->head_, other->head_);
}

template<class K, class T>
Map<K,T>::~Map()
{
    this->clear();
}

template<class K, class T>
T& Map<K, T>::operator[](K&& key)
{
    const auto create_node = [=]()
    {
        auto ret = new Node;
        ret->key_ = key;
        ret->next_ = nullptr;
        return ret;
    };

    const auto visit_node = [=](const auto& self, Node* node)
    {
        if (node->key_ == key)
            return &node->val_;

        if (node->next_ == nullptr)
        {
            node->next_ = create_node();
            return &node->val_;
        }

        return self(self, node->next_);
    };

    if (!this->head_)
    {
        this->head_ = create_node();
        return this->head_->val_;
    }

    return *visit_node(visit_node, this->head_);
}

template<class K, class T>
void Map<K,T>::clear()
{
    const auto visit_node = [](const auto& self, Node* node) -> void
    {
        if (node->next_)
            self(self, node->next_);
        delete node;
    };

    if (this->head_)
        visit_node(visit_node, this->head_);
}

}
