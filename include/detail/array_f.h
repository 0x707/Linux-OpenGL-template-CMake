#ifndef ARRAY_F_KERAM_CLASS_H_
#define ARRAY_F_KERAM_CLASS_H_

#include <array>

template<std::size_t S>
using stride_arr = std::array<std::size_t, S>;

constexpr std::size_t vrt_offset{ 3 };
constexpr std::size_t tex_offset{ 2 };
constexpr std::size_t col_offset{ 3 };
constexpr std::size_t no_offset{ 0 };

template<std::size_t S1, std::size_t S2>
class array_f
{
public:
	constexpr array_f(std::array<float, S1>, stride_arr<S2>) noexcept;
	constexpr array_f(float(&)[S1], stride_arr<S2>) noexcept;
	constexpr std::array<float, S1> const& get() const noexcept { return arr_; }

	constexpr std::size_t stride_elem(int) const noexcept;
	constexpr std::size_t offset_size() const noexcept;
	constexpr std::size_t stride(int) const noexcept;
	constexpr std::size_t sizeof_this() const noexcept;
	constexpr float const* data() const noexcept;
private:
	std::array<float, S1> arr_;
	stride_arr<S2> strides_;
	std::size_t offset_;
};

#include "array_f.inl"

#endif // ARRAY_F_KERAM_CLASS_H_