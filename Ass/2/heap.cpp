#include <bits/stdc++.h>
#include <iostream>

typedef long long int lint;

lint hip[100007]; // stores the heap
lint ind = 0; // stores the last element of the heap

void print() {
  for(lint i = 1; i <= ind; i++) {
    std::cout << hip[i] << ' ';
  }
  std::cout  << '\n';
}

void heapify(lint index) { // heapifies the heap index up, by parent
  // This function assumes the rest of the function was a proper max heap
  // Basically only the last element added is initially assumed
  // to be in trouble
  if(index == 1) { // parent is stored at 1
    return;
  }

  lint temp;

  // std::cout << "Checking validity at heap[" << index << "] = " << hip[index] << ", parent is heap[" << index/2 << "] as " << hip[index/2] << std::endl;
  if(hip[index] > hip[index/2]) { // Max heap. Parent must be >= child
    // swap
    temp = hip[index/2];
    hip[index/2] = hip[index];
    hip[index] = temp;

    //call again on new Parent
    heapify(index/2);
  }

}

void heapdown(lint index) {
  lint temp;

  if(2*index > ind) {
    return;
  }

  if(hip[index] < hip[2*index] || hip[index] < hip[2*index+1]) {
    if(hip[2*index] > hip[2*index+1]) {
      temp = hip[index];
      hip[index] = hip[2*index];
      hip[2*index] = temp;
    }
    else {
      temp = hip[index];
      hip[index] = hip[2*index+1];
      hip[2*index+1] = temp;
    }
  }
}

void hinsert(lint data) { // Assumes the rest of the heap is a heap proper
  hip[++ind] = data;
  heapify(ind);
  // std::cout << heapify(ind) << '\n';
}

void hdel(lint index) {
  if(ind == 0) {
    std::cout << "Heap is empty" << std::endl;
    return;
  }
  lint temp = hip[index];
  hip[index] = hip[ind];
  ind--; // fuck the last one in particular
  
  if(hip[index] < temp) {
    heapdown(index);
  }
  else {
    heapify(index);
  }

}

int main() {
  lint opt, temp;
  while(true) {
    std::cout<< "Hi. Enter 1 to Insert, 2 to delete, 3 to print." << std::endl;
    std::cin >> opt;

    switch (opt) {
      case 1:
        std::cout << "Enter value to insert" << '\n';
        std::cin >> temp;

        hinsert(temp);
        print();
        break;
      case 2:
        std::cout << "Enter node number to delete" << '\n';
        std::cin >> temp;

        hdel(temp);
        print();
        break;
      case 3:
        print();
        break;
      default:
        std::cout << "Wrong input, try again" << std::endl;
        break;
    }
  }

  return 0;
}
