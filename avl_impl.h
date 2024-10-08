#ifndef AVL_IMPL_H
#define AVL_IMPL_H

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <cmath>

#include "avl.h"

// AVLNode

template <typename T>
AVLNode<T>::AVLNode(T value)
        : data(value), left(nullptr), right(nullptr), height(0) {}

// AVLTree

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
int AVLTree<T>::height(AVLNode<T>* node) {
    if(node==nullptr){
        return -1;
    }
    return 1+std::max(height(node->left),height(node->right));
}

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T>* node) {
    if (node->left!=nullptr && node->right!=nullptr){
        return (node->left->height)-(node->right->height);
    }
    else if (node->left!=nullptr && node->right==nullptr){
        return (node->left->height)-(-1);
    }
    else if (node->left==nullptr && node->right!=nullptr){
        return (-1)-(node->right->height);
    }
    else{
        return 0;
    }
}

template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y) {
    AVLNode<T>* z=y->left;
    y->left=z->right;
    z->right=y;
    y=z;
    y->height=height(y);
    y->right->height=height(y->right);
    return y;
}

template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x) {
    AVLNode<T>* z=x->right;
    x->right=z->left;
    z->left=x;
    x=z;
    x->height=height(x);
    x->left->height=height(x->left);
    return x;
}

template <typename T>
AVLNode<T>* AVLTree<T>::balancearNode(AVLNode<T> *node) {
    int balanceFactor=getBalance(node);
    if (balanceFactor>=2){
        int balanceFactorLeft=getBalance(node->left);
        if (balanceFactorLeft<=-1){
            node->left=leftRotate(node->left);
        }
        node=rightRotate(node);
    }
    else if (balanceFactor<=-2){
        int balanceFactorRight=getBalance(node->right);
        if (balanceFactorRight>=1){
            node->right=rightRotate(node->right);
        }
        node=leftRotate(node);
    }
    return node;
}

template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
    if (node==nullptr){
        return nullptr;
    }
    AVLNode<T>* result=node;
    while (result!=nullptr){
        if (result->left==nullptr){
            break;
        }
        result=result->left;
    }
    return result;
}

// Inserción
template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T key) {
    AVLNode<T>* current=node;
    if (current==nullptr){
        current=new AVLNode<T>(key);
        current->height=0;
        node=current;
    }
    std::vector<AVLNode<T>*> ruta;
    bool cambiarAltura{false};
    while (current->data!=key){
        if (current->data>key){
            if (current->left==nullptr){
                current->left=new AVLNode<T>(key);
                // Actualizando la altura del nuevo nodo insertado
                current->left->height=0;
                if (current->height==0){
                    cambiarAltura=true;
                }
            }
            ruta.push_back(current); // Cambio hecho aquí
            current=current->left; // Apunta al nodo insertado o sigue
        }
        else{
            if (current->right==nullptr){
                current->right=new AVLNode<T>(key);
                // Actualizando la altura del nuevo nodo insertado
                current->right->height=0;
                if (current->height==0){
                    cambiarAltura=true;
                }
            }
            ruta.push_back(current); // Cambio hecho aquí
            current=current->right; // Apunta al nodo insertado o sigue
        }
    }
    ruta.push_back(current);
    if (cambiarAltura){
        // Actualizando las alturas
        // Necesitamos enlazar los nuevos nodos
        // a la hora de hacer el autobalanceo
        for (int i=ruta.size()-2;i>=0;--i) {
            ruta[i]->height=height(ruta[i]);
            if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                AVLNode<T>* tempNode=ruta[i];
                ruta[i]=balancearNode(ruta[i]);
                if (i>0){
                    // Haciendo los nuevos enlaces
                    if (ruta[i-1]->left==tempNode){
                        ruta[i-1]->left=ruta[i];
                    }
                    else{
                        ruta[i-1]->right=ruta[i];
                    }
                }
            }
        }
        node=ruta[0];
    }
    return node;
}

// Eliminar un nodo
template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* rt, T key) {
    AVLNode<T>* prev=nullptr;
    AVLNode<T>* current=rt;
    int ubicacion{}; // 1->left 2->right
    std::vector<AVLNode<T>*> ruta;
    while (current!=nullptr){
        if (current->data==key){
            break;
        }
        else if (current->data>key){
            prev=current;
            ruta.push_back(current);
            current=current->left;
            ubicacion=1;
        }
        else{
            prev=current;
            ruta.push_back(current);
            current=current->right;
            ubicacion=2;
        }
    }
    if (current!=nullptr){
        if (ubicacion==1){
            // current->Hijo izquierdo
            if (current->left==nullptr && current->right==nullptr){
                // es una hoja
                prev->left=nullptr;
                delete current;
                if (prev->right==nullptr){
                    // Actualizando las alturas
                    // Necesitamos enlazar los nuevos nodos
                    // a la hora de hacer el autobalanceo
                    for (int i=ruta.size()-1;i>=0;--i) {
                        ruta[i]->height=height(ruta[i]);
                        if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                            AVLNode<T>* tempNode=ruta[i];
                            ruta[i]=balancearNode(ruta[i]);
                            if (i>0){
                                // Haciendo los nuevos enlaces
                                if (ruta[i-1]->left==tempNode){
                                    ruta[i-1]->left=ruta[i];
                                }
                                else{
                                    ruta[i-1]->right=ruta[i];
                                }
                            }
                        }
                    }
                    rt=ruta[0];
                }
            }
            else if (current->left!=nullptr && current->right==nullptr){
                prev->left=current->left;
                delete current;
                // Actualizando las alturas
                // Necesitamos enlazar los nuevos nodos
                // a la hora de hacer el autobalanceo
                for (int i=ruta.size()-1;i>=0;--i) {
                    ruta[i]->height=height(ruta[i]);
                    if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                        AVLNode<T>* tempNode=ruta[i];
                        ruta[i]=balancearNode(ruta[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (ruta[i-1]->left==tempNode){
                                ruta[i-1]->left=ruta[i];
                            }
                            else{
                                ruta[i-1]->right=ruta[i];
                            }
                        }
                    }
                }
                rt=ruta[0];
            }
            else if (current->left==nullptr && current->right!=nullptr){
                prev->left=current->right;
                delete current;
                // Actualizando las alturas
                // Necesitamos enlazar los nuevos nodos
                // a la hora de hacer el autobalanceo
                for (int i=ruta.size()-1;i>=0;--i) {
                    ruta[i]->height=height(ruta[i]);
                    if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                        AVLNode<T>* tempNode=ruta[i];
                        ruta[i]=balancearNode(ruta[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (ruta[i-1]->left==tempNode){
                                ruta[i-1]->left=ruta[i];
                            }
                            else{
                                ruta[i-1]->right=ruta[i];
                            }
                        }
                    }
                }
                rt=ruta[0];
            }
            else{
                prev->left=current->right;
                T rootLeft=current->left->data;
                AVLNode<T>* rightCurrent=current->right;
                std::vector<AVLNode<T>*> rutaDerecha;
                while (rightCurrent->data>rootLeft){
                    if (rightCurrent->left==nullptr){
                        rutaDerecha.push_back(rightCurrent);
                        break;
                    }
                    rutaDerecha.push_back(rightCurrent);
                    rightCurrent=rightCurrent->left;
                }
                rightCurrent->left=current->left;
                delete current;
                // Actualizando las alturas
                // Necesitamos enlazar los nuevos nodos
                // a la hora de hacer el autobalanceo
                for (int i=rutaDerecha.size()-1;i>=0;--i) {
                    rutaDerecha[i]->height=height(rutaDerecha[i]);
                    if (getBalance(rutaDerecha[i])>=2 || getBalance(rutaDerecha[i])<=-2){
                        AVLNode<T>* tempNode=rutaDerecha[i];
                        rutaDerecha[i]=balancearNode(rutaDerecha[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (rutaDerecha[i-1]->left==tempNode){
                                rutaDerecha[i-1]->left=rutaDerecha[i];
                            }
                            else{
                                rutaDerecha[i-1]->right=rutaDerecha[i];
                            }
                        }
                        else{
                            // Haciendo los nuevos enlaces
                            if (ruta[ruta.size()-1]->left==tempNode){
                                ruta[ruta.size()-1]->left=rutaDerecha[0];
                            }
                            else{
                                ruta[ruta.size()-1]->right=rutaDerecha[0];
                            }
                        }
                    }
                }
                for (int i=ruta.size()-1;i>=0;--i) {
                    ruta[i]->height=height(ruta[i]);
                    if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                        AVLNode<T>* tempNode=ruta[i];
                        ruta[i]=balancearNode(ruta[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (ruta[i-1]->left==tempNode){
                                ruta[i-1]->left=ruta[i];
                            }
                            else{
                                ruta[i-1]->right=ruta[i];
                            }
                        }
                    }
                }
                rt=ruta[0];
            }
        }
        else if (ubicacion==2){
            // current->Hijo derecho
            if (current->left==nullptr && current->right==nullptr){
                // es una hoja
                prev->right=nullptr;
                delete current;
                // Actualizando las alturas
                if (prev->left==nullptr){
                    // Actualizando las alturas
                    // Necesitamos enlazar los nuevos nodos
                    // a la hora de hacer el autobalanceo
                    for (int i=ruta.size()-1;i>=0;--i) {
                        ruta[i]->height=height(ruta[i]);
                        if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                            AVLNode<T>* tempNode=ruta[i];
                            ruta[i]=balancearNode(ruta[i]);
                            if (i>0){
                                // Haciendo los nuevos enlaces
                                if (ruta[i-1]->left==tempNode){
                                    ruta[i-1]->left=ruta[i];
                                }
                                else{
                                    ruta[i-1]->right=ruta[i];
                                }
                            }
                        }
                    }
                    rt=ruta[0];
                }
            }
            else if (current->left!=nullptr && current->right==nullptr){
                prev->right=current->left;
                delete current;
                // Actualizando las alturas
                // Necesitamos enlazar los nuevos nodos
                // a la hora de hacer el autobalanceo
                for (int i=ruta.size()-1;i>=0;--i) {
                    ruta[i]->height=height(ruta[i]);
                    if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                        AVLNode<T>* tempNode=ruta[i];
                        ruta[i]=balancearNode(ruta[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (ruta[i-1]->left==tempNode){
                                ruta[i-1]->left=ruta[i];
                            }
                            else{
                                ruta[i-1]->right=ruta[i];
                            }
                        }
                    }
                }
                rt=ruta[0];
            }
            else if (current->left==nullptr && current->right!=nullptr){
                prev->right=current->right;
                delete current;
                // Actualizando las alturas
                // Necesitamos enlazar los nuevos nodos
                // a la hora de hacer el autobalanceo
                for (int i=ruta.size()-1;i>=0;--i) {
                    ruta[i]->height=height(ruta[i]);
                    if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                        AVLNode<T>* tempNode=ruta[i];
                        ruta[i]=balancearNode(ruta[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (ruta[i-1]->left==tempNode){
                                ruta[i-1]->left=ruta[i];
                            }
                            else{
                                ruta[i-1]->right=ruta[i];
                            }
                        }
                    }
                }
                rt=ruta[0];
            }
            else{
                prev->right=current->right;
                T rootLeft=current->left->data;
                AVLNode<T>* rightCurrent=current->right;
                std::vector<AVLNode<T>*> rutaDerecha;
                while (rightCurrent->data>rootLeft){
                    if (rightCurrent->left==nullptr){
                        rutaDerecha.push_back(rightCurrent);
                        break;
                    }
                    rutaDerecha.push_back(rightCurrent);
                    rightCurrent=rightCurrent->left;
                }
                rightCurrent->left=current->left;
                delete current;
                // Actualizando las alturas
                // Necesitamos enlazar los nuevos nodos
                // a la hora de hacer el autobalanceo
                for (int i=rutaDerecha.size()-1;i>=0;--i) {
                    rutaDerecha[i]->height=height(rutaDerecha[i]);
                    if (getBalance(rutaDerecha[i])>=2 || getBalance(rutaDerecha[i])<=-2){
                        AVLNode<T>* tempNode=rutaDerecha[i];
                        rutaDerecha[i]=balancearNode(rutaDerecha[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (rutaDerecha[i-1]->left==tempNode){
                                rutaDerecha[i-1]->left=rutaDerecha[i];
                            }
                            else{
                                rutaDerecha[i-1]->right=rutaDerecha[i];
                            }
                        }
                        else{
                            // Haciendo los nuevos enlaces
                            if (ruta[ruta.size()-1]->left==tempNode){
                                ruta[ruta.size()-1]->left=rutaDerecha[0];
                            }
                            else{
                                ruta[ruta.size()-1]->right=rutaDerecha[0];
                            }
                        }
                    }
                }
                for (int i=ruta.size()-1;i>=0;--i) {
                    ruta[i]->height=height(ruta[i]);
                    if (getBalance(ruta[i])>=2 || getBalance(ruta[i])<=-2){
                        AVLNode<T>* tempNode=ruta[i];
                        ruta[i]=balancearNode(ruta[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (ruta[i-1]->left==tempNode){
                                ruta[i-1]->left=ruta[i];
                            }
                            else{
                                ruta[i-1]->right=ruta[i];
                            }
                        }
                    }
                }
                rt=ruta[0];
            }
        }
        else if (ubicacion==0){
            // El key a remover se encuentra en la raíz
            // Por lo tanto, prev==nullptr
            if (current->left==nullptr && current->right==nullptr){
                // es una hoja
                rt=nullptr;
                delete current;
            }
            else if (current->left!=nullptr && current->right==nullptr){
                rt=current->left;
                delete current;
            }
            else if (current->left==nullptr && current->right!=nullptr){
                rt=current->right;
                delete current;
            }
            else{
                rt=current->right;
                T rootLeft=current->left->data;
                AVLNode<T>* rightCurrent=current->right;
                std::vector<AVLNode<T>*> rutaDerecha;
                while (rightCurrent->data>rootLeft){
                    if (rightCurrent->left==nullptr){
                        rutaDerecha.push_back(rightCurrent);
                        break;
                    }
                    rutaDerecha.push_back(rightCurrent);
                    rightCurrent=rightCurrent->left;
                }
                rightCurrent->left=current->left;
                delete current;
                // Actualizando las alturas
                // Necesitamos enlazar los nuevos nodos
                // a la hora de hacer el autobalanceo
                for (int i=rutaDerecha.size()-1;i>=0;--i) {
                    rutaDerecha[i]->height=height(rutaDerecha[i]);
                    if (getBalance(rutaDerecha[i])>=2 || getBalance(rutaDerecha[i])<=-2){
                        AVLNode<T>* tempNode=rutaDerecha[i];
                        rutaDerecha[i]=balancearNode(rutaDerecha[i]);
                        if (i>0){
                            // Haciendo los nuevos enlaces
                            if (rutaDerecha[i-1]->left==tempNode){
                                rutaDerecha[i-1]->left=rutaDerecha[i];
                            }
                            else{
                                rutaDerecha[i-1]->right=rutaDerecha[i];
                            }
                        }
                    }
                }
                rt=rutaDerecha[0];
            }
        }
        return rt;
    }
    else{
        return rt;
    }
}

// Búsqueda
template <typename T>
bool AVLTree<T>::search(AVLNode<T>* node, T key) {
    AVLNode<T>* iter=node;
    while (iter!=nullptr){
        if (iter->data==key){
            return true;
        }
        else if (iter->data>key){
            iter=iter->left;
        }
        else{
            iter=iter->right;
        }
    }
    return false;
}

// Recorrido preorder
template <typename T>
void AVLTree<T>::preorder(AVLNode<T>* rt, std::vector<T>& ret) {
    if (rt==nullptr){
        return;
    }
    // Current Node
    ret.push_back(rt->data);
    // Left
    preorder(rt->left,ret);
    // Right
    preorder(rt->right,ret);
}

// Recorrido inorder
template <typename T>
void AVLTree<T>::inorder(AVLNode<T>* rt, std::vector<T>& ret) {
    if (rt==nullptr){
        return;
    }
    // Left
    inorder(rt->left,ret);
    // Current Node
    ret.push_back(rt->data);
    // Right
    inorder(rt->right,ret);
}

// Recorrido postorder
template <typename T>
void AVLTree<T>::postorder(AVLNode<T>* rt, std::vector<T>& ret) {
    if (rt==nullptr){
        return;
    }
    // Left
    postorder(rt->left,ret);
    // Right
    postorder(rt->right,ret);
    // Current Node
    ret.push_back(rt->data);
}

template<typename T>
void AVLTree<T>::getNodes(AVLNode<T> *rt, std::vector<AVLNode<T>*> &ret) {
    if (rt==nullptr){
        return;
    }
    // Left
    preorder(rt->left,ret);
    // Current Node
    ret.push_back(rt);
    // Right
    preorder(rt->right,ret);
}

/// Public functions

template <typename T>
void AVLTree<T>::insert(T key) {
    root=insert(root,key);
}

template <typename T>
void AVLTree<T>::remove(T key) {
    root=remove(root,key);
}

template <typename T>
bool AVLTree<T>::search(T key) {
    return search(root,key);
}

template <typename T>
std::vector<T> AVLTree<T>::preorderTraversal() {
    std::vector<T> result;
    preorder(root,result);
    return result;
}

template <typename T>
std::vector<T> AVLTree<T>::inorderTraversal() {
    std::vector<T> result;
    inorder(root,result);
    return result;
}

template <typename T>
std::vector<T> AVLTree<T>::postorderTraversal() {
    std::vector<T> result;
    postorder(root,result);
    return result;
}

template <typename T>
int AVLTree<T>::height() {
    return root->height;
}

template <typename T>
bool AVLTree<T>::isBalanced() {
    std::vector<AVLNode<T>*> recorrido;
    getNodes(root,recorrido);
    for (const auto& item:recorrido) {
        int factor=getBalance(item);
        if (factor!=-1 && factor!=0 && factor!=1){
            return false;
        }
    }
    return true;
}

#endif
