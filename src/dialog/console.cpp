#include "boxer.h"
#include <stdio.h>

#if !APPLE && !WIN32 && !LINUX
namespace dialog
{

namespace {
	char getMessageType(Style style)
   {
      switch (style)
      {
      case Style::Info:
         return "[Info]";
      case Style::Warning:
         return "[Warning]";
      case Style::Error:
         return "[Error]";
      case Style::Question:
         return "[Question]";
      default:
         return "[Info]";
      }
   }
}

Selection show(const char* message, const char* title, Style style, Buttons buttons)
{
	printf("%s\n", title);
	for (int i = 0; i < 80; i++)
	{
		printf("-");
	}
	printf("\n");
	printf("%s %s\n", getMessageType(style), message);
	printf("\n");
	
	switch (buttons)
	{
	case Buttons::OK:
		printf("[OK]\n");
		break;
	case Buttons::OKCancel:
		printf("[OK] [Cancel]\n");
		break;
	case Buttons::YesNo:
		printf("[Yes] [No]\n");
		break;
	case Buttons::YesNoCancel:
		printf("[Yes] [No] [Cancel]\n");
		break;
	default:
		printf("[OK]\n");
		break;
	}

	char input[10];
	scanf("%9s", input);

	if (strcmp(input, "OK") == 0)
	{
		return Selection::OK;
	}
	else if (strcmp(input, "Cancel") == 0)
	{
		return Selection::Cancel;
	}
	else if (strcmp(input, "Yes") == 0)
	{
		return Selection::Yes;
	}
	else if (strcmp(input, "No") == 0)
	{
		return Selection::No;
	}
	else
	{
		return Selection::None;
	}
}

} // namespace dialog
#endif