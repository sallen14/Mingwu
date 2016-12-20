#ifndef WUCOMMANDLINE_H
#define WUCOMMANDLINE_H

#include <QObject>
#include <QString>

#ifdef __linux__

#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#ifndef wuSHELL
#define wuSHELL
//code from stockoverflow stderr redirection
// Pointer to array allocated at run-time.
//
static pid_t    *pidChild = NULL;

// From our open_max(), {Prog openmax}.

static int      maxFileSize;
#endif
#endif

class wuCommandLine : public QObject
{
    Q_OBJECT
public:
    explicit wuCommandLine(QObject *parent = 0);
    Q_INVOKABLE wuCommandLine(QString cmd);
    //Function: execute stored command
    Q_INVOKABLE void exe();
    //Function: execute user entered command
    Q_INVOKABLE void exe(QString cmd);
    //Function: execute user entered command and return error if any
    Q_INVOKABLE QString exec(QString cmd);
    //Function: return errors from executed command
    Q_INVOKABLE QString getErr(){ return _err;}
signals:

public slots:
private:
    QString _cmd;//Stroe command to be executed
    QString _err;//Store error or command result

    //Function: opens the process port to execute command to internal file
    bool open(std::FILE* intern, QString cmd);
#ifdef __linux__
    FILE *openShell(const char *cmdstring, const char *type)
    {
        int     i;
        int     pfd[2];
        pid_t   pid;
        FILE    *fp;

        // only allow "r" "e" or "w"
        if ((type[0] != 'r' && type[0] != 'w' && type[0] != 'e') || type[1] != 0) {
            errno = EINVAL;     // required by POSIX
            return(NULL);
        }

        if (pidChild == NULL) {     // first time through
            // allocate zeroed out array for child pids
            maxFileSize = 256;
            if ((pidChild = (pid_t*)calloc(maxFileSize, sizeof(pid_t))) == NULL)
                return(NULL);
        }

        if (pipe(pfd) < 0)
            return(NULL);   // errno set by pipe()

        if ((pid = fork()) < 0) {
            return(NULL);   // errno set by fork()
        } else if (pid == 0) {                          // child
            if (*type == 'e') {
                close(pfd[0]);
                if (pfd[1] != STDERR_FILENO) {
                    dup2(pfd[1], STDERR_FILENO);
                    close(pfd[1]);
                }
            } else if (*type == 'r') {
                close(pfd[0]);
                if (pfd[1] != STDOUT_FILENO) {
                    dup2(pfd[1], STDOUT_FILENO);
                    close(pfd[1]);
                }
            } else {
                close(pfd[1]);
                if (pfd[0] != STDIN_FILENO) {
                    dup2(pfd[0], STDIN_FILENO);
                    close(pfd[0]);
                }
            }

            // close all descriptors in pidChild[]
            for (i = 0; i < maxFileSize; i++)
                if (pidChild[i] > 0)
                    close(i);

            execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
            _exit(127);
        }

        // parent continues...
        if (*type == 'e') {
            close(pfd[1]);
            if ((fp = fdopen(pfd[0], "r")) == NULL)
                return(NULL);
        } else if (*type == 'r') {
            close(pfd[1]);
            if ((fp = fdopen(pfd[0], type)) == NULL)
                return(NULL);

        } else {
            close(pfd[0]);
            if ((fp = fdopen(pfd[1], type)) == NULL)
                return(NULL);
        }

        pidChild[fileno(fp)] = pid; // remember child pid for this fd
        return(fp);
    }
    int closeShell(FILE *fp)
    {
        int     fd, stat;
        pid_t   pid;

        if (pidChild == NULL) {
            errno = EINVAL;
            return(-1);     // popen() has never been called //
        }

        fd = fileno(fp);
        if ((pid = pidChild[fd]) == 0) {
            errno = EINVAL;
            return(-1);     // fp wasn't opened by popen() //
        }

        pidChild[fd] = 0;
        if (fclose(fp) == EOF)
            return(-1);

        while (waitpid(pid, &stat, 0) < 0)
            if (errno != EINTR)
                return(-1); // error other than EINTR from waitpid()

        return(stat);   // return child's termination status
    }
#endif
};

#endif // WUCOMMANDLINE_H
