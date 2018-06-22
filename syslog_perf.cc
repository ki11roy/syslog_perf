#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

const int  iter  = 200000;
const char msg[] = "123456789 123456789 123456789 123456789 123456789";

struct timeval t0;
struct timeval t1;

void start ()
{
    gettimeofday (&t0, nullptr);
}

void stop ()
{
    gettimeofday (&t1, nullptr);
}

void report (char *action)
{
    double dt = (double)t1.tv_sec - (double)t0.tv_sec +
        1e-6 * ((double)t1.tv_usec - (double)t0.tv_usec);
    double mb = 1e-6 * sizeof (msg) * iter;

    if (action == NULL)
        printf ("Test Case             Calls       Payload     Duration    Thoughput \n"
                "                      []          [MB]        [s]         [MB/s]    \n"
                "--------------------  ----------  ----------  ----------  ----------\n");
    else {
        if (strlen (action) > 20) action[20] = 0;
        printf ("%-20s  %-10d  %-10.2f  %-10.2f  %-10.2f\n",
                action, iter, mb, dt, mb / dt);
    }
}

void test_syslog ()
{
    int i;

    openlog ("test_syslog", LOG_PID | LOG_NDELAY, LOG_LOCAL0);
    start ();
    for (i = 0; i < iter; i++)
        syslog (LOG_DEBUG, msg);
    stop ();
    closelog ();
    report ("syslog");
}

void test_syslog_format ()
{
    int i;

    openlog ("test_syslog", LOG_PID | LOG_NDELAY, LOG_LOCAL0);
    start ();
    for (i = 0; i < iter; i++)
        syslog (LOG_DEBUG, "%s", msg);
    stop ();
    closelog ();
    report ("syslog %s");
}

void test_write_devnull ()
{
    int i, fd;

    fd = open ("/dev/null", O_WRONLY);
    start ();
    for (i = 0; i < iter; i++)
        write (fd, msg, sizeof(msg));
    stop ();
    close (fd);
    report ("write /dev/null");
}

void test_printf ()
{
    int i;
    FILE *fp;

    fp = fopen ("/tmp/test_printf", "w");
    start ();
    for (i = 0; i < iter; i++)
        fprintf (fp, "%s", msg);
    stop ();
    fclose (fp);
    report ("printf %s");
}

int main (int argc, char **argv)
{
    report (NULL);
    test_syslog ();
    test_syslog_format ();
    test_write_devnull ();
    test_printf ();
}
