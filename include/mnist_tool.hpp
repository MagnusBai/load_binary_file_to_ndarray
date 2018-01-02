#ifndef MNIST_TOOL_HPP
#define MNIST_TOOL_HPP

// #include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <assert.h>

#ifndef IN
#define IN
#define OUT
#endif

using std::shared_ptr;

uint32_t swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

bool createTrainLabelsIdx1Ubyte(const char* IN path, shared_ptr<int>& OUT ptr_mat, uint32_t& OUT H, uint32_t& OUT W);

bool createTrainLabelsIdx1Ubyte(const char* IN path, shared_ptr<int>& OUT ptr_mat, uint32_t& OUT H, uint32_t& OUT W) {
  // FILE * p_file;
  // p_file = fopen (path , "rb");
  // if(p_file == NULL) { return false; }
  // {
  //   char magic_number[4];
  //   if( fgets(magic_number, 4, p_file)==NULL ) { return false; }
  //   #ifdef DEBUG 
  //   std::cout << "magic number: " << swap_endian(*((uint32_t*)magic_number)) << std::endl;
  //   #endif
  // }
  // {
  //   char number_of_items[4];
  //   if( fgets(number_of_items, 4, p_file)==NULL ) { return false; }
  //   W=1; H=*((uint32_t*)number_of_items);
  //   #ifdef DEBUG
  //   std::cout << "number of items: " << H << std::endl;
  //   std::cout << "number of items: " << swap_endian(H) << std::endl;
  //   #endif
  // }
  // fclose (p_file);
  std::ifstream label_file(path, std::ios::in | std::ios::binary);
  {
    uint32_t magic;
    label_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if(magic!=2049) return false;
  }
  {
    uint32_t num_labels;
    label_file.read(reinterpret_cast<char*>(&num_labels), 4);
    num_labels = swap_endian(num_labels);
    H=num_labels; W=1;
    if(num_labels!=60000) return false;
  }
  ptr_mat = shared_ptr<int>(new int [W*H]);
  {
    char label;
    for (int item_id = 0; item_id < H; ++item_id) {
      label_file.read(&label, 1);
      ptr_mat.get()[item_id]=(int)label;
    }
  }
  return true;
}

#endif