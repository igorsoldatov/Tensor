//
// Created by igor on 03.10.18.
//
#include "tensor.hpp"

template<typename T>
Tensor<T>::Tensor() {
   data_ = store();
   data_->resize(0);
   size_ = 0;
   offset_ = 0;
}

template<typename T>
Tensor<T>::Tensor(std::vector<int> dimSizes) {
   dims_ = dimSizes;
   init();
   data_ = std::make_shared<std::vector<T>>();
   data_->resize(size_);
   offset_ = 0;
}

template<typename T>
Tensor<T>::Tensor(const Tensor<T> &rhs) : size_(rhs.size_), dims_(rhs.dims_), stride_(rhs.stride_),
                                          rank_(rhs.rank_), offset_(rhs.offset_) {
   if (this == &rhs){
      return;
   }
   data_ = std::make_shared<std::vector<T>>();
   data_->resize(rhs.data_->size());
   std::memcpy(this->raw(), rhs.raw(), rhs.size()*sizeof(T));
};

template<typename T>
Tensor<T>::Tensor(Tensor<T> &&rhs) : data_(std::move(rhs.data_)), size_(std::move(rhs.size_)),
                                     dims_(std::move(rhs.dims_)), stride_(std::move(rhs.stride_)),
                                     rank_(std::move(rhs.rank_)), offset_(std::move(rhs.offset_)) {
}

template<typename T>
Tensor<T>& Tensor<T>::operator=(const Tensor<T> &rhs){
   if (this == &rhs){
      return *this;
   }
   data_ = std::make_shared<std::vector<T>>();
   data_->resize(rhs.size());
   std::memcpy(this->raw(), rhs.raw(), rhs.size()*sizeof(T));
   this->dims_ = rhs.dim();
   this->rank_ = rhs.rank();
   this->size_ = rhs.size();
   this->stride_ = rhs.stride();
   this->offset_ = rhs.offset();
   return *this;
}

template<typename T>
Tensor<T>& Tensor<T>::operator=(Tensor<T> &&rhs){
   if (this == &rhs){
      return *this;
   }
   data_ = std::move(rhs.data_);
   dims_ = std::move(rhs.dims_);
   rank_ = std::move(rhs.rank_);
   size_ = std::move(rhs.size_);
   stride_ = std::move(rhs.stride_);
   offset_ = std::move(rhs.offset_);
   return *this;
}

template<typename T>
Tensor<T> Tensor<T>::operator()(int low, int high) {
   std::vector<int> dims = this->dim();
   dims[0] = high - low;
   int last_stride = *std::prev(this->stride_.end());
   size_t offset = offset_ + (low * last_stride);
   Tensor<T> t(data_, offset, dims);
   return t;
}

template<typename T>
Tensor<T> Tensor<T>::operator()(int pos) {
   std::vector<int> dims;
   dims.resize(dims_.size() - 1);
   std::copy(std::next(dims_.cbegin()), dims_.cend(), dims.begin());
   int last_stride = *std::prev(this->stride_.end());
   size_t offset = offset_ + (pos * last_stride);
   Tensor<T> t(data_, offset, dims);
   return t;
}

template<typename T>
T& Tensor<T>::operator[](std::vector<int> pos) {
   assert(pos.size() == dims_.size());
   size_t p = offset_;
   int i = 0;
   int j = rank_ - 1;
   for ( ; i < rank_; ++i, --j){
      p += pos[i] * stride_[j];
   }
   return data_->operator[](p);
}

template<typename T>
Tensor<T> Tensor<T>::reshape(std::vector<int> newDimSizes) {
   store data = std::make_shared<std::vector<T>>();
   data->resize(data_->size());
   std::memcpy(data->data(), raw(), data_->size()*sizeof(T));
   return Tensor(data, offset_, newDimSizes);
}

template<typename T>
Tensor<T>::Tensor(store data, size_t offset, std::vector<int> dims) {
   data_ = std::move(data);
   dims_ = std::move(dims);
   offset_ = std::move(offset);
   init();
}

template<typename T>
void Tensor<T>::init() {
   size_ = 1;
   rank_ = dims_.size();
   stride_.resize(rank_);
   stride_[0] = 1;
   for (int n = 0; n < rank_; ++n) {
      size_ *= dims_[n];
   }
   for (int n = 1; n < rank_; ++n) {
      //stride_[n] = stride_[n - 1] * ((dims_[n - 1] == 1) ? dims_[n] : dims_[n - 1]);
      stride_[n] = stride_[n - 1] * dims_[n];
   }
}