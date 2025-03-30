#include <cstdint>
#include <vector>

constexpr uint8_t MAX_CHARS = 128;

enum class ArgFlags
{
    I,
    O
};

struct Arg 
{
    Arg() = default;
    Arg(char8_t* feed);
    Arg(char8_t* flag, char8_t* file);
    ArgFlags m_flag;
    char8_t m_file[128];
};

class ArgParser
{
    public:
        ArgParser(int argc, char8_t* argv[]);
        const std::vector<Arg> Args() const;
    private:
        std::vector<Arg> m_args;
};
