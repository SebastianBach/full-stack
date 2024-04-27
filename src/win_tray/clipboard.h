#ifndef CLIPBOARD_H_
#define CLIPBOARD_H_

#include <vector>

namespace clipboard
{
using text = std::vector<wchar_t>;

void clear();
void format_text();
void get_text(text& text);
void set_text(const text& text);

} // namespace clipboard

#endif
