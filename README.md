# What's this?
Update uid/gid of an user on a Synology NAS. 

CAUTION: Use carefully. Changing an special user may break your system.

# Use
## Backup db files
```
$ cp -pr /var/run/synosdk /var/run/synosdk.old
```

## Execute the program
```
$ ./synouidmod USERNAME1
Database opened successfully
User 'USERNAME1' has been found: username=username1, uid=1500, gid=1500
No modifications applied to database
$ sudo ./synouidmod USERNAME1 3000 4000
Database opened successfully
User 'USERNAME1' has been found: username=username1, uid=1500, gid=1500
Modifying 'username1' to uid=3000, gid=4000
Update successfull
```

## Update the user on GUI
Update a field (like description) on Synology DiskStation.

# Build
It's strongly recommended to build this program on a virtual environment like LXD.

## Download toolkit
Download ds.(arch)-(ver).dev.txz and toolchain from sourceforge.
https://originhelp.synology.com/developer-guide/compile_applications/download_dsm_tool_chain.html

## Set a virtual environment up
```
lxc launch ubuntu:18.04 synodev
lxc exec synodev
sudo -i -u ubuntu ssh-import-id gh:(userid)
```

## Extract archives
```
sudo tar xpf ds.armada38x-6.2.dev.txz -C /
sudo tar xpf armada38x-gcc493_glibc220_hard-GPL.txz -C /usr/local
```

CAUTION: ds.* archives extracts files to root. This may break the build environment.

## Change the platform in env.sh
```
PLATFORM=arm-unknown-linux-gnueabi
```

## Execute the build.sh
```
./build.sh
```
