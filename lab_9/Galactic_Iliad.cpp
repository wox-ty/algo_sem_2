#include <vector>
#include <algorithm>
#include "set"
#include "iostream"


struct Node {
    Node *left;
    Node *right;
    int data;
    int sub_tree_size;

    Node() = default;

    explicit Node(int val) {
        left = nullptr;
        right = nullptr;
        data = val;
        sub_tree_size = 0;
    };
    explicit Node(int val, int sub_size) {
        left = nullptr;
        right = nullptr;
        data = val;
        sub_tree_size = sub_size;
    };
};


class BSTree {
public:
    Node *root = nullptr;
    int size = 0;
private:
    Node *add_rec(Node *cur_node, int val, int sub_size) {
        if (cur_node == nullptr) {
            return new Node(val, sub_size);
        } else if (val < cur_node->data) {
            cur_node->sub_tree_size += 1;
            cur_node->left = add_rec(cur_node->left, val, 0);
        } else if (val > cur_node->data) {
            cur_node->right = add_rec(cur_node->right, val, 0);
        }
        return cur_node;
    }

    Node *remove_rec(Node *cur_node, int val) {
        if (cur_node == nullptr) {
            return cur_node;
        }

        if (val < cur_node->data) {
            --cur_node->sub_tree_size;
            cur_node->left = remove_rec(cur_node->left, val);
        } else if (val > cur_node->data) {
            cur_node->right = remove_rec(cur_node->right, val);
        } else if (cur_node->left != nullptr && cur_node->right != nullptr) {
            cur_node->data = findMin(cur_node->right)->data;
            cur_node->right = remove_rec(cur_node->right, cur_node->data);
        } else {
            if (cur_node->left != nullptr) {
                cur_node = cur_node->left;
            } else if (cur_node->right != nullptr) {
                cur_node = cur_node->right;
            } else {
                cur_node = nullptr;
            }
        }
        return cur_node;
    }

    Node *findMin(Node *cur_node) {
        if (cur_node->left == nullptr) {
            return cur_node;
        }
        return findMin(cur_node->left);
    }

    Node *find_recursive(Node *cur_node, int val) {
        if (cur_node == nullptr || val == cur_node->data){
            return cur_node;
        }
        if (val < cur_node->data){
            return find_recursive(cur_node->left, val);
        }
        else if (val > cur_node->data){
            return find_recursive(cur_node->right, val);
        }
    }

    Node *find_kth_L_rec(Node *cur_node, int val){
        if (cur_node == nullptr){
            return cur_node;
        }

        if (cur_node->sub_tree_size < val){
            return find_kth_L_rec(cur_node->right, val-cur_node->sub_tree_size-1);
        }
        else if (cur_node->sub_tree_size > val){
            return find_kth_L_rec(cur_node->left, val);
        }
        else{
            return cur_node;
        }
    }

public:

    BSTree() = default;

    void add(int val) {
        if (root == nullptr) {
            ++size;
            root = new Node(val);
            return;
        } else {
            add_rec(root, val, 0);
            ++size;
        }
    }

    bool find(int val) {
        return find_recursive(root, val);
    }

    void remove(int val) {
        root = remove_rec(root, val);
        --size;
    }

    int find_kth_L(int val){
        Node *tmp = find_kth_L_rec(root, val);
        return tmp ? tmp->data : 0;
    }
};


class dsu{
public:
    std::vector<int> par;
    std::vector<int> rank;
    std::vector<BSTree> ls;

    dsu(int n){
        par.resize(n);
        rank.resize(n,0);
        for (int i = 0; i < n; ++i) {
            par[i] = i;
        }
        ls.resize(n);
        for (int i = 0; i < n; ++i) {
            ls[i].add(i+1);
        }
    }

    int find(int x){
        if (par[x] != x){
            par[x] = find(par[x]);
        }
        return par[x];
    }

    void unite(int x, int y){
        int rX = find(x);
        int rY = find(y);

        if (rX == rY){
            return;
        }

        if (rank[rX] < rank[rY]){
            par[rX] = rY;
            int tmp_size = ls[rX].size;
            for (int i = 0; i < tmp_size; ++i) {
                ls[rY].add(ls[rX].root->data);
                ls[rX].remove(ls[rX].root->data);
            }
        }
        else if (rank[rX] > rank[rY]){
            par[rY] = rX;
            int tmp_size = ls[rY].size;
            for (int i = 0; i < tmp_size; ++i) {
                ls[rX].add(ls[rY].root->data);
                ls[rY].remove(ls[rY].root->data);
            }
        }
        else{
            par[rY] = rX;
            int tmp_size = ls[rY].size;
            for (int i = 0; i < tmp_size; ++i) {
                ls[rX].add(ls[rY].root->data);
                ls[rY].remove(ls[rY].root->data);
            }
            rank[rX]++;
        }
    }

};

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, q;
    std::cin >> n >> q;

    int t, x, y;
    dsu galaxies(n);

    for (int i = 0; i < q; ++i) {
        std::cin >> t;
        if (t == 1) {
            std::cin >> x >> y;
            x--;
            y--;
            galaxies.unite(x, y);
        }
        else {
            std::cin >> x;
            x--;
            int pos = galaxies.find(x);
            BSTree *cur_gal = &galaxies.ls[pos];
            int size = cur_gal->size;
            if (size % 2 == 0){
                std::cout << cur_gal->find_kth_L(size / 2 - 1) << "\n";
            }   
            else if (size == 1){
                std::cout << cur_gal->root->data << "\n";
            }
            else{
                std::cout << cur_gal->find_kth_L(size / 2) << "\n";
            }
        }
    }
    return 0;
}