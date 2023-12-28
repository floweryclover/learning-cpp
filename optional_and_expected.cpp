#include <iostream>
#include <string>

#include <optional> // C++17 (https://en.cppreference.com/w/cpp/utility/optional)
#include <expected> // C++23 (https://en.cppreference.com/w/cpp/utility/expected)

class ParseError
{
public:
    void PrintDetail()
    {
        std::cerr << "parse error" << std::endl;
    }
};

// 예제를 위해 크기 0인 배열을 가정
class UserDefinedArray
{
private:
    int data;
public:
    UserDefinedArray() : data(10) {}

    std::optional<int> operator[](int index)
    {
        if (index == 0)
        {
            return data;
        }
        else
        {
            return std::nullopt;
        }
    }
};

// 예제를 위해 "123" 만 파싱 가능
std::expected<int, ParseError> Parse(const std::string& intString)
{
    if (intString == "123")
    {
        return 123;
    }
    else
    {
        return std::unexpected(ParseError());
    }
}

int main()
{
    UserDefinedArray arr;
    if (arr[0].has_value())
    {
        std::cout << "arr[0] has value: " << arr[0].value() << std::endl;
    }
    if (!arr[1].has_value()) // out of bound ? (arr의 크기는 1)
    {
        std::cout << "arr[1] has no value" << std::endl;
        // std::cout << "arr[1]: " << arr[1].value() << std::endl; ERROR!
        std::cout << "    otherwise: " << arr[1].value_or(0) << std::endl;
    }

    auto successfulResult = Parse("123");
    if (successfulResult.has_value())
    {
        std::cout << "successful parsing: " << successfulResult.value() << std::endl;
    }

    auto failedResult = Parse("not a number");
    if (!failedResult.has_value())
    {
        std::cerr << "parsing failed" << std::endl;
        std::cout << "    otherwise: " << failedResult.value_or(0) << std::endl;
    }
    //if (failedResult.error() == ParseError()) enum으로 에러 타입을 정하던가 연산자 오버로딩하면 디테일한 에러 분기 가능
    // else if (failedResult.error() == MultipleErrors::OneError) ..
    return 0;
}
