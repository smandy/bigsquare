#include <type_traits>
#include <iostream>

using namespace std;

int main( int argc, char **argv) {
    cout << "is intagral char " << is_integral_v<char> << endl;
    cout << "is same val " << is_same_v<char,char> << endl;
    cout << "is same val " << is_same<char,char>::value << endl;

    cout << "char uint_8 " << is_same<char,uint8_t>::value << endl;
    cout << "char uint_16 " << is_same<char,uint16_t>::value << endl;
                                                                       
};
