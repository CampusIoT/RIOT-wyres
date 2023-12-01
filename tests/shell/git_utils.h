/*
 * Copyright (C) 2020-2022 Université Grenoble Alpes
 */

#ifndef GIT_UTILS_H
#define GIT_UTILS_H

/*
 * @brief print info
 */
void print_git(void);

/*
 * @brief git command
 *
 * @param argc
 * @param argv
 */
int git_cmd(int argc, char *argv[]);

#endif
