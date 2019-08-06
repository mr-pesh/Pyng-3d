template <typename T>
__always_inline int popcnt(T value) noexcept
{
    if constexpr (std::_Is_any_of_v<T, int, unsigned int>
        || sizeof(T) < sizeof(unsigned int)) {
        return __builtin_popcount(static_cast<unsigned int>(value));
    }
    else if (std::_Is_any_of_v<T, long, unsigned long>) {
        return __builtin_popcountl(static_cast<unsigned long>(value));
    }
    else if (std::_Is_any_of_v<T, long long, unsigned long long>) {
        return __builtin_popcountll(static_cast<unsigned long long>(value));
    }
}
