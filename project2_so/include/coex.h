#ifndef __COEX_H__
#define __COEX_H__

#include <QString>
#include <iostream>

namespace coex
{
	enum typeOS
	{
		ceUnknown,
		ceLinux,
		ceWindows95,
		ceWindows98,
		ceWindowsXP,
		ceWindowsVista,
		ceWindows7,
		ceWindows8
	};

	struct config
	{
		config()
		{
			os = coex::ceUnknown;
		};

		QString inputFolder;
		QString outputFolder;
		typeOS os;
	};
}

#endif //__COEX_H__
