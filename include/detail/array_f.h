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
	constexpr array_f(float const (&)[S1], stride_arr<S2>) noexcept;

	constexpr array_f(array_f<S1, S2> const&) = default;
	constexpr array_f(array_f<S1, S2>&&) = default;
	constexpr array_f<S1,S2>& operator=(array_f<S1, S2> const& other) = default;
	constexpr array_f<S1,S2>& operator=(array_f<S1, S2>&&) = default;

	constexpr float operator[](std::size_t) const noexcept;

	constexpr float const* data() const noexcept;
	
	constexpr std::size_t read_from_here(std::size_t) const noexcept;
	constexpr std::size_t size() const noexcept { return S1; }
	constexpr std::size_t strides_size() const noexcept { return S2; }
	constexpr std::size_t sizeof_content() const noexcept;
	constexpr std::size_t sizeof_offset() const noexcept;
	constexpr std::size_t stride(int) const noexcept;
private:
	std::array<float, S1> arr_;
	stride_arr<S2> strides_;
	std::size_t offset_;
};

#include "array_f.inl"

#endif // ARRAY_F_KERAM_CLASS_H_