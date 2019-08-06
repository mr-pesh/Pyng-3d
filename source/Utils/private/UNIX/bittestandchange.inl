template <typename T, typename Size>
__always_inline bool bittestandchange(T volatile* value, Size index) noexcept
{
    bool old;

    __asm__ __volatile__("btc %2,%1\n\t"
        CC_SET(c)
        : CC_OUT(c) (old), BITOP_ADDR(value)
        : "Ir" (index) : "memory");

    return old;
}
