#include "shell.h"

/*
 * shell_history_file - obtain the history file path
 * @info: parameter structure
 *
 * Return: allocated string containing the history file path
 */

char *shell_history_file(ino_t *info)
{
        char *buf, *dir;

        dir = _getenv(info, "HOME=");
        if (!dir)
                return (NULL);
        buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
        if (!buf)
                return (NULL);
        buf[0] = 0;
        _strcpy(buf, dir);
        _strcat(buf, "/");
        _strcat(buf, HIST_FILE);
        return (buf);

}

/**
 * pen_history - Creates a file or enter an existing file for storing history.
 * @ino_t: The parameter structure.
 *
 * Return: 1 on success, -1 otherwise.
 */

int pen_history(ino_t *info)
{
        size_t fd;
        char *filename = shell_history_file(info);
        list_t *node = NULL;

        if (!filename)
                return (-1);

        fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(filename);
        if (fd == -1)

                return (-1);

        for (node = info->history; node; node = node->next)

        {
                _putsfd(node->str, fd);
                _putfd('\n', fd)
        }

        _putfd(BUF_FLUSH, fd);
        close(fd);

        return (1);

}

/**
 * read_history - Reads history entries from a file.
 * @info: The parameter structure.
 *
 * Return: Number of history entries on success, 0 otherwise.
 */

int read_history(ino_t *info)

{
        int i, last = 0, linecount = 0;
        size_t fd, rdlen, fsize = 0;
        struct stat st;
        char *buf = NULL, *filename = shell_history_file(info);

        if (!filename)

                return (0);

        fd = open(filename, O_RDONLY);
        free(filename);

        if (fd == -1)
                return (0);

        if (!fstat(fd, &st))
                fsize = st.st_size;

        if (fsize < 2)
                return (0);

        buf = malloc(sizeof(char) * (fsize + 1));

        if (!buf)
                return (0);

        rdlen = read(fd, buf, fsize);

        buf[fsize] = 0;

        if (rdlen <= 0)
                return (free(buf), 0);

	close(fd);

        for (i = 0; i < fsize; i++)

                if (buf[i] == '\n')

                {
                        buf[i] = 0;
                        dev_history_list(info, buf + last, linecount++);

                        last = i + 1;
                }

        if (last != i)
                dev_history_list(info, buf + last, linecount++);

        free(buf);

        info->histcount = linecount;

        while (info->histcount-- >= HIST_MAX)

                delete_node_at_index(&(info->history), 0);

        rearrange_history(info);

        return (info->histcount);

}

/**
 * dev_history_list - Adds an entry to a history linked list.
 * @info: Parameter structure.
 * @buf: Buffer containing the history entry.
 * @linecount: The history line count.
 *
 * Return: Always 0.
 */
int dev_history_list(ino_t *info, char *buf, int linecount)
{
        list_t *node = NULL;

        if (info->history)
                node = info->history;

        add_node_end(&node, buf, linecount);


        if (!info->history)
                info->history = node;

        return (0);
}

/**
 * rearrange_history - Renumbers the history linked list after changes.
 * @info: Parameter structure.
 *
 * Return: The new history count.
 */
int rearrange_history(ino_t *info)
{
        list_t *node = info->history;
        int i = 0;

        while (node)
	{
                node->num = i++;
                node = node->next;
        }

        return (info->histcount = i);
}
