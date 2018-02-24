#include <bits/stdc++.h>
#include <iostream>

typedef long long int lint;

typedef struct data {
  /* data */
  lint days;
  lint sadness;
} girl;

girl * hip[100007]; // stores the heap
lint ind = 0; // stores the last element of the heap

void print() {
  for(lint i = 1; i <= ind; i++) {
    std::cout << hip[i]->sadness << ' ';
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

  girl * temp;

  // std::cout << "Checking validity at heap[" << index << "] = " << hip[index] << ", parent is heap[" << index/2 << "] as " << hip[index/2] << std::endl;
  if(hip[index]->sadness > hip[index/2]->sadness) { // Max heap. Parent must be >= child
    // swap
    temp = hip[index/2];
    hip[index/2] = hip[index];
    hip[index] = temp;

    //call again on new Parent
    heapify(index/2);
  }

}

void heapdown(lint index) {
  girl * temp;
  if(hip[index]->sadness < hip[2*index]->sadness || hip[index]->sadness < hip[2*index+1]->sadness) {
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

void hinsert(girl * data) { // Assumes the rest of the heap is a heap proper
  hip[++ind] = data;
  heapify(ind);
  // std::cout << heapify(ind) << '\n';
}

void hdel(lint index) {
  if(ind == 0) {
    std::cout << "Heap is empty" << std::endl;
    return;
  }
  girl * temp = hip[index];
  hip[index] = hip[ind];
  ind--; // fuck the last one in particular

  if(hip[index]->sadness < temp->sadness) {
    heapdown(index);
  }
  else {
    heapify(index);
  }

}

int main() {
  /* code */
  lint T, i, j, N, D, k, sad = 0, din; // T <= 10, 1 <= N, D <= 1e5

  std::cin >> T; // number of test cases
  for(i = 0; i < T; i++) {

    din = 0, sad = 0;

    std::cin >> N >> D; // test case i input

    for(j = 0; j < N; j++) { // for test i
      girl * g = (girl *) malloc(sizeof(girl));
      std::cin >> g->days >> g->sadness; // TODO ADD INPUT FOR DAY OF ENTRY
      //hinsert(g);
      //print();
    }

    // iterate through each day
    for(j = 1; j <= D; j++) {
      {// for each girl in day, add her to the heap
        hinsert(girl);
        sad += girl->sadness * girl->days;
      }

      // now remove max sadness for the day;
      sad -= hip[1]->sadness;
      hip[1]->sadness = hip[1]->sadness - 1;

      if(hip[1]->sadness == 0) {
        hdel(1);
      }
    }

    std::cout >> sad >> std::endl; // print the minimum sadness for the test

    }


  return 0;
}
