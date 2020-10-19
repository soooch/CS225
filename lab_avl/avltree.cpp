/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * y = t->right;
    t->right = y->left;
    y->left = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * y = t->left;
    t->left = y->right;
    y->right = t;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int b = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (b > 1) {
        if (heightOrNeg1(subtree->right->right) < heightOrNeg1(subtree->right->left)) {
            rotateRightLeft(subtree);
        }
        else {
            rotateLeft(subtree);
        }
    }
    else if (b < -1) {
        if (heightOrNeg1(subtree->left->left) < heightOrNeg1(subtree->left->right)) {
            rotateLeftRight(subtree);
        }
        else {
            rotateRight(subtree);
        }
    }
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    // debug prints
    if (false) {
    std::cout << "b: " << b << std::endl;
    std::cout << subtree->key << ": " << subtree->height << std::endl;
    if (subtree->left == NULL) {
        std::cout << "left == NULL" << std::endl;
    }
    else {
        std::cout << subtree->left->key << ": " << subtree->left->height << std::endl;
    }
    if (subtree->right == NULL) {
        std::cout << "right == NULL" << std::endl;
    }
    else {
        std::cout << subtree->right->key << ": " << subtree->right->height << std::endl;
    }
    std::cout << std::endl;
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
    if (root == NULL) {
        root = new Node(key, value);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) return;
    if (key < subtree->key) {
        insert(subtree->left, key, value);
        if (subtree->left == NULL) {
            subtree->left = new Node(key, value);
        }
    }
    else {
        insert(subtree->right, key, value);
        if (subtree->right == NULL) {
            subtree->right = new Node(key, value);
        }
    }
    rebalance(subtree);
    return;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            if (subtree->left->right != NULL) {
                Node * pred = subtree->left;
                while (pred->right->right != NULL) {
                    pred = pred->right;
                }
                swap(subtree, pred->right);
                remove(pred->right, pred->right->key);
            }
            else {
                swap(subtree, subtree->left);
                if (subtree->left->left != NULL) {
                    swap(subtree->left, subtree->left->left);
                    delete subtree->left->left;
                    subtree->left->left = NULL;
                }
                else {
                    delete subtree->left;
                    subtree->left = NULL;
                }
            }
        } else {
            /* one-child remove */
            // your code here
            Node * replacement;
            if (subtree->left != NULL) {
                replacement = subtree->left;
                subtree->left = NULL;
            }
            else {
                replacement = subtree->right;
                subtree->right = NULL;
            }
            swap(subtree, replacement);
            delete(replacement);
        }
        // your code here
    }
    rebalance(subtree);
    return;
}
