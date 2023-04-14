// cheating a bit since I'm looing at how others implement this
namespace dstd::impl
{

struct dummy_init_t{};
constexpr dummy_init_t dummy_init{};

template<class T>
union storage_t
{
    byte dummy;
    T value;

    constexpr storage_t(dummy_init_t)
        : dummy()
    {}

    template<class... Args>
    constexpr storage_t(Args&&... args)
        : value(forward<Args>(args)...)
    {}

    ~storage_t()
    {}
};

}
