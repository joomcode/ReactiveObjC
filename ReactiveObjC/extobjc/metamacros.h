/**
 * Macros for metaprogramming
 * ExtendedC
 *
 * Copyright (C) 2012 Justin Spahr-Summers
 * Released under the MIT license
 */

/**
 * Executes one or more expressions (which may have a void type, such as a call
 * to a function that returns no value) and always returns true.
 */
#undef metamacro_exprify
#define metamacro_exprify(...) \
    ((__VA_ARGS__), true)

/**
 * Returns a string representation of VALUE after full macro expansion.
 */
#undef metamacro_stringify
#define metamacro_stringify(VALUE) \
        metamacro_stringify_(VALUE)

/**
 * Returns A and B concatenated after full macro expansion.
 */
#undef metamacro_concat
#define metamacro_concat(A, B) \
        metamacro_concat_(A, B)

/**
 * Returns the Nth variadic argument (starting from zero). At least
 * N + 1 variadic arguments must be given. N must be between zero and twenty,
 * inclusive.
 */
#undef metamacro_at
#define metamacro_at(N, ...) \
        metamacro_concat(metamacro_at, N)(__VA_ARGS__)

/**
 * Returns the number of arguments (up to twenty) provided to the macro. At
 * least one argument must be provided.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#undef metamacro_argcount
#define metamacro_argcount(...) \
        metamacro_at(40, __VA_ARGS__, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/**
 * Identical to #metamacro_foreach_cxt, except that no CONTEXT argument is
 * given. Only the index and current argument will thus be passed to MACRO.
 */
#undef metamacro_foreach
#define metamacro_foreach(MACRO, SEP, ...) \
        metamacro_foreach_cxt(metamacro_foreach_iter, SEP, MACRO, __VA_ARGS__)

/**
 * For each consecutive variadic argument (up to twenty), MACRO is passed the
 * zero-based index of the current argument, CONTEXT, and then the argument
 * itself. The results of adjoining invocations of MACRO are then separated by
 * SEP.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#undef metamacro_foreach_cxt
#define metamacro_foreach_cxt(MACRO, SEP, CONTEXT, ...) \
        metamacro_concat(metamacro_foreach_cxt, metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * Identical to #metamacro_foreach_cxt. This can be used when the former would
 * fail due to recursive macro expansion.
 */
#undef metamacro_foreach_cxt_recursive
#define metamacro_foreach_cxt_recursive(MACRO, SEP, CONTEXT, ...) \
        metamacro_concat(metamacro_foreach_cxt_recursive, metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * In consecutive order, appends each variadic argument (up to twenty) onto
 * BASE. The resulting concatenations are then separated by SEP.
 *
 * This is primarily useful to manipulate a list of macro invocations into instead
 * invoking a different, possibly related macro.
 */
#undef metamacro_foreach_concat
#define metamacro_foreach_concat(BASE, SEP, ...) \
        metamacro_foreach_cxt(metamacro_foreach_concat_iter, SEP, BASE, __VA_ARGS__)

/**
 * Iterates COUNT times, each time invoking MACRO with the current index
 * (starting at zero) and CONTEXT. The results of adjoining invocations of MACRO
 * are then separated by SEP.
 *
 * COUNT must be an integer between zero and twenty, inclusive.
 */
#undef metamacro_for_cxt
#define metamacro_for_cxt(COUNT, MACRO, SEP, CONTEXT) \
        metamacro_concat(metamacro_for_cxt, COUNT)(MACRO, SEP, CONTEXT)

/**
 * Returns the first argument given. At least one argument must be provided.
 *
 * This is useful when implementing a variadic macro, where you may have only
 * one variadic argument, but no way to retrieve it (for example, because \c ...
 * always needs to match at least one argument).
 *
 * @code

#undef varmacro
#define varmacro(...) \
    metamacro_head(__VA_ARGS__)

 * @endcode
 */
#undef metamacro_head
#define metamacro_head(...) \
        metamacro_head_(__VA_ARGS__, 0)

/**
 * Returns every argument except the first. At least two arguments must be
 * provided.
 */
#undef metamacro_tail
#define metamacro_tail(...) \
        metamacro_tail_(__VA_ARGS__)

/**
 * Returns the first N (up to twenty) variadic arguments as a new argument list.
 * At least N variadic arguments must be provided.
 */
#undef metamacro_take
#define metamacro_take(N, ...) \
        metamacro_concat(metamacro_take, N)(__VA_ARGS__)

/**
 * Removes the first N (up to twenty) variadic arguments from the given argument
 * list. At least N variadic arguments must be provided.
 */
#undef metamacro_drop
#define metamacro_drop(N, ...) \
        metamacro_concat(metamacro_drop, N)(__VA_ARGS__)

/**
 * Decrements VAL, which must be a number between zero and forty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#undef metamacro_dec
#define metamacro_dec(VAL) \
        metamacro_at(VAL, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,38, 39)

/**
 * Increments VAL, which must be a number between zero and forty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#undef metamacro_inc
#define metamacro_inc(VAL) \
        metamacro_at(VAL, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41)

/**
 * If A is equal to B, the next argument list is expanded; otherwise, the
 * argument list after that is expanded. A and B must be numbers between zero
 * and twenty, inclusive. Additionally, B must be greater than or equal to A.
 *
 * @code

// expands to true
metamacro_if_eq(0, 0)(true)(false)

// expands to false
metamacro_if_eq(0, 1)(true)(false)

 * @endcode
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#undef metamacro_if_eq
#define metamacro_if_eq(A, B) \
        metamacro_concat(metamacro_if_eq, A)(B)

/**
 * Identical to #metamacro_if_eq. This can be used when the former would fail
 * due to recursive macro expansion.
 */
#undef metamacro_if_eq_recursive
#define metamacro_if_eq_recursive(A, B) \
        metamacro_concat(metamacro_if_eq_recursive, A)(B)

/**
 * Returns 1 if N is an even number, or 0 otherwise. N must be between zero and
 * twenty, inclusive.
 *
 * For the purposes of this test, zero is considered even.
 */
#undef metamacro_is_even
#define metamacro_is_even(N) \
        metamacro_at(N, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1)

/**
 * Returns the logical NOT of B, which must be the number zero or one.
 */
#undef metamacro_not
#define metamacro_not(B) \
        metamacro_at(B, 1, 0)

// IMPLEMENTATION DETAILS FOLLOW!
// Do not write code that depends on anything below this line.
#undef metamacro_stringify_
#define metamacro_stringify_(VALUE) # VALUE
#undef metamacro_concat_
#define metamacro_concat_(A, B) A ## B
#undef metamacro_foreach_iter
#define metamacro_foreach_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)
#undef metamacro_head_
#define metamacro_head_(FIRST, ...) FIRST
#undef metamacro_tail_
#define metamacro_tail_(FIRST, ...) __VA_ARGS__
#undef metamacro_consume_
#define metamacro_consume_(...)
#undef metamacro_expand_
#define metamacro_expand_(...) __VA_ARGS__

// implemented from scratch so that metamacro_concat() doesn't end up nesting
#undef metamacro_foreach_concat_iter
#define metamacro_foreach_concat_iter(INDEX, BASE, ARG) metamacro_foreach_concat_iter_(BASE, ARG)
#undef metamacro_foreach_concat_iter_
#define metamacro_foreach_concat_iter_(BASE, ARG) BASE ## ARG

// metamacro_at expansions
#undef metamacro_at0
#define metamacro_at0(...) metamacro_head(__VA_ARGS__)
#undef metamacro_at1
#define metamacro_at1(_0, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at2
#define metamacro_at2(_0, _1, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at3
#define metamacro_at3(_0, _1, _2, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at4
#define metamacro_at4(_0, _1, _2, _3, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at5
#define metamacro_at5(_0, _1, _2, _3, _4, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at6
#define metamacro_at6(_0, _1, _2, _3, _4, _5, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at7
#define metamacro_at7(_0, _1, _2, _3, _4, _5, _6, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at8
#define metamacro_at8(_0, _1, _2, _3, _4, _5, _6, _7, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at9
#define metamacro_at9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at10
#define metamacro_at10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at11
#define metamacro_at11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at12
#define metamacro_at12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at13
#define metamacro_at13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at14
#define metamacro_at14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at15
#define metamacro_at15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at16
#define metamacro_at16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at17
#define metamacro_at17(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at18
#define metamacro_at18(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at19
#define metamacro_at19(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at20
#define metamacro_at20(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at21
#define metamacro_at21(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at22
#define metamacro_at22(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at23
#define metamacro_at23(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at24
#define metamacro_at24(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at25
#define metamacro_at25(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at26
#define metamacro_at26(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at27
#define metamacro_at27(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at28
#define metamacro_at28(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at29
#define metamacro_at29(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at30
#define metamacro_at30(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at31
#define metamacro_at31(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at32
#define metamacro_at32(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at33
#define metamacro_at33(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at34
#define metamacro_at34(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at35
#define metamacro_at35(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at36
#define metamacro_at36(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at37
#define metamacro_at37(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at38
#define metamacro_at38(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at39
#define metamacro_at39(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, ...) metamacro_head(__VA_ARGS__)
#undef metamacro_at40
#define metamacro_at40(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, ...) metamacro_head(__VA_ARGS__)

// metamacro_foreach_cxt expansions
#undef metamacro_foreach_cxt0
#define metamacro_foreach_cxt0(MACRO, SEP, CONTEXT)
#undef metamacro_foreach_cxt1
#define metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#undef metamacro_foreach_cxt2
#define metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) \
    SEP \
    MACRO(1, CONTEXT, _1)

#undef metamacro_foreach_cxt3
#define metamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP \
    MACRO(2, CONTEXT, _2)

#undef metamacro_foreach_cxt4
#define metamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    metamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP \
    MACRO(3, CONTEXT, _3)

#undef metamacro_foreach_cxt5
#define metamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    metamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP \
    MACRO(4, CONTEXT, _4)

#undef metamacro_foreach_cxt6
#define metamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    metamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP \
    MACRO(5, CONTEXT, _5)

#undef metamacro_foreach_cxt7
#define metamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    metamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP \
    MACRO(6, CONTEXT, _6)

#undef metamacro_foreach_cxt8
#define metamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    metamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    MACRO(7, CONTEXT, _7)

#undef metamacro_foreach_cxt9
#define metamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    metamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    MACRO(8, CONTEXT, _8)

#undef metamacro_foreach_cxt10
#define metamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    metamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    MACRO(9, CONTEXT, _9)

#undef metamacro_foreach_cxt11
#define metamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    metamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP \
    MACRO(10, CONTEXT, _10)

#undef metamacro_foreach_cxt12
#define metamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    metamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP \
    MACRO(11, CONTEXT, _11)

#undef metamacro_foreach_cxt13
#define metamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    metamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP \
    MACRO(12, CONTEXT, _12)

#undef metamacro_foreach_cxt14
#define metamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    metamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP \
    MACRO(13, CONTEXT, _13)

#undef metamacro_foreach_cxt15
#define metamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    metamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP \
    MACRO(14, CONTEXT, _14)

#undef metamacro_foreach_cxt16
#define metamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    metamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP \
    MACRO(15, CONTEXT, _15)

#undef metamacro_foreach_cxt17
#define metamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    metamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP \
    MACRO(16, CONTEXT, _16)

#undef metamacro_foreach_cxt18
#define metamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    metamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP \
    MACRO(17, CONTEXT, _17)

#undef metamacro_foreach_cxt19
#define metamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    metamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP \
    MACRO(18, CONTEXT, _18)

#undef metamacro_foreach_cxt20
#define metamacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    metamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP \
    MACRO(19, CONTEXT, _19)

#undef metamacro_foreach_cxt21
#define metamacro_foreach_cxt21(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    metamacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    SEP \
    MACRO(20, CONTEXT, _20)

#undef metamacro_foreach_cxt22
#define metamacro_foreach_cxt22(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    metamacro_foreach_cxt21(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    SEP \
    MACRO(21, CONTEXT, _21)

#undef metamacro_foreach_cxt23
#define metamacro_foreach_cxt23(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    metamacro_foreach_cxt22(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    SEP \
    MACRO(22, CONTEXT, _22)

#undef metamacro_foreach_cxt24
#define metamacro_foreach_cxt24(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    metamacro_foreach_cxt23(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    SEP \
    MACRO(23, CONTEXT, _23)

#undef metamacro_foreach_cxt25
#define metamacro_foreach_cxt25(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    metamacro_foreach_cxt24(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    SEP \
    MACRO(24, CONTEXT, _24)

#undef metamacro_foreach_cxt26
#define metamacro_foreach_cxt26(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    metamacro_foreach_cxt25(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    SEP \
    MACRO(25, CONTEXT, _25)

#undef metamacro_foreach_cxt27
#define metamacro_foreach_cxt27(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    metamacro_foreach_cxt26(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    SEP \
    MACRO(26, CONTEXT, _26)

#undef metamacro_foreach_cxt28
#define metamacro_foreach_cxt28(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    metamacro_foreach_cxt27(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    SEP \
    MACRO(27, CONTEXT, _27)

#undef metamacro_foreach_cxt29
#define metamacro_foreach_cxt29(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    metamacro_foreach_cxt28(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    SEP \
    MACRO(28, CONTEXT, _28)

#undef metamacro_foreach_cxt30
#define metamacro_foreach_cxt30(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    metamacro_foreach_cxt29(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    SEP \
    MACRO(29, CONTEXT, _29)

#undef metamacro_foreach_cxt31
#define metamacro_foreach_cxt31(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    metamacro_foreach_cxt30(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    SEP \
    MACRO(30, CONTEXT, _30)

#undef metamacro_foreach_cxt32
#define metamacro_foreach_cxt32(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    metamacro_foreach_cxt31(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    SEP \
    MACRO(31, CONTEXT, _31)

#undef metamacro_foreach_cxt33
#define metamacro_foreach_cxt33(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    metamacro_foreach_cxt32(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    SEP \
    MACRO(32, CONTEXT, _32)

#undef metamacro_foreach_cxt34
#define metamacro_foreach_cxt34(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    metamacro_foreach_cxt33(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    SEP \
    MACRO(33, CONTEXT, _33)

#undef metamacro_foreach_cxt35
#define metamacro_foreach_cxt35(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    metamacro_foreach_cxt34(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    SEP \
    MACRO(34, CONTEXT, _34)

#undef metamacro_foreach_cxt36
#define metamacro_foreach_cxt36(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    metamacro_foreach_cxt35(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    SEP \
    MACRO(35, CONTEXT, _35)

#undef metamacro_foreach_cxt37
#define metamacro_foreach_cxt37(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    metamacro_foreach_cxt36(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    SEP \
    MACRO(36, CONTEXT, _36)

#undef metamacro_foreach_cxt38
#define metamacro_foreach_cxt38(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    metamacro_foreach_cxt37(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    SEP \
    MACRO(37, CONTEXT, _37)

#undef metamacro_foreach_cxt39
#define metamacro_foreach_cxt39(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    metamacro_foreach_cxt38(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    SEP \
    MACRO(38, CONTEXT, _38)

#undef metamacro_foreach_cxt40
#define metamacro_foreach_cxt40(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
    metamacro_foreach_cxt39(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    SEP \
    MACRO(39, CONTEXT, _39)

// metamacro_foreach_cxt_recursive expansions
#undef metamacro_foreach_cxt_recursive0
#define metamacro_foreach_cxt_recursive0(MACRO, SEP, CONTEXT)
#undef metamacro_foreach_cxt_recursive1
#define metamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#undef metamacro_foreach_cxt_recursive2
#define metamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
    metamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) \
    SEP \
    MACRO(1, CONTEXT, _1)

#undef metamacro_foreach_cxt_recursive3
#define metamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    metamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP \
    MACRO(2, CONTEXT, _2)

#undef metamacro_foreach_cxt_recursive4
#define metamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    metamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP \
    MACRO(3, CONTEXT, _3)

#undef metamacro_foreach_cxt_recursive5
#define metamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    metamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP \
    MACRO(4, CONTEXT, _4)

#undef metamacro_foreach_cxt_recursive6
#define metamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    metamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP \
    MACRO(5, CONTEXT, _5)

#undef metamacro_foreach_cxt_recursive7
#define metamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    metamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP \
    MACRO(6, CONTEXT, _6)

#undef metamacro_foreach_cxt_recursive8
#define metamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    metamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    MACRO(7, CONTEXT, _7)

#undef metamacro_foreach_cxt_recursive9
#define metamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    metamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    MACRO(8, CONTEXT, _8)

#undef metamacro_foreach_cxt_recursive10
#define metamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    metamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    MACRO(9, CONTEXT, _9)

#undef metamacro_foreach_cxt_recursive11
#define metamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    metamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP \
    MACRO(10, CONTEXT, _10)

#undef metamacro_foreach_cxt_recursive12
#define metamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    metamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP \
    MACRO(11, CONTEXT, _11)

#undef metamacro_foreach_cxt_recursive13
#define metamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    metamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP \
    MACRO(12, CONTEXT, _12)

#undef metamacro_foreach_cxt_recursive14
#define metamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    metamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP \
    MACRO(13, CONTEXT, _13)

#undef metamacro_foreach_cxt_recursive15
#define metamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    metamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP \
    MACRO(14, CONTEXT, _14)

#undef metamacro_foreach_cxt_recursive16
#define metamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    metamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP \
    MACRO(15, CONTEXT, _15)

#undef metamacro_foreach_cxt_recursive17
#define metamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    metamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP \
    MACRO(16, CONTEXT, _16)

#undef metamacro_foreach_cxt_recursive18
#define metamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    metamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP \
    MACRO(17, CONTEXT, _17)

#undef metamacro_foreach_cxt_recursive19
#define metamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    metamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP \
    MACRO(18, CONTEXT, _18)

#undef metamacro_foreach_cxt_recursive20
#define metamacro_foreach_cxt_recursive20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    metamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP \
    MACRO(19, CONTEXT, _19)

// metamacro_for_cxt expansions
#undef metamacro_for_cxt0
#define metamacro_for_cxt0(MACRO, SEP, CONTEXT)
#undef metamacro_for_cxt1
#define metamacro_for_cxt1(MACRO, SEP, CONTEXT) MACRO(0, CONTEXT)

#undef metamacro_for_cxt2
#define metamacro_for_cxt2(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt1(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(1, CONTEXT)

#undef metamacro_for_cxt3
#define metamacro_for_cxt3(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt2(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(2, CONTEXT)

#undef metamacro_for_cxt4
#define metamacro_for_cxt4(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt3(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(3, CONTEXT)

#undef metamacro_for_cxt5
#define metamacro_for_cxt5(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt4(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(4, CONTEXT)

#undef metamacro_for_cxt6
#define metamacro_for_cxt6(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt5(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(5, CONTEXT)

#undef metamacro_for_cxt7
#define metamacro_for_cxt7(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt6(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(6, CONTEXT)

#undef metamacro_for_cxt8
#define metamacro_for_cxt8(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt7(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(7, CONTEXT)

#undef metamacro_for_cxt9
#define metamacro_for_cxt9(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt8(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(8, CONTEXT)

#undef metamacro_for_cxt10
#define metamacro_for_cxt10(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt9(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(9, CONTEXT)

#undef metamacro_for_cxt11
#define metamacro_for_cxt11(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt10(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(10, CONTEXT)

#undef metamacro_for_cxt12
#define metamacro_for_cxt12(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt11(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(11, CONTEXT)

#undef metamacro_for_cxt13
#define metamacro_for_cxt13(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt12(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(12, CONTEXT)

#undef metamacro_for_cxt14
#define metamacro_for_cxt14(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt13(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(13, CONTEXT)

#undef metamacro_for_cxt15
#define metamacro_for_cxt15(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt14(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(14, CONTEXT)

#undef metamacro_for_cxt16
#define metamacro_for_cxt16(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt15(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(15, CONTEXT)

#undef metamacro_for_cxt17
#define metamacro_for_cxt17(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt16(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(16, CONTEXT)

#undef metamacro_for_cxt18
#define metamacro_for_cxt18(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt17(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(17, CONTEXT)

#undef metamacro_for_cxt19
#define metamacro_for_cxt19(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt18(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(18, CONTEXT)

#undef metamacro_for_cxt20
#define metamacro_for_cxt20(MACRO, SEP, CONTEXT) \
    metamacro_for_cxt19(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(19, CONTEXT)

// metamacro_if_eq expansions
#undef metamacro_if_eq0
#define metamacro_if_eq0(VALUE) \
    metamacro_concat(metamacro_if_eq0_, VALUE)

#undef metamacro_if_eq0_0
#define metamacro_if_eq0_0(...) __VA_ARGS__ metamacro_consume_
#undef metamacro_if_eq0_1
#define metamacro_if_eq0_1(...) metamacro_expand_
#undef metamacro_if_eq0_2
#define metamacro_if_eq0_2(...) metamacro_expand_
#undef metamacro_if_eq0_3
#define metamacro_if_eq0_3(...) metamacro_expand_
#undef metamacro_if_eq0_4
#define metamacro_if_eq0_4(...) metamacro_expand_
#undef metamacro_if_eq0_5
#define metamacro_if_eq0_5(...) metamacro_expand_
#undef metamacro_if_eq0_6
#define metamacro_if_eq0_6(...) metamacro_expand_
#undef metamacro_if_eq0_7
#define metamacro_if_eq0_7(...) metamacro_expand_
#undef metamacro_if_eq0_8
#define metamacro_if_eq0_8(...) metamacro_expand_
#undef metamacro_if_eq0_9
#define metamacro_if_eq0_9(...) metamacro_expand_
#undef metamacro_if_eq0_10
#define metamacro_if_eq0_10(...) metamacro_expand_
#undef metamacro_if_eq0_11
#define metamacro_if_eq0_11(...) metamacro_expand_
#undef metamacro_if_eq0_12
#define metamacro_if_eq0_12(...) metamacro_expand_
#undef metamacro_if_eq0_13
#define metamacro_if_eq0_13(...) metamacro_expand_
#undef metamacro_if_eq0_14
#define metamacro_if_eq0_14(...) metamacro_expand_
#undef metamacro_if_eq0_15
#define metamacro_if_eq0_15(...) metamacro_expand_
#undef metamacro_if_eq0_16
#define metamacro_if_eq0_16(...) metamacro_expand_
#undef metamacro_if_eq0_17
#define metamacro_if_eq0_17(...) metamacro_expand_
#undef metamacro_if_eq0_18
#define metamacro_if_eq0_18(...) metamacro_expand_
#undef metamacro_if_eq0_19
#define metamacro_if_eq0_19(...) metamacro_expand_
#undef metamacro_if_eq0_20
#define metamacro_if_eq0_20(...) metamacro_expand_
#define metamacro_if_eq0_21(...) metamacro_expand_
#define metamacro_if_eq0_22(...) metamacro_expand_
#define metamacro_if_eq0_23(...) metamacro_expand_
#define metamacro_if_eq0_24(...) metamacro_expand_
#define metamacro_if_eq0_25(...) metamacro_expand_
#define metamacro_if_eq0_26(...) metamacro_expand_
#define metamacro_if_eq0_27(...) metamacro_expand_
#define metamacro_if_eq0_28(...) metamacro_expand_
#define metamacro_if_eq0_29(...) metamacro_expand_
#define metamacro_if_eq0_30(...) metamacro_expand_
#define metamacro_if_eq0_31(...) metamacro_expand_
#define metamacro_if_eq0_32(...) metamacro_expand_
#define metamacro_if_eq0_33(...) metamacro_expand_
#define metamacro_if_eq0_34(...) metamacro_expand_
#define metamacro_if_eq0_35(...) metamacro_expand_
#define metamacro_if_eq0_36(...) metamacro_expand_
#define metamacro_if_eq0_37(...) metamacro_expand_
#define metamacro_if_eq0_38(...) metamacro_expand_
#define metamacro_if_eq0_39(...) metamacro_expand_

#undef metamacro_if_eq1
#define metamacro_if_eq1(VALUE) metamacro_if_eq0(metamacro_dec(VALUE))
#undef metamacro_if_eq2
#define metamacro_if_eq2(VALUE) metamacro_if_eq1(metamacro_dec(VALUE))
#undef metamacro_if_eq3
#define metamacro_if_eq3(VALUE) metamacro_if_eq2(metamacro_dec(VALUE))
#undef metamacro_if_eq4
#define metamacro_if_eq4(VALUE) metamacro_if_eq3(metamacro_dec(VALUE))
#undef metamacro_if_eq5
#define metamacro_if_eq5(VALUE) metamacro_if_eq4(metamacro_dec(VALUE))
#undef metamacro_if_eq6
#define metamacro_if_eq6(VALUE) metamacro_if_eq5(metamacro_dec(VALUE))
#undef metamacro_if_eq7
#define metamacro_if_eq7(VALUE) metamacro_if_eq6(metamacro_dec(VALUE))
#undef metamacro_if_eq8
#define metamacro_if_eq8(VALUE) metamacro_if_eq7(metamacro_dec(VALUE))
#undef metamacro_if_eq9
#define metamacro_if_eq9(VALUE) metamacro_if_eq8(metamacro_dec(VALUE))
#undef metamacro_if_eq10
#define metamacro_if_eq10(VALUE) metamacro_if_eq9(metamacro_dec(VALUE))
#undef metamacro_if_eq11
#define metamacro_if_eq11(VALUE) metamacro_if_eq10(metamacro_dec(VALUE))
#undef metamacro_if_eq12
#define metamacro_if_eq12(VALUE) metamacro_if_eq11(metamacro_dec(VALUE))
#undef metamacro_if_eq13
#define metamacro_if_eq13(VALUE) metamacro_if_eq12(metamacro_dec(VALUE))
#undef metamacro_if_eq14
#define metamacro_if_eq14(VALUE) metamacro_if_eq13(metamacro_dec(VALUE))
#undef metamacro_if_eq15
#define metamacro_if_eq15(VALUE) metamacro_if_eq14(metamacro_dec(VALUE))
#undef metamacro_if_eq16
#define metamacro_if_eq16(VALUE) metamacro_if_eq15(metamacro_dec(VALUE))
#undef metamacro_if_eq17
#define metamacro_if_eq17(VALUE) metamacro_if_eq16(metamacro_dec(VALUE))
#undef metamacro_if_eq18
#define metamacro_if_eq18(VALUE) metamacro_if_eq17(metamacro_dec(VALUE))
#undef metamacro_if_eq19
#define metamacro_if_eq19(VALUE) metamacro_if_eq18(metamacro_dec(VALUE))
#undef metamacro_if_eq20
#define metamacro_if_eq20(VALUE) metamacro_if_eq19(metamacro_dec(VALUE))

// metamacro_if_eq_recursive expansions
#undef metamacro_if_eq_recursive0
#define metamacro_if_eq_recursive0(VALUE) \
    metamacro_concat(metamacro_if_eq_recursive0_, VALUE)

#undef metamacro_if_eq_recursive0_0
#define metamacro_if_eq_recursive0_0(...) __VA_ARGS__ metamacro_consume_
#undef metamacro_if_eq_recursive0_1
#define metamacro_if_eq_recursive0_1(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_2
#define metamacro_if_eq_recursive0_2(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_3
#define metamacro_if_eq_recursive0_3(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_4
#define metamacro_if_eq_recursive0_4(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_5
#define metamacro_if_eq_recursive0_5(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_6
#define metamacro_if_eq_recursive0_6(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_7
#define metamacro_if_eq_recursive0_7(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_8
#define metamacro_if_eq_recursive0_8(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_9
#define metamacro_if_eq_recursive0_9(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_10
#define metamacro_if_eq_recursive0_10(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_11
#define metamacro_if_eq_recursive0_11(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_12
#define metamacro_if_eq_recursive0_12(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_13
#define metamacro_if_eq_recursive0_13(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_14
#define metamacro_if_eq_recursive0_14(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_15
#define metamacro_if_eq_recursive0_15(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_16
#define metamacro_if_eq_recursive0_16(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_17
#define metamacro_if_eq_recursive0_17(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_18
#define metamacro_if_eq_recursive0_18(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_19
#define metamacro_if_eq_recursive0_19(...) metamacro_expand_
#undef metamacro_if_eq_recursive0_20
#define metamacro_if_eq_recursive0_20(...) metamacro_expand_

#undef metamacro_if_eq_recursive1
#define metamacro_if_eq_recursive1(VALUE) metamacro_if_eq_recursive0(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive2
#define metamacro_if_eq_recursive2(VALUE) metamacro_if_eq_recursive1(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive3
#define metamacro_if_eq_recursive3(VALUE) metamacro_if_eq_recursive2(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive4
#define metamacro_if_eq_recursive4(VALUE) metamacro_if_eq_recursive3(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive5
#define metamacro_if_eq_recursive5(VALUE) metamacro_if_eq_recursive4(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive6
#define metamacro_if_eq_recursive6(VALUE) metamacro_if_eq_recursive5(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive7
#define metamacro_if_eq_recursive7(VALUE) metamacro_if_eq_recursive6(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive8
#define metamacro_if_eq_recursive8(VALUE) metamacro_if_eq_recursive7(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive9
#define metamacro_if_eq_recursive9(VALUE) metamacro_if_eq_recursive8(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive10
#define metamacro_if_eq_recursive10(VALUE) metamacro_if_eq_recursive9(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive11
#define metamacro_if_eq_recursive11(VALUE) metamacro_if_eq_recursive10(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive12
#define metamacro_if_eq_recursive12(VALUE) metamacro_if_eq_recursive11(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive13
#define metamacro_if_eq_recursive13(VALUE) metamacro_if_eq_recursive12(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive14
#define metamacro_if_eq_recursive14(VALUE) metamacro_if_eq_recursive13(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive15
#define metamacro_if_eq_recursive15(VALUE) metamacro_if_eq_recursive14(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive16
#define metamacro_if_eq_recursive16(VALUE) metamacro_if_eq_recursive15(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive17
#define metamacro_if_eq_recursive17(VALUE) metamacro_if_eq_recursive16(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive18
#define metamacro_if_eq_recursive18(VALUE) metamacro_if_eq_recursive17(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive19
#define metamacro_if_eq_recursive19(VALUE) metamacro_if_eq_recursive18(metamacro_dec(VALUE))
#undef metamacro_if_eq_recursive20
#define metamacro_if_eq_recursive20(VALUE) metamacro_if_eq_recursive19(metamacro_dec(VALUE))

// metamacro_take expansions
#undef metamacro_take0
#define metamacro_take0(...)
#undef metamacro_take1
#define metamacro_take1(...) metamacro_head(__VA_ARGS__)
#undef metamacro_take2
#define metamacro_take2(...) metamacro_head(__VA_ARGS__), metamacro_take1(metamacro_tail(__VA_ARGS__))
#undef metamacro_take3
#define metamacro_take3(...) metamacro_head(__VA_ARGS__), metamacro_take2(metamacro_tail(__VA_ARGS__))
#undef metamacro_take4
#define metamacro_take4(...) metamacro_head(__VA_ARGS__), metamacro_take3(metamacro_tail(__VA_ARGS__))
#undef metamacro_take5
#define metamacro_take5(...) metamacro_head(__VA_ARGS__), metamacro_take4(metamacro_tail(__VA_ARGS__))
#undef metamacro_take6
#define metamacro_take6(...) metamacro_head(__VA_ARGS__), metamacro_take5(metamacro_tail(__VA_ARGS__))
#undef metamacro_take7
#define metamacro_take7(...) metamacro_head(__VA_ARGS__), metamacro_take6(metamacro_tail(__VA_ARGS__))
#undef metamacro_take8
#define metamacro_take8(...) metamacro_head(__VA_ARGS__), metamacro_take7(metamacro_tail(__VA_ARGS__))
#undef metamacro_take9
#define metamacro_take9(...) metamacro_head(__VA_ARGS__), metamacro_take8(metamacro_tail(__VA_ARGS__))
#undef metamacro_take10
#define metamacro_take10(...) metamacro_head(__VA_ARGS__), metamacro_take9(metamacro_tail(__VA_ARGS__))
#undef metamacro_take11
#define metamacro_take11(...) metamacro_head(__VA_ARGS__), metamacro_take10(metamacro_tail(__VA_ARGS__))
#undef metamacro_take12
#define metamacro_take12(...) metamacro_head(__VA_ARGS__), metamacro_take11(metamacro_tail(__VA_ARGS__))
#undef metamacro_take13
#define metamacro_take13(...) metamacro_head(__VA_ARGS__), metamacro_take12(metamacro_tail(__VA_ARGS__))
#undef metamacro_take14
#define metamacro_take14(...) metamacro_head(__VA_ARGS__), metamacro_take13(metamacro_tail(__VA_ARGS__))
#undef metamacro_take15
#define metamacro_take15(...) metamacro_head(__VA_ARGS__), metamacro_take14(metamacro_tail(__VA_ARGS__))
#undef metamacro_take16
#define metamacro_take16(...) metamacro_head(__VA_ARGS__), metamacro_take15(metamacro_tail(__VA_ARGS__))
#undef metamacro_take17
#define metamacro_take17(...) metamacro_head(__VA_ARGS__), metamacro_take16(metamacro_tail(__VA_ARGS__))
#undef metamacro_take18
#define metamacro_take18(...) metamacro_head(__VA_ARGS__), metamacro_take17(metamacro_tail(__VA_ARGS__))
#undef metamacro_take19
#define metamacro_take19(...) metamacro_head(__VA_ARGS__), metamacro_take18(metamacro_tail(__VA_ARGS__))
#undef metamacro_take20
#define metamacro_take20(...) metamacro_head(__VA_ARGS__), metamacro_take19(metamacro_tail(__VA_ARGS__))

// metamacro_drop expansions
#undef metamacro_drop0
#define metamacro_drop0(...) __VA_ARGS__
#undef metamacro_drop1
#define metamacro_drop1(...) metamacro_tail(__VA_ARGS__)
#undef metamacro_drop2
#define metamacro_drop2(...) metamacro_drop1(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop3
#define metamacro_drop3(...) metamacro_drop2(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop4
#define metamacro_drop4(...) metamacro_drop3(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop5
#define metamacro_drop5(...) metamacro_drop4(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop6
#define metamacro_drop6(...) metamacro_drop5(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop7
#define metamacro_drop7(...) metamacro_drop6(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop8
#define metamacro_drop8(...) metamacro_drop7(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop9
#define metamacro_drop9(...) metamacro_drop8(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop10
#define metamacro_drop10(...) metamacro_drop9(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop11
#define metamacro_drop11(...) metamacro_drop10(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop12
#define metamacro_drop12(...) metamacro_drop11(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop13
#define metamacro_drop13(...) metamacro_drop12(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop14
#define metamacro_drop14(...) metamacro_drop13(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop15
#define metamacro_drop15(...) metamacro_drop14(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop16
#define metamacro_drop16(...) metamacro_drop15(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop17
#define metamacro_drop17(...) metamacro_drop16(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop18
#define metamacro_drop18(...) metamacro_drop17(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop19
#define metamacro_drop19(...) metamacro_drop18(metamacro_tail(__VA_ARGS__))
#undef metamacro_drop20
#define metamacro_drop20(...) metamacro_drop19(metamacro_tail(__VA_ARGS__))
