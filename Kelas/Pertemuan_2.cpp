#include <iostream>
#include <string>
using namespace std;

string buah[5] = {"apel" , "guava" , "mangga" , "pisang"};
int main(){
    buah[4] = {"lemon"};
    for (int i = 0; i < 5; i++){
        cout << buah[i] << endl;
    }
    return 0;
}