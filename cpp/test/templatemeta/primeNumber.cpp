#include <iostream>

template <int _P, int _Q = _P>
class IsPrime
{
public:
    enum{result = (_P % (_Q - 1) ) && IsPrime<_P, _Q - 1>::result };
};

template <int _P>
class IsPrime<_P, 2>
{
public:
    enum{ result = 1};
};

template<bool C, typename Ta, typename Tb>
class IfThenElse
{
    public:
        typedef Tb ResultT;
};

template<typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb>
{
public:
    typedef Ta ResultT;
};

template <int _P, int _Q = 0>
class CountPrime
{
public:
    typedef typename IfThenElse<IsPrime<_P>::result,
        CountPrime<_P - 1, _Q + 1>,
        CountPrime<_P - 1, _Q> >::ResultT
        SubT;
    enum { result = SubT::result };
};

template <int _Q>
class CountPrime<2, _Q>
{
public:
    enum{result = _Q + 1 };
};

int main()
{
    std::cout << IsPrime<33>::result << std::endl;    //判断素数
    std::cout << IsPrime<11>::result << std::endl;
    std::cout << IsPrime<7>::result << std::endl;
    std::cout << IsPrime<179>::result << std::endl;
    std::cout << CountPrime<100>::result << std::endl;    //统计x以内素数
    return 0;
}
