//------------------------------------------------------------------------------
// Conversion types for constants
//------------------------------------------------------------------------------

#ifdef _MSC_VER
#  define WEAK __declspec(selectany)
#else
#  define WEAK __attribute__((selectany))
#endif

struct alignas(16) GLM_VECU32
{
    union
    {
        uint32_t u[4]; glm_vec4 v;
    };
    inline operator glm_vec4() const { return v; }
};

struct alignas(16) GLM_VECF32
{
    union
    {
        float_t f[4]; glm_vec4 v;
    };
    inline operator glm_vec4() const { return v; }
};

struct alignas(16) GLM_VECI32
{
    union
    {
        int32_t i[4]; glm_vec4 v;
    };
    inline operator glm_vec4() const { return v; }
};

extern const WEAK GLM_VECI32 SSE2_INFINITY = { { { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } } };
extern const WEAK GLM_VECU32 SSE2_NEG_ZERO = { { { 0x80000000, 0x80000000, 0x80000000, 0x80000000 } } };
extern const WEAK GLM_VECF32 SSE2_FIX_UINT = { { { 2.14748365e+09, 2.14748365e+09, 2.14748365e+09, 2.14748365e+09 } } };
extern const WEAK GLM_VECF32 SSE2_ZERO_VEC = { { {  0.0f,  0.0f,  0.0f,  0.0f } } };
extern const WEAK GLM_VECF32 SSE2_NEG_ONE  = { { { -1.0f, -1.0f, -1.0f, -1.0f } } };
extern const WEAK GLM_VECF32 SSE2_POS_ONE  = { { {  1.0f,  1.0f,  1.0f,  1.0f } } };
extern const WEAK GLM_VECF32 SSE2_PI_VEC   = { { { 3.141592654f, 3.141592654f, 3.141592654f, 3.141592654f } } };
