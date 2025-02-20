#!/usr/bin/env bash
#
# Create the markdown text for a GitHub release.
# Steps:
# - Create and push the tag for the release.
# - Create the release on GitHub and upload binaries.
# - Run this script to generate the markdown text.
# - Edit the release on GitHub with this text.
#

SCRIPT=$(basename $0 .sh)
SCRIPTDIR=$(cd $(dirname $0); pwd)
info() { echo >&2 "$SCRIPT: $*"; }
error() { echo >&2 "$SCRIPT: $*"; exit 1; }

# Directories.
ROOTDIR=$(cd $SCRIPTDIR/..; pwd)

# Get most recent git tag.
TAG=$(cd $ROOTDIR; git tag --sort=-creatordate | head -1)
[[ -n "$TAG" ]] || error "no git tag found"

# Get content of web page for release.
HOST=https://github.com
URL=$HOST/tsduck/tsduck/releases/tag/$TAG
HTMLFILE=/tmp/tsduck-$TAG.html
LINKFILE=/tmp/tsduck-$TAG.links
wget -q -O "$HTMLFILE" "$URL" || error "error getting $URL"

# Extract all href in HTML file. We assume that there is at most 1 href by line.
sed -e '/href="/!d' -e 's|^.*href="||' -e 's|".*$||' -e "s|^/|$HOST/|" $HTMLFILE | \
    grep -e '\.exe' -e '\.deb' -e '\.rpm' -e '\.zip' >$LINKFILE

# Get links for all expected targets.
getlink() {
    pattern="$1"
    link=$(grep "$pattern" $LINKFILE | tail -1)
    [[ -n "$link" ]] || error "no link found for $pattern"
    file=$(sed <<<$link -e 's|^.*/||')
    echo "[$file]($link)"
}
WIN32=$(getlink '/TSDuck-Win32-.*\.exe$')
WIN64=$(getlink '/TSDuck-Win64-.*\.exe$')
WIN32Z=$(getlink '/TSDuck-Win32-.*-Portable\.zip$')
WIN64Z=$(getlink '/TSDuck-Win64-.*-Portable\.zip$')
EL64=$(getlink '/tsduck-[0-9].*\.el[0-9]*\.x86_64\.rpm$')
FC64=$(getlink '/tsduck-[0-9].*\.fc[0-9]*\.x86_64\.rpm$')
UB64=$(getlink '/tsduck_[0-9].*\.ubuntu.*_amd64\.deb$')
DB64=$(getlink '/tsduck_[0-9].*\.debian.*_amd64\.deb$')
ARM=$(getlink '/tsduck_[0-9].*_armhf\.deb$')
EL64DEV=$(getlink '/tsduck-devel-[0-9].*\.el[0-9]*\.x86_64\.rpm$')
FC64DEV=$(getlink '/tsduck-devel-[0-9].*\.fc[0-9]*\.x86_64\.rpm$')
UB64DEV=$(getlink '/tsduck-dev_[0-9].*\.ubuntu.*_amd64\.deb$')
DB64DEV=$(getlink '/tsduck-dev_[0-9].*\.debian.*_amd64\.deb$')
ARMDEV=$(getlink '/tsduck-dev_[0-9].*_armhf\.deb$')

# Now create the markdown file.
cat <<EOF
Binaries for command-line tools and plugins:
* Windows 32 bits: $WIN32
* Windows 64 bits: $WIN64
* Windows 32 bits (portable): $WIN32Z
* Windows 64 bits (portable): $WIN64Z
* RedHat, AlmaLinux 64 bits: $EL64
* Fedora 64 bits: $FC64
* Debian 64 bits: $DB64
* Ubuntu 64 bits: $UB64
* Raspbian 32 bits (Raspberry Pi): $ARM
* macOS: [use Homebrew](https://tsduck.io/doxy/installing.html#macinstall)

Binaries for development environment:
* Windows: Included in installer (select option "Development")
* RedHat, AlmaLinux 64 bits: $EL64DEV
* Fedora 64 bits: $FC64DEV
* Debian 64 bits: $DB64DEV
* Ubuntu 64 bits: $UB64DEV
* Raspbian 32 bits (Raspberry Pi): $ARMDEV
* macOS: Included in Homebrew package
EOF

rm -f $HTMLFILE $LINKFILE
