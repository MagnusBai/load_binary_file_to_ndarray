#include <iostream>

#include <memory>
#include "mnist_tool.hpp"

using std::shared_ptr;

int main() {
  shared_ptr<int> ptr_train_label; uint32_t w_train_label, h_train_label;
  createTrainLabelsIdx1Ubyte("data/train-labels-idx1-ubyte", ptr_train_label, h_train_label, w_train_label);
  return 0;
}
