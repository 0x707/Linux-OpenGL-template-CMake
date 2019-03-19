#include "array_f.h"

// non-member functions

template<std::size_t S>
constexpr std::size_t count_offset(stride_arr<S> const& arr) noexcept
{
	std::size_t result{ 0 };
	for (auto const& x : arr)
		result += x;
	return result;
}

template<typename T, std::size_t S>
constexpr std::size_t arr_size(T(&)[S]) noexcept
{
    return S;
}

// end of non-member funcs

template<std::size_t S1, std::size_t S2>
constexpr array_f<S1,S2>::array_f(
	std::array<float, S1> arr, stride_arr<S2> strides ) noexcept
	: arr_{std::move(arr)}, strides_{std::move(strides)}
	, offset_{ 0 }
{
	offset_ = count_offset(strides_);
}

template<std::size_t S1, std::size_t S2>
constexpr array_f<S1, S2>::array_f(float(&arr)[S1], stride_arr<S2> strides) noexcept
	: strides_{std::move(strides)}
	, offset_{0}
{
	for (std::size_t i = 0; i < S1; ++i)
		arr_[i] = arr[i];

	offset_ = count_offset(strides_);
}

template<std::size_t S1, std::size_t S2>
constexpr std::size_t array_f<S1, S2>::stride_elem(int idx) const noexcept
{
	assert(idx <= strides_.size());
	return strides_[idx];
}

template<std::size_t S1, std::size_t S2>
constexpr std::size_t array_f<S1, S2>::offset_size() const noexcept
{
    return offset_ * sizeof(float);
}

template<std::size_t S1, std::size_t S2>
constexpr std::size_t array_f<S1, S2>::stride(int idx) const noexcept
{
    std::size_t result = 0;

    for (int i = 0; i < idx; ++i)
        result += strides_[i];

    return result * sizeof(float);    
}

template<std::size_t S1, std::size_t S2>
constexpr std::size_t array_f<S1, S2>::sizeof_this() const noexcept
{
    return S1 * sizeof(float);
}

template<std::size_t S1, std::size_t S2>
constexpr float const* array_f<S1, S2>::data() const noexcept
{
    return arr_.data();
}