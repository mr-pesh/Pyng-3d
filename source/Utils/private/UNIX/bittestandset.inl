template <typename T, typename Size>
__always_inline bool bittestandset(T volatile* value, Size index) noexcept
{
    bool old;

    asm("bts %2,%1\n\t"
        CC_SET(c)
        : CC_OUT(c) (old), BITOP_ADDR(value)
        : "Ir" (index));

    return old;
}
