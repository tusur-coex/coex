#include "coex.h"

#include <QString>

extern "C"
{
	QString getLibName();
	namespace coex
	{
		coex::typeOS detectOS(QString);
		coex::typeOS retOS();
	}
}
