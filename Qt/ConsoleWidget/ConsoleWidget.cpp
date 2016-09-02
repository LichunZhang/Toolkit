/*=========================================================================
   Program:   MainProject
   FileName:  ConsoleWidget.cpp
   Date:      2016/08/12
   Purpose:	  Widget to call the console(cmd) and show the message in it.
   Version:   v1.0
   Copyright: Lichun Zhang from Soochow University
   Email:     lczhang2011@gmail.com
=========================================================================*/
#include "ConsoleWidget.h"

#include <QTextEdit>
#include <QGridLayout>
#include <QTextCodec>

ConsoleWidget::ConsoleWidget(QWidget *parent) :
	QWidget(parent)
	,m_Shell(new QProcess(this))
	,m_Console(new QTextEdit(this))
{
	QGridLayout *layout=new QGridLayout(this);
	layout->addWidget(m_Console);

	m_Console->setTextColor(Qt::white);
	m_Console->setFont(QFont( "Times New Roman" , 12));
	m_Console->setStyleSheet(tr("background-color: rgb(0, 0, 0)"));

	m_Shell->setReadChannelMode(QProcess::MergedChannels);
	// Start Shell
	m_Shell->start("cmd", QStringList(), QIODevice::ReadWrite);

	connect(m_Shell, SIGNAL(readyRead()),
		this, SLOT(ShowOutput()));
	setLayout(layout);
}

ConsoleWidget::~ConsoleWidget()
{
	m_Shell->kill();
	m_Shell->waitForFinished();
}


void ConsoleWidget::WriteCmdStr( const QString &str )
{
	QByteArray bytes=QString(str+"\n").toUtf8();
	m_Shell->write(bytes);
}


void ConsoleWidget::ShowOutput()
{
	// Read standard output data
	QByteArray bytes = m_Shell->readAllStandardOutput();
	QTextCodec* gbkCodec = QTextCodec::codecForLocale();	//codecForName("GBK")
	QString result = gbkCodec->toUnicode(bytes);  
	// Split data by "\n"
	QStringList lines = result.split("\n");
	// Show data in QTextEdit
	foreach (QString line, lines)
	{
		m_Console->append(line);
	}
}

void ConsoleWidget::Print( const QString &str )
{
	QByteArray bytes=QString(str+"\n").toUtf8();
	QTextCodec* gbkCodec = QTextCodec::codecForLocale();
	QString result = gbkCodec->toUnicode(bytes);  
	// Split data by "\n"
	QStringList lines = result.split("\n");
	// Show data in QTextEdit
	foreach (QString line, lines)
	{
		m_Console->append(line);
	}
}

