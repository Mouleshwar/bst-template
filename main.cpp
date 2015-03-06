#include <iostream>

using namespace std;

template<class T>
class TreeNode {
public:
    T *info;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parentNode;
};

template <class T>
class BinarySearchTree {

private:
    TreeNode *root;

public:
    BinarySearchTree() {
        root = NULL;
    }
    bool isEmpty() const {
        return root == NULL;
    };
    T* insert(T*);
    void remove(T*);
    T* search(T*);
    T* min();
    T* max();
    T* inOrderSucc(T*);
    T* inOrderPred(T*);
    int height();
    void printInOrder();
    void printPreOrder();
    void printPostOrder();

    T *min(TreeNode *indexRoot);

    T *max(TreeNode *indexRoot);
};

template <class T>
T* BinarySearchTree<T>::insert(T *datap) {
    TreeNode *t = new TreeNode;
    TreeNode *parent;
    t->info = *datap;
    t->left = NULL;
    t->right = NULL;
    t->parentNode = NULL;
    parent = NULL;
    if(isEmpty()) {
        root = t;
        return root->info;
    } else {
        TreeNode *curr;
        curr = root;
        while(curr){
            parent = curr;
            if(t->info > curr->info) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
            curr->parentNode = parent;
        }

        if(t->info < parent->info){
            parent->left = t;
            parent->left->parentNode = parent;
            return parent->left->info;
        } else {
            parent->right = t;
            parent->right->parentNode = parent;
            return parent->right->info;
        }
    }
}

template <class T>
void BinarySearchTree::remove(T *datap){
    bool found = false;
    if(isEmpty()) {
        cout<<" The tree is empty!!\n";
        return;
    }
    TreeNode *curr;
    TreeNode *parent;
    curr = root;
    parent = (TreeNode*) NULL;
    while(curr!=NULL){
        if(curr->info == *datap){
            found = true;
            break;
        } else {
            parent = curr;
            if(*datap > curr->info) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
    }
    if(!found) {
        cout<<" Data not found\n";
        return;
    }

    //if the node to be deleted has a single child
    if((curr->left == NULL && curr->right != NULL) ||
            (curr->left != NULL && curr->right == NULL))
    {
        if(curr->left == NULL && curr->right != NULL)
        {
            if(parent->left == curr)
            {
                parent->left = curr->right;
                curr->right->parentNode = parent;
                delete curr;
            }
            else
            {
                parent->right = curr->right;
                parent->right->parentNode = parent;
                delete curr;
            }
        }
        else // left child present, no right child
        {
            if(parent->left == curr)
            {
                parent->left = curr->left;
                parent->left->parentNode = parent;
                delete curr;
            }
            else
            {
                parent->right = curr->left;
                parent->right->parentNode = parent;
                delete curr;
            }
        }
        return;
    }

    //if the node to be deleted is a leaf
    if( curr->left==NULL && curr->right==NULL){
        if(parent==NULL) {
            delete curr;
        } else {
            if(parent->left==curr) {
                parent->left=NULL;
            } else {
                parent->right=NULL;
            }
            delete curr;
            return;
        }
    }

    //if the node to be deleted has 2 childs, replace the node with smallest value in right subtree
    if(curr->right!=NULL && curr->left!=NULL) {
        TreeNode *chkr;
        chkr = curr->right;
        if(chkr->left==NULL && chkr->right==NULL) {
            chkr->parentNode = curr->parentNode;
            curr = chkr;
            delete chkr;
            curr->right = NULL;
        } else {
            if((curr->right)->left!=NULL) {
                TreeNode *lcurr;
                TreeNode *lcurrp;
                lcurrp = curr->right;
                lcurr = (curr->right)->left;
                while(lcurr->left!=NULL) {
                    lcurrp = lcurr;
                    lcurr = lcurr->left;
                }
                curr->info = lcurr->info;
                delete lcurr;
                lcurrp->left = NULL;
            } else {
                TreeNode *tmp;
                tmp = curr->right;
                curr->info = tmp->info;
                curr->right = tmp->right;
                delete tmp;
            }
        }
        return;
    }
}

template <class T>
TreeNode* BinarySearchTree::search(T *datap) {
    bool found = false;
    if(isEmpty()) {
        cout<<" The tree is empty!!\n";
        return NULL;
    }
    TreeNode *curr;
    TreeNode *parent;
    curr = root;
    parent = (TreeNode*) NULL;
    while(curr!=NULL) {
        if(curr->info == *datap) {
            found = true;
            break;
        } else {
            parent = curr;
            if(*datap > curr->info) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
    }
    if(!found) {
        cout<<"No such element found in the tree!!\n";
        return NULL;
    } else {
        return curr;
    }
}

template <class T>
T* BinarySearchTree::min(TreeNode *indexRoot) {
    TreeNode *curr;
    if(indexRoot!=NULL) {
        curr = indexRoot;
    } else {
        curr = root;
    }
    while(curr->left!=NULL) {
        curr = curr->left;
    }
    return curr->info;
}

template <class T>
T* BinarySearchTree::max(TreeNode *indexRoot) {
    TreeNode *curr;
    if(indexRoot!=NULL) {
        curr = indexRoot;
    } else {
        curr = root;
    }
    while(curr->right!=NULL) {
        curr = curr->right;
    }
    return curr->info;
}

template <class T>
T* BinarySearchTree::inOrderSucc(T *datap) {
    TreeNode *curr;
    curr = search(datap);
    if(curr->right!=NULL) {
        return min(curr);
    } else {
        TreeNode *p = curr->parentNode;
        while(p!=NULL && curr==p->right) {
            curr = p;
            p = p->right;
        }
        return p->info;
    }
}

template <class T>
T* BinarySearchTree::inOrderPred(T *datap) {
    TreeNode *curr;
    TreeNode *tempRoot = root;
    curr = search(datap);
    if(curr->left!=NULL) {
        return max(curr);
    } else {
        TreeNode *p = curr->parentNode;
        while(root!=NULL) {
            if(curr->info > root->info) {
                p = tempRoot;
                tempRoot = tempRoot->right;
            } else if(curr->info < tempRoot->info) {
                tempRoot = tempRoot->left;
            } else {
                break;
            }
        }
        return p->info;
    }

}

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}