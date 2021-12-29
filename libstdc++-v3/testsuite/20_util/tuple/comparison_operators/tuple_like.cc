// { dg-do compile { target c++20 } }

// Copyright (C) 2014-2021 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>

#include <tuple>
#include <array>
#include <testsuite_hooks.h>

void test01()
{
  std::tuple a{0, 1, 2};
  std::array<int, 3> b{0, 1, 2};
  std::array<int, 3> c{0, 0, 0};
  VERIFY(a == b);
  VERIFY(b == a);
  VERIFY(a != c);
  VERIFY(c != a);
}


void test02()
{
  std::tuple a{0, 1, 2};
  std::array<int, 3> b{0, 1, 3};
  VERIFY( !(a > a) && !(b > b) );
  VERIFY( a >= a && b >= b );
  VERIFY( a < b && !(b < a) && a <= b && !(b <= a) );
  VERIFY( b > a && !(a > b) && b >= a && !(a >= b) );

  VERIFY( std::is_lt(a <=> b) );
  VERIFY( std::is_gt(b <=> a) );

  static_assert( std::is_same_v<decltype(a <=> b), std::strong_ordering> );
}

int main() {
    test01();
    test02();
}