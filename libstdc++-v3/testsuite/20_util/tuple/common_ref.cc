// { dg-do compile { target c++20 } }

#include <tuple>
#include <array>
#include <testsuite_hooks.h>

template<typename A, typename B>
struct test{
    A a;
    B b;
};

namespace std {
    template <typename A, typename B>
    struct tuple_size<test<A, B>> : std::integral_constant<std::size_t, 2> {};

    template <typename A, typename B>
    struct tuple_element<0, test<A, B>> {
        using type = A;
    };

    template <typename A, typename B>
    struct tuple_element<1, test<A, B>> {
        using type = B;
    };
}

template< std::size_t I, typename A, typename B>
constexpr auto & get(test<A, B>& v ) {
    static_assert(I <2);
    if constexpr(I == 0) {
        return v.a;
    }
    if constexpr(I == 1) {
        return v.b;
    }
}

template< std::size_t I, typename A, typename B>
constexpr std::add_rvalue_reference_t<std::tuple_element_t<I, test<A, B>>> get(test<A, B>&& v ) {
    static_assert(I <2);
    if constexpr(I == 0) {
        return std::move(v.index);
    }
    if constexpr(I == 1) {
        return std::move(v.value);
    }
}

template< std::size_t I, typename A, typename B>
constexpr const auto & get(const test<A, B>& v ) {
    static_assert(I < 2);
    if constexpr(I == 0) {
        return v.a;
    }
    if constexpr(I == 1) {
        return v.b;
    }
}

struct mo{
    mo() = default;
    mo(mo&&) = default;
    mo(const mo&) = delete;
};


static_assert(std::common_reference_with<std::tuple<int&, int&>, std::tuple<int, int>>);
static_assert(std::common_reference_with<std::tuple<int&, int&>, std::pair<int, int>>);
static_assert(std::common_reference_with<std::pair<int&, int&>, std::pair<int, int>>);
static_assert(std::common_reference_with<std::pair<int&, int&>, std::tuple<int, int>>);

static_assert(std::common_reference_with<std::tuple<int, mo&>, std::tuple<int, mo>&&>);
static_assert(std::common_reference_with<std::tuple<int, mo&>, std::pair<int, mo>&&>);
static_assert(std::common_reference_with<std::pair<int, mo&>, std::tuple<int, mo>&&>);

static_assert(std::same_as<std::common_reference_t<std::tuple<int, mo&>, std::tuple<int, mo>>, std::tuple<int, mo>>);
static_assert(std::same_as<std::common_reference_t<test<int, mo&>, std::tuple<int, mo>>, std::tuple<int, mo>>);

static_assert(std::same_as<std::common_reference_t<test<int, mo&>&, std::tuple<int, mo>&>, std::tuple<int&, mo&>>);

static_assert(std::same_as<std::common_reference_t<std::tuple<>, std::tuple<>>, std::tuple<>>);
static_assert(std::same_as<std::common_reference_t<std::tuple<int>, std::tuple<int>>, std::tuple<int>>);
static_assert(std::same_as<std::common_reference_t<std::tuple<int>, std::tuple<int&>>, std::tuple<int>>);
static_assert(std::same_as<std::common_reference_t<std::tuple<int&>, std::tuple<int&>>, std::tuple<int&>>);


static_assert(std::same_as<std::common_reference_t<std::tuple<int, int>, std::pair<int, int>>, std::tuple<int, int>>);
static_assert(std::same_as<std::common_reference_t<std::tuple<int, int>, std::pair<int&, int&>>, std::tuple<int, int>>);
static_assert(std::same_as<std::common_reference_t<std::tuple<int&, int&>, std::pair<int&, int&>>, std::tuple<int&, int&>>);


static_assert(std::same_as<std::common_reference_t<std::tuple<mo>, std::tuple<mo>>, std::tuple<mo>>);
static_assert(std::same_as<std::common_reference_t<std::tuple<mo&>, std::tuple<mo&&>>, std::tuple<const mo&>>);
static_assert(std::same_as<std::common_reference_t<std::tuple<mo>, std::tuple<mo&&>>, std::tuple<mo>>);