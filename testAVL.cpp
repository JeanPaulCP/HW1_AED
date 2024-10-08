#include <iostream>
#include <vector>
#include "avl.h"
using namespace std;

int main(){
    AVLTree<int> tree;

    tree.insert(10);
    cout<<tree.height()<<endl;
    //ASSERT_TRUE(tree.height() == 0);

    tree.insert(20);
    cout<<tree.height()<<endl;
    //ASSERT_TRUE(tree.height() == 1);

    tree.insert(30);
    cout<<tree.height()<<endl;
    //ASSERT_TRUE(tree.height() == 2);

    tree.insert(40);
    cout<<tree.height()<<endl;
    //ASSERT_TRUE(tree.height() == 2);

    tree.insert(50); // Error aquí en el balanceo del árbol
    cout<<tree.height()<<endl;
    //ASSERT_TRUE(tree.height() == 3);

    tree.insert(25);
    cout<<tree.height()<<endl;
    //ASSERT_TRUE(tree.height() == 3);

    std::vector<int> detected = tree.inorderTraversal();
    std::vector<int> expected{10, 20, 25, 30, 40, 50};

    for (const auto& item:detected) {
        cout<<item<<" ";
    }

    //ASSERT_TRUE(detected == expected);

    cout<<endl<<boolalpha<<tree.search(10)<<endl;
    //ASSERT_TRUE(tree.search(10) == true);

    tree.remove(10);
    cout<<boolalpha<<tree.search(10)<<endl;
    //ASSERT_TRUE(tree.search(10) == false);

    std::vector<int> detected2 = tree.inorderTraversal();
    std::vector<int> expected2{20, 25, 30, 40, 50};

    for (const auto& item:detected2) {
        cout<<item<<" ";
    }
    //ASSERT_TRUE(detected == expected);

    cout<<endl<<boolalpha<<tree.search(20)<<endl;
    //ASSERT_TRUE(tree.search(20) == true);

    cout<<boolalpha<<tree.search(25)<<endl;
    //ASSERT_TRUE(tree.search(25) == true);

    cout<<boolalpha<<tree.search(30)<<endl;
    //ASSERT_TRUE(tree.search(30) == true);

    cout<<boolalpha<<tree.search(40)<<endl;
    //ASSERT_TRUE(tree.search(40) == true);

    cout<<boolalpha<<tree.search(50)<<endl;
    //ASSERT_TRUE(tree.search(50) == true);

    cout<<boolalpha<<tree.search(15)<<endl;
    //ASSERT_TRUE(tree.search(15) == false);

    return 0;
}
