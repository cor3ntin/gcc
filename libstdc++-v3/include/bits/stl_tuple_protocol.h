#pragma once
#if __cplusplus >= 201103L

#include <type_traits>
#include <concepts>



namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

#if __cplusplus >= 202000

template <std::size_t, typename T>
void get(T&&) = delete;

template <typename T, std::size_t N>
constexpr bool __is_tuple_element = requires (T t) {
    typename std::tuple_element_t<N-1, std::remove_const_t<T>>;
    { std::get<N-1>(t) } -> std::convertible_to<std::tuple_element_t<N-1, T>&>;
} && __is_tuple_element<T, N-1>;

template <typename T>
constexpr bool __is_tuple_element<T, 0> = true;

template <typename, typename>
class pair;

template <typename...>
class tuple;

template <typename>
constexpr bool __is_standard_tuple_like = false;

template <typename A, typename B>
constexpr bool __is_standard_tuple_like<std::pair<A, B>> = true;

template <typename... Args>
constexpr bool __is_standard_tuple_like<std::tuple<Args...>> = true;


template <typename T, typename U = std::remove_cvref_t<T>>
concept __tuple_like = __is_standard_tuple_like<U> || requires {
    typename std::tuple_size<U>::type;
    std::same_as<typename std::tuple_size<U>::type, std::size_t>;
} && __is_tuple_element<U, std::tuple_size_v<U>>;

template <typename T, auto N>
concept __tuple_like_of_size = __tuple_like<T>
  && std::tuple_size_v<std::remove_cvref_t<T>> == N;

template <typename T>
concept __pair_like = __tuple_like_of_size<T, 2>;

template <typename Source, typename Target>
using __copy_lvalue_reference_t = std::conditional_t<std::is_lvalue_reference_v<Source>, std::add_lvalue_reference_t<Target>, Target>;

template <template <typename, typename> typename F, typename T, typename... Args>
constexpr bool __all_tuple_elements = []<std::size_t... I>(std::index_sequence<I...>) {
        return (true && ... && F<Args, decltype((get<I>(std::declval<T>())))>::value);
    }(std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>());

#endif

} // namespace std

#endif
