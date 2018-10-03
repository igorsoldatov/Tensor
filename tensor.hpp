//
// Created by igor on 03.10.18.
//

#ifndef TENSOR_TENSOR_HPP
#define TENSOR_TENSOR_HPP

#include <vector>
#include <cstring>
#include <memory>
#include <assert.h>

template < typename T >
class Tensor {
public:
   typedef std::shared_ptr<std::vector<T>> store;

   Tensor();

   Tensor(std::vector<int> dimSizes);

   Tensor(const Tensor<T>& rhs);

   Tensor(Tensor<T>&& rhs);

   Tensor& operator=(const Tensor<T> &rhs);

   Tensor& operator=(Tensor<T> &&rhs);

   Tensor operator()(int low, int high);

   Tensor operator()(int pos);

   T& operator[](std::vector<int> pos);

   Tensor reshape(std::vector<int> newDimSizes);

   std::vector<int> dim() const { return dims_; }

   std::vector<int> stride() const { return stride_; }

   size_t size() const { return size_; }

   size_t rank() const { return rank_; }

   size_t offset() const { return offset_; }

   T* raw() { return data_.get()->data(); }

   const T* raw() const { return data_.get()->data(); }

   void init();

private:
   store data_;
   std::vector<int> dims_;
   std::vector<int> stride_;
   size_t size_;
   size_t rank_;
   size_t offset_;

   Tensor( store data, size_t offset, std::vector<int> dims);
};

#endif //TENSOR_TENSOR_HPP
