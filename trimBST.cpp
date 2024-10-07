/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        TreeNode* temp=root;
        vector<int> rutaOrdenada=DFSinorder(temp);
        TreeNode* result=root;
        for (const auto item:rutaOrdenada) {
            if (item<low || item>high){
                result=deleteNode(temp, item);
            }
        }
        return result;
    }
    vector<int> DFSinorder(TreeNode* root){
        if (root==nullptr){
            return {};
        }
        else{
            vector<int> result=DFSinorder(root->left);
            result.push_back(root->val);
            vector<int> right=DFSinorder(root->right);
            for (const auto& item:right) {
                result.push_back(item);
            }
            return result;
        }
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root==nullptr){
            return root;
        }
        else{
            // Buscando al nodo
            TreeNode* current=root;
            TreeNode* prev=nullptr;
            int ubicacion{}; // 1 left y 2 right (dónde se encuentra el
            // current con respecto al prev)
            while (current!=nullptr){
                if (current->val==key){
                    break;
                }
                else if(current->val>key){
                    prev=current;
                    current=current->left;
                    ubicacion=1;
                }
                else{
                    prev=current;
                    current=current->right;
                    ubicacion=2;
                }
            }
            if (current==nullptr){ // No se encontró en la búsqueda
                return root;
            }
            else{// Se encontró en la búsqueda
                // Existen 3 posibilidades:
                // Es nodo hoja (tiene 0 hijos)
                if (current->left==nullptr && current->right==nullptr){
                    if (ubicacion==1){
                        // Left
                        prev->left=nullptr;
                    }
                    else if (ubicacion==2){
                        // Right
                        prev->right=nullptr;
                    }
                    else if (ubicacion==0){
                        // prev=nullptr
                        root=prev;
                    }
                    delete current;
                    return root;
                }
                    // Tiene hijos:
                    // Tiene 1 hijo (derecho o izquierdo)
                else if (current->left!=nullptr && current->right==nullptr){ // Solo tiene hijo izquierdo
                    TreeNode* leftCurrent=current->left;
                    if (ubicacion==1){
                        // Left
                        prev->left=leftCurrent;
                    }
                    else if (ubicacion==2){
                        // Right
                        prev->right=leftCurrent;
                    }
                    else if (ubicacion==0){
                        // prev==nullptr
                        prev=leftCurrent;
                        root=prev;
                    }
                    delete current;
                    return root;
                }
                else if (current->left==nullptr && current->right!=nullptr){ // Solo tiene hijo derecho
                    TreeNode* rightCurrent=current->right;
                    if (ubicacion==1){
                        // Left
                        prev->left=rightCurrent;
                    }
                    else if (ubicacion==2){
                        // Right
                        prev->right=rightCurrent;
                    }
                    else if (ubicacion==0){
                        // prev==nullptr
                        prev=rightCurrent;
                        root=prev;
                    }
                    delete current;
                    return root;
                }
                    // Tiene 2 hijos
                else if (current->left!=nullptr && current->right!=nullptr){
                    TreeNode* leftCurrent=current->left;
                    TreeNode* rightCurrent=current->right;
                    if (ubicacion==1){
                        // Left
                        prev->left=rightCurrent;
                    }
                    else if (ubicacion==2){
                        // Right
                        prev->right=rightCurrent;
                    }
                    else if (ubicacion==0){
                        // prev==nullptr
                        prev=rightCurrent;
                        root=prev;
                    }
                    delete current;
                    int valLeft{leftCurrent->val};
                    TreeNode* temp=rightCurrent;
                    TreeNode* prevTemp=temp;
                    while (temp!=nullptr){
                        if (temp->val>valLeft){
                            prevTemp=temp;
                            temp=temp->left;
                        }
                    }
                    prevTemp->left=leftCurrent;
                    return root;
                }
                else {
                    return nullptr;
                }
            }
        }
    }
};

int main(){
    TreeNode* root=new TreeNode(1);
    TreeNode* n1=new TreeNode(2);

    root->right=n1;

    Solution s1;
    s1.trimBST(root,2,4);

    return 0;
}