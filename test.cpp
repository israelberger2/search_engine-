#include <vector>
#include <algorithm>
#include <iostream>


int main()
{
    std::vector<int> v = {1,2,3,4,1,6,7,1,6,7,88};
    auto res = std::remove_if(v.begin(), v.end(), [](int el){return el != 1;});
    // v.erase(res, v.end());
    for(auto x : v){
        std::cout << x << '\n';       
    }

    return 0;
}