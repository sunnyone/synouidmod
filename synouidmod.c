#include <fcntl.h>
#include <stdio.h>
#include <synosdk/user.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: synouidmod USERNAME [uid] [gid]\n");
        return 1;
    }

    int modify = argc >= 3 ? 1 : 0;
    char *username = argv[1];
    uid_t uid;
    gid_t gid;
    if (modify) {
        uid = atoi(argv[2]);
        gid = atoi(argv[3]);
    }

    int userdb = 0;
    PSYNOUSER user = NULL;
    PSYNOSHADOW shadow = NULL;
    int exitCode = 1;

    userdb = SYNOUserDbOpen(modify ? O_RDWR : O_RDONLY);
    if (!userdb) {
        fprintf(stderr, "Failed to open database (permission?).\n");
        goto finish;
    }

    SYNOUserDbGet(userdb, username, &user);
    if (!user) {
        fprintf(stderr, "User '%s' is not found.\n", username);
        goto finish;
    }
    printf("User entry %s is found: username=%s, uid=%d, gid=%d\n", username, user->szName, user->pw_uid, user->pw_gid);
    if (!modify) {
        exitCode = 0;
        goto finish;
    }

    printf("Modify to: uid=%d, gid=%d\n", uid, gid);
    SLIBUserShadowAlloc(&shadow, SYNO_SHADOW_UPDATE_USER);
    user->pw_uid = uid;
    user->pw_gid = gid;
    SYNOUserDbUpdate(userdb, username, user, shadow);

    exitCode = 0;
    finish:
    if (!shadow) {
        SLIBUserShadowFree(shadow);
    }
    if (!user) {
        SYNOUserFree(user);
    }
    if (userdb) {
        SYNOUserDbClose(userdb);
    }

    return exitCode;
}
