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

    // convert username to uppercase
    int i = 0;
    for (i = 0; username[i]; i++ ) {
        username[i] = toupper( (unsigned char)username[i]);
    }

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
    } else {
        printf("Database successfully opened\n");
    }

    if (SYNOUserDbGet(userdb, username, &user) == -1 || !user) {
        fprintf(stderr, "User '%s' not found.\n", username);
        goto finish;
    }

    printf("User '%s' has beend found: username=%s, uid=%d, gid=%d\n", username, user->szName, user->pw_uid, user->pw_gid);
    if (!modify) {
        fprintf(stderr, "No modifications applied to database.\n", username);
        exitCode = 0;
        goto finish;
    }

    printf("Modifying '%s' to uid=%d, gid=%d\n", user->szName, uid, gid);

    SLIBUserShadowAlloc(&shadow, SYNO_SHADOW_UPDATE_USER);
    if (!shadow) {
        fprintf(stderr, "SLIBUserShadowAlloc failed\n");
        goto finish;
    }

    user->pw_uid = uid;
    user->pw_gid = gid;

    if (SYNOUserDbUpdate(userdb, username, user, shadow) == -1) {
        fprintf(stderr, "Update failed\n");
        goto finish;
    }

    printf("Update successfull\n");
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