#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "master.h"

int mbm_load_config();
int mbm_main();
int mbm_cleanup();

struct master srv;

int
main(int argc, char **argv)
{
    pid_t pid, sid;
    FILE *fp = 0;

    /*

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);

    umask(0);
    sid = setsid();

    if (sid < 0)
        exit(EXIT_FAILURE);
        */


    openlog("mb-masterd", 0, 0);
    syslog(LOG_INFO, "started");

    close(stdin);
    close(stdout);
    close(stderr);

    if (mbm_load_config() != 0)
        goto error;

    if (srv.config_file) {
        /* load the configuration file */
        if (!(fp = fopen(srv.config_file, "rb"))) {
            syslog(LOG_ERR, "could not open file '%s'", srv.config_file);
            goto error;
        }

        /* calculate the file length */
        fseek(fp, 0, SEEK_END);
        srv.config_sz = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (!(srv.config_buf = malloc(srv.config_sz))) {
            syslog(LOG_ERR, "out of mem");
            goto error;
        }

        if ((size_t)srv.config_sz != fread(srv.config_buf, 1, srv.config_sz, fp)) {
            syslog(LOG_ERR, "read error");
            goto error;
        }
    } else
        srv.config_sz = 0;

    mbm_main();

    /*
    if (mkfifo("/var/run/mb-masterd/mb-masterd.sock", 770) != 0) {
        fprintf("error: unable to create mb-masterd.sock\n");
        return 1;
    }
    */

    mbm_cleanup();

    closelog();
    return 0;

error:
    if (fp)
        fclose(fp);
    closelog();
    return 1;
}

int
mbm_main()
{
    int sock;
    int i_sock;
    struct sockaddr_in i_addr;
    socklen_t sin_sz;

    memset(&i_addr, 0, sizeof(struct sockaddr_in));
    sin_sz = sizeof(struct sockaddr_in);

    srv.addr.sin_family = AF_INET;
    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (bind(sock, (struct sockaddr*)&srv.addr, sizeof srv.addr) == -1) {
        syslog(LOG_ERR, "could not bind to %s:%hd", inet_ntoa(srv.addr.sin_addr), ntohs(srv.addr.sin_port));
        return 1;
    }

    if (listen(sock, 1024) == -1) {
        syslog(LOG_ERR, "could not listen on %s:%hd", inet_ntoa(srv.addr.sin_addr), ntohs(srv.addr.sin_port));
        return 1;
    }

    syslog(LOG_INFO, "listening on %s:%hd", inet_ntoa(srv.addr.sin_addr), ntohs(srv.addr.sin_port));

    do {
        if ((i_sock = accept(sock, (struct sockaddr *)&i_addr, &sin_sz)) == -1) {
            syslog(LOG_ERR, "fatal: accept() failed: %s", strerror(errno));
            return 1;
        }
        syslog(LOG_INFO, "accepted connection from %s", inet_ntoa(i_addr.sin_addr));

        pthread_t thr;
        if (pthread_create(&thr, 0, &mbm_conn_main, (void*)i_sock) != 0) {
            syslog(LOG_ERR, "fatal: pthread_create() failed");
            return 1;
        }
    } while (1);

    return 0;
}

int
mbm_cleanup()
{
    if (srv.config_sz)
        free(srv.config_buf);
}

int
mbm_load_config()
{
    FILE *fp;
    char in[256];
    char *p;
    char *s;
    int len;

    if (!(fp = fopen("/home/sdac/svn/methabot/trunk/src/mb-masterd/mb-masterd.conf", "r"))) {
        syslog(LOG_ERR, "could not open configuration file");
        return 1;
    }

    while (fgets(in, 256, fp)) {
        if (in[0] == '#')
            continue;
        if (p = strchr(in, '=')) {
            len = p-in;
            while (isspace(in[len-1]))
                len--;
            do p++;
            while (isspace(*p));

            switch (len) {
                case 6:
                    if (strncmp(in, "listen", 6) == 0) {
                        s = strchr(p, ':');
                        if (s) {
                            srv.addr.sin_port = htons(atoi(s+1));
                            *s = '\0';
                        } else
                            srv.addr.sin_port = htons(MBM_DEFAULT_PORT);
                        srv.addr.sin_addr.s_addr = inet_addr(p);
                    }
                    break;

                default:
                    for (s=in; isalnum(*s) || *s == '_'; s++)
                        ;
                    *s = '\0';
                    syslog(LOG_ERR, "unknown option '%s'", in);
                    break;
            }
        }
    }

    fclose(fp);

    return 0;
}

