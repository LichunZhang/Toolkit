/*=========================================================================
   Program:   MainProject
   FileName:  ConsoleWidget.h
   Date:      2016/08/12
   Purpose:	  Widget to call the console(cmd) and show the message in it.
   Version:   v1.0
   Copyright: Lichun Zhang from Soochow University
   Email:     lczhang2011@gmail.com
=========================================================================*/

#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QProcess>

//class QProcess;
class QTextEdit;


class ConsoleWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ConsoleWidget(QWidget *parent = 0);
	~ConsoleWidget();

	void Print(const QString &str);
	void WriteCmdStr(const QString &str);
	QProcess::ProcessState GetProcessState() const {return m_Shell->state();}



private slots:
	void ShowOutput();


private:
	QProcess *m_Shell;
	QTextEdit *m_Console;

};

#endif // CONSOLEWIDGET_H
