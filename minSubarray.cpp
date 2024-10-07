#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        size_t sumaTotal{};
        for (int num : nums) {
            sumaTotal+=num;
        }
        if (sumaTotal%p==0){
            return 0;
        }
        else{
            for (int i = 1; i <= nums.size()-1; ++i) {
                for (int j = 0; j <= nums.size()-i; ++j) {
                    size_t subSuma{};
                    for (int k = 0; k <i ;++k) {
                        subSuma+=nums[j+k];
                    }
                    if ((sumaTotal-subSuma)%p==0){
                        return i;
                    }
                }
            }
            return -1;
        }
    }
};

int main(){
    vector<int> input={6,3,5,2};
    Solution s1;
    cout<<s1.minSubarray(input,9)<<endl;
    return 0;
}