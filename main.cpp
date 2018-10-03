#include <iostream>
#include "tensor.cpp"

int main() {
   Tensor<float> t1 = Tensor<float>({5, 5, 5});
   Tensor<float> t2 = t1(3, 4);
   Tensor<float> t3 = t2;
   Tensor<float> t4 = t1(3);
   t4 = t1(3);
   Tensor<float> t5 = t1(3)(4)(2, 5);
   t5[{1}] = 100.0;
   t1[{3, 4, 4}] = -100.0;

   std::cout << "testing..." << std::endl;
   std::cout << "t5[{1}]     = " << t5[{1}] << std::endl;
   std::cout << "t1[{3,4,3}] = " << t1[{3,4,3}] << std::endl;
   std::cout << "t2[{0,4,3}] = " << t2[{0,4,3}] << std::endl;
   std::cout << "t4[{4,3}]   = " << t4[{4,3}] << std::endl;
   std::cout << "t3[{0,4,3}] = " << t3[{0,4,3}] << std::endl;
   std::cout << "t1[{3,4,4}] = " << t1[{3,4,4}] << std::endl;
   std::cout << "t2[{0,4,4}] = " << t2[{0,4,4}] << std::endl;
   std::cout << "t4[{4,4}]   = " << t4[{4,4}] << std::endl;
   std::cout << "t5[{2}]     = " << t5[{2}] << std::endl;
   std::cout << "t3[{0,4,4}] = " << t3[{0,4,4}] << std::endl;

   assert((t5[{1}]     == 100.0));
   assert((t1[{3,4,3}] == 100.0));
   assert((t2[{0,4,3}] == 100.0));
   assert((t4[{4,3}]   == 100.0));
   assert((t3[{0,4,3}] == 0.0));
   assert((t1[{3,4,4}] == -100.0));
   assert((t2[{0,4,4}] == -100.0));
   assert((t4[{4,4}]   == -100.0));
   assert((t5[{2}]     == -100.0));
   assert((t3[{0,4,4}] == 0.0));

   std::cout << "SUCCESS!!!" << std::endl << std::endl;
   std::cout << "reshape testing..." << std::endl;

   Tensor<float> t6 = t1.reshape({5,25});
   std::cout << "t6[{3,23}] = " << t6[{3,23}] << std::endl;
   Tensor<float> t7 = t2.reshape({5,5});
   std::cout << "t7[{4,3}]  = " << t7[{4,3}] << std::endl;

   return 0;
}