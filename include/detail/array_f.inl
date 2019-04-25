#include "array_f.h"
#include <cassert>

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

template<std::size_t S>
constexpr std::size_t stride_offset(stride_arr<S> const& arr, std::size_t idx)
{
	std::size_t result{0};
	for (std::size_t i = 0; i < idx; ++i)
		result += arr[i];
	return result;
}

// end of non-member funcs

template<std::size_t S1, std::size_t S2>
constexpr array_f<S1,S2>::array_f(
	std::array<float, S1> arr, stride_arr<S2> strides ) noexcept
	: arr_{arr}, strides_{strides}
	, offset_{ count_offset(strides_) }
{
	assert(offset_ <= S1 && (S1 % offset_ == 0));
}

template<std::size_t S1, std::size_t S2>
constexpr array_f<S1, S2>::array_f(float const (&arr)[S1], stride_arr<S2> strides) noexcept
	: strides_{strides}
	, offset_{ count_offset(strides_) }
{
	assert(offset_ <= S1 && (S1 % offset_ == 0));
	for (std::size_t i = 0; i < S1; ++i)
		arr_[i] = arr[i];

}

template<std::size_t S1, std::size_t S2>
constexpr float array_f<S1, S2>::operator[](std::size_t idx) const noexcept
{
	return arr_[idx];
}

template<std::size_t S1, std::size_t S2>
constexpr float const* array_f<S1, S2>::data() const noexcept
{
    return arr_.data();
}

template<std::size_t S1, std::size_t S2>
constexpr std::size_t array_f<S1, S2>::read_from_here(std::size_t stride_pos) const noexcept
{
	assert(stride_pos < strides_.size());
	return stride_offset(strides_, stride_pos) * sizeof(float);
}

template<std::size_t S1, std::size_t S2>
constexpr std::size_t array_f<S1, S2>::sizeof_content() const noexcept
{
    return S1 * sizeof(float);
}


template<std::size_t S1, std::size_t S2>
constexpr std::size_t array_f<S1, S2>::sizeof_offset() const noexcept
{
    return offset_ * sizeof(float);
}

template<std::size_t S1, std::size_t S2>
constexpr std::size_t array_f<S1, S2>::stride(int idx) const noexcept
{
	assert(idx <= strides_.size());
	return strides_[idx];
}