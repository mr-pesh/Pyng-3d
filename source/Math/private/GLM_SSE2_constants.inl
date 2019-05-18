//------------------------------------------------------------------------------
// Conversion types for constants
//------------------------------------------------------------------------------

template <typename T>
struct alignas(16) GLM_VEC_
{
    union
    {
        T u[4]; glm_vec4 v;
    };
    constexpr operator glm_vec4() const { return v; }
};

using GLM_VECI32 = GLM_VEC_<int32_t>;
using GLM_VECF32 = GLM_VEC_<float_t>;
using GLM_VECU32 = GLM_VEC_<uint32_t>;

inline constexpr GLM_VECI32 SSE2_INFINITY = { { { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } } };
inline constexpr GLM_VECU32 SSE2_NEG_ZERO = { { { 0x80000000, 0x80000000, 0x80000000, 0x80000000 } } };
inline constexpr GLM_VECF32 SSE2_FIX_UINT = { { { 32768.f*65536.f, 32768.f*65536.f, 32768.f*65536.f, 32768.f*65536.f } } };
inline constexpr GLM_VECF32 SSE2_ZERO_VEC = { { {  0.0f,  0.0f,  0.0f,  0.0f } } };
inline constexpr GLM_VECF32 SSE2_NEG_ONE  = { { { -1.0f, -1.0f, -1.0f, -1.0f } } };
inline constexpr GLM_VECF32 SSE2_POS_ONE  = { { {  1.0f,  1.0f,  1.0f,  1.0f } } };
inline constexpr GLM_VECF32 SSE2_PI_VEC   = { { { 3.141592654f, 3.141592654f, 3.141592654f, 3.141592654f } } };
