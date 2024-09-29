#ifndef CLIPBOARD_H_
#define CLIPBOARD_H_


#include <string>

namespace clipboard
{
using text = std::string;

void clear();
void format_text();
void get_text(text& text);
void set_text(const text& text);

} // namespace clipboard

#endif
