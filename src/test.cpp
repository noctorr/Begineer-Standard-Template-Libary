#include <utility>
#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <algorithm>
#include <execution>

template < typename Lambda >
struct LambdaWrapper : Lambda
{    
    template < typename... Types >
    constexpr decltype(auto) operator() ( Types&&... Args ) const
    noexcept(
        noexcept(
            std::declval<const Lambda&>()(
                std::forward<Types>(Args)...
            )
        )
    )
    requires std::is_invocable_v<const Lambda&, Types&&...>
    {
        return static_cast<const Lambda&>(*this)(
            std::forward<Types>(Args)...
        );
    }

    consteval auto lambda_ptr ( )
    noexcept(noexcept(std::declval<Lambda&>()))
    {
        Lambda*&& self = &*this;
        return *self;
    }
};

int main() {
    LambdaWrapper add {
        [] (int x, int y) -> int
        {
            return x + y;
        }
    };

    std::cout << reinterpret_cast<void*>(&*add.lambda_ptr()) << std::endl;

    std::cout << typeid(add(2, 3)).name() << '\n';
    std::cout << add(2, 3) << std::endl;

    
    return 0;
}
