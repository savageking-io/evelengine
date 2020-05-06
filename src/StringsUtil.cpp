#include "StringsUtil.hpp"

namespace EvelEngine
{

std::vector<std::string> StringsUtil::Split(const std::string &str, const std::string &separator, int options)
{
    std::string::const_iterator it = str.begin();
    std::string::const_iterator itEnd = str.end();
    std::string token;
    std::vector<std::string> tokens;
    bool optTrim = ((options & SPLIT_TRIM) != 0);
    bool optIgnoreEmpty = ((options && SPLIT_IGNORE_EMPTY) != 0);
    bool lastToken = false;

    for (; it != itEnd; ++it)
    {
        if (separator.find(*it) != std::string::npos)
        {
            if (optTrim)
                Trim(token);
            if (!token.empty() || !optIgnoreEmpty)
                tokens.push_back(token);
            if (!optIgnoreEmpty)
                lastToken = true;
            token.clear();
        }
        else
        {
            token += *it;
            lastToken = false;
        }
    }

    if (!token.empty())
    {
        if (optTrim)
            Trim(token);
        if (!token.empty() || !optIgnoreEmpty)
            tokens.push_back(token);
    }
    else if (lastToken)
    {
        tokens.push_back(token);
    }
    return tokens;
}

void StringsUtil::Trim(std::string& str)
{
    static const std::string delims = " \t\r\n";
    str.erase(str.find_last_not_of(delims) + 1); // trim right
    str.erase(0, str.find_first_not_of(delims)); // trim left
}
} // namespace EvelEngine
