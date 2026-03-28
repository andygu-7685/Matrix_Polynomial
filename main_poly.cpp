#include <iostream>
#include <iomanip>
#include <vector>

#include "./includes/poly_list/polynomial.h"   
using namespace std;





bool all_test(vector<CoefType> v1, vector<CoefType> v2, bool debug = false){

    polynomial p1(v1);
    polynomial p2(v2);
    int ctr = 0;
    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;



    // Test addition
    polynomial sum = p1 + p2;
    sum = sum - p2;
    if(test_equal(sum, p1))
        ctr++;

    if(debug){
        cout << "order: " << (p1 + p2).order() << " sum = p1 + p2: " << (p1 + p2);
        cout << "order: " << sum.order() << " sum = sum - p2: " << sum;
        cout << ((test_equal(sum, p1)) ? "sum == p1: true\n" : "sum == p1: false\n");
        cout << "order: " << p1.order() << " Polynomial 1: " << p1;
        cout << "order: " << p2.order() << " Polynomial 2: " << p2;
        cout << "order: " << sum.order() << " Sum: " << sum << endl;
    }
    


    //test multi & divide
    polynomial prod = p1 * p2;
    prod = prod / p2;
    if(test_equal(prod, p1))
        ctr++;
    
    if(debug){
        cout << "order: " << (p1 * p2).order() << " prod = p1 * p2: " << (p1 * p2);
        cout << "order: " << prod.order() << " prod = prod / p2: " << prod;
        cout << ((test_equal(prod, p1)) ? "prod == p1: true\n" : "prod == p1: false\n");
        cout << "order: " << p1.order() << " Polynomial 1: " << p1;
        cout << "order: " << p2.order() << " Polynomial 2: " << p2;
        cout << "order: " << prod.order() << " Prod: " << prod << endl;
    }



    // Test modulus (remainder)
    polynomial remainder = p1 % p2;
    polynomial quotient = p1 / p2;
    polynomial result = (quotient * p2) + remainder;
    if(test_equal(result, p1))
        ctr++;

    if(debug){
        cout << "order: " << remainder.order() << " remainder = p1 mod p2: " << remainder;
        cout << "order: " << quotient.order() << " quotient = p1 / p2: " << quotient;
        cout << "order: " << result.order() << " result = (quotient * p2) + remainder " << result << endl;
        cout << ((test_equal(result, p1)) ? "result == p1: true\n" : "result == p1: false\n");
        cout << "order: " << p1.order() << " Polynomial 1: " << p1;
        cout << "order: " << p2.order() << " Polynomial 2: " << p2;
        cout << "order: " << result.order() << " Result: " << result << endl;
    }

    if(ctr == 3)
        cout << "||||||||||||||All tests passed||||||||||||||\n";
    else
        cout << "#####################Some tests failed#####################\n";

    return (ctr == 3);
}





int main(int argv, char** argc) {
    
    // Test polynomial creation
    vector<vector<CoefType>> allList{
    vector<CoefType>{1, 0, -3.2, 0, 0, 0, 3.1, 0, 28.3, 6, 7},
    vector<CoefType>{1, 0, 0, 0, 1, 0, 1, 1, 1, 1},
    vector<CoefType>{0, 0, 3, 0, 5, 0, 3.1, -3, 28, -9, 6.4, 6, 0},
    vector<CoefType>{0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
    vector<CoefType>{-2, 1.2, 3.3, -3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3.1, 0, 280008, 6},
    vector<CoefType>{1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    vector<CoefType>{0, 0, 0, -50, 22.2, 15.3, -3030, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -32.1, 0, 280008, -64.5, 0, 0},
    vector<CoefType>{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0},
    vector<CoefType>{1, 2, 11, 0, 3, 10},
    vector<CoefType>{1, 2.2, -11, 5.4, -3.0, 10},
    vector<CoefType>{0, 10, 3, 0, 0, 0, 3.1, 0, 0},
    vector<CoefType>{0, 3, 0},
    vector<CoefType>{1},
    vector<CoefType>{0, 0, 3, 0, 0, 0, 3.1, 0, 28, 6, 7},
    vector<CoefType>{1, 0, 0, 0, 3, 0, 3, 9, 2, 5},
    vector<CoefType>{0, 9, 3, 0, 5, 0, 3.1, 3, 28, 9, 6, 6, 9},
    vector<CoefType>{1, 2, 0, 0, 3, 10, 11},
    vector<CoefType>{0, 0, 3, 3, 0, 0, 3.1, 0, 28, 6},
    vector<CoefType>{1, 9, 0, 2, 3, 0, 3, 9, 13},
    vector<CoefType>{0, 10, 3, 0, 5, 5, 3.1, 3, 28},
    };
    int fail_ctr = 0;

    bool testResult = true;
    for(int i = 0; i < allList.size(); i++){
        for(int j = 0; j < allList.size(); j++){
            if(true){      //(allList[i].size() >= allList[j].size()){
                testResult = all_test(allList[i], allList[j]);
            }

            if(!testResult){
                cout << i << " : " << j << endl;
                fail_ctr++;
                //break;
            }
        }
        //if(!testResult) break;
    }
    cout << ((testResult) ? "true\n" : "false\n");
    cout << "fail_ctr: " << fail_ctr << endl;

    return 0;
}



