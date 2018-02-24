// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

typedef long long int lint;

typedef struct data {
  /* data */
  lint days;
  lint sadness;
} girl;

girl * hip[200010]; // stores the heap
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

  if(2*index > ind) {
    return;
  }

  // HORRIBLE, HORRIBLE HACKS TO DEBUG. OH, THE HORROR
  // if(2*index+1 > (ind+1)) {
  //   temp = hip[index];
  //   hip[index] = hip[2*index];
  //   hip[2*index] = temp;
  // }
  else if(hip[index]->sadness < hip[2*index]->sadness || hip[index]->sadness < hip[2*index+1]->sadness) {
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
  // std::cout << "Copied hip[index] into temp" << '\n';
  hip[index] = hip[ind];
  // std::cout << "Replaced hip[index] with hip[ind]" << '\n';
  ind--; // fuck the last one in particular
  // std::cout << "Reduced heap size by 1 (ind--), ind = " << ind << '\n';

  if(hip[index]->sadness < temp->sadness) {
    // std::cout << "Since hip[index] < temp, we going down" << '\n';
    heapdown(index);
    // std::cout << "We went down" << '\n';
  }
  else {
    // std::cout << "Since hip[index] > temp, up up and away" << '\n';
    heapify(index);
    // std::cout << "Woohoo" << '\n';
  }
  free(temp);
}

int main() {
  /* code */
  lint T, i, j, N, D, k, sad = 0, temp; // T <= 10, 1 <= N, D <= 1e5

  std::cin >> T; // number of test cases
  for(i = 0; i < T; i++) {
    sad = 0;

    std::cin >> N >> D; // test case i input

    std::vector<girl *> din[D+1]; // vector array of all additions

    // reserve 10 for all din[] elements

    for(j = 0; j < N; j++) { // for test i
      girl * g = (girl *) malloc(sizeof(girl));
      std::cin >> temp >> g->days >> g->sadness; // TODO ADD INPUT FOR DAY OF ENTRY
      if(din[temp].size() == 0) {
        din[temp].reserve(10);
      }
      din[temp].push_back(g);
      // std::cout << "Pushed girl with sadness=" << g->sadness << " days=" << g->days << " onto list for day " << temp << '\n';
      //hinsert(g);
      //print();
    }

    // iterate through each day
    for(j = 1; j <= D; j++) {
      // std::cout << "On day " << (j) << " we have ";

      for(k = 0; k < din[j].size(); k++) {
        girl * g = din[j][k];
        sad += g->sadness * g->days;
        hinsert(g);
      }

      // for (girl * g : din[j]) {// for each girl in day, add her to the heap
      //   // std::cout << " sadness: " << g->sadness << " for " << g->days << " days\n";
      //   sad += g->sadness * g->days;
      //   hinsert(g);
      // }
      // std::cout << "Total sadness at start of day: " << sad << '\n';
      // now remove max sadness for the day;
      sad -= hip[1]->sadness;
      hip[1]->days = hip[1]->days - 1;

      if(sad < 0) {
        sad = 0;
      }

      // std::cout << "removed " << hip[1]->sadness << " from sadness. Days left for current : " << hip[1]->days << '\n';
      if(hip[1]->days == 0) {
        // std::cout << "We bout to get deleting baby" << '\n';
        hdel(1);
      }

      // std::cout << "Total sadness at end of day: " << sad << '\n';
    }

    std::cout << sad << std::endl; // print the minimum sadness for the test

    }


  return 0;
}
