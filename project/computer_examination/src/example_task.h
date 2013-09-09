#ifndef __EXAMPLE_TASKS_H__
#define __EXAMPLE_TASKS_H__

#include "task.h"

class exampleTask : public coex::task 
{
	public:
		exampleTask();
	
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

#endif // __EXAMPLE_TASKS_H__
