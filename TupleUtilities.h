#include <cstddef>
#include <tuple>
#include <utility>

#include <type_traits>


namespace tutilities{
    /**see http://www.cppsamples.com/common-tasks/apply-tuple-to-function.html*/
    template<typename F, typename Tuple, size_t ...S >
    decltype(auto) apply_tuple_impl(F&& fn, Tuple&& t, std::index_sequence<S...>)
    {
        return std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))...);
    }
    /**applies arguments to function*/
    template<typename F, typename Tuple>
    decltype(auto) apply_tuple(F&& fn, Tuple&& t)
    {
        std::size_t constexpr tSize
            = std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
        return apply_tuple_impl(std::forward<F>(fn),
                                std::forward<Tuple>(t),
                                std::make_index_sequence<tSize>());
    }

    template <std::size_t Ofst, class Tuple, std::size_t... I>
    constexpr auto slice_impl(Tuple&& t, std::index_sequence<I...>){
        return std::forward_as_tuple(
            std::get<I + Ofst>(std::forward<Tuple>(t))...);
    }
    /**see http://stackoverflow.com/questions/8569567/get-part-of-stdtuple*/
    /**splices tuple into sections.  Call using tuple_splice<firstindex, secondindex>(tuple).  Make sure that firstindex and secondindex are constexpr*/
    template <std::size_t I1, std::size_t I2, class Cont>
    constexpr auto tuple_slice(Cont&& t)  {
        static_assert(I2 >= I1, "invalid slice");
        static_assert(std::tuple_size<std::decay_t<Cont>>::value >= I2, 
            "slice index out of bounds");

        return slice_impl<I1>(std::forward<Cont>(t),std::make_index_sequence<I2 - I1>{});
    }




    /**see https://codereview.stackexchange.com/questions/51407/stdtuple-foreach-implementation*/
    template <typename Tuple, typename F, std::size_t ...Indices>
    auto for_each_impl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
        //constexpr 
        return std::make_tuple(f(std::get<Indices>(std::forward<Tuple>(tuple)), Indices, tuple_slice<0, Indices>(tuple), tuple_slice<Indices+1, std::tuple_size<std::remove_reference_t<Tuple>>::value>(tuple))...);

    }
    /**iterates over a tuple with callback f(val, index, sequence from 0 to index-1, sequence from index+1 to end)*/
    template <typename Tuple, typename F>
    auto for_each(Tuple&& tuple, F&& f) {
        constexpr std::size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
        return for_each_impl(std::forward<Tuple>(tuple), std::forward<F>(f),
                    std::make_index_sequence<N>{});
    }
}