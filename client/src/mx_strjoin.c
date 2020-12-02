#include "../inc/uchat_client.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL)
        return NULL;
    else if (s1 == NULL)
        return strdup(s2);
    else if (s2 == NULL)
        return strdup(s1);
    else {
        int ns1 = strlen(s1), ns2 = strlen(s2);
        char *new = mx_strnew(ns1 + ns2);

        new = strcpy(new, s1);
        new = strcat(new, s2);
        return new;
    }
}
