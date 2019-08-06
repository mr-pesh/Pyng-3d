template <typename T, typename Size>
__always_inline bool bittest(T volatile const* value, Size bit) noexcept
{
    bool old;

    asm("bt %2,%1\n\t"
        CC_SET(c)
        : CC_OUT(c) (old)
        : "m" (*value), "Ir" (bit));

    return old;
}
