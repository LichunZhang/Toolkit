/*=========================================================================
   Program:   MainProject
   FileName:  DirWatcher.cpp
   Date:      2016/08/26
   Purpose:	  Monitoring files for modifications in the directory.
   Version:   v2.0
   Copyright: Lichun Zhang from Soochow University
   Email:     lczhang2011@gmail.com
=========================================================================*/

#include "DirWatcher.h"
#include <QDir>


DirWatcher::DirWatcher(QObject *parent):QObject(parent)
	,m_Watcher(new QFileSystemWatcher(this))
{
	connect(m_Watcher,SIGNAL(directoryChanged(const QString&)),SLOT(FiltSignal(const QString &)));
}

DirWatcher::~DirWatcher()
{

}

// When a file in the path is added, modified or deleted
void DirWatcher::FiltSignal( const QString &path )
{
	QStringList filelist=QDir(path).entryList(m_NameFilters,QDir::Files|QDir::NoSymLinks);//QStringList("*.fds")
	QSet<QString> fileset=m_FileMap[path];

	// Deleted
	if (filelist.length()<m_FileMap[path].size()){
		QSet<QString>::iterator it=fileset.begin();
		while(it!=fileset.end()){
			if (!filelist.contains(*it)){
				emit filesDeleted(path+"\\"+(*it));
				it=fileset.erase(it);
			}
			else
				++it;
		}	
	}
	// Added
	else if(filelist.length()>m_FileMap[path].size()){
		for (QStringList::const_iterator it=filelist.constBegin();it!=filelist.constEnd();++it){
			if (!fileset.contains(*it)){
				fileset.insert(*it);
				emit filesAdded(path+"\\"+(*it));
			}
		}
	}
	//TODO Modified 
}

bool DirWatcher::hasPath()
{
	QStringList list=m_Watcher->directories();
	if (!list.isEmpty())
		return true;
	else
		return false;
}

void DirWatcher::setPath( const QString &path )
{
	if (path.isEmpty())
		return;
	if (hasPath()){
		removeAllPath();
		addPath(path);
	}else{
		addPath(path);
	}
}


void DirWatcher::setPaths( const QStringList &paths )
{
	if (paths.isEmpty())
		return;
	if (hasPath()){
		removeAllPath();
		addPaths(paths);
	}else{
		addPaths(paths);
	}
}



void DirWatcher::addPath( const QString &path )
{
	m_Watcher->addPath(path);
	insertPathFileSet(path);
}

void DirWatcher::addPaths( const QStringList &paths )
{
	m_Watcher->addPaths(paths);
	for (QStringList::const_iterator it=paths.constBegin();it!=paths.constEnd();++it)
		insertPathFileSet(*it);
}



void DirWatcher::insertPathFileSet( const QString& path )
{
	QStringList filelist=QDir(path).entryList(m_NameFilters,QDir::Files| QDir::NoSymLinks);
	for (QStringList::const_iterator it=filelist.constBegin();it!=filelist.constEnd();++it)
	{
		m_FileMap[path].insert(*it);
	}
}

void DirWatcher::setPathFileSet( const QString& path )
{
	m_FileMap.clear();
	QStringList filelist=QDir(path).entryList(m_NameFilters,QDir::Files| QDir::NoSymLinks);
	m_FileMap[path]=QSet<QString>::fromList(filelist);
}
