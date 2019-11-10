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
$ ./synouidmod USERNAME
User entry USERNAME is found: username=yoichi, uid=1500, gid=1500
$ sudo ./synouidmod YOICHI 3000 4000
User entry YOICHI is found: username=yoichi, uid=1500, gid=1500
Modify to: uid=3000, gid=4000
```

## Update the user on GUI
Update a field (like description) on Synology DiskStation.

# Build
Strongly recommended to build this program on a virtual environment like LXD.

## Download toolkit
Download ds.(arch)-(ver).dev.txz and toolchain from sourceforge.
https://originhelp.synology.com/developer-guide/compile_applications/download_dsm_tool_chain.html

## Set virtual environment up
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

## Change platform on env.sh
```
PLATFORM=arm-unknown-linux-gnueabi
```

## Execute build.sh
```
./build.sh
```
