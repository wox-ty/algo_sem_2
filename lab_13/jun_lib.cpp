#include "iostream"
#include "vector"
#include "string"
//#include "blazingio.hpp"

struct Node {
    Node *left{};
    Node *right{};
    std::string data;
    long long height{};
    long long balance{};
    long long sub_tree_size{};

    Node() = default;

    explicit Node(std::string &val) {
        left = nullptr;
        right = nullptr;
        data = val;
        height = 1;
        balance = 0;
        sub_tree_size = 1;
    };
};


class AVLTree {
public:
    Node *root = nullptr;

private:
    Node *add_rec(Node *cur_node, std::string &val) {
        if (cur_node == nullptr) {
            return new Node(val);
        } else if (val <= cur_node->data) {
            cur_node->left = add_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val);
        } else {
            return cur_node;
        }
        return Balance(cur_node);
    }

    void updateNode(Node *cur_node) {
        cur_node->height = 1 + std::max(height(cur_node->left), height(cur_node->right));
        cur_node->balance = height(cur_node->right) - height(cur_node->left);
        cur_node->sub_tree_size = 1 + sub_tree_size(cur_node->left) + sub_tree_size(cur_node->right);
    }

    long long height(Node *cur_node) {
        return cur_node == nullptr ? 0 : cur_node->height;
    }

    long long sub_tree_size(Node *cur_node) {
        return cur_node == nullptr ? 0 : cur_node->sub_tree_size;
    }

    Node *rotate_left(Node *cur_node) {
        Node *tmp = cur_node->right;
        cur_node->right = tmp->left;
        tmp->left = cur_node;

        updateNode(cur_node);
        updateNode(tmp);

        return tmp;
    }

    Node *rotate_right(Node *cur_node) {
        Node *tmp = cur_node->left;
        cur_node->left = tmp->right;
        tmp->right = cur_node;

        updateNode(cur_node);
        updateNode(tmp);

        return tmp;
    }

    Node *Balance(Node *cur_node) {
        if (cur_node == nullptr) {
            return nullptr;
        }
        updateNode(cur_node);
        if (cur_node->balance == 2) {
            if (height(cur_node->right->left) > height(cur_node->right->right)) {
                cur_node->right = rotate_right(cur_node->right);
            }
            return rotate_left(cur_node);
        } else if (cur_node->balance == -2) {
            if (height(cur_node->left->right) > height(cur_node->left->left)) {
                cur_node->left = rotate_left(cur_node->left);
            }
            return rotate_right(cur_node);
        }
        return cur_node;
    }

    std::string kthSmallest(Node *node, long long k) {
        if (node == nullptr) {
            return "";
        }
        long long leftSubtreeSize = sub_tree_size(node->left);
        if (k == leftSubtreeSize + 1) {
            return node->data;
        } else if (k <= leftSubtreeSize) {
            return kthSmallest(node->left, k);
        } else {
            return kthSmallest(node->right, k - leftSubtreeSize - 1);
        }
    }

public:
    AVLTree() = default;
    void add(std::string &val) {
        root = add_rec(root, val);
    }
    std::string findKthSmallest(long long k) {
        return kthSmallest(root, k);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long N;
    std::cin >> N;

    AVLTree tree;

    std::string data;
    for (long long i = 0; i < N; ++i) {
        std::cin >> data;
        if (isdigit(data[0])) {
            std::cout << tree.findKthSmallest(std::stoll(data)) << "\n";
        } else {
            tree.add(data);
        }
    }

    return 0;
}
/*
7
larin
sobolev
sobolev
instasamka
sobolev
4
1
*/