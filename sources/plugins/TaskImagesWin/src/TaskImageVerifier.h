#ifndef __IMAGE_VERIFY_TASK_H__
#define __IMAGE_VERIFY_TASK_H__

#include "coex.h"

#include <QString>
#include <QStringList>

class TaskImageVerifier : coex::ITask
{
	public:
        TaskImageVerifier();
		virtual QString help();
		virtual QString name();
		virtual QString author();
		virtual QString description();

		virtual bool isSupportOS(const coex::ITypeOperationSystem *os);
		virtual void setOption(QStringList options);
		virtual bool execute(const coex::IConfig *config);
	private:
		bool m_bDebug;
};

extern "C"
{
	coex::ITask* createTask();
}

#endif // __IMAGE_VERIFY_TASK_H__
