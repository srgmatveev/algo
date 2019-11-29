//
// Created by sergio on 29.11.2019.
//
#pragma once

#include <vector>
#include <memory>

template<typename T>
class Matrix {
private:
    T n{2}; //size of matrix
    std::vector<std::vector<T>> matrix;
public:
    Matrix() {
        std::vector<T> first{1, 1};
        std::vector<T> second{1, 0};
        matrix.emplace_back(first);
        matrix.emplace_back(second);
    }

    Matrix(bool trivial) {
        if (trivial) {
            std::vector<T> first{1, 0};
            std::vector<T> second{0, 1};
            matrix.emplace_back(first);
            matrix.emplace_back(second);
        } else {
            std::vector<T> first{1, 1};
            std::vector<T> second{1, 0};
            matrix.emplace_back(first);
            matrix.emplace_back(second);
        }


    }

    std::shared_ptr<Matrix<T>> operator*(std::shared_ptr<Matrix<T>> right) {
        std::shared_ptr<Matrix<T>> tmp = std::make_shared<Matrix<T>>();
        std::vector<T> tmp_first;
        tmp_first.resize(2);
        std::vector<T> tmp_second;
        tmp_second.resize(2);
        tmp_first[0] = this->matrix[0][0] * right->matrix[0][0] +
                       this->matrix[0][1] * right->matrix[1][0];
        tmp_first[1] = this->matrix[0][0] * right->matrix[0][1] +
                       this->matrix[0][1] * right->matrix[1][1];

        tmp_second[0] = this->matrix[1][0] * right->matrix[0][0] +
                        this->matrix[1][1] * right->matrix[1][0];

        tmp_second[1] = this->matrix[1][0] * right->matrix[0][1] +
                        this->matrix[1][1] * right->matrix[1][1];


        tmp->matrix[0] = tmp_first;
        tmp->matrix[1] = tmp_second;

        return tmp;
    }

    T result() {
        return matrix[0][0];
    }

};

template<class T>
std::shared_ptr<Matrix<T>> binpow(std::shared_ptr<Matrix<T>> a, const T &n) {
    if (n == 0)
        return std::make_shared<Matrix<T>>(true);
    if (n % 2 == 1){
        return  std::shared_ptr<Matrix<T>>(*(Matrix<T>*)a.get()* binpow(a, n - 1));
    }
    else {
        std::shared_ptr<Matrix<T>> b = binpow(a, n / 2);
        return std::shared_ptr<Matrix<T>>(*(Matrix<T>*)b.get() * b);
    }
}

template<class T>
T fibonacci(const T &t) {
    if (t == 0) return 0;
    std::shared_ptr<Matrix<T>> matrix = std::make_shared<Matrix<T>>();
    std::shared_ptr<Matrix<T>> m = binpow(matrix, t - 1);
    return m->result();
}
