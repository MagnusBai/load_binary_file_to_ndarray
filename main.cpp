#include <iostream>

#include <memory>
#include "mnist_tool.hpp"

using std::shared_ptr;

int main() {
  shared_ptr<int> ptr_train_label; uint32_t w_train_label, h_train_label;
  if(!
    createLabelsIdx1Ubyte("data/train-labels-idx1-ubyte", ptr_train_label, h_train_label, w_train_label)
  ) {
    std::cout << "loading train-labels-idx1-ubyte failed\n";
  }

	shared_ptr<int> ptr_train_images; uint32_t w_train_im, h_train_im, n_train_im;
  createImagesIdx3Ubyte("data/train-images-idx3-ubyte", ptr_train_images, n_train_im, h_train_im, w_train_im);
  return 0;
}
