#include "shell.h"

/**
 * _display_env - Prints the current environment variables.
 * @info: Structure containing potential arguments.
 * 
 * Return: Always 0.
 */
int _display_env(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * _retrieve_env - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 * 
 * Return: The value of the environment variable or NULL if not found.
 */
char *_retrieve_env(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *value;

    while (node)
    {
        value = starts_with(node->str, name);
        if (value && *value)
            return (value);
        node = node->next;
    }

    return (NULL);
}

/**
 * _my_env - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments.
 * 
 * Return: 0 on success, 1 on failure.
 */
int _my_env(info_t *info)
{
    if (info->argc != 3)
    {
        _error_puts("Incorrect number of arguments\n");
        return (1);
    }

    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);

    return (1);
}

/**
 * _remove_env - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * 
 * Return: 0 on success, 1 on failure.
 */
int _remove_env(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _error_puts("Too few arguments.\n");
        return (1);
    }

    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * _populate_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * 
 * Return: Always 0.
 */
int _populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);

    info->env = node;
    return (0);
}
