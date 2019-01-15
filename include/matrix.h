#pragma once
#include <array>

using std::array;
using std::size_t;

template<typename T, size_t N0, size_t N1>
using flat_mat = array<T, N0 * N1>;


template<typename T>
struct ArrayWrapper
{
	ArrayWrapper(T& arr, unsigned cols_count, unsigned row) : arr_{arr}, cols_count_{cols_count}, row_{row} {}

	decltype(std::declval<T>()[0])& operator[](unsigned col) { return arr_[row_ * cols_count_ + col]; }
	decltype(std::declval<T const>()[0]) const& operator[](unsigned col) const { return arr_[row_ * cols_count_ + col]; }

private:
	T& arr_;
	unsigned row_;
	unsigned cols_count_;
};

template<typename T, size_t N0, size_t N1>
struct MatrixWrapper
{
public:
	template<typename... Args>
	MatrixWrapper(Args ...args);

	MatrixWrapper(array<T, N0 * N1> const&);
	MatrixWrapper(array<T, N0 * N1> &&);

	template<typename V, size_t S0, size_t S1, size_t S2>
	MatrixWrapper<V, S2, S1>& operator*=(MatrixWrapper<V, S2, S0> const&);

	template<typename V, size_t S0, size_t S1, size_t S2>
	friend MatrixWrapper<V, S2, S1> operator*(MatrixWrapper<V, S0, S1> const&,
		MatrixWrapper<V, S2, S0> const&);

	ArrayWrapper<array<T,N0 *N1>> operator[](unsigned);
	ArrayWrapper<const array<T,N0 *N1>> operator[](unsigned) const;

	T& at(unsigned, unsigned);
	T const& at(unsigned, unsigned) const;

private:
	array<T, N0 * N1> flat_matrix_;
};

template<typename T, size_t N0, size_t N1>
template<typename... Args>
MatrixWrapper<T, N0, N1>::MatrixWrapper(Args ...args)
	: flat_matrix_{ args... }
{
}

template<typename T, size_t N0, size_t N1>
MatrixWrapper<T, N0, N1>::MatrixWrapper(array<T, N0 * N1> const& other)
	: flat_matrix_{ other }
{
}

template<typename T, size_t N0, size_t N1>
MatrixWrapper<T, N0, N1>::MatrixWrapper(array<T, N0 * N1> && other)
	: flat_matrix_{std::move(other)}
{
}

template<typename T, size_t N0, size_t N1>
template<typename V, size_t S0, size_t S1, size_t S2>
MatrixWrapper<V, S2, S1>&
MatrixWrapper<T, N0, N1>::operator*=(MatrixWrapper<V, S2, S0> const& other)
{
}

template<typename V, size_t S0, size_t S1, size_t S2>
MatrixWrapper<V, S2, S1> operator*(MatrixWrapper<V, S0, S1> const& left,
	MatrixWrapper<V, S2, S0> const& right)
{
	MatrixWrapper<V, S2, S1> result;

	for (unsigned k = 0; k < S2; ++k) {
		for (unsigned i = 0; i < S1; ++i) {
			for (unsigned j = 0; j < S0; ++j) {
				result.at(i,k) += left.at(i,j) * right.at(j,k);
			}
		}
	}

	return result
}

template<typename T, size_t N0, size_t N1>
T& MatrixWrapper<T, N0, N1>::at(unsigned first, unsigned second)
{
	return flat_matrix_[first * N0 + second];
}

template<typename T, size_t N0, size_t N1>
T const& MatrixWrapper<T, N0, N1>::at(unsigned first, unsigned second) const
{
	return flat_matrix_[first * N0 + second];
}

template<typename T, size_t N0, size_t N1>
ArrayWrapper<array<T,N0 *N1>> MatrixWrapper<T,N0,N1>::operator[](unsigned idx)
{
	return ArrayWrapper<array<T, N0 * N1>>{flat_matrix_, N0, idx};
}

template<typename T, size_t N0, size_t N1>
ArrayWrapper<const array<T,N0 *N1>> MatrixWrapper<T,N0,N1>::operator[](unsigned idx) const
{
	return ArrayWrapper<const array<T,N0 *N1>>{flat_matrix_, N0, idx};
}