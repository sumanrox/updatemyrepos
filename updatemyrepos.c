#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>

// ANSI color escape codes
#define COLOR_RED     "\x1B[31m"
#define COLOR_GREEN   "\x1B[32m"
#define COLOR_ORANGE  "\x1B[38;5;208m"
#define COLOR_SKY_BLUE "\x1B[38;5;39m"
#define COLOR_RESET   "\x1B[0m"

typedef struct {
    char path[512];
} RepoLocation;

RepoLocation *repo_locations = NULL;
int total_repos = 0;
int max_repos = 0;


int is_git_repo(const char *dir) {
    char git_path[512];
    snprintf(git_path, sizeof(git_path), "%s/.git", dir);
    DIR *dirp = opendir(git_path);
    if (dirp) {
        closedir(dirp);
        return 1;
    }
    return 0;
}

void add_repo_location(const char *path) {
    if (total_repos >= max_repos) {
        max_repos = (max_repos == 0) ? 1 : max_repos * 2;
        repo_locations = realloc(repo_locations, max_repos * sizeof(RepoLocation));
    }
    strcpy(repo_locations[total_repos].path, path);
    total_repos++;
}

int count_git_repos(const char *root_dir) {
    int count = 0;
    DIR *dirp = opendir(root_dir);
    if (!dirp) {
        fprintf(stderr, "Error opening directory: %s\n", root_dir);
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dirp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char path[512];
        snprintf(path, sizeof(path), "%s/%s", root_dir, entry->d_name);

        if (is_git_repo(path)) {
            count++;
            add_repo_location(path);
        }

        if (entry->d_type == DT_DIR) {
            count += count_git_repos(path);
        }
    }

    closedir(dirp);
    return count;
}

void git_pull_repos(const char *git_path) {
    for (int i = 0; i < total_repos; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process (execute git pull and suppress output)
            chdir(repo_locations[i].path);
            freopen("/dev/null", "w", stdout);
            freopen("/dev/null", "w", stderr);
            execlp(git_path, git_path, "pull", NULL);
            perror("Error executing git pull");
            exit(1);
        } else if (pid < 0) {
            // Error occurred
            fprintf(stderr, "Error forking process for %s\n", repo_locations[i].path);
        } else {
            // Parent process (wait for child to finish)
            int status;
            waitpid(pid, &status, 0);
            printf("\r%s[+] Updating Repository:%s %d/%d", COLOR_GREEN, COLOR_RESET, i + 1, total_repos);
            fflush(stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s <root_directory> [<git_path>]\n", argv[0]);
        return 1;
    }

    const char *root_dir = argv[1];
    const char *git_path = (argc == 3) ? argv[2] : "git";

    printf("%s\n[+] Searching In:%s %s\n", COLOR_ORANGE, COLOR_RESET, root_dir);

    int total_repos_in_dir = count_git_repos(root_dir);

    if (total_repos_in_dir >= 0) {
        if (total_repos_in_dir > 0) {
            printf("[+] Found Repository: %s%d%s\n", COLOR_SKY_BLUE, total_repos_in_dir, COLOR_RESET);
        } else {
            printf("[!] %sN0 Git Repos F0und%s\n", COLOR_RED, COLOR_RESET);
        }
    } else {
        fprintf(stderr, "[!] Error occurred while searching Git repositories.\n");
        return 1;
    }
    git_pull_repos(git_path);
    // Free the dynamically allocated memory for repo_locations
    free(repo_locations);
    printf("\n");
    return 0;
}