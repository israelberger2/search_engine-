#include <map>
#include <iostream>
 
#include <string>
    
void reverseString(std::string& str){
    if(str.size() <= 1){
        return;
    }

    size_t first = 0;
    size_t end = str.size()-1;

    while(first < end)
    {
        char tmp = str[end];
        str[end] = str[first];
        str[first] = tmp;
        ++first;
        --end;
    }
    
}
int main() {
    std::string str = "abcd";
    reverseString(str);
    std::cout << "str: " << str << '\n';
    

    return 0;
}





 