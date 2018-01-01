#ifndef MNIST_TOOL_HPP
#define MNIST_TOOL_HPP

#include <stdio.h>
#include <memory>
#include <iostream>

#ifndef IN
#define IN
#define OUT
#endif

using std::shared_ptr;

bool createTrainLabelsIdx1Ubyte(const char* IN path, shared_ptr<int>& OUT ptr_mat, int& OUT H, int& OUT W);

bool createTrainLabelsIdx1Ubyte(const char* IN path, shared_ptr<int>& OUT ptr_mat, int& OUT H, int& OUT W) {
  FILE * p_file;
  p_file = fopen (path , "rb");
  if(p_file == NULL) { return false; }
  {
    char magic_number[4];
    if( fgets(magic_number, 4, p_file)==NULL ) { return false; }
#ifdef DEBUG
    std::cout << "magic number: " << *((int*)magic_number) << std::endl;
#endif
  }
  {
    char number_of_items[4];
    if( fgets(number_of_items, 4, p_file)==NULL ) { return false; }
    W=1; H=*((int*)number_of_items);
#ifdef DEBUG
    std::cout << "number of items: " << *((int*)number_of_items) << std::endl;
#endif
  }
  fclose (p_file);
}

#endif