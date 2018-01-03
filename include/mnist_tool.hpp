#ifndef MNIST_TOOL_HPP
#define MNIST_TOOL_HPP

// #include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <ios>

#ifndef IN
#define IN
#define OUT
#endif

#ifndef __ERRORHANDLE__
#define __ERRORHANDLE__
#endif

using std::shared_ptr;

uint32_t swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

bool createTrainLabelsIdx1Ubyte(const char* IN path, shared_ptr<int>& OUT ptr_mat, uint32_t& OUT H, uint32_t& OUT W);

bool createTrainLabelsIdx1Ubyte(const char* IN path, shared_ptr<int>& OUT ptr_mat, uint32_t& OUT H, uint32_t& OUT W) {
  std::ifstream label_file(path, std::ios::in | std::ios::binary);
  {
    __ERRORHANDLE__ if(!label_file.good()) return false;
  }
  {
    uint32_t magic;
    label_file.read(reinterpret_cast<char*>(&magic), 4);
    __ERRORHANDLE__ if(!label_file.good()) return false;
    magic = swap_endian(magic);
    __ERRORHANDLE__ if(magic!=2049) return false;
  }
  {
    uint32_t num_labels;
    label_file.read(reinterpret_cast<char*>(&num_labels), 4);
    __ERRORHANDLE__ if(!label_file.good()) return false;
    num_labels = swap_endian(num_labels);
    H=num_labels; W=1;
    __ERRORHANDLE__ if(num_labels!=60000) return false;
  }
  ptr_mat = shared_ptr<int>(new int [W*H]);
  {
    char label;
    for (int item_id = 0; item_id < H; ++item_id) {
      label_file.read(&label, 1);
      __ERRORHANDLE__ if(!label_file.good()) return false;
      ptr_mat.get()[item_id]=(int)label;
    }
  }
  return true;
}

bool createTrainImagesIdx3Ubyte(const char* IN path, shared_ptr<int>& OUT ptr_mat, uint32_t& OUT N, uint32_t& OUT H, uint32_t& OUT W) {
  std::ifstream image_file(path, std::ios::in | std::ios::binary);

  uint32_t magic, num_items, rows, cols;

  image_file.read(reinterpret_cast<char*>(&magic), 4);
  magic = swap_endian(magic);

  image_file.read(reinterpret_cast<char*>(&num_items), 4);
  num_items = swap_endian(num_items);

  image_file.read(reinterpret_cast<char*>(&rows), 4);
  rows = swap_endian(rows);
  image_file.read(reinterpret_cast<char*>(&cols), 4);
  cols = swap_endian(cols);

  H=rows; W=cols; N=num_items;
  ptr_mat = shared_ptr<int>(new int [N*H*W]);
  char* pixels = new char[rows * cols];
  for (int item_id = 0; item_id < num_items; ++item_id) {
    image_file.read(pixels, rows * cols);
    for(int i=0; i<H*W; ++i) {
      ptr_mat.get()[item_id*H*W+i] = (int)(pixels[i]);
    }
  }

  return true;
}

#endif