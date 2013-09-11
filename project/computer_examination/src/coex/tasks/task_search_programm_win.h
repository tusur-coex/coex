#ifndef __TASK_SEARCH_PROGRAMM_WIN_H__
#define __TASK_SEARCH_PROGRAMM_WIN_H__

#include "../task.h"

class taskSearchProgrammWin : public coex::task 
{
	public:
		taskSearchProgrammWin();
	
		// coex::Task 
		virtual bool supportOS(const coex::typeOS &os);
		virtual QString name();
		virtual QString description();
		virtual bool test();
		virtual bool execute(const coex::config &config);
		
	private:
		QString m_strName;
		QString m_strDescription;
};

#endif // __TASK_SEARCH_PROGRAMM_WIN_H__
