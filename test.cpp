#include <iostream>
#include <vector>


bool polindrom(char** metrix, int row, int column)
{
    int firstR = 0;
    int firstC = 0;
    int endR = row -1;
    int endC = column -1;

    while (endR > firstR || (firstR == endR && firstC < endC) ){        
       if(metrix[firstR][firstC] != metrix[endR][endC]){        
        return false;
       }
       if(firstC == column-1){
        firstR = 0;
        ++firstR;
       }else{
        ++firstC;
       }

        if(endC == 0){
            endC = column -1;
            --endR;
        }else{
            --endC;
        }
    }

    return true;
}

int main()
{
    char** mtx = new char*[4];

    for(int i = 0; i < 4; ++i){
        mtx[i] = new char[4];
    }


    char c ='a';
    for(int i = 0; i < 4; ++i){
        std::cout << i << '\n';
        
        **(mtx +i) = c++ ;
    }

    for(int i = 0; i < 4; ++i){
       std::cout << i << " char: " << **(mtx +i) << '\n';
    }
    //  = {{'a', 't', 'e', 'r'}, {'r', 'e', 't','a'}};
    // std::cout << polindrom(mtx, 2, 4) << '\n';
     
    return 0;
}