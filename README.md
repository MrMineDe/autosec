# autosec
Automatic secretary similar to reclaim.ai for CalDAV

## Build
```sh
git clone https://github.com/mrminede/autosec
cd autosec
make install
./autosec
```

Don't forget to export the `$LD_LIBRARY_PATH` environment variable to include ical's shared objects, if you want to compile dynamically:

```
# POSIX
export LD_LIBRARY_PATH=/path/to/autosec/lib/libical/lib:$LD_LIBRARY_PATH

# Fish
set -x LD_LIBRARY_PATH /path/to/autosec/lib/libical/lib $LD_LIBRARY_PATH
```
