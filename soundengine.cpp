#include "slideshowengine.h"

void slideShowEngine::startSound()
{
QString command;

            command="/usr/bin/mplayer -slave ";
            for(int i=0; i<m_sequence->soundtracks().count();i++)
            {
                command.append(m_sequence->soundtracks().at(i));
                command.append(" ");
            }
            qDebug() << command;
            m_mplayerProcess.start(command);
            //m_mplayerProcess.write(command.toUtf8());
}


void slideShowEngine::pauseSound()
{
    QString command;
    command="pause\n";
    m_mplayerProcess.write(command.toUtf8());

}

void slideShowEngine::resumeSound()
{

    QString command;
    command="pause\n";
    m_mplayerProcess.write(command.toUtf8());

}


void slideShowEngine::stopSound()
{
    m_mplayerProcess.terminate();
    m_mplayerProcess.waitForFinished();
}

