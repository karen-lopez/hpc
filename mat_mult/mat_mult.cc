/*
compile line:
g++ -std=c++11 -pthread mat_mult.cc
run line:
./a.out
*/

#include "ThreadPool.hh"
#include "matrix.hh"
#include "timer.hh"
#include <cassert>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

/**
 * Classical matrix multiplication
 */
Matrix mult(const Matrix& a, const Matrix& b) {
  assert(a.numCols() == b.numRows());
  Matrix result(a.numRows(), b.numCols());

  for (size_t r = 0; r < a.numRows(); r++)
    for (size_t c = 0; c < b.numCols(); c++)
      for (size_t nc = 0; nc < b.numRows(); nc++)
        result.at(r, c) += a.at(r, nc) * b.at(nc, c);
  return result;
}

/**
 * First try to parallel matrix multiplication.
 *
 * To learn:
 *  - Too many threads are bad!
 *  - Threads are not for free
 *  - Just using threads does not make a program fater!
 */
void computeCell(const Matrix& a, const Matrix& b, size_t ra, size_t cb,
                 double& result) {
  assert(a.numCols() == b.numRows());
  result = 0.0;
  for (size_t nc = 0; nc < b.numRows(); nc++) {
    result += a.at(ra, nc) * b.at(nc, cb);
  }
}

Matrix mult2(const Matrix& a, const Matrix& b) {
  assert(a.numCols() == b.numRows());
  Matrix result(a.numRows(), b.numCols());

  vector<thread> threads;

  for (size_t r = 0; r < a.numRows(); r++)
    for (size_t c = 0; c < b.numCols(); c++) {
      double& res = result.at(r, c);
      threads.push_back(thread(computeCell, cref(a), cref(b), r, c, ref(res)));
    }

  for (thread& t : threads)
    t.join();
  return result;
}

/**
 * Second try to parallel matrix multiplication.
 *
 * To learn:
 *  - Problem knowledge is mandatory
 *  - Context switching needs to be compensated with thread load.
 */
void computeCol(const Matrix& a, const Matrix& b, size_t col, Matrix& result) {
  assert(a.numCols() == b.numRows());
  for (size_t r = 0; r < a.numRows(); r++) {
    for (size_t c = 0; c < a.numRows(); c++) {
      result.at(r, col) += a.at(r, c) * b.at(c, col);
    }
  }
}

Matrix mult3(const Matrix& a, const Matrix& b) {
  assert(a.numCols() == b.numRows());
  Matrix result(a.numRows(), b.numCols());

  vector<thread> threads;
  for (size_t c = 0; c < b.numCols(); c++)
    threads.push_back(thread(computeCol, cref(a), cref(b), c, ref(result)));

  for (thread& t : threads)
    t.join();
  return result;
}

/**
 * Third try to parallel matrix multiplication.
 *
 * To learn:
 *  - A pooler does not solve a problem! if the programmer does not know what
 *    concurrency is.
 */
double computeCell(const Matrix& a, const Matrix& b, size_t ra, size_t cb) {
  assert(a.numCols() == b.numRows());
  double result = 0.0;
  for (size_t nc = 0; nc < b.numRows(); nc++) {
    result += a.at(ra, nc) * b.at(nc, cb);
  }
  return result;
}

Matrix mult4(const Matrix& a, const Matrix& b) {
  assert(a.numCols() == b.numRows());
  Matrix result(a.numRows(), b.numCols());
  {
    ThreadPool pool(4);
    for (size_t r = 0; r < a.numRows(); r++)
      for (size_t c = 0; c < b.numCols(); c++) {
        pool.enqueue([&result, &a, &b, r, c]() {
          result.at(r, c) = computeCell(a, b, r, c);
        });
      }
  }
  return result;
}

/*
Matrix mult4(const Matrix& a, const Matrix& b) {
  assert(a.numCols() == b.numRows());
  Matrix result(a.numRows(), b.numCols());
  {
    ThreadPool pool(4);
    for (size_t c = 0; c < b.numCols(); c++)
      pool.enqueue(
          [&result, &a, &b, r, c]() { computeCol(a, b, r, c, result); });
  }

return result;
}
*/
void test(size_t n) {
  for (size_t i = 10; i < n;) {
    Matrix a(i, i);
    Matrix b(i, i);

    a.fill();
    b.fill();

    cout << i;

    Timer t;
    Matrix r = mult(a, b);
    cout << " - " << t.elapsed();

    Timer t2;
    Matrix s = mult2(a, b);
    cout << " - " << t2.elapsed();

    // Timer t3;
    // Matrix u = mult3(a, b);
    // cout << " - " << t3.elapsed();

    Timer t4;
    Matrix v = mult4(a, b);
    cout << " - " << t4.elapsed();

    Timer t5;
    Matrix w = mult4(a, b);
    cout << " - " << t4.elapsed();

    cout << endl;

    i += 10;
  }
}

int main() {
  cout << "Concurrency!!" << endl;
  test(1000);
  //
  // Matrix a(2, 2);
  // a.fill();
  // a.print();
  //
  // Matrix b(2, 2);
  // b.fill();
  // b.print();
  //
  // Matrix c = mult(a, b);
  // Matrix n = mult3(a, b);
  // cout << (c == n) << endl;
  // // Matrix c(2, 2);
  // computeCol(a, b, 0, c);
  // c.print();

  // Matrix asq = mult(a, a);
  // Matrix asq2 = mult2(a, a);
  // cout << (asq == asq2) << endl;
}