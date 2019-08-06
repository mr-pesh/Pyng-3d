template <typename T, typename Size>
__always_inline bool bittestandreset(T volatile* value, Size index) noexcept
{
    bool old;

    __asm__ __volatile__("btr %2,%1\n\t"
        CC_SET(c)
        : CC_OUT(c) (old), BITOP_ADDR(value)
        : "Ir" (index));

    return old;
}
