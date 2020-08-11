#include <iostream>
#include <time.h>
#include <chrono>
#include <emmintrin.h>
#include <nmmintrin.h>

#define ONE_HUNDRED_THOUSAND 100000

int main() {
    srand(time(NULL));
    //so idk what i'm doing
    long long int tab_1[ONE_HUNDRED_THOUSAND];
    long long int tab_2[ONE_HUNDRED_THOUSAND];
    long long int tab_3[ONE_HUNDRED_THOUSAND]; // output
    for (int i = 0; i < ONE_HUNDRED_THOUSAND; i++) {
        tab_1[i] = 10;
        tab_2[i] = 20;

        tab_3[i] = 0;
    }
    auto start = std::chrono::steady_clock::now();
    for(int i = 0; i < ONE_HUNDRED_THOUSAND; i++){
        tab_3[i] = (tab_2[i] + tab_1[i])*(tab_2[i] + tab_1[i]);
    }
    auto end = std::chrono::steady_clock::now();




    auto _start = std::chrono::steady_clock::now();
    __m128i _tab_a,_tab_b,_partial_add_a, _partial_multiplication;
    for(int i = 0; i < ONE_HUNDRED_THOUSAND; i+=4) {
        _tab_a = _mm_setr_epi32(tab_1[i], tab_1[i + 1], tab_1[i + 2], tab_1[i + 3]);
        _tab_b = _mm_setr_epi32(tab_2[i], tab_2[i + 1], tab_2[i + 2], tab_2[i + 3]);

        _partial_add_a = _mm_add_epi32(_tab_a, _tab_b);
        _partial_multiplication = _mm_mul_epi32(_partial_add_a, _partial_add_a);

// check if not in reversse
        tab_3[i] = _partial_multiplication[i];
        tab_3[i+1] = _partial_multiplication[i+1];
        tab_3[i+2] = _partial_multiplication[i+2];
        tab_3[i+3] = _partial_multiplication[i+3];

    }
    auto _end = std::chrono::steady_clock::now();


    std::cout << "Hello, World!" << std::endl;

    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<" nanoseconds\n";

    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start).count()<<" _nanoseconds\n";
    for(int i=0;i<10;i++){
        int address = rand() % ONE_HUNDRED_THOUSAND;

        printf("%d\t+\t%d\t=\t%d\t[%d]\n", tab_1[address],tab_2[address],tab_3[address],address);


    }

    return 0;
}
