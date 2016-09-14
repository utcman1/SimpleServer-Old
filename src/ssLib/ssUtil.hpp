// remove element from vector and erase it
template<typename T>
inline void erase(std::vector<T>& _v, const T& _item)
{
	_v.erase(std::remove(_v.begin(), _v.end(), _item), _v.end());
}
