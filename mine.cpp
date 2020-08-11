#include <iostream>
#include <emmintrin.h>
#include <nmmintrin.h>
#include <chrono>
#include <limits>

struct vector4
{
    long long int v1;
    long long int v2;
    long long int v3;
    long long int v4;
};


vector4 add(vector4 a, vector4 b) {
    __m128i __vector_1 = _mm_setr_epi32(a.v1, a.v2, a.v3, a.v4);
    __m128i __vector_2 = _mm_setr_epi32(a.v1, a.v2, a.v3, a.v4);

    __m128i __wynik = _mm_add_epi32(__vector_1, __vector_2);

    vector4 wynik{ __wynik[0], __wynik[1], __wynik[2], __wynik[3] };

    return wynik;

}

vector4 multiply(vector4 a, vector4 b) {
    __m128i __vector_1 = _mm_setr_epi32(a.v1, a.v2, a.v3, a.v4);
    __m128i __vector_2 = _mm_setr_epi32(a.v1, a.v2, a.v3, a.v4);

    __m128i __wynik = _mm_mul_epi32(__vector_1, __vector_2);

    vector4 wynik{ __wynik[0], __wynik[1], __wynik[2], __wynik[3] };

    return wynik;

}

int main() {
    vector4 v1 ={ 100, 200, 300, 400 };
    vector4 v2 ={ 100, 200, 300, 400 };
    vector4 v3;

    auto start = std::chrono::high_resolution_clock::now();

    for (long int i = 0; i < 10000000000; i++) {
        if (v3.v1 >= INT32_MAX ||v3.v2 >= INT32_MAX ||v3.v3 >= INT32_MAX ||v3.v4 >= INT32_MAX) {
            v3 = add(multiply(v3, v3), multiply(v3, v3));
        }
        else {
            v3.v1 = 0;
            v3.v2 = 0;
            v3.v3 = 0;
            v3.v4 = 0;
        }

    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end -start).count() << std::endl;

    start = std::chrono::high_resolution_clock::now();

    for (long int i = 0; i < 10000000000; i++) {
        if (v3.v1 >= INT32_MAX ||v3.v2 >= INT32_MAX ||v3.v3 >= INT32_MAX ||v3.v4 >= INT32_MAX) {
            if (v3.v1 >= INT32_MAX ||v3.v2 >= INT32_MAX ||v3.v3 >= INT32_MAX ||v3.v4 >= INT32_MAX) {
                v3.v1 = (v3.v1 * v3.v1) + (v3.v1* v3.v1);
                v3.v2 = (v3.v2 * v3.v2) + (v3.v2* v3.v2);
                v3.v3 = (v3.v3 * v3.v3) + (v3.v3* v3.v3);
                v3.v4 = (v3.v4 * v3.v4) + (v3.v4* v3.v4);
            }
        }
        else {
            v3.v1 = 0;
            v3.v2 = 0;
            v3.v3 = 0;
            v3.v4 = 0;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end -start).count();

}
