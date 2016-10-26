
/* files-processes/fork-and-exec.c */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Forks off a child process that will execute the specified program.
 * Parent will wait for child to terminate before exiting.
 *
 * man 3 execlp
 */
int main(int argc, char *argv[])
{
    pid_t pid;
    char *exe;

    /* check command line args in parent */
    if(argc == 1) {
        fprintf(stderr, "Usage: %s <exe>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* grab the command we are going to exec */
    exe = argv[1];

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(errno);
    } else if (pid == 0) {  /* child */
        execlp(exe, exe, (char *) NULL);
        /* if we get this far, something is not right */
        perror("exec failed");
        exit(errno);
    }

    /* parent continues concurrently with child */
    printf("Created child with pid %d\n",pid);

    /* wait for normal termination of child process */
    printf("Parent waiting for child to finish...\n");
    if (waitpid(pid, NULL, 0) != pid) {
        perror("waitpid");
        exit(errno);
    }
    printf("Parent exiting\n");
    exit(EXIT_SUCCESS);
}
