
// -------------------------------------
// projects/allocator/TestAllocator1.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

// --------------
// TestAllocator1
// --------------

template <typename A>
struct TestAllocator1 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            std::allocator<int>,
            std::allocator<double>,
            my_allocator<int,    100>,
            my_allocator<double, 100>>
        my_types_1;

TYPED_TEST_CASE(TestAllocator1, my_types_1);

TYPED_TEST(TestAllocator1, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator1, test_10) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type  x;
    const size_type       s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

// --------------
// TestAllocator2
// --------------

TEST(TestAllocator2, const_index) {
    const my_allocator<int, 100> x;
    ASSERT_EQ(x[0], 92);
    ASSERT_EQ(x[96],92);
}

TEST(TestAllocator2, index) {
    my_allocator<int, 100> x;
    ASSERT_EQ(x[0], 92);
    ASSERT_EQ(x[96],92);}

// --------------
// TestAllocator3
// --------------

template <typename A>
struct TestAllocator3 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            my_allocator<int,    100>,
            my_allocator<double, 100>>
        my_types_2;

TYPED_TEST_CASE(TestAllocator3, my_types_2);

TYPED_TEST(TestAllocator3, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator3, test_10) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 10;
    const value_type     v = 2;
    const pointer        b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;
            }
        }
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);
            }
            x.deallocate(b, s);
            throw;
        }
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);
        }
        x.deallocate(b, s);
    }
}

// // --------------
// // TestAllocator4
// // Constructor
// // --------------

TEST(TestAllocator4, my_allocator1) {
    try{
        my_allocator<int, 4> x;
        ASSERT_EQ(false, true);
    } catch (std::bad_alloc &exception){
        ASSERT_EQ(true, true);
    }
}

TEST(TestAllocator4, my_allocator2) {
    try{
        my_allocator<int, 4> x;
        ASSERT_EQ(false, true);
    } catch (std::bad_alloc &exception){
        ASSERT_EQ(true, true);
    }
}

TEST(TestAllocator4, my_allocator3) {
    try{
        my_allocator<int, 4> x;
        ASSERT_EQ(false, true);
    } catch (std::bad_alloc &exception){
        ASSERT_EQ(true, true);
    }
}



// // --------------
// // TestAllocator5
// // valid()
// // --------------

// checks that a freshly constructed heap is valid
TEST(TestAllocator5, valid1) {
  my_allocator<int, 100> x; 
  ASSERT_EQ(x.valid(), true);
}

//checks that if you allocate it's valid
TEST(TestAllocator5, valid2) {
  my_allocator<int, 100> x;
  int *p = x.allocate(2);
  ASSERT_EQ(x.valid(), true);
}

//allocate then deallocate
TEST(TestAllocator5, valid3) {
  my_allocator<int, 100> x;
  int *p = x.allocate(2);
  x.deallocate(p, 2);
  ASSERT_EQ(x.valid(), true);
}

//series of allocates 
TEST(TestAllocator5, valid4) {
  my_allocator<double, 100> y;
  y.allocate(2);
  y.allocate(3);
  y.allocate(4);
  ASSERT_EQ(y.valid(), true);
}



// // --------------
// // TestAllocator6
// // allocate()
// // --------------

TEST(TestAllocator6, allocate1) {
  my_allocator<int, 100> x;
  try {
    x.allocate(200);
    ASSERT_EQ(false, true);
  } catch (std::bad_alloc &exception) {
    ASSERT_EQ(true, true);
  }
}

TEST(TestAllocator6, allocate2) {
  my_allocator<double, 100> x;
  x.allocate(1); 
  const my_allocator<double, 100> y = x;
  ASSERT_EQ(y[0], -8);
}

TEST(TestAllocator6, allocate3) {
  my_allocator<double, 100> x;
  x.allocate(1); 
  const my_allocator<double, 100> y = x;
  ASSERT_EQ(y[0], -8);
}

//allocate fully
TEST(TestAllocator6, allocate4) {
  my_allocator<int, 100> x;
  x.allocate(1); 
  x.allocate(20);
  const my_allocator<int, 100> y = x;
  ASSERT_EQ(y[0], -4);
  ASSERT_EQ(y[12], -80);
  ASSERT_EQ(y[96], -80);
}



// // --------------
// // TestAllocator7
// // deallocate()
// // --------------

TEST(TestAllocator7, deallocate1) {
  my_allocator<int, 100> x; 
  int *p = x.allocate(2); 
  x.deallocate(p, 2);
  try {
    x.deallocate(p, 2); //try to deallocate twice
    ASSERT_EQ(false, true);
  } catch (std::invalid_argument &exception) {
    ASSERT_EQ(true, true);
  }

}

TEST(TestAllocator7, deallocate2) {
  my_allocator<int, 100> x; 
  int *p = x.allocate(2);
  const my_allocator<int, 100> y = x; 
  ASSERT_EQ(-8, y[0]);
  ASSERT_EQ(76, y[16]);
  x.deallocate(p, 2);
  const my_allocator<int, 100> z = x;
  ASSERT_EQ(92, z[0]);
}

TEST(TestAllocator7, deallocate3) {
  my_allocator<int, 100> x; 
  int *p = 0; 
  try {
    x.deallocate(p, 2); 
    ASSERT_EQ(false, true);
  } catch (std::invalid_argument &exception) {
    ASSERT_EQ(true, true);
  }
}


// // --------------
// // TestAllocator8
// // private helper
// // has_valid_remaining_space (int free_block, int to_allocate)
// // --------------

TEST(TestAllocator8, valid_space1) {
  my_allocator<int, 100> x; 
  ASSERT_EQ(x.has_valid_remaining_space(20, 16), 0);
}

TEST(TestAllocator8, valid_space2) {
  my_allocator<int, 100> x; 
  ASSERT_EQ(x.has_valid_remaining_space(100, 4), 96);
}
