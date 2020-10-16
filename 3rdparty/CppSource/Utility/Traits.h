/*
 * Copyright 2011-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// @author: Andrei Alexandrescu

#pragma once

#include <functional>
#include <limits>
#include <memory>
#include <type_traits>


template <std::size_t I>
using index_constant = std::integral_constant<std::size_t, I>;

/***
 *  _t
 *
 *  Instead of:
 *
 *    using decayed = typename std::decay<T>::type;
 *
 *  With the C++14 standard trait aliases, we could use:
 *
 *    using decayed = std::decay_t<T>;
 *
 *  Without them, we could use:
 *
 *    using decayed = _t<std::decay<T>>;
 *
 *  Also useful for any other library with template types having dependent
 *  member types named `type`, like the standard trait types.
 */
template <typename T>
using _t = typename T::type;

/**
 * A type trait to remove all const volatile and reference qualifiers on a
 * type T
 */
template <typename T>
struct remove_cvref {
  using type =
      typename std::remove_cv<typename std::remove_reference<T>::type>::type;
};
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;


namespace detail {

template <typename Src>
struct like_ {
  template <typename Dst>
  using apply = Dst;
};

template <typename Src>
struct like_<Src const> {
  template <typename Dst>
  using apply = Dst const;
};

template <typename Src>
struct like_<Src volatile> {
  template <typename Dst>
  using apply = Dst volatile;
};

template <typename Src>
struct like_<Src const volatile> {
  template <typename Dst>
  using apply = Dst const volatile;
};

template <typename Src>
struct like_<Src&> {
  template <typename Dst>
  using apply = typename like_<Src>::template apply<Dst>&;
};

template <typename Src>
struct like_<Src&&> {
  template <typename Dst>
  using apply = typename like_<Src>::template apply<Dst>&&;
};
} // namespace detail

//  mimic: like_t, p0847r0
template <typename Src, typename Dst>
using like_t = typename detail::like_<Src>::template apply<remove_cvref_t<Dst>>;

//  mimic: like, p0847r0
template <typename Src, typename Dst>
struct like {
  using type = like_t<Src, Dst>;
};


/**
 *  type_t
 *
 *  A type alias for the first template type argument. `type_t` is useful for
 *  controlling class-template and function-template partial specialization.
 *
 *  Example:
 *
 *    template <typename Value>
 *    class Container {
 *     public:
 *      template <typename... Args>
 *      Container(
 *          type_t<in_place_t, decltype(Value(std::declval<Args>()...))>,
 *          Args&&...);
 *    };
 *
 *  void_t
 *
 *  A type alias for `void`. `void_t` is useful for controling class-template
 *  and function-template partial specialization.
 *
 *  Example:
 *
 *    // has_value_type<T>::value is true if T has a nested type `value_type`
 *    template <class T, class = void>
 *    struct has_value_type
 *        : std::false_type {};
 *
 *    template <class T>
 *    struct has_value_type<T, folly::void_t<typename T::value_type>>
 *        : std::true_type {};
 */

/**
 * There is a bug in libstdc++, libc++, and MSVC's STL that causes it to
 * ignore unused template parameter arguments in template aliases and does not
 * cause substitution failures. This defect has been recorded here:
 * http://open-std.org/JTC1/SC22/WG21/docs/cwg_defects.html#1558.
 *
 * This causes the implementation of std::void_t to be buggy, as it is likely
 * defined as something like the following:
 *
 *  template <typename...>
 *  using void_t = void;
 *
 * This causes the compiler to ignore all the template arguments and does not
 * help when one wants to cause substitution failures.  Rather declarations
 * which have void_t in orthogonal specializations are treated as the same.
 * For example, assuming the possible `T` types are only allowed to have
 * either the alias `one` or `two` and never both or none:
 *
 *  template <typename T,
 *            typename std::void_t<std::decay_t<T>::one>* = nullptr>
 *  void foo(T&&) {}
 *  template <typename T,
 *            typename std::void_t<std::decay_t<T>::two>* = nullptr>
 *  void foo(T&&) {}
 *
 * The second foo() will be a redefinition because it conflicts with the first
 * one; void_t does not cause substitution failures - the template types are
 * just ignored.
 */

namespace traits_detail {
template <class T, class...>
struct type_t_ {
  using type = T;
};
} // namespace traits_detail

template <class T, class... Ts>
using type_t = typename traits_detail::type_t_<T, Ts...>::type;
template <class... Ts>
using void_t = type_t<void, Ts...>;
