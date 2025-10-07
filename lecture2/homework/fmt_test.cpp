#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/core.h>

int main()
{
    fmt::print("=== Examples ===\n\n");

    std::string result1 =fmt::format("{0}, {1}, {2}", 'a', 'b', 'c');
    fmt::print("{}\n", result1);
    // Result: "a, b, c"
    std::string result2 =fmt::format("{}, {}, {}", 'a', 'b', 'c');
    fmt::print("{}\n", result2);
    // Result: "a, b, c"
    std::string result3 =fmt::format("{2}, {1}, {0}", 'a', 'b', 'c');
    fmt::print("{}\n", result3);
    // Result: "c, b, a"
    std::string result4 =fmt::format("{0}{1}{0}", "abra", "cad"); // arguments' indices can be repeated
    fmt::print("{}\n\n", result4);
    // Result: "abracadabra"

    std::string result5 =fmt::format("{:<30}", "left aligned");
    fmt::print("{}\n", result5);
    // Result: "left aligned                  "
    std::string result6 =fmt::format("{:>30}", "right aligned");
    fmt::print("{}\n", result6);
    // Result: "                 right aligned"
    std::string result7 =fmt::format("{:^30}", "centered");
    fmt::print("{}\n", result7);
    // Result: "           centered           "
    std::string result8 =fmt::format("{:*^30}", "centered"); // use '*' as a fill char
    fmt::print("{}\n\n", result8);
    // Result: "***********centered***********"

    std::string result9 =fmt::format("{:<{}}", "left aligned", 30);
    fmt::print("{}\n\n", result9);
    // Result: "left aligned

    std::string result10 =fmt::format("{:.{}f}", 3.14, 1);
    fmt::print("{}\n\n", result10);
    // Result: "3.1"

    std::string result11 =fmt::format("{:+f}; {:+f}", 3.14, -3.14); // show it always
    fmt::print("{}\n", result11);
    // Result: "+3.140000; -3.140000"
    std::string result12 =fmt::format("{: f}; {: f}", 3.14, -3.14); // show a space for positive numbers
    fmt::print("{}\n", result12);
    // Result: " 3.140000; -3.140000"
    std::string result13 =fmt::format("{:-f}; {:-f}", 3.14, -3.14); // show only the minus -- same as '{:f}; {:f}'
    fmt::print("{}\n\n", result13);
    // Result: "3.140000; -3.140000"

    std::string result14 =fmt::format("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    fmt::print("{}\n", result14);
    // Result: "int: 42;  hex: 2a;  oct: 52; bin: 101010"
    // with 0x or 0 or 0b as prefix:
    std::string result15 =fmt::format("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42);
    fmt::print("{}\n\n", result15);
    // Result: "int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010"

    std::string result16 =fmt::format("{:#04x}", 0);
    fmt::print("{}\n\n", result16);
    // Result: "0x00"

    fmt::print(
        "┌{0:─^{2}}┐\n"
        "│{1: ^{2}}│\n"
        "└{0:─^{2}}┘\n\n",
        "", "Hello, world!", 20);

    auto t = tm();
    t.tm_year = 2010 - 1900;
    t.tm_mon = 7;
    t.tm_mday = 4;
    t.tm_hour = 12;
    t.tm_min = 15;
    t.tm_sec = 58;
    fmt::print("{:%Y-%m-%d %H:%M:%S}\n\n", t);
    // Prints: 2010-08-04 12:15:58

    auto s = fmt::format(std::locale("en_US.UTF-8"), "{:L}", 1234567890);
    fmt::print("{}\n\n", s);
    // s == "1,234,567,890"
}
