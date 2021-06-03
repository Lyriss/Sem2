#pragma once
template<typename T>
T minT(T a, T b) {
	return a > b ? b : a;
}