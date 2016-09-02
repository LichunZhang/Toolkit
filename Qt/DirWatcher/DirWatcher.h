/*=========================================================================
   Program:   MainProject
   FileName:  DirWatcher.h
   Date:      2016/08/26
   Purpose:	  Monitoring files for modifications in the directory.
   Version:   v2.0
   Copyright: Lichun Zhang from Soochow University
   Email:     lczhang2011@gmail.com
=========================================================================*/

#ifndef __DIRWATCHER_H
#define __DIRWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QSet>
#include <QMap>
#include <QStringList>

class DirWatcher:public QObject{
	Q_OBJECT;
public:
	DirWatcher(QObject *parent);
	virtual ~DirWatcher();

	void addPath(const QString &path);
	void addPaths(const QStringList &paths);
	void setPath(const QString &path);
	void setPaths(const QStringList &paths);

	void removePath(const QString &file)	{m_Watcher->removePath(file);m_FileMap.clear();}
	void removePaths(const QStringList &files) {m_Watcher->removePaths(files);m_FileMap.clear();}
	void removeAllPath() {m_Watcher->removePaths(m_Watcher->directories());m_FileMap.clear();}

	bool hasPath();

	void addNameFilter(const QString filter) {m_NameFilters.push_back(filter);}
	void setNameFilter(const QStringList filters) {m_NameFilters=filters;}

	QStringList getDirectories() {return m_Watcher->directories();}

signals:
	void filesAdded ( const QString& file );
	void filesDeleted (const QString& file);

protected slots:
	void FiltSignal(const QString &path);

protected:
	void insertPathFileSet(const QString& path);
	void setPathFileSet(const QString& path);

private:
	QFileSystemWatcher* m_Watcher;
	QMap<QString,QSet<QString>> m_FileMap;
	//QSet<QString> m_StrSet;
	QStringList m_NameFilters;
};
#endif	//__DIRWATCHER_H
