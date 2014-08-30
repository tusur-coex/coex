#!/bin/bash
CURRPWD=$(echo "`pwd`")
OK=" ..... ok"
LOGFILE="$CURRPWD/logs/log_build.log"
ERRORLOGFILE="$CURRPWD/logs/errorlog_build.log"
echo $CURRPWD > $LOGFILE

echo -ne " * delete folder 'bin'"
rm -rf 'bin'
echo $OK

echo -ne " * delete all 'Makefile'"
find . -iname 'Makefile' -delete
echo $OK

echo -ne " * delete all '*.o'"
find . -iname '*.o' -delete
echo $OK

echo -ne " * delete all 'tmp'"
find . -iname 'tmp' -delete
echo $OK

echo -ne " * build 'coex'"
cd $CURRPWD/app/
qmake-qt4
make >> $LOGFILE 2>> $ERRORLOGFILE
echo $OK

echo " * build plugins"
cd $CURRPWD/plugins
for D in `find ./ -mindepth 1 -maxdepth 1 -type d `
do
	cd $CURRPWD/plugins
	cd $D
	DIRNAME=$(basename "`pwd`")
	echo -ne " * * build '$DIRNAME'"

	qmake-qt4 >> $LOGFILE 2>> $ERRORLOGFILE
	if [ $? -ne 0 ]; then
		echo ""
		echo "ERRORS, log look in file: $ERRORLOGFILE"
		exit;
	fi

	make >> $LOGFILE 2>> $ERRORLOGFILE
	if [ $? -ne 0 ]; then
		echo ""
		echo "ERRORS, log look in file: $ERRORLOGFILE"
		exit;
	fi
	echo $OK
done

