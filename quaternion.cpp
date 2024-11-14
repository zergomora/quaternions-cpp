#include <iostream>
#include <vector>

template <typename T>
class Quaternion {
private:
    std::vector<T> lambda;
public:
    Quaternion(T c0, T c1, T c2, T c3) {
        lambda = {c0, c1, c2, c3};
    }
    Quaternion(T c1, T c2, T c3) :
        Quaternion(T(), c1, c2, c3) {}
    Quaternion(T c0) :
        Quaternion(c0, T(), T(), T()) {}
    Quaternion() :
        Quaternion(T(), T(), T(), T()) {}
    
    T& operator[](size_t index) {
        return lambda[index];
    }

    Quaternion& operator+(Quaternion B) {
        for(size_t i = 0; i < 4; i++) {
            lambda[i] += B[i];
        }
        return *this;
    }

    Quaternion& operator+=(Quaternion B) {
        for(size_t i = 0; i < 4; i++) {
            lambda[i] += B[i];
        }
        return *this;
    }

    Quaternion& operator-=(Quaternion B) {
        for(size_t i = 0; i < 4; i++) {
            lambda[i] -= B[i];
        }
        return *this;
    }

    Quaternion& conjugate() {
        for(size_t i = 1; i < 4; i++) {
            lambda[i] = -lambda[i];
        }
        return *this;  
    }

    /**friend Quaternion& operator*(T value) {
        for(size_t i = 0; i < 4; i++) {
            lambda[i] *= value;
        }
        return *this;
    }**/
};

template<typename T>
T scalarp(Quaternion<T> A, Quaternion<T> B) {
    T result = 0;
    for(size_t i = 0; i < 4; i++) {
        result += A[i] * B[i];  
    }
    return result;
}

template<typename T>
auto vectorp(Quaternion<T> A, Quaternion<T> B) {
    Quaternion<T> result = A; 

    result[1] = A[2]*B[3] - A[3]*B[2];
    result[2] = A[3]*B[1] - A[1]*B[1];
    result[3] = A[1]*B[2] - A[2]*B[1];

    return result;
}

template<typename T>
auto quaternionp(Quaternion<T> A, Quaternion<T> B) {
    Quaternion<T> temp1 = vectorp(A, B), temp2; 

    temp2[0] = A[0]*B[0] - scalarp(A, B);
    temp2[1] = A[0]*B[1] + B[0]*A[1];
    temp2[2] = A[0]*B[2] + B[0]*A[2];
    temp2[3] = A[0]*B[3] + B[0]*A[3];

    Quaternion<T> result = temp1 + temp2;

    return result;
}

int main() {
    Quaternion<int> q1(0,1,0,0), q2(0,0,1,0);

    //q1+=q2;
    //q1[3] = 5;
    /**std::cout << q1[3] << std::endl;**/

    //std::cout << scalarp(q1, q2) << std::endl;
    std::cout << q1.conjugate()[1] << std::endl;
    //std::cout << vectorp(q1, q2)[1] << std::endl;
    std::cout << quaternionp(q1, q2)[3] << std::endl;

}
