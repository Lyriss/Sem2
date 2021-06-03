#pragma once
template<class T,class T1>
class Pair {
public:
	Pair(T first=T(), T1 second=T1()):first(first),second(second){}
	T first;
	T1 second;
	template<class T, class T1> friend bool operator >(const Pair<T, T1>& a, const Pair<T, T1>& b);
	template<class T, class T1> friend bool operator <(const Pair<T, T1>& a, const Pair<T, T1>& b);
};
template<class T, class T1>
bool operator> (const Pair<T,T1>& a, const Pair<T,T1>& b) {
	return a.second > b.second;
}
template<class T, class T1>
bool operator< (const Pair<T, T1>& a, const Pair<T, T1>& b) {
	return a.second < b.second;
}