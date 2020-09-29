//
//  linear.cpp
//  linear
//
//  Created by Mitchell McLinton on 6/2/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include <iostream>
#include <cassert>

bool somePredicate(double x) { return x < 0; }

/* TODO: REMOVE ALL ABOVE */


  // Return true if the somePredicate function returns false for at
  // least one of the array elements; return false otherwise.
bool anyFalse(const double a[], int n)
{
    if (n <= 0)
        return false;
    else if (!somePredicate(a[0]))    // n > 0; a[0] still has non-garbage value
        return true;
    else
        return anyFalse(a+1, n-1);
}

  // Return the number of elements in the array for which the
  // somePredicate function returns true.
int countTrue(const double a[], int n)
{
    int count = 0;
    
    if (n <= 0)
        return count;
    else if (somePredicate(a[0]))
        count++;
    count += countTrue(a+1, n-1);
    return count;
}

  // Return the subscript of the first element in the array for which
  // the somePredicate function returns true.  If there is no such
  // element, return -1.
int firstTrue(const double a[], int n)
{
    if (n <= 0)
        return -1;
    else if (somePredicate(a[0]))
        return 0;
    else {
        int result = firstTrue(a+1, n-1);
        if (result != -1)
            return 1+result;
        else
            return -1;
    }
}

  // Return the subscript of the smallest element in the array (i.e.,
  // return the smallest subscript m such that a[m] <= a[k] for all
  // k from 0 to n-1).  If the function is told to examine no
  // elements, return -1.
int positionOfSmallest(const double a[], int n)
{
    if (n <= 0)
        return -1;
    else if (n == 1)
        return 0;
    else {
        int minIdx = 1+positionOfSmallest(a+1, n-1);
        if (a[0] <= a[minIdx])
            return 0;
        else
            return minIdx;
    }
}

  // If all n2 elements of a2 appear in the n1 element array a1, in
  // the same order (though not necessarily consecutively), then
  // return true; otherwise (i.e., if the array a1 does not contain
  // a2 as a not-necessarily-contiguous subsequence), return false.
  // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
  // For example, if a1 is the 7 element array
  //    10 50 40 20 50 40 30
  // then the function should return true if a2 is
  //    50 20 30
  // or
  //    50 40 40
  // and it should return false if a2 is
  //    50 30 20
  // or
  //    10 20 20
bool contains(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return true;
    else if (n1 < n2)
        return false;
    else if (a1[0] == a2[0])
        return contains(a1+1, n1-1, a2+1, n2-1);
    else
        return contains(a1+1, n1-1, a2, n2);
}

/* TODO: REMOVE ALL BELOW */
int main() {
    double a10[5] = { 3, -4, -5, -6, 7 };
    double a11[5] = { -3, -4, -6, -6, -7 };
    assert(anyFalse(a10, 5));
    assert(!anyFalse(a11, 5));
    assert(!anyFalse(a10, 0));
    assert(!anyFalse(a10, -99));
    
    assert(countTrue(a10, 5) == 3);
    assert(countTrue(a11, 5) == 5);
    double a20[5] = { 3, 4, 5, 6, 7};
    assert(countTrue(a20, 5) == 0);
    assert(countTrue(a20, 0) == 0);
    assert(countTrue(a20, -17) == 0);
    
    assert(firstTrue(a10, 5) == 1);
    assert(firstTrue(a11, 5) == 0);
    assert(firstTrue(a20, 5) == -1);
    assert(firstTrue(a20, -2) == -1);
    assert(firstTrue(a10, 0) == -1);
    
    assert(positionOfSmallest(a10, 5) == 3);
    assert(positionOfSmallest(a11, 5) == 4);
    assert(positionOfSmallest(a20, 5) == 0);
    double a21[5] = { 3, 3, 3, 3, 3};
    assert(positionOfSmallest(a21, 5) == 0);
    assert(positionOfSmallest(a20, -3) == -1);
    assert(positionOfSmallest(a20, 0) == -1);
    double a22[1] = { -999999 };
    assert(positionOfSmallest(a22, 1) == 0);
    
    double a90[7] = { 10, 20, 50, 70, 90, 30, 40 };
    double a91[3] = { 20, 90, 30};
    assert(contains(a90, 7, a91, 3));
    double a92[3] = { 20, 10, 50 };
    assert(!contains(a90, 7, a92, 3));
    assert(!contains(a90, 3, a92, 5));
    assert(!contains(a90, -3, a92, 5));
    assert(contains(a90, 7, a92, -2));
    assert(contains(a90, 7, a92, 0));
    assert(contains(a90, 0, a92, 0));
    assert(contains(a90, -4187, a92, -3298764));
    assert(contains(a90, 7, a90, 7));
    assert(contains(a90, 7, a90, 6));
    assert(contains(a90, 7, a90, 5));
    assert(contains(a90, 7, a90, 4));
    assert(contains(a90, 7, a90, 3));
    assert(contains(a90, 7, a90, 2));
    assert(contains(a90, 7, a90, 1));
    assert(contains(a90, 7, a90, 0));
    
    std::cout << "Actually passed all tests!" << std::endl;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    double a1[3] = { 1, 4, 7 };
    double a2[6] = { -3, -69, -4, -8, -9, -10 };
    assert(anyFalse(a1, 3));
    assert(!anyFalse(a2, 6));
    
    double a3[5] = { -5, 9, -8, 0, 3 };
    assert(countTrue(a1, 3) == 0);
    assert(countTrue(a2, 6) == 6);
    assert(countTrue(a3, 5) == 2);
    
    double a4[4] = { 3, 2, 1, -9 };
    assert(firstTrue(a1, 3) == -1);
    assert(firstTrue(a2, 6) == 0);
    assert(firstTrue(a4, 4) == 3);
    
    double a5[4] = { 3, 4, 1, 5 };
    assert(positionOfSmallest(a5, 4) == 2);
    assert(positionOfSmallest(a1, 3) == 0);
    assert(positionOfSmallest(a3, 5) == 2);
    
    double arr1[7] = { 10, 50, 40, 20, 50, 40, 30 };
    double arr20[3] = { 50, 20, 30 };
    double arr21[3] = { 50, 40, 40 };
    double arr22[3] = { 50, 30, 20 };
    double arr23[3] = { 10, 20, 20 };
    assert(contains(arr1, 7, arr20, 3));
    assert(contains(arr1, 7, arr21, 3));
    assert(!contains(arr1, 7, arr22, 3));
    assert(!contains(arr1, 7, arr23, 3));
    
    double arr3[5] = { -67, 23.3, 45.7, 29.1, 69.2 };
    double arr40[2] = { 23.3, 69.2 };
    double arr41[1] = { -67 };
    double arr42[3] = { -67, 45.7, 69.2 };
    double arr43[3] = { 29.1, 45.7, 69.2 };
    double arr44[3] = { -67, 23.3, 11.1 };
    assert(contains(arr3, 5, arr40, 2));
    assert(contains(arr3, 5, arr41, 1));
    assert(contains(arr3, 5, arr42, 3));
    assert(!contains(arr3, 5, arr43, 3));
    assert(!contains(arr3, 5, arr44, 3));
    
    assert(!contains(arr3, 5, arr40, 6));
    assert(contains(arr3, -2, arr40, -2));  // will return true as if n2 < 0 we act as if it is 0
    assert(contains(arr3, 5, arr40, -9));
    assert(!contains(arr3, -4, arr40, 3));  // will return false as if n1 < 0 we act as if it is 0; array of 0 elements has only 1 subsequence --> itself
    
    
    std::cout << "Passed all tests!" << std::endl;
}
